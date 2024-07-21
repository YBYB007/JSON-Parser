#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>


class JSON
{
public:
    // 全局访问不到
    enum class TYPE
    {
        Null,
        String,
        Number,
        Boolean,
        Array,
        Object
    };

private:
    // 数据类型
    TYPE type;
    // 联合体
    union
    {
        std::string *str;
        double num;
        bool boolean;
        // 数据元素的插入直接用emplace_back就不需要自己构造结点了
        std::vector<JSON> *arr;
        std::unordered_map<std::string, JSON> *object;
    };

public:
    // 各种类型初始化
    JSON() : type(TYPE::Null), num(0) {}
    JSON(const std::string &s) : type(TYPE::String), str(new std::string(s)) {}
    JSON(double n) : type(TYPE::Number), num(n) {}
    JSON(bool b, int) : type(TYPE::Boolean), boolean(b) {}
    JSON(const std::vector<JSON> &vec) : type(JSON::TYPE::Array), arr(new std::vector<JSON>(vec)) {}
    JSON(const std::unordered_map<std::string, JSON> &map) : type(JSON::TYPE::Object), object(new std::unordered_map<std::string, JSON>(map)) {}
    ~JSON();

    // 拷贝构造
    JSON(const JSON &other);
    // 赋值运算符
    JSON &operator=(const JSON &other);

    // 结点操作
    TYPE getType() const;
    std::string getString() const;
    double getNumber() const;
    bool getBoolean() const;
    void setNumber(double data);
    void setBoolean(bool b);
    const std::vector<JSON> &getArray() const;
    const std::unordered_map<std::string, JSON> &getObject() const;
    // 可变
    std::vector<JSON> &getEnableArray() const;
    std::unordered_map<std::string, JSON> &getEnableObject() const;

    // JSON 序列化
    friend std::ostream &operator<<(std::ostream &os, const JSON &jv);
    friend std::ofstream &operator<<(std::ofstream &fs, const JSON &jv);

    // JSON 反序列化

};