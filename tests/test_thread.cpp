#include "slinnr/sylar.h"

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

int count = 0;
sylar::Mutex s_mutex;

void func1(){
    SYLAR_LOG_INFO(g_logger) << "thread_name: " << sylar::Thread::GetName()
    << " this name: " << sylar::Thread::GetThis()->getName()
    << " id: " << sylar::GetThreadId()
    << " this.id: " << sylar::Thread::GetThis() -> getId();
    for (int i = 0; i < 1000000; ++i) {
        sylar::Mutex::Lock lock(s_mutex);
        ++count;
    }
}

void func2(){
    while(true){
        SYLAR_LOG_INFO(g_logger) << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    }
}

void func3(){
    while(true){
        SYLAR_LOG_INFO(g_logger) << "=============================================================";
    }
}

int main(int argc, char** argv){
    SYLAR_LOG_INFO(g_logger) << "thread test begin";
	YAML::Node root = YAML::LoadFile("/home/slinnr/cppworkspace/slinnrserver/bin/conf/log2.yaml");
    sylar::Config::LoadFromYaml(root);

    std::vector<sylar::Thread::ptr> thrs;
    for (int i=0; i < 2; ++i){
        sylar::Thread::ptr thr1(new sylar::Thread(&func2, "name_" + std::to_string(i)));
        sylar::Thread::ptr thr2(new sylar::Thread(&func3, "name_" + std::to_string(i)));
        thrs.push_back(thr1);
        thrs.push_back(thr2);
    }
    for (size_t i = 0; i < thrs.size(); ++i){
        thrs[i] -> join();
    }
    SYLAR_LOG_INFO(g_logger) << "thread test end";
    SYLAR_LOG_INFO(g_logger) << "count = " << count;
    return 0;
}


