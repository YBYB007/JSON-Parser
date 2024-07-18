#pragma once
#include <string>
#include <vector>
#include <unordered_map>

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
        std::vector<JSON> *arr;
        std::unordered_map<std::string, JSON> *object;
    };

public:
    // 各种类型初始化
    JSON() : type(TYPE::Null), num(0) {}
    JSON(const std::string &s) : type(TYPE::String), str(new std::string(s)) {}
    JSON(double n) : type(TYPE::Number), num(n) {}
    JSON(bool b) : type(TYPE::Boolean), boolean(b) {}
    JSON(const std::vector<JSON> &vec) : type(TYPE::Array), arr(new std::vector<JSON>(vec)) {}
    JSON(const std::unordered_map<std::string, JSON> &map) : type(TYPE::Object), object(new std::unordered_map<std::string, JSON>(map)) {}
    ~JSON();

    // 拷贝构造
    JSON(const JSON &other);
    // 赋值运算符
    JSON &operator=(const JSON &other);

    // 数据
    TYPE getType() const;
    std::string getString() const;
    double getNumber() const;
    bool getBoolean() const;
    const std::vector<JSON> &getArray() const;
    const std::unordered_map<std::string, JSON> &getObject() const;
};