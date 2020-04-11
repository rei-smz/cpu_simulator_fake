//
// Created by Rei Shimizu on 2020/4/1.
//
#include "basic_operation.cpp"
using namespace std;
int main()
{
    if(input_file.is_open())
    {
        read_command();
        opr();
        input_file.close();
    }
    return 0;
}
