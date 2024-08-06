#pragma once

#include<memory>
#include<sstream>
#include<map>
#include<set>
#include <functional>
#include "log.h"
#include "yaml-cpp/yaml.h"
#include<boost/lexical_cast.hpp>
#include <iostream>
#include "thread.h"

namespace sylar {
class ConfigVarBase {
public:
	typedef std::shared_ptr<ConfigVarBase> ptr;
	ConfigVarBase(const std::string& name, const std::string& description = "") :
		m_name(name), m_description(description)
	{
		std::transform(name.begin(), name.end(), m_name.begin(), ::tolower);
	}
	virtual ~ConfigVarBase() {}
	const std::string& getName() const { return m_name; }
	const std::string& getDescription() const { return m_description; }
	virtual std::string toString() = 0;
	virtual bool fromString(const std::string& val) = 0;
	virtual std::string getTypeName() const = 0;
protected:
	std::string m_name;
	std::string m_description;
};

template<class F,  class T>
class LexicalCast{
public:
	T operator()(const F& f) {
		return boost::lexical_cast<T>(f);
	}
};

template<class T>
class LexicalCast<std::string, std::vector<T>>{
public:
	std::vector<T> operator()(const std::string& v){
		YAML::Node node = YAML::Load(v);
		typename std::vector<T> vec;
		std::stringstream ss;
		for (size_t i = 0; i < node.size(); ++i ){
			ss.str("");
			ss << node[i];
			vec.push_back(LexicalCast<std::string, T>()(ss.str()));
		}
		return vec;
	}
};

template<class T>
class LexicalCast<std::vector<T>, std::string>{
public:
	std::string operator()(const std::vector<T> v){
		YAML::Node node;
		for (auto& i : v){
			node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
		}
		std::stringstream ss;
		ss << node;
		return ss.str();
	}
};

template<class T>
class LexicalCast<std::string, std::list<T>>{
public:
	std::list<T> operator()(const std::string& v){
		YAML::Node node = YAML::Load(v);
		typename std::list<T> lst;
		std::stringstream ss;
		for (size_t i = 0; i < node.size(); ++i ){
			ss.str("");
			ss << node[i];
			lst.push_back(LexicalCast<std::string, T>()(ss.str()));
		}
		return lst;
	}
};

template<class T>
class LexicalCast<std::list<T>, std::string>{
public:
	std::string operator()(const std::list<T> v){
		YAML::Node node;
		for (auto& i : v){
			node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
		}
		std::stringstream ss;
		ss << node;
		return ss.str();
	}
};

template<class T>
class LexicalCast<std::string, std::set<T>>{
public:
	std::set<T> operator()(const std::string& v){
		YAML::Node node = YAML::Load(v);
		typename std::set<T> lst;
		std::stringstream ss;
		for (size_t i = 0; i < node.size(); ++i ){
			ss.str("");
			ss << node[i];
			lst.insert(LexicalCast<std::string, T>()(ss.str()));
		}
		return lst;
	}
};


template<class T>
class LexicalCast<std::set<T>, std::string>{
public:
	std::string operator()(const std::set<T> v){
		YAML::Node node;
		for (auto& i : v){
			node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
		}
		std::stringstream ss;
		ss << node;
		return ss.str();
	}
};

template<class T>
class LexicalCast<std::string, std::map<std::string, T>>{
public:
	std::map<std::string, T> operator()(const std::string& v){
		YAML::Node node = YAML::Load(v);
		typename std::map<std::string, T> mapdata;
		std::stringstream ss;
		for (auto it = node.begin(); it != node.end(); ++it){
			ss.str("");
			ss << it -> second;
			mapdata.insert(std::make_pair(it->first.Scalar(), LexicalCast<std::string, T>()(ss.str())));
		}
		return mapdata;
	}
};

template<class T>
class LexicalCast<std::map<std::string, T>, std::string>{
public:
	std::string operator()(std::map<std::string, T> mapdata){
		YAML::Node node;
		for (auto& i : mapdata){
			node[i.first] = YAML::Load(LexicalCast<T, std::string>()(i.second));
		}
		std::stringstream ss;
		ss << node;
		return ss.str();
	}
};

template<class T, class FromStr = LexicalCast<std::string, T>, class ToStr = LexicalCast<T, std::string> >
class ConfigVar : public ConfigVarBase {
public:
	typedef std::shared_ptr<ConfigVar> ptr;
	typedef std::function<void (const T& old_value, const T& new_value) > on_change_cb;
	typedef RWMutex RWMutexType;

