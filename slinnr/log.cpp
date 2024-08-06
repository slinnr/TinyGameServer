#include"log.h"
#include <iostream>
#include <map>
#include <functional>
#include "config.h"

namespace sylar {

Logger::Logger(const std::string& name): m_name(name), m_level(LogLevel::DEBUG){
    m_formatter.reset(new LogFormatter("%d{%Y-%m-%d %H:%M:%S}%T%t%T%N%T%F%T[%p]%T[%c]%T%f:%l%T%m%n"));
}

void Logger::log(LogLevel::Level level, LogEvent::ptr event) {
	if (level >= m_level) {
        auto self = shared_from_this();
        MutexType::Lock lock(m_mutex);
        if (!m_appenders.empty()){
            for (auto& i : m_appenders) {
			    i->log(level, event, self);
		    }
        }else if(m_root){
            m_root->log(level, event);
        }

	}
}

void Logger::debug(LogEvent::ptr event){
	log(LogLevel::DEBUG, event);
}

void Logger::info(LogEvent::ptr event) {
	log(LogLevel::INFO, event);
}

void Logger::warn(LogEvent::ptr event) {
	log(LogLevel::WARN, event);
}

void Logger::error(LogEvent::ptr event) {
	log(LogLevel::ERR, event);
}

void Logger::fatal(LogEvent::ptr event) {
	log(LogLevel::FATAL, event);
}

void Logger::addAppender(LogAppender::ptr appender)
{
    MutexType::Lock lock(m_mutex);
    if (!appender->getFormatter()) {
        MutexType::Lock ll(appender->m_mutex);
        appender->m_formatter = m_formatter;
    }
	m_appenders.push_back(appender);
}

void Logger::delAppender(LogAppender::ptr appender)
{
    MutexType::Lock lock(m_mutex);
	for (auto it = m_appenders.begin(); it != m_appenders.end(); ++it) {
		if (*it == appender) {
			m_appenders.erase(it);
			break;
		}
	}
}

void Logger::clearAppender()
{
    MutexType::Lock lock(m_mutex);
	m_appenders.clear();
}

void Logger::setFormatter(LogFormatter::ptr val){
    MutexType::Lock lock(m_mutex);
    m_formatter = val;
    for (auto& i : m_appenders){
        MutexType::Lock ll(i->m_mutex);
        if (!i->m_hasFormatter) {
            i -> m_formatter = m_formatter;
        }
    }
}

void Logger::setFormatter(const std::string& val){
    sylar::LogFormatter::ptr new_val(new sylar::LogFormatter(val));
    if (new_val -> isError()){
        std::cout << "Logger setFormatter name = " << m_name << "value= "
            << val << "invalid formatter" << std::endl;
        return;
    }
    // m_formatter = new_val;
    setFormatter(new_val);
}
LogFormatter::ptr Logger::getFormatter() {
    MutexType::Lock lock(m_mutex);
    return m_formatter;
}

std::string Logger::toYamlString() {
    MutexType::Lock lock(m_mutex);
    YAML::Node node;
    node["name"] = m_name;
    if (m_level != LogLevel::Level::UNKNOWN){
        node["level"] = LogLevel::ToString(m_level);
    }
    if (m_formatter){
        node["formatter"] = m_formatter->getPattern();
    }
    for (auto& i : m_appenders) {
        node["appenders"].push_back(YAML::Load(i->toYamlString()));
    }
    std::stringstream ss;
    ss << node;
    return ss.str();
}

LogEvent::LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level, const char* file, int32_t line, uint32_t elapse, 
            uint32_t threadId, uint32_t fiberId, uint32_t time, const std::string& threadName) :
    m_file(file),
    m_line(line),
    m_elapse(elapse),
    m_threadId(threadId),
    m_fiberId(fiberId),
    m_time(time),
    m_logger(logger),
    m_level(level),
    m_threadName(threadName)
{
}


class StringFormatItem :public LogFormatter::FormatItem {
public:
    StringFormatItem(const std::string& str = "")
        :m_string(str){}
    void format(std::ostream& os, LogEvent::ptr event, LogLevel::Level level, Logger::ptr logger) {
        os << m_string;
    }
private:
    std::string m_string;
};


