/*
 * @Author: 光城
 * @Date: 2021-05-11 08:25:17
 * @LastEditors: 光城
 * @LastEditTime: 2021-05-12 13:46:46
 * @Description:
 * @FilePath: \code\kg\phone\phone.cpp
 */
#include "phone.h"

/**
 * @description: 处理输入
 * @param {*}
 * @return {*}
 */
Phone* PhoneManageSystem::inputUser() {
}

/**
 * @description: 构造
 * @param {*}
 * @return {*}
 */
PhoneManageSystem::PhoneManageSystem() {
    head = tail = new Phone("",0); //创建一个空的点
}

/**
 * @description: 析构
 * @param {*}
 * @return {*}
 */
PhoneManageSystem::~PhoneManageSystem() {
    while ( head != tail ) {
        auto t_head = head;
        head = head->next;
        delete t_head;
    }
    delete tail; //删除创建的空节点
}


/**
 * @description: O(1) 创建 尾部添加电话本记录 添加同时要求用户输入数据
 * @param {*}
 * @return {*}
 */
void PhoneManageSystem::create() {
    auto ph = tail;

    std::cout << "输入姓名：" <<std::endl;
    cin >> ph->name ;
    std::cout << "输入电话（一个9位置数字）：" <<std::endl;
    cin >> ph->number;

    //check
    if( phone_record.find(ph->number) != phone_record.end() ){
        std::cout << "已经输入这个电话了，录入不成功！"  << std::endl;
        return;
    }
    else {
        //auto a = std::make_pair(ph->number,ph);
        phone_record.insert(std::make_pair(ph->number,ph));
        std::cout << "录入成功！"  << std::endl;
    }

    auto t = new Phone("",0);
    ph->next = t;
    tail = t;
}

/**
 * @description: O(n) 遍历 查看当前电话本记录有哪些
 * @param {*}
 * @return {*}
 */
void PhoneManageSystem::display() {
    if( head == tail ){
        std::cout << "Nothing " << std::endl;
        return;
    }

    auto t= head;
    while ( t!= tail ) {
        std::cout << "姓名：" << head->name << std::endl;
        std::cout << "电话：" << head->number<< std::endl << std::endl;
        t = t->next;
    }

}


/**
 * @description: O(1)搜索 查找电话本中的记录
 * @param {*}
 * @return {*}
 */
void PhoneManageSystem::search() {
    decltype(node::number) t;
    std::cout << "请输入电话号码：" << std::endl;
    cin >> t;
    if( phone_record.find(t) == phone_record.end()){
        std::cout << "没有找到" << std::endl;
    }
    else {
        std::cout << "找到信息如下" << std::endl;
        auto ph = phone_record.find(t)->second;
        std::cout << "姓名：" << ph->name << std::endl;
        std::cout << "电话：" << ph->number<< std::endl << std::endl;
    }
}

/**
 * @description: 删除 O(n) 在该函数中输入手机号 删除电话本中的记录
 * @param {*}
 * @return {*}
 */
void PhoneManageSystem::del() {
    decltype(node::number) num;
    std::cout << "请输入电话号码：" << std::endl;
    cin >> num;
    if( phone_record.find(num) == phone_record.end()){
        std::cout << "没有找到" << std::endl;
    }
    else {
        auto ph         = phone_record.find(num)->second;
        auto t          = head;
        decltype(t) pre = nullptr;
        while ( t != tail) {
            if( t == ph ){
                phone_record.erase(num);
                if( pre == nullptr){ //证明t是head
                    head = head->next;
                }
                else {
                    pre->next = t->next;
                }
                delete t; //释放对应的节点 内存
                break;
            }
            pre = t;
            t = t->next;
        }
        std::cout << "删除成功！" << std::endl;
    }
}


/**
 * @description: 数量
 * @param {*}
 * @return {*}
 */
int PhoneManageSystem::getSize() {
    int num=0;
    auto t = head;
    while ( t != tail) {
        num++;
        t = t->next;
    }
    return num;
}
