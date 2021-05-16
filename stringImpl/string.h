#pragma once

#include <string>
#include <cstring>
#include <iostream>
#include <vector>

#ifdef DEBUG

#include <cstdio>
#define log(...) { \
    fprintf(stderr,"In [ %s ],At line [ %d ]\n",__func__,__LINE__); \
        fprintf(stderr,__VA_ARGS__); \
        fprintf(stderr,"\n"); \
}

#elif 
#define log(...) 
#endif

class String{

    private:
        char * data_;
        size_t size_;

    public:
        String();//默认构造
        String(const char* str);                 // 构造
        String(const String & other); // 拷贝构造
        ~String(); //析构
        String& operator=(const String & other); //拷贝赋值
        String(String && other);    //移动赋值
        String& operator=(String && other) noexcept; //移动赋值
        char & operator[](size_t index);    // 重载下标操作
        bool operator==(const String & other);  // reload
        String operator+(const String & other); // 拼接
        const char* c_str() const;  //
        size_t length();    
        friend std::ostream & operator<<(std::ostream &out, String & str);    // 输出
        friend std::istream & operator>>(std::istream &in, String & str);     // 输入
    private:
        void __init(const char * str); // 初始化
        void __clean();         // 
        void __swap(String& other); // 交换
};



