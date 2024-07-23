#include "../core/json.cpp"

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
    JSON my_json = JSON::map_del(file);
    std::cout << my_json;
    file.close();
}