	ConfigVar(const std::string& name, const T& default_value, const std::string& description = "")
		:ConfigVarBase(name, description)
		,m_val(default_value){}
	
	std::string toString() override
	{
		try
		{
			// return boost::lexical_cast<std::string>(m_val);
			RWMutexType::ReadLock lock(m_mutex);
			return ToStr()(m_val);
		}
		catch (const std::exception& e)
		{
			SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ConfigVar::toString exception"
				<<e.what() << "convert: "<<typeid(m_val).name() << "to String";
		}
		return "";
	}

	bool fromString(const std::string& val) override
	{
		try
		{
			setValue(FromStr()(val));
		}
		catch (const std::exception& e)
		{
			SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ConfigVar::toString exception"
				<< e.what() << "convert: String to " << typeid(m_val).name();
		}
		return false;
	}
	const T getValue() {
		RWMutexType::ReadLock lock(m_mutex);
		 return m_val; 
	}
	void setValue(const T& val) { 
		{
			RWMutexType::ReadLock lock(m_mutex);
			if (val == m_val){
				return;
			}
			for (auto& i : m_cbs){
				i.second(m_val, val);
			}
		}
		RWMutexType::WriteLock lock(m_mutex);
		m_val = val; 
	}
	std::string getTypeName() const override { return typeid(T).name(); }
	uint64_t addListener(on_change_cb cb){
		static uint64_t s_fun_id = 0;
		RWMutexType::WriteLock lock(m_mutex);
		++s_fun_id;
		m_cbs[s_fun_id] = cb;
		return s_fun_id;
	}
	void delListener(uint64_t key){
		RWMutexType::WriteLock lock(m_mutex);
		m_cbs.erase(key);
	}
	on_change_cb getListener(uint64_t key){
		RWMutexType::ReadLock lock(m_mutex);
		auto it = m_cbs.find(key);
		return it == m_cbs.end()? nullptr: it->second;
	}

	void clearListener() {
		RWMutexType::WriteLock lock(m_mutex);
		m_cbs.clear();
	}

private:
	T m_val;
	RWMutexType m_mutex;
	// 变更回调函数组
	std::map<uint64_t, on_change_cb> m_cbs;  //functional没有比较函数 和 == 函数，
};

class Config {
public:
	typedef std::map<std::string, ConfigVarBase::ptr> ConfigVarMap;
	typedef RWMutex RWMutexType;

	template<class T>
	static typename ConfigVar<T>::ptr Lookup(const std::string& name,
			const T& default_value, const std::string & description = "")
	{
		RWMutexType::WriteLock lock(GetMutex());
		auto it = getDatas().find(name);
		if (it != getDatas().end()){
			auto tmp = std::dynamic_pointer_cast<ConfigVar<T> >(it->second);
			if (tmp){
				SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "Look up name =" << name << "exist";
			}else{
				SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "Look up name =" << name << "exist but type not" <<
				 typeid(T).name() << " real_type=" << it->second->getTypeName() << " " << it->second->toString();
				 return nullptr;
			}
		}
		if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyz._0123456789") != std::string::npos) {
			SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "Look up name invalid" << name;
			throw std::invalid_argument(name);
		}
		typename ConfigVar<T>::ptr v(new ConfigVar<T>(name, default_value, description));
		getDatas()[name] = v;
		return v;
	}

	static void LoadFromYaml(const YAML::Node& root);
	static ConfigVarBase::ptr LookupBase(const std::string& name);
	static void Visit(std::function<void(ConfigVarBase::ptr)> cb);
private:
	static ConfigVarMap& getDatas() {
		static ConfigVarMap m_datas;
		return m_datas;
	}
	static RWMutexType& GetMutex() {
		static RWMutexType s_mutex;
		return s_mutex;
	}
};
}
