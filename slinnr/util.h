#pragma once
#include <thread>
#include <sys/syscall.h>
#include <unistd.h>
#include <string>
#include <vector>

namespace sylar {
pid_t GetThreadId();
void Backtrace(std::vector<std::string>& bt, int size, int skip);
std::string BacktraceToString(int size, int skip = 2, const std::string& prefix="");
}
