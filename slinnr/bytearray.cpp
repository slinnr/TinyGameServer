#include "bytearray.h"
#include <fstream>
#include <sstream>
#include <string.h>
#include <iomanip>

#include "endian.h"
#include "log.h"

namespace sylar {

static sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");

ByteArray::Node::Node(size_t s)
{
}

ByteArray::Node::Node()
{
}

ByteArray::Node::~Node() {

}

ByteArray::ByteArray(size_t base_size)
{
}

ByteArray::~ByteArray() {

}

bool ByteArray::isLittleEndian() const {
}

void ByteArray::setIsLittleEndian(bool val) {
    
}

void ByteArray::writeFint8  (int8_t value) {
}

void ByteArray::writeFuint8 (uint8_t value) {
}

void ByteArray::writeFint16 (int16_t value) {


}

void ByteArray::writeFuint16(uint16_t value) {
    
}

void ByteArray::writeFint32 (int32_t value) {
   
}

void ByteArray::writeFuint32(uint32_t value) {
    
}

void ByteArray::writeFint64 (int64_t value) {
    
}

void ByteArray::writeFuint64(uint64_t value) {

}

static uint32_t EncodeZigzag32(const int32_t& v) {

}

static uint64_t EncodeZigzag64(const int64_t& v) {

}

static int32_t DecodeZigzag32(const uint32_t& v) {
}

static int64_t DecodeZigzag64(const uint64_t& v) {
}


void ByteArray::writeInt32  (int32_t value) {
}

void ByteArray::writeUint32 (uint32_t value) {

}

void ByteArray::writeInt64  (int64_t value) {
}

void ByteArray::writeUint64 (uint64_t value) {

}

void ByteArray::writeFloat  (float value) {
}

void ByteArray::writeDouble (double value) {
}

void ByteArray::writeStringF16(const std::string& value) {

}

void ByteArray::writeStringF32(const std::string& value) {

}

void ByteArray::writeStringF64(const std::string& value) {

}

void ByteArray::writeStringVint(const std::string& value) {

}

void ByteArray::writeStringWithoutLength(const std::string& value) {
}

int8_t   ByteArray::readFint8() {
}

uint8_t  ByteArray::readFuint8() {
}


int16_t  ByteArray::readFint16() {
}
uint16_t ByteArray::readFuint16() {
}

int32_t  ByteArray::readFint32() {
}

uint32_t ByteArray::readFuint32() {
}

int64_t  ByteArray::readFint64() {
}

uint64_t ByteArray::readFuint64() {
}

#undef XX

int32_t  ByteArray::readInt32() {
}

uint32_t ByteArray::readUint32() {

}

int64_t  ByteArray::readInt64() {
}

uint64_t ByteArray::readUint64() {

}

double   ByteArray::readDouble() {

}

std::string ByteArray::readStringF16() {

}

std::string ByteArray::readStringF32() {

}

std::string ByteArray::readStringF64() {

}

std::string ByteArray::readStringVint() {

}

void ByteArray::clear() {

}

void ByteArray::write(const void* buf, size_t size) {

}

void ByteArray::read(void* buf, size_t size) {

}

void ByteArray::read(void* buf, size_t size, size_t position) const {
}

void ByteArray::setPosition(size_t v) {

}

bool ByteArray::writeToFile(const std::string& name) const {

}

bool ByteArray::readFromFile(const std::string& name) {

}

void ByteArray::addCapacity(size_t size) {

}

std::string ByteArray::toString() const {

}

std::string ByteArray::toHexString() const {

}


uint64_t ByteArray::getReadBuffers(std::vector<iovec>& buffers, uint64_t len) const {

}

uint64_t ByteArray::getReadBuffers(std::vector<iovec>& buffers
                                ,uint64_t len, uint64_t position) const {

}

uint64_t ByteArray::getWriteBuffers(std::vector<iovec>& buffers, uint64_t len) {

}

}
