#include "json.h"

// 拷贝构造函数
JSON::JSON(const JSON &other) : type(other.type)
{
    switch (type)
    {
    case TYPE::String:
        str = new std::string(*other.str);
        break;
    case TYPE::Number:
        num = other.num;
        break;
    case TYPE::Boolean:
        boolean = other.boolean;
        break;
    case TYPE::Array:
        arr = new std::vector<JSON>(*other.arr);
        break;
    case TYPE::Object:
        object = new std::unordered_map<std::string, JSON>(*other.object);
        break;
    case TYPE::Null:
        break;
    }
}

// 析构函数
JSON::~JSON()
{
    switch (type)
    {
    case TYPE::String:
        delete str;
        break;
    case TYPE::Number:
        break;
    case TYPE::Boolean:
        break;
    case TYPE::Array:
        delete arr;
        break;
    case TYPE::Object:
        delete object;
        break;
    case TYPE::Null:
        break;
    }
}

// 赋值运算符
JSON &JSON::operator=(const JSON &other)
{
    if (this != &other)
    {
        JSON temp(other);
        std::swap(type, temp.type);
        std::swap(str, temp.str);
        std::swap(num, temp.num);
        std::swap(boolean, temp.boolean);
        std::swap(arr, temp.arr);
        std::swap(object, temp.object);
    }
    return *this;
}

// 返回数据
JSON::TYPE JSON::getType() const
{
    return type;
}
std::string JSON::getString() const
{
    if (type != TYPE::String)
        throw std::runtime_error("Not a string");
    return *str;
}
double JSON::getNumber() const
{
    if (type != TYPE::Number)
        throw std::runtime_error("Not a number");
    return num;
}
bool JSON::getBoolean() const
{
    if (type != TYPE::Boolean)
        throw std::runtime_error("Not a boolean");
    return boolean;
}
const std::vector<JSON> &JSON::getArray() const
{
    if (type != TYPE::Array)
        throw std::runtime_error("Not an array");
    return *arr;
}
const std::unordered_map<std::string, JSON> &JSON::getObject() const
{
    if (type != TYPE::Object)
        throw std::runtime_error("Not an object");
    return *object;
}

