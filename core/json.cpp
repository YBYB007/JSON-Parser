
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

std::vector<JSON> &JSON::getEnableArray() const
{
    if (type != TYPE::Array)
        throw std::runtime_error("Not an array");
    return *arr;
}
std::unordered_map<std::string, JSON> &JSON::getEnableObject() const
{
    if (type != TYPE::Object)
        throw std::runtime_error("Not an object");
    return *object;
}

// JSON数据的输出
void JSON_print(const JSON &temp, int depth = 0, bool is_value = false)
{
    std::string str(depth * 3, ' ');
    std::string str1((depth + 1) * 3, ' ');
    switch (temp.getType())
    {
    case JSON::TYPE::Null:
        std::cout << (is_value ? " " : str) << "\"" << "NaN" << "\"" << std::endl;
        break;
    case JSON::TYPE::String:
        std::cout << (is_value ? " " : str) << "\"" << temp.getString() << "\"" << std::endl;
        break;
    case JSON::TYPE::Number:
        std::cout << (is_value ? " " : str) << temp.getNumber() << std::endl;
        break;
    case JSON::TYPE::Boolean:
        std::cout << (is_value ? " " : str) << "\"" << (temp.getBoolean() ? "true" : "false") << "\":" << std::endl;
        break;
    case JSON::TYPE::Array:
        std::cout << (is_value ? " " : str) << "[" << std::endl;
        ++depth;
        for (const auto &i : temp.getArray())
        {
            JSON_print(i, depth);
        }
        std::cout << str << "]" << std::endl;
        break;
    case JSON::TYPE::Object:
        ++depth;
        std::cout << "{" << std::endl;
        for (const auto &i : temp.getObject())
        {
            std::cout << str1 << "\"" << i.first << "\":";
            JSON_print(i.second, depth, true);
        }
        std::cout << str << "}" << std::endl;
        break;
    default:
        throw std::runtime_error("print error ");
        break;
    }
}

std::ostream &operator<<(std::ostream &os, const JSON &jv){
    JSON_print(jv,0,false);
    return os;
}

