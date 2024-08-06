#include "../slinnr/config.h"
#include "../slinnr/log.h"
#include <map>
#include <list>
#include <iostream>
#include <yaml-cpp/yaml.h>


// sylar::ConfigVar<int>::ptr g_int_value_config = sylar::Config::Lookup("system.port", (int)8080, "system port");
// sylar::ConfigVar<float>::ptr g_int_value_config_2 = sylar::Config::Lookup("system.port", (float)8080, "system port");
// sylar::ConfigVar<std::vector<int>>::ptr g_vec_value_config = sylar::Config::Lookup("system.vec", std::vector<int>{1, 2}, "vec_int");
// sylar::ConfigVar<std::list<int>>::ptr g_list_value_config = sylar::Config::Lookup("system.list", std::list<int>{10, 20}, "list_int");
// sylar::ConfigVar<std::set<int>>::ptr g_set_value_config = sylar::Config::Lookup("system.set", std::set<int>{10, 20, 20, 10}, "set_int");
// sylar::ConfigVar<std::map<std::string, int>>::ptr g_map_value_config = sylar::Config::Lookup("system.map", std::map<std::string, int>{{"a", 1},{"b", 2}}, "set_map");

void test_yaml() {
	YAML::Node root = YAML::LoadFile("/home/slinnr/cppworkspace/slinnrserver/bin/conf/test.yaml");
	SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << root;
}


class Person{
public:
	Person() {};
	std::string m_name = "";
	int m_age = 0;
	bool m_sex = 0;
	
	std::string toString() const{
		std::stringstream ss;
		ss << "[person name =" << m_name
			<< "age=" << m_age
			<< "sex= " << m_sex
			<< "]";
		return ss.str();
	}

	bool operator==(const Person& oth) const{
		return m_name == oth.m_name
		&& m_age == oth.m_age
		&& m_sex == oth.m_sex;
	}
};

namespace sylar{
template<>
class LexicalCast<std::string, Person> {
public:
    Person operator()(const std::string& v) {
        YAML::Node node = YAML::Load(v);
        Person p;
        p.m_name = node["name"].as<std::string>();
        p.m_age = node["age"].as<int>();
        p.m_sex = node["sex"].as<bool>();
        return p;
    }
};

template<>
class LexicalCast<Person, std::string> {
public:
    std::string operator()(const Person& p) {
        YAML::Node node;
        node["name"] = p.m_name;
        node["age"] = p.m_age;
        node["sex"] = p.m_sex;
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

}

// sylar::ConfigVar<Person>::ptr g_person_value_config = sylar::Config::Lookup("class.person", Person(), "person_obj");

// void test_class(){
// 	SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "before" << g_person_value_config -> getValue().toString() << "-" << g_person_value_config->toString();
// 	YAML::Node root = YAML::LoadFile("/home/slinnr/cppworkspace/slinnrserver/bin/conf/test.yaml");
// 	sylar::Config::LoadFromYaml(root);
// 	SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "after" << g_person_value_config -> getValue().toString() << "-" << g_person_value_config->toString();
// }

// void test_config(){
// 	SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "before" << g_int_value_config -> getValue();
// 	#define XX(g_var, name, prefix) \
// 	for (auto& i : g_var->getValue()){\
// 		SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << #prefix " " #name": " << i;\
// 	}

// 	#define XX_MAP(g_var, name, prefix) \
// 	for (auto& i : g_var->getValue()){\
// 		SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << #prefix " " #name": {" << i.first\
// 		<< "-" << i.second << "}"; \
// 	}
// 	XX(g_vec_value_config, int_vec, before);
// 	XX(g_list_value_config, int_list, before);
// 	XX(g_set_value_config, int_set, before);
// 	XX_MAP(g_map_value_config, int_map, before);
// 	SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "before" << g_int_value_config -> getValue();
// 	YAML::Node root = YAML::LoadFile("/home/slinnr/cppworkspace/slinnrserver/bin/conf/test.yaml");
// 	sylar::Config::LoadFromYaml(root);
// 	SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "after" << g_int_value_config -> getValue();
// 	XX(g_vec_value_config, int_vec, after);
// 	XX(g_list_value_config, int_list, after);
// 	XX(g_set_value_config, int_set, after);
// 	XX_MAP(g_map_value_config, int_map, after);
// }

void test_log(){
	static sylar::Logger::ptr system_log = SYLAR_LOG_NAME("system");
	SYLAR_LOG_INFO(system_log) << "hello slinnr1" << std::endl;
	std::cout << sylar::LoggerMgr::GetInstance() -> toYamlString() << std::endl;
	YAML::Node root = YAML::LoadFile("/home/slinnr/cppworkspace/slinnrserver/bin/conf/log.yaml");
	sylar::Config::LoadFromYaml(root);
	std::cout << "====================" << std::endl;
	std::cout << sylar::LoggerMgr::GetInstance()->toYamlString() << std::endl;
	std::cout << root << std::endl;
	SYLAR_LOG_INFO(system_log) << "hello slinnr2" << std::endl;
	system_log -> setFormatter("%d - %m%n");
	SYLAR_LOG_INFO(system_log) << "hello slinnr3" << std::endl;
}

int main(int argc, char** argv) {
	// SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_int_value_config->getValue();
	// SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_int_value_config->toString();
	// test_yaml();
	// test_config();
	// test_class();
	test_log();
	SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "log test";
	return 0;
}
