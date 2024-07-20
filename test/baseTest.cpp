#include "../core/json.cpp"


void basetest()
{
    // NULL
    JSON myJson_null;
    //JSON_print(myJson_null);

    // String
    JSON myJson_string("hello world");
    //JSON_print(myJson_string);

    // Number
    JSON myJson_Number(36);
    //JSON_print(myJson_Number);

    // Boolean
    JSON myJson_bool(true);
    //JSON_print(myJson_bool);

    // Array
    std::vector<JSON> vec;
    vec.emplace_back(myJson_null);
    vec.emplace_back(myJson_string);
    vec.emplace_back(myJson_Number);
    vec.emplace_back(myJson_bool);
    vec.emplace_back(vec);
    JSON myJson_vector(vec);
    //JSON_print(myJson_vector);

    // Object
    std::unordered_map<std::string, JSON> map;
    map.insert(std::make_pair("girlfriend", myJson_null));
    map.insert(std::make_pair("name", myJson_string));
    map.insert(std::make_pair("ID", myJson_Number));
    map.insert(std::make_pair("other", myJson_vector));
    JSON myJson_map(map);
    //JSON_print(myJson_map);

    // Object 嵌套
    std::unordered_map<std::string, JSON> map1;
    map1.insert(std::make_pair("girlfriend", myJson_null));
    map1.insert(std::make_pair("name", myJson_string));
    map1.insert(std::make_pair("ID", myJson_Number));
    map1.insert(std::make_pair("other", myJson_vector));
    map1.insert(std::make_pair("son", myJson_map));
    JSON myJson_map1(map1);
    std::cout<<myJson_map1;
}
