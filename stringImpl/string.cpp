#include "string.h"

String::String() :data_(nullptr),size_(0){}

String::String(const char * str){
    __init(str);
}

String::String(const String & other){
    __init(other.data_);
}

String::~String(){
    __clean();
}


String& String::operator=(const String & other) //拷贝赋值
{
    if( this == &other) return *this;
    __clean();
    __init(other.data_);
    return *this;
}

String::String(String && other)    //移动赋值
{
    //__swap(other);
    __clean();
    data_ = other.data_;
    size_ = other.size_;

    other.data_ = nullptr;
    other.size_ = 0;
}


String& String::operator=(String && other) noexcept  //移动赋值
{
    __clean();
    data_ = other.data_;
    size_ = other.size_;

    other.data_ = nullptr;
    other.size_ = 0;
    return *this;
}

char & String::operator[](size_t index)    // 重载下标操作
{
    if( index < 0 || index >=size_ )
        throw "index not right";
    else
        return data_[index];
}

bool String::operator==(const String & other)  // reload
{
    return  strcmp(data_, other.data_);
}

String String::operator+(const String & other) // 拼接
{
    String ret;
    ret.size_ = size_ + other.size_;
    ret.data_ = new char[ret.size_+1];
    strncpy(ret.data_, data_, size_);
    strncpy(ret.data_+size_, other.data_, other.size_);
    return ret;
}

const char * String::c_str() const {
    return data_;
}

size_t String::length()  {
    return size_;
}

void String::__init(const char * str){
    if( strlen(str) == 0 ) {
        data_ = nullptr;
        size_  = 0;
    }
    else {
        data_ = new char[strlen(str)+1];
        size_ = strlen(str);
        strcpy(data_, str);
    }
}

std::ostream & operator<<(std::ostream &out, String & str)    // 输出
{

    if( str.data_ !=nullptr)
        out << str.data_;
    return out;
}

std::istream & operator>>(std::istream &in, String & str)     // 输入
{

    //显然这里有更好的实现方式 
    // 1. 我们要一个判断方式来找到诗入的字符串长度
    // 2. 动态申请内存
    // 用getchar
    //log("Input String Size \n");
    //in >> str.size_;
    //if( str.size_ < 1 )
        //throw "input error";
    //str.data_ = new char[str.size_+1];
    //in >> str.data_;
    std::vector<char> v;
    char c = in.peek();

    auto judge_blank_char = [&c](){
        return  (c == EOF || c == '\n' || c == '\r' || c == ' ' || c == '\t');
    };

    //过滤空白字符
    while ( judge_blank_char() ) {
        in.get();
        c = in.peek();
    }

    while (  judge_blank_char() == false ) {
        v.push_back( in.get());
        c = in.peek();
    }

    if( v.size() > 0){
        str.size_ = v.size();
        str.data_ = new char[str.size_+1];
        for(int i=0;i<v.size();++i){
            str.data_[i] = v[i];
        }
    }

    return in;
}

void String::__clean(){
    if( data_ != nullptr){
        delete [] data_;
        data_ = nullptr;
        size_  = 0;
    }
}

void String::__swap(String & other){ //用于移动构造
    std::swap(other.data_,data_);
    std::swap(other.size_,size_);
}