class TabFormatItem :public LogFormatter::FormatItem {
public:
    TabFormatItem(const std::string& str = ""){}
    void format(std::ostream& os, LogEvent::ptr event, LogLevel::Level level, Logger::ptr logger) {
        os << "\t";
    }
private:
    std::string m_string;
};

class MessageFormatItem :public LogFormatter::FormatItem {
public:
    MessageFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, LogEvent::ptr event, LogLevel::Level level, Logger::ptr logger) {
        os << event->getMessage();
    }
};

class LevelFormatItem :public LogFormatter::FormatItem {
public:
    LevelFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, LogEvent::ptr event, LogLevel::Level level, Logger::ptr logger) {
        os << LogLevel::ToString(level);
    }
};

class ElapseFormatItem : public LogFormatter::FormatItem {
public:
    ElapseFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, LogEvent::ptr event, LogLevel::Level level, Logger::ptr logger) {
        os << event->getElapse();
    }
};

class NameFormatItem : public LogFormatter::FormatItem {
public:
    NameFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, LogEvent::ptr event, LogLevel::Level level, Logger::ptr logger) {
        os << event->getLogger()->getName();
    }
};

class ThreadIdFormatItem : public LogFormatter::FormatItem {
public:
    ThreadIdFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, LogEvent::ptr event, LogLevel::Level level, Logger::ptr logger) {
        os << event->getThreadId();
    }
};


class FilenameFormatItem : public LogFormatter::FormatItem {
public:
    FilenameFormatItem(const std::string& str = ""){}
    void format(std::ostream& os, LogEvent::ptr event, LogLevel::Level level, Logger::ptr logger) {
        os << event->getFile();
    }
};

class LineFormatItem : public LogFormatter::FormatItem {
public:
    LineFormatItem(const std::string& str = ""){}
    void format(std::ostream& os, LogEvent::ptr event, LogLevel::Level level, Logger::ptr logger) {
        os << event->getLine();
    }
};

class FiberIdFormatItem : public LogFormatter::FormatItem {
public:
    FiberIdFormatItem(const std::string& str = ""){}
    void format(std::ostream& os, LogEvent::ptr event, LogLevel::Level level, Logger::ptr logger) {
        os << event->getFiberId();
    }
};

class ThreadNameFormatItem : public LogFormatter::FormatItem {
public:
    ThreadNameFormatItem(const std::string& str = ""){}
    void format(std::ostream& os, LogEvent::ptr event, LogLevel::Level level, Logger::ptr logger) {
        os << event->getThreadName();
    }
};

class NewLineFormatItem : public LogFormatter::FormatItem {
public:
    NewLineFormatItem(const std::string& str = ""){}
    void format(std::ostream& os, LogEvent::ptr event, LogLevel::Level level, Logger::ptr logger) {
        os << std::endl;
    }
};

class DateTimeFormatItem : public LogFormatter::FormatItem {
public:
    DateTimeFormatItem(const std::string& str = "%Y-%m-%d %H:%M:%S"):
    m_format(str)
    {
        if (m_format.empty()) {
            m_format = "%Y-%m-%d %H:%M:%S";
        }
    }
    void format(std::ostream& os, LogEvent::ptr event, LogLevel::Level level, Logger::ptr logger) {
        time_t datatime = event->getTime();
        struct tm tm;
        localtime_r(&datatime, &tm); //linux��Ҫ��localtime_r
        char buf[64];
        strftime(buf, sizeof(buf), m_format.c_str(), &tm);
        os << buf;
    }
private:
    std::string m_format;
};

LogFormatter::ptr LogAppender::getFormatter(){
    MutexType::Lock lock(m_mutex);
	return m_formatter; 
}

FileLogAppender::FileLogAppender(const std::string & filename): m_filename(filename)
{
    reopen();
}

void FileLogAppender::log(LogLevel::Level level, LogEvent::ptr event, std::shared_ptr<Logger> logger) {
	if (level >= m_level) {
        MutexType::Lock lock(m_mutex);
		m_filestream << m_formatter -> format(event, level, logger);
	}
}
bool FileLogAppender::reopen()
{
    MutexType::Lock lock(m_mutex);
	if (m_filestream) {
		m_filestream.close();
	}
	m_filestream.open(m_filename);
	return !!m_filestream;  //˫��̾���Ƿ�0ת��1,0ֵ����0
}

