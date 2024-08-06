#pragma once

#include <string>
#include <stdint.h>
#include <memory>
#include <list>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <sys/syscall.h>
#include "util.h"
#include "singleton.h"
#include "thread.h"

#define SYLAR_LOG_LEVEL(logger, level) \
    if(logger->getLevel() <= level) \
        sylar::LogEventWrap(sylar::LogEvent::ptr(new sylar::LogEvent(logger, level, \
                        __FILE__, __LINE__, 0, sylar::GetThreadId(),\
                0, time(0), sylar::Thread::GetName()))).getSS()


#define SYLAR_LOG_INFO(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::INFO)
#define SYLAR_LOG_DEBUG(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::DEBUG)
#define SYLAR_LOG_WARN(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::WARN)
#define SYLAR_LOG_ERROR(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::ERR)
#define SYLAR_LOG_FATAL(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::FATAL)
#define SYLAR_LOG_ROOT() sylar::LoggerMgr::GetInstance()->getRoot()

#define SYLAR_LOG_NAME(name) sylar::LoggerMgr::GetInstance()->getLogger(name)

namespace sylar{

class Logger;
class LoggerManager;

static const std::string levelString[6] = { "UNKNOWN", "DEBUG", "INFO", "WARN", "ERROR", "FATAL" };
//日志级别
class LogLevel {
public:
	enum Level {
		UNKNOWN = 0,
		DEBUG = 1,
		INFO = 2,
		WARN = 3,
		ERR = 4,
		FATAL = 5
	};
	static const std::string ToString(LogLevel::Level level) {
		if (level < UNKNOWN || level > FATAL) {
			return "UNKNOWN";
		}
		return levelString[level];
	}

	static const Level FromString(const std::string& str) {
		if (str == "DEBUG"){
			return LogLevel::Level::DEBUG;
		}else if (str == "INFO"){
			return LogLevel::Level::INFO;
		}else if (str == "ERROR"){
			return LogLevel::Level::ERR;
		}else if (str == "FATAL")
		{
			return LogLevel::Level::FATAL;
		}else{
			return LogLevel::Level::UNKNOWN;
		}
		
	}
};

//日志事件
class LogEvent {
public:
	typedef std::shared_ptr<LogEvent> ptr;
	LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level, const char* file, 
	int32_t line, uint32_t elapse, uint32_t threadId, uint32_t fiberId, uint32_t time,
	const std::string& threadName);
	const char* getFile() { return m_file; }
	int32_t getLine() { return m_line; }
	uint32_t getElapse() { return m_elapse; }
	uint32_t getThreadId() { return m_threadId; }
	uint32_t getFiberId() { return m_fiberId; }
	uint64_t getTime() { return m_time; }
	std::string getThreadName() { return m_threadName; }
	LogLevel::Level getLevel() { return m_level; }
	std::string getMessage() { return m_ss.str(); }
	std::stringstream& getSS() { return m_ss; }
	std::shared_ptr<Logger> getLogger() const { return m_logger; }
private:
	std::shared_ptr<Logger> m_logger; //日志器
	const char* m_file = nullptr; // 文件名
	int32_t m_line = 0; // 行号
	uint32_t m_elapse = 0; // 程序启动开始到现在的毫秒数
	uint32_t m_threadId = 0;// 线程ID
	uint32_t m_fiberId = 0; //协程id
	uint64_t m_time;  // 时间戳
	LogLevel::Level m_level;  // 日志等级
	std::stringstream m_ss;
	std::string m_threadName;
};


/**
 * @brief 日志事件包装器。作用是为了让宏定义也能流式打印日志
 */
class LogEventWrap {
public:

	/**
	 * @brief 构造函数
	 * @param[in] e 日志事件
	 */
	LogEventWrap(LogEvent::ptr e);

	/**
	 * @brief 析构函数
	 */
	~LogEventWrap();

	/**
	 * @brief 获取日志事件
	 */
	LogEvent::ptr getEvent() const { return m_event; }

	/**
	 * @brief 获取日志内容流
	 */
	std::stringstream& getSS();
private:
	/**
	 * @brief 日志事件
	 */
	LogEvent::ptr m_event;
};


