#include "../core/json.cpp"

JSON vec_del(std::ifstream &file);
JSON map_del(std::ifstream &file);
JSON set_JSON(const std::string &str);
bool isDouble(const std::string &str);

// 1.{ Object 开始
//      1.1 读取到的第一个应该是" 否则是非法格式
//      1.2 { Object 开始 只在值的部分可以遇到
//          递归调用1
//      1.3 } Object 结束标志
//      1.4 [ Vector 开始
//          1.4.1 " 读取字符串并判断类型(Null boolean String 数字 )
//          1.4.2 { 递归调用1
//          1.4.3 [ 递归调用1.4
//          1.4.4 ] Vector 结束标志
//          1.4.5 , 还有值的标志
//          1.4.6 其他代表着后面还有值
//      1.5 " 读取字符串并判断类型(Null boolean String)
//      1.6 数字，只在值的部分可以遇到
//      1.7 :键结束的标志 值开始的标志
//      1.8 ,值结束的标志，代表还有值，继续
//      1.9 其他的是非法格式
// 2.非法的JSON对象

// V 读取
JSON vec_del(std::ifstream &file)
{
    char ch;
    if (file.get(ch) && ch == ']')
    {
        return JSON::get_vec_JSON();
    }
    else
    {
       file.seekg(-1, std::ios::cur); // 从当前位置向前移动一个字符
    }
    std::string value = "";
    JSON my_vec = JSON::get_vec_JSON();

    // 逐字符读取
    while (file.get(ch))
    {
        // v 字符处理
        if (ch == '"')
        {
            while (file.get(ch))
            {
                if (ch == '"')
                {
                    // 插入一组值
                    my_vec.getEnableArray().emplace_back(set_JSON(value));
                    if (file.get(ch) && ch == ',')
                    {
                        // 继续执行
                        value = "";
                        break;
                    }
                    else if (ch == ']')
                    {
                        // 返回对象
                        return std::move(my_vec);
                    }
                    else
                    {
                        std::runtime_error("非法格式");
                    }
                }
                value += ch;
            }
        }
        // v null处理
        else if (ch == 'n')
        {
            value += ch;
            while (file.get(ch))
            {
                if (ch == ',')
                {
                    if (value == "null")
                    {
                        my_vec.getEnableArray().emplace_back(JSON());
                        // 继续执行
                        value = "";
                        break;
                    }
                    else
                    {
                        std::runtime_error("非法格式!");
                    }
                }
                else if (ch == ']')
                {
                    if (value == "null")
                    {
                        my_vec.getEnableArray().emplace_back(JSON());
                        return std::move(my_vec);
                    }
                    else
                    {
                        std::runtime_error("非法格式!");
                    }
                }
                else
                {
                    value += ch;
                }
            }
        }
        // 数字
        else if (ch == '-' || (ch >= '0' && ch <= '9'))
        {
            value += ch;
            while (file.get(ch))
            {
                if (ch == ',')
                {
                    if (isDouble(value))
                    {
                        my_vec.getEnableArray().emplace_back(JSON(std::stod(value)));
                        // 继续执行
                        value = "";
                        break;
                    }
                    else
                    {
                        std::runtime_error("非法格式!");
                    }
                }
                else if (ch == ']')
                {
                    if (isDouble(value))
                    {
                        my_vec.getEnableArray().emplace_back(JSON(std::stod(value)));
                        return std::move(my_vec);
                    }
                    else
                    {
                        std::runtime_error("非法格式!");
                    }
                }
                else
                {
                    value += ch;
                }
            }
        }
        // v 嵌套
        else if (ch == '{')
        {
            my_vec.getEnableArray().emplace_back(map_del(file));
            if (file.get(ch) && ch == ',')
            {
                value = "";
                continue;
            }
            else if (ch == ']' || ch == '}')
            {
                return std::move(my_vec);
            }
        }
        else if (ch == '[')
        {
            my_vec.getEnableArray().emplace_back(vec_del(file));
            if (file.get(ch) && ch == ',')
            {
                value = "";
                continue;
            }
            else if (ch == ']' || ch == '}')
            {
                return std::move(my_vec);
            }
        }
        else
        {
            exit(1);
        }
    }
    exit(1);
}

