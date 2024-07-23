#include "../core/json.cpp"
void ser_des_test(){

    std::string input_file_name="../test/input.json";
    std::string input_us_file_name="../test/input_us.json";
    JSON::us(input_file_name,input_us_file_name);

    JSON my_json=JSON::Deserialization(input_us_file_name);
    std::cout<<my_json;

    std::string out_file_name="../test/out.json";
    std::string out_us_file_name="../test/out_us.json";

    JSON::Serialization(my_json,out_file_name);
    JSON::us(out_file_name,out_us_file_name);
    
}