std::string FileLogAppender::toYamlString(){
    YAML::Node node;
    node["type"] = "FileLogAppender";
    node["file"] = m_filename;
    if (m_level != LogLevel::Level::UNKNOWN){
        node["level"] = LogLevel::ToString(m_level);
    }
    if (m_formatter && m_hasFormatter) {
        node["formatter"] = m_formatter -> getPattern();
    }
    std::stringstream ss;
    ss << node;
    return ss.str();
}

void StdoutLogAppender::log(LogLevel::Level level, LogEvent::ptr event, std::shared_ptr<Logger> logger) {
	if (level >= m_level){
        MutexType::Lock lock(m_mutex);
		std::cout << m_formatter -> format(event, level, logger);
	}
}

std::string StdoutLogAppender::toYamlString(){
    YAML::Node node;
    MutexType::Lock lock(m_mutex);
    node["type"] = "StdoutLogAppender";
    if (m_level != LogLevel::Level::UNKNOWN){
        node["level"] = LogLevel::ToString(m_level);
    }
    if (m_formatter && m_hasFormatter) {
        node["formatter"] = m_formatter->getPattern();
    }
    std::stringstream ss;
    ss << node;
    return ss.str();
}

LogFormatter::LogFormatter(const std::string& pattern):m_pattern(pattern) {
    init();
}

std::string LogFormatter::format(LogEvent::ptr event, LogLevel::Level level, std::shared_ptr<Logger> logger) {
	std::stringstream ss;
	for (auto& i : m_items) {
		i -> format(ss, event, level, logger);
	}
	return ss.str();
}

bool LogFormatter::isError() const {
    return m_error;
}

