#include "../core/json.cpp"
void Serialization()
{

//     {
//     "company": {
//         "name": "Example Corp",
//         "employee": [
//             {
//                 "id": 1,
//                 "name": "John Doe",
//                 "role": "Developer"
//             },
//             {
//                 "id": 2,
//                 "name": "Jane Smith",
//                 "role": "Designer"
//             }
//         ]
//     },
//     "booleans": [
//         "true",
//         "false"
//     ],
//     "numbers": [
//         10,
//         20.5,
//         30
//     ],
//     "strings": [
//         "apple",
//         "banana",
//         "cherry"
//     ],
//     "nulls": [
//         null,
//         null,
//         null
//     ],
//     "emptyArray": {},
//     "emptyObject": []
// }


    // JSON包装
    JSON employess_mes1=JSON::get_map_JSON();
    employess_mes1.getEnableObject().insert(std::make_pair("role", JSON("Developer")));
    employess_mes1.getEnableObject().insert(std::make_pair("name", JSON("John Doe")));
    employess_mes1.getEnableObject().insert(std::make_pair("id", JSON(1)));

    JSON employees=JSON::get_vec_JSON();
    employees.getEnableArray().emplace_back(std::move(employess_mes1));

    JSON employess_mes2=JSON::get_map_JSON();
    employess_mes2.getEnableObject().insert(std::make_pair("role", JSON("Designer")));
    employess_mes2.getEnableObject().insert(std::make_pair("name", JSON("Jane Smith")));
    employess_mes2.getEnableObject().insert(std::make_pair("id", JSON(2)));

    employees.getEnableArray().emplace_back(std::move(employess_mes2));

    JSON booleans=JSON::get_vec_JSON();
    booleans.getEnableArray().emplace_back(JSON(true, 1));
    booleans.getEnableArray().emplace_back(JSON(false, 0));

    JSON numbers=JSON::get_vec_JSON();
    numbers.getEnableArray().emplace_back(JSON(10));
    numbers.getEnableArray().emplace_back(JSON(20.5));
    numbers.getEnableArray().emplace_back(JSON(30));

    JSON strings=JSON::get_vec_JSON();
    strings.getEnableArray().emplace_back(JSON("apple"));
    strings.getEnableArray().emplace_back(JSON("banana"));
    strings.getEnableArray().emplace_back(JSON("cherry"));

    JSON nulls=JSON::get_vec_JSON();
    nulls.getEnableArray().emplace_back(JSON());
    nulls.getEnableArray().emplace_back(JSON());
    nulls.getEnableArray().emplace_back(JSON());

    JSON company=JSON::get_map_JSON();
    company.getEnableObject().insert(std::make_pair("employee", employees));
    company.getEnableObject().insert(std::make_pair("name", JSON("Example Corp")));

    // 整个对象
    JSON my_json=JSON::get_map_JSON();
    my_json.getEnableObject().insert(std::make_pair("emptyObject", JSON::get_vec_JSON()));
    my_json.getEnableObject().insert(std::make_pair("emptyArray", JSON::get_map_JSON()));
    my_json.getEnableObject().insert(std::make_pair("nulls", nulls));
    my_json.getEnableObject().insert(std::make_pair("strings", strings));
    my_json.getEnableObject().insert(std::make_pair("numbers", numbers));
    my_json.getEnableObject().insert(std::make_pair("booleans", booleans));
    my_json.getEnableObject().insert(std::make_pair("company", company));

    std::cout << my_json << std::endl;

     // JSON序列化
    std::string file="../test/data.json";
    std::ofstream outputFile(file, std::ios::out);
    if (!outputFile) {
        std::cerr << "Unable to open file!" << std::endl;
        return ; // 打开文件失败，返回错误代码
    }
    
    outputFile << my_json << std::endl;
    outputFile.flush(); // 刷新缓冲区，确保内容立即写入
    outputFile.close(); // 关闭文件流

    if (!outputFile) {
        std::cerr << "Failed to write to file!" << std::endl;
        return ; // 写入失败，返回错误代码
    }

    std::cout << "File written successfully!" << std::endl;

    std::string outfile="../test/data_us.json";

    // 压缩
    JSON::us(file,outfile);
}