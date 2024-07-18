#include <iostream>
#include "core/json.cpp"

int main(int argc, char const *argv[])
{
    /* code */
    JSON myJson;
    if(myJson.getType()==JSON::TYPE::Null)
    std::cout<<"NULL"<<std::endl;
    return 0;
}
