// slinnrserver.cpp: 定义应用程序的入口点。
//
#include <thread>
#include "slinnrserver.h"
#include "../slinnrserver/slinnr/log.h"
#include <windows.h>

using namespace std;

//int main()
//{
//	sylar::Logger::ptr logger{ new sylar::Logger };
//	logger->addAppender(sylar::LogAppender::ptr{ new sylar::StdoutLogAppender });
//	SYLAR_LOG_INFO(logger) << "hello sylar";
//	//sylar::LogEvent::ptr event (new sylar::LogEvent(__FILE__, __LINE__, 0, GetCurrentThreadId(), 2, time(0)));
//	//event->getSS() << "hello sylar";
//	//sylar::FileLogAppender::ptr file_appender(new sylar::FileLogAppender("./log.txt"));
//	//sylar::LogFormatter::ptr fmt(new sylar::LogFormatter{ "%d%T%%T%m%n" });
//	//file_appender->setFormatter(fmt);
//	//logger->addAppender(file_appender);
//	//logger->log(sylar::LogLevel::DEBUG, event);
//	auto l = sylar::LoggerMgr::GetInstance()->getLogger("xx");
//	cout << "Hello CMake." << endl;
//	return 0;
//}