// K-V读取
JSON map_del(std::ifstream &file)
{
    char ch;
    if (file.get(ch) && ch == '}')
    {
        return JSON::get_map_JSON();
    }
    else
    {
        file.seekg(-1, std::ios::cur); // 从当前位置向前移动一个字符
    }
    bool is_value = false;
    bool key_first = true;
    std::string key = "";
    std::string value = "";
    std::stack<JSON> json_stack;
    JSON my_obj = JSON::get_map_JSON();
    while (file.get(ch))
    {
        // k 处理
        if (key_first && !is_value && ch == '"')
        {
            key_first = false;
            while (file.get(ch) && ch != '"')
            {
                // 读取Key
                key += ch;
            }
        }
        // key 读取完毕状态转变
        else if (!key_first && !is_value && ch == ':')
        {
            is_value = true;
        }

        // v 处理
        else if (is_value)
        {
            // v 字符处理
            if (is_value && (ch == '"'))
            {
                while (file.get(ch))
                {
                    if (ch == '"')
                    {
                        // 插入一组值
                        my_obj.getEnableObject().insert(std::make_pair(key, set_JSON(value)));
                        if (file.get(ch) && ch == ',')
                        {
                            // 继续执行
                            is_value = false;
                            key_first = true;
                            key = "";
                            value = "";
                            break;
                        }
                        else if (ch == '}')
                        {
                            // 返回对象
                            return std::move(my_obj);
                        }
                        else
                        {
                            std::runtime_error("非法格式");
                        }
                    }
                    value += ch;
                }
            }
            // v null处理
            else if (is_value && ch == 'n')
            {
                value += ch;
                while (file.get(ch))
                {
                    if (ch == ',')
                    {
                        if (value == "null")
                        {
                            my_obj.getEnableObject().insert(std::make_pair(key, JSON()));
                            // 继续执行
                            is_value = false;
                            key_first = true;
                            key = "";
                            value = "";
                            break;
                        }
                        else
                        {
                            std::runtime_error("非法格式!");
                        }
                    }
                    else if (ch == '}')
                    {
                        if (value == "null")
                        {
                            my_obj.getEnableObject().insert(std::make_pair(key, JSON()));
                            return std::move(my_obj);
                        }
                        else
                        {
                            std::runtime_error("非法格式!");
                        }
                    }
                    else
                    {
                        value += ch;
                    }
                }
            }
            // 数字
            else if (is_value && (ch == '-' || (ch >= '0' && ch <= '9')))
            {
                value += ch;
                while (file.get(ch))
                {
                    if (ch == ',')
                    {
                        if (isDouble(value))
                        {
                            my_obj.getEnableObject().insert(std::make_pair(key, JSON(std::stod(value))));
                            // 继续执行
                            is_value = false;
                            key_first = true;
                            key = "";
                            value = "";
                            break;
                        }
                        else
                        {
                            std::runtime_error("非法格式!");
                        }
                    }
                    else if (ch == '}')
                    {
                        if (isDouble(value))
                        {
                            my_obj.getEnableObject().insert(std::make_pair(key, JSON(std::stod(value))));
                            return std::move(my_obj);
                        }
                        else
                        {
                            std::runtime_error("非法格式!");
                        }
                    }
                }
            }
            // v 嵌套
            else if (is_value && ch == '{')
            {
                my_obj.getEnableObject().insert(std::make_pair(key, map_del(file)));
                if (file.get(ch) && ch == ',')
                {
                    is_value = false;
                    key_first = true;
                    key = "";
                    value = "";
                    continue;
                }
                else if (ch == ']' || ch == '}')
                {
                    return std::move(my_obj);
                }
            }
            else if (is_value && ch == '[')
            {
                my_obj.getEnableObject().insert(std::make_pair(key, vec_del(file)));
                if (file.get(ch) && ch == ',')
                {
                    is_value = false;
                    key_first = true;
                    key = "";
                    value = "";
                    continue;
                }
                else if (ch == ']' || ch == '}')
                {
                    return std::move(my_obj);
                }
            }
            else
            {
                std::runtime_error("非法格式");
            }
        }
        else
        {
            std::runtime_error("非法格式!");
        }
    }
    exit(1);
}

JSON set_JSON(const std::string &str)
{
    if (str == "true")
    {
        return JSON(true, 0);
    }
    else if (str == "false")
    {
        return JSON(false, 0);
    }
    else
    {
        return JSON(str);
    }
}

bool isDouble(const std::string &str)
{
    std::istringstream iss(str);
    double f;
    char c;

    // 尝试将字符串转换为 double
    iss >> std::noskipws >> f; // 禁止跳过任何空白字符
    // 检查是否成功读取到double且没有错误
    if (iss.eof() && !iss.fail())
    {
        // 检查字符串后面是否还有非空白字符
        while (iss >> std::noskipws >> c)
        {
            if (!std::isspace(c))
            {
                return false; // 发现非空白字符，返回 false
            }
        }
        return true; // 字符串是有效的浮点数
    }
    else
    {
        return false; // 转换失败或有错误
    }
}


// 反序列化
void Deserialization()
{
    std::ifstream file("../test/test_data.json");
    if (!file.is_open())
    {
        std::cerr << "无法打开文件" << std::endl;
        return;
    }

    std::string str;
    char ch;
    file.get(ch);
    if (ch != '{')
    {
        std::cout << "非法的JSON格式" << std::endl;
    }
    JSON my_json = map_del(file);
    std::cout << my_json;
    file.close();
}