//日志格式器
class LogFormatter {
public:
	typedef std::shared_ptr<LogFormatter> ptr;
	LogFormatter(const std::string& pattern);
	bool isError() const;
	void init();
	//%t	%thread_id%m%n
	std::string format(LogEvent::ptr event, LogLevel::Level level, std::shared_ptr<Logger> logger);
	std::string getPattern() const {return m_pattern;}
public:
	class FormatItem {
	public:
		typedef std::shared_ptr<FormatItem> ptr;
		virtual ~FormatItem() {}
		virtual void format(std::ostream& os, LogEvent::ptr event, LogLevel::Level level, std::shared_ptr<Logger> logger) = 0;
	};

private:
	std::string m_pattern;
	std::vector<FormatItem::ptr> m_items;
	bool m_error = false;
};


// 日志输入地
class LogAppender {
friend class Logger;
public:
	typedef std::shared_ptr<LogAppender> ptr;
	typedef Mutex MutexType;

	virtual ~LogAppender() {}
	virtual void log(LogLevel::Level level, LogEvent::ptr event, std::shared_ptr<Logger> logger) = 0;
	void setFormatter(LogFormatter::ptr val){
		Mutex::Lock lock(m_mutex);
		m_formatter = val;
		if (m_formatter) {
			m_hasFormatter = true;
		}else{
			m_hasFormatter = false;
    	}
}
	LogFormatter::ptr getFormatter();
	void setLevel(LogLevel::Level level) {m_level = level;}
	virtual std::string toYamlString() = 0;
protected:
	bool m_hasFormatter = false;
	LogLevel::Level m_level = LogLevel::DEBUG;
	MutexType m_mutex;
	LogFormatter::ptr m_formatter; 
};


// 日志器
class Logger : public std::enable_shared_from_this<Logger> {
friend class LoggerManager;
public:
	typedef std::shared_ptr<Logger> ptr;
	typedef Mutex MutexType;

	Logger(const std::string& name = "root");

	void log(LogLevel::Level level, LogEvent::ptr event);

	void debug(LogEvent::ptr event);
	void info(LogEvent::ptr event);
	void warn(LogEvent::ptr event);
	void error(LogEvent::ptr event);
	void fatal(LogEvent::ptr event);
	void addAppender(LogAppender::ptr appender);
	void delAppender(LogAppender::ptr appender);
	void clearAppender();
	std::string getName() const { return m_name; }
	LogLevel::Level getLevel() const { return m_level; }
	void setLevel(LogLevel::Level val) { m_level = val; }

	void setFormatter(LogFormatter::ptr val);
	void setFormatter(const std::string& val);
	LogFormatter::ptr getFormatter();

	std::string toYamlString();

private:
	std::string m_name;						//日志名称
	LogLevel::Level m_level;				//日志级别
	std::list<LogAppender::ptr> m_appenders; //Appender集合
	LogFormatter::ptr m_formatter;
	Logger::ptr m_root;
	MutexType m_mutex;
};

//输出到控制台的Appender
class StdoutLogAppender : public LogAppender {
friend class Logger;
public:
	typedef std::shared_ptr<StdoutLogAppender> ptr;
	void log(LogLevel::Level level, LogEvent::ptr event, std::shared_ptr<Logger> logger) override;
	std::string toYamlString();
};

//定义输出到文件的Appender
class FileLogAppender : public LogAppender {
friend class Logger;
public:
	typedef std::shared_ptr<FileLogAppender> ptr;
	FileLogAppender(const std::string& filename);
	void log(LogLevel::Level level, LogEvent::ptr event, std::shared_ptr<Logger> logger) override;
	bool reopen();
	std::string toYamlString();
private:
	std::string m_filename;
	std::ofstream m_filestream;
};

class LoggerManager {
public:
	typedef Mutex MutexType;
	LoggerManager();
	Logger::ptr getLogger(const std::string& name);
	Logger::ptr getRoot() const { return m_root; }
	std::string toYamlString();
	void init();
private:
	MutexType m_mutex;
	std::map<std::string, Logger::ptr> m_loggers;
	Logger::ptr m_root;
};

typedef sylar::Singleton<LoggerManager> LoggerMgr;

}
