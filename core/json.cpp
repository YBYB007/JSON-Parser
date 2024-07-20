
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


// JSON 序列化
std::ostream &JSON_print(std::ostream &os, const JSON &temp, int depth = 0, bool is_value = false, bool is_end = false, bool is_obj = true)
{
    std::string str(depth * 4, ' ');
    std::string str1((depth + 1) * 4, ' ');
    switch (temp.getType())
    {
    case JSON::TYPE::Null:
        os << (is_value ? " " : str) << "null" << (is_end ? "" : ",") << std::endl;
        break;
    case JSON::TYPE::String:
        os << (is_value ? " " : str) << "\"" << temp.getString() << "\"" << (is_end ? "" : ",") << std::endl;
        break;
    case JSON::TYPE::Number:
        os << (is_value ? " " : str) << temp.getNumber() << "" << (is_end ? "" : ",") << std::endl;
        break;
    case JSON::TYPE::Boolean:
        os << (is_value ? " " : str) << "\"" << (temp.getBoolean() ? "true" : "false") << "\"" << (is_end ? "" : ",") << std::endl;
        break;
    case JSON::TYPE::Array:
        if (temp.getArray().size() == 0)
        {
            os << (is_value ? " " : str) << "[]" << (is_end ? "" : ",") << std::endl;
            break;
        }
        ++depth;
        os << (is_value ? " " : str) << "[" << std::endl;
        for (size_t i = 0; i < temp.getArray().size(); ++i)
        {
            // 当前元素是最后一个元素
            if (i == temp.getArray().size() - 1)
            {
                JSON_print(os,temp.getArray().at(i), depth, false, true, false);
            }
            else
            {
                JSON_print(os,temp.getArray().at(i), depth, false, false, false);
            }
        }
        os << str << (is_end ? "]" : "],") << std::endl;
        break;
    case JSON::TYPE::Object:
        if (temp.getObject().size() == 0)
        {
            os << (is_value ? " " : str) << "{}" << (is_end ? "" : ",") << std::endl;
            break;
        }
        ++depth;
        os << (is_value ? " " : str) << "{" << std::endl;
        for (auto it = temp.getObject().begin(); it != temp.getObject().end(); ++it)
        {
            os << str1 << "\"" << it->first << "\":";
            // 当前元素是最后一个元素
            if (std::next(it) == temp.getObject().end())
            {
                JSON_print(os,it->second, depth, true, true, false);
            }
            else
            {
                JSON_print(os,it->second, depth, true, false, false);
            }
        }
        os << str << (is_end ? "}" : (is_obj ? "}" : "},")) << std::endl;
        break;
    default:
        throw std::runtime_error("print error ");
        break;
    }
    return os;
}

std::ofstream &operator<<(std::ofstream &os, const JSON &jv)
{
    JSON_print(os, jv, 0, false);
    return os;
}

std::ostream &operator<<(std::ostream &os, const JSON &jv)
{
    JSON_print(os,jv, 0, false);
    return os;
}

// JSON反序列化