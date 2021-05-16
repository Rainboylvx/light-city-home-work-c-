/*
 * @Author: 光城
 * @Date: 2021-05-08 08:45:45
 * @LastEditors: 光城
 * @LastEditTime: 2021-05-08 11:18:04
 * @Description:
 * @FilePath: \code\kg\string\string.cpp
 */
#include "string.h"
String::String() : data_(nullptr), size_(0) {}
String::String(const char* str) { __init(str); }
void String::__init(const char* str) {
  if (!str) {
    size_ = 0;
    data_ = nullptr;
  } else {
    size_ = std::strlen(str);
    data_ = new char[size_ + 1];
    strncpy_s(data_, size_ + 1, str, size_);
  }
}
void String::__clean() {
  if (!size_ && data_ != nullptr) {
    delete[] data_;
  }
  size_ = 0;
}

/**
 * @description: 拷贝构造
 * @param {const} String
 * @return {*}
 */
String::String(const String& other) {
  std::cout << "copy ct" << std::endl;
  __init(other.data_);
}

/**
 * @description: 拷贝赋值
 * @param {*}
 * @return {*}
 */
String& String::operator=(const String& other) {
  std::cout << "copy as" << std::endl;
  if (this != &other) {
    __clean();
    __init(other.data_);
  }
  return *this;
}

/**
 * @description: 移动构造
 * @param {const} String
 * @return {*}
 */
String::String(String&& other) noexcept {
  std::cout << "move ct" << std::endl;
  __clean();
  __swap(other);
}

/**
 * @description: 移动赋值
 * @param {*}
 * @return {*}
 */
String& String::operator=(String&& other) noexcept {
  if (this != &other) {
    __clean();
    __swap(other);
  }
  return *this;
}
/**
 * @description: 交换两个对象
 * @param {*}
 * @return {*}
 */
void String::__swap(String& other) {
  data_ = nullptr;
  data_ = other.data_;
  size_ = other.size_;
  other.data_ = nullptr;
  other.size_ = 0;
}

/**
 * @description: 重载[]操作符
 * @param {*}
 * @return {*}
 */
char& String::operator[](size_t index) {
  if (index >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[index];
}

bool String::operator==(const String& other) {
  if (size_ != other.size_) return false;
  return 0 == std::strcmp(data_, other.data_);
}

String String::operator+(const String& other) {
 	String s;
	s.size_ = this->size_ + other.size_;
	s.data_ = new char[s.size_ + 1];
	strncpy_s(s.data_ , this->size_ + 1, this->data_, this->size_);
	strncpy_s(s.data_ + this->size_, other.size_ + 1, other.data_, other.size_);
  return s;
}

String::~String() { __clean(); }

const char* String::c_str() const { return data_; }

size_t String::length() { return size_; }

std::ostream& operator<<(std::ostream& out, const String& str) {
  if (nullptr == str.data_) {
    out << "";
  } else {
    out << str.data_;
  }
  return out;
}
std::istream& operator>>(std::istream& in, String& str) {
  std::cout << "Please input string size: ";
  in >> str.size_;
  str.data_ = new char[str.size_ + 1];
  std::cout << "Please input string data: ";
  in >> str.data_;
  int len = strlen(str.data_);
  if (len > str.size_) {
    std::cout << "error! data len > size" << std::endl;
    exit(1);
  }
  return in;
}
