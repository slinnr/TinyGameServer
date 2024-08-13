#include <iostream>

int main(int argc, char** argv) {
    std::cout << "hello world" << std::endl;
    void* ptr = malloc(1000);
    char* bytePtr = static_cast<char*>(ptr);
    bytePtr[500] = 'A';
    std::cout << bytePtr[501] << std::endl;
	return 0;
}
