//
// Created by Rei Shimizu on 2020/4/1.
//
#include "header.h"
#include "CPU.cpp"
using namespace std;
CPU core1,core2;
void opr_t1();
void opr_t2();
int main()
{
    /*core1.read_command(input_file1,0);
    core2.read_command(input_file2,64);
    input_file1.close();
    input_file2.close();*/
    thread t1(opr_t1);
    thread t2(opr_t2);
    t1.join();
    t2.join();
    input_file1.close();
    return 0;
}
void opr_t1()
{
    core1.read_command(input_file1,0);
    core1.opr(0,64);
}
void opr_t2()
{
    core1.read_command(input_file1,64);
    core2.opr(64,128);
}