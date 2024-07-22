#include "../core/json.cpp"

void Deserialization()
{
    std::stack<JSON> json_stack;

    std::ifstream file("../test/data.json"); // 替换为你的文件名
    if (!file.is_open())
    {
        std::cerr << "Unable to open file!" << std::endl;
        return;
    }
    std::string line, word;
    while (std::getline(file, line))
    {
        std::istringstream lineStream(line);
        // 使用空白字符作为分隔符，逐个单词读取
        while (lineStream >> word)
        {
            std::cout << word << std::endl; // 打印单词
            if (word == "{")
            {
            }
            else if (word == "[")
            {
            }
        }
    }
    std::cout << std::endl;
    JSON my_json = JSON::get_map_JSON();
    std::cout << my_json << std::endl;
    // 处理完毕
    file.close();
    // 返回指针
}
