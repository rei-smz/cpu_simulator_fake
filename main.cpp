//
// Created by Rei Shimizu on 2020/4/1.
//
#include "CPU.cpp"
using namespace std;
int main()
{
    CPU cpu;
    if(input_file.is_open())
    {
        cpu.read_command();
        cpu.opr();
        input_file.close();
    }
    return 0;
}