//%xxx %xxx{xxx} %%
void LogFormatter::init() {
    //str, format, type
    std::vector<std::tuple<std::string, std::string, int> > vec;
    std::string nstr;
    for (size_t i = 0; i < m_pattern.size(); ++i) {
        if (m_pattern[i] != '%') {
            nstr.append(1, m_pattern[i]);
            continue;
        }

        if ((i + 1) < m_pattern.size()) {
            if (m_pattern[i + 1] == '%') {
                nstr.append(1, '%');
                continue;
            }
        }

        size_t n = i + 1;
        int fmt_status = 0;
        size_t fmt_begin = 0;

        std::string str;
        std::string fmt;
        while (n < m_pattern.size()) {
            if (!fmt_status && (!isalpha(m_pattern[n]) && m_pattern[n] != '{'
                && m_pattern[n] != '}')) {
                str = m_pattern.substr(i + 1, n - i - 1);
                break;
            }
            if (fmt_status == 0) {
                if (m_pattern[n] == '{') {
                    str = m_pattern.substr(i + 1, n - i - 1);
                    //std::cout << "*" << str << std::endl;
                    fmt_status = 1; //������ʽ
                    fmt_begin = n;
                    ++n;
                    continue;
                }
            }
            else if (fmt_status == 1) {
                if (m_pattern[n] == '}') {
                    fmt = m_pattern.substr(fmt_begin + 1, n - fmt_begin - 1);
                    //std::cout << "#" << fmt << std::endl;
                    fmt_status = 0;
                    ++n;
                    break;
                }
            }
            ++n;
            if (n == m_pattern.size()) {
                if (str.empty()) {
                    str = m_pattern.substr(i + 1);
                }
            }
        }

        if (fmt_status == 0) {
            if (!nstr.empty()) {
                vec.push_back(std::make_tuple(nstr, std::string(), 0));
                nstr.clear();
            }
            vec.push_back(std::make_tuple(str, fmt, 1));
            i = n - 1;
        }
        else if (fmt_status == 1) {
            std::cout << "pattern parse error: " << m_pattern << " - " << m_pattern.substr(i) << std::endl;
            m_error = true;
            vec.push_back(std::make_tuple("<<pattern_error>>", fmt, 0));
        }
    }

    if (!nstr.empty()) {
        vec.push_back(std::make_tuple(nstr, "", 0));
    }
    static std::map<std::string, std::function<FormatItem::ptr(const std::string& str)> > s_format_items = {
#define XX(str, C) \
        {#str, [](const std::string& fmt) { return FormatItem::ptr(new C(fmt));}}
        XX(m, MessageFormatItem),           //m:��Ϣ
        XX(p, LevelFormatItem),             //p:��־����
        XX(r, ElapseFormatItem),            //r:�ۼƺ�����
        XX(c, NameFormatItem),              //c:��־����
        XX(t, ThreadIdFormatItem),          //t:�߳�id
        XX(n, NewLineFormatItem),           //n:����
        XX(d, DateTimeFormatItem),          //d:ʱ��
        XX(f, FilenameFormatItem),          //f:�ļ���
        XX(l, LineFormatItem),              //l:�к�
        XX(T, TabFormatItem),               //T:Tab
        XX(F, FiberIdFormatItem),           //F:Э��id
        XX(N, ThreadNameFormatItem),        //N:�߳�����
#undef XX
    };

    for (auto& i : vec) {
        if (std::get<2>(i) == 0) {
            m_items.push_back(FormatItem::ptr(new StringFormatItem(std::get<0>(i))));
        }
        else {
            auto it = s_format_items.find(std::get<0>(i));
            if (it == s_format_items.end()) {
                m_items.push_back(FormatItem::ptr(new StringFormatItem("<<error_format %" + std::get<0>(i) + ">>")));
                m_error = true;
            }
            else {
                m_items.push_back(it->second(std::get<1>(i)));
            }
        }

        //std::cout << "(" << std::get<0>(i) << ") - (" << std::get<1>(i) << ") - (" << std::get<2>(i) << ")" << std::endl;
    }
    //std::cout << m_items.size() << std::endl;
}
LoggerManager::LoggerManager()
{
    m_root.reset(new Logger);
    m_root->addAppender(LogAppender::ptr(new StdoutLogAppender));
    m_loggers[m_root->m_name] = m_root;
    init();
}

Logger::ptr LoggerManager::getLogger(const std::string& name)
{
    MutexType::Lock lock(m_mutex);
    auto it = m_loggers.find(name);
    if (it != m_loggers.end()){
        return it -> second;
    }
    Logger::ptr logger(new Logger(name));
    logger->m_root = m_root;
    m_loggers[name] = logger;
    return logger;
}

std::string LoggerManager::toYamlString(){
    MutexType::Lock lock(m_mutex);
    YAML::Node node;
    for (auto& i : m_loggers){
        node.push_back(YAML::Load(i.second->toYamlString()));
    }
    std::stringstream ss;
    ss << node;
    return ss.str();
}

LogEventWrap::LogEventWrap(LogEvent::ptr e)
    :m_event(e)
{
}
LogEventWrap::~LogEventWrap()
{
    m_event->getLogger()->log(m_event->getLevel(), m_event);
}
std::stringstream& LogEventWrap::getSS()
{
    return m_event->getSS();
}

struct LogAppenderDefine
{
    int type = 0; //1 file 2 stdout
    LogLevel::Level level = LogLevel::UNKNOWN;
    std::string formatter;
    std::string file;

    bool operator==(const LogAppenderDefine& oth) const{
        return type == oth.type && level == oth.level && formatter == oth.formatter
                && file == oth.file;
    }
};


struct LogDefine {
    std::string name;
    LogLevel::Level level = LogLevel::UNKNOWN;
    std::string formatter;
    std::vector<LogAppenderDefine> appenders;

bool operator==(const LogDefine& oth) const {
        return name == oth.name
            && level == oth.level
            && formatter == oth.formatter
            && appenders == appenders;
    }

    bool operator<(const LogDefine& oth) const {
        return name < oth.name;
    }
    
};

template<>
class LexicalCast<std::string, std::set<LogDefine> > {
public:
    std::set<LogDefine> operator()(const std::string& v) {
        YAML::Node node = YAML::Load(v);
        std::set<LogDefine> lgs;
        for(auto n : node){
            if (!n["name"].IsDefined()){
                continue;;
            }
            LogDefine lg;
            lg.name = n["name"].as<std::string>();
            lg.level = LogLevel::FromString(n["level"].as<std::string>());
            if (n["formatter"].IsDefined()){
                lg.formatter = n["formatter"].as<std::string>();
            }
            if (n["appenders"].IsDefined()){
                for(size_t x = 0; x < n["appenders"].size(); ++x){
                    auto a = n["appenders"][x];
                    if (!a["type"].IsDefined()){
                        continue;
                    }
                    std::string type = a["type"].as<std::string>();
                    LogAppenderDefine lad;
                    std::cout << "formatter is = " << a["formatter"] << std::endl;
                    if (type == "FileLogAppender") {
                        lad.type = 1;
                        lad.file = a["file"].as<std::string>();
                        if (a["formatter"].IsDefined()){
                            lad.formatter = a["formatter"].as<std::string>();
                        }
                    }else if (type == "StdoutLogAppender"){
                        lad.type = 2;
                    }else{
                        std::cout << "log config error: appender type is invalid" << std::endl;
                        continue;
                    }
                    lg.appenders.push_back(lad);
                    
                }
            }
            lgs.insert(lg);
        }
        return lgs;
    }
};

template<>
class LexicalCast<std::set<LogDefine>, std::string> {
public:
    std::string operator()(const std::set<LogDefine>& lgs) {
        YAML::Node node;
        for(auto lg : lgs){
            YAML::Node n;
            n["name"] = lg.name;
            if (!lg.level == LogLevel::Level::UNKNOWN){
                n["level"] = LogLevel::ToString(lg.level);
            }
            if (!lg.formatter.empty()){
                n["formatter"] = lg.formatter;
            }
            for (auto& a : lg.appenders){
                YAML::Node sunNode;
                if (a.type == 1) {
                    sunNode["type"] = "FileLogAppender";
                }else if (a.type == 2){
                    sunNode["type"] = "StdoutLogAppender";
                }
                if (!a.level == LogLevel::Level::UNKNOWN){
                    sunNode["level"] = LogLevel::ToString(a.level);
                }
                if (!a.formatter.empty()){
                    sunNode["formatter"] = a.formatter;
                }
                n["appenders"].push_back(sunNode);
            }
        node.push_back(n);
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

sylar::ConfigVar<std::set<LogDefine> >::ptr g_log_defines = 
    sylar::Config::Lookup("logs", std::set<LogDefine>(), "logs config");

struct LogIniter {
    LogIniter() {
        g_log_defines -> addListener([](const std::set<LogDefine>& old_value,
         const std::set<LogDefine>& new_value){
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "on_logger_conf_changed";
            for (auto& i : new_value){
                sylar::Logger::ptr logger;
                auto it = old_value.find(i);
                if (it == old_value.end()){
                    //新增logger
                    logger.reset(new sylar::Logger(i.name));
                }else{
                    if (!(i == *it)){
                        // 修改的logger
                         logger = SYLAR_LOG_NAME(i.name);
                    }
                }
                logger -> setLevel(i.level);
                if (!i.formatter.empty()){
                    logger -> setFormatter(i.formatter);
                }
                logger->clearAppender();
                for (auto& a : i.appenders) {
                    sylar::LogAppender::ptr ap;
                    if (a.type == 1){
                        ap.reset(new FileLogAppender(a.file));
                    }else if(a.type == 2) {
                        ap.reset(new StdoutLogAppender);                        
                    }
                    ap -> setLevel(a.level);
                    if (!a.formatter.empty()) {
                        LogFormatter::ptr fmt(new LogFormatter(a.formatter));
                    }else{
                        std::cout << "logger name :" << logger -> getName() << "  appender type = " << a.type << "formatter = " << a.formatter << "is invaild" << std::endl; 
                    }
                    logger->addAppender(ap);
                }
            }
            for (auto& i : old_value){
                auto it = new_value.find(i);
                if (it == new_value.end()){
                    //删除log
                    auto logger = SYLAR_LOG_NAME(i.name);
                    logger -> setLevel((LogLevel::Level)100);
                    logger -> clearAppender();
                }
            }
        });
    }

};

static LogIniter __log_init;

void LoggerManager::init(){
 
}
}
