#include "../core/json.cpp"


void basetest()
{
    // NULL
    JSON myJson_null;

    // String
    JSON myJson_string("AUG 8");

    // Number
    JSON myJson_Number(130223);

    // Boolean
    JSON myJson_bool(true,0);
   
    // Array
    std::vector<JSON> vec;
    vec.emplace_back(myJson_null);
    vec.emplace_back(myJson_string);
    vec.emplace_back(myJson_Number);
    vec.emplace_back(myJson_bool);
    vec.emplace_back(vec);
    JSON myJson_vector(vec);
   
    // Object
    std::unordered_map<std::string, JSON> map;
    map.insert(std::make_pair("girlfriend", myJson_null));
    map.insert(std::make_pair("name", myJson_string));
    map.insert(std::make_pair("ID", myJson_Number));
    map.insert(std::make_pair("other", myJson_vector));
    JSON myJson_map(map);
    
    // Object 嵌套
    std::unordered_map<std::string, JSON> map1;
    map1.insert(std::make_pair("girlfriend", myJson_null));
    map1.insert(std::make_pair("name", myJson_string));
    map1.insert(std::make_pair("ID", myJson_Number));
    map1.insert(std::make_pair("birthday", myJson_vector));
    map1.insert(std::make_pair("son", myJson_map));
    JSON myJson_map1(map1);
    std::cout<<myJson_map1;
}
