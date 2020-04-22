//
// Created by Rei Shimizu on 2020/4/1.
//
#include "header.h"
#include "CPU.cpp"
using namespace std;
CPU core1,core2;
int size1,size2;
void opr_t1();
void opr_t2();
int main()
{
    size1=core1.read_command(input_file1,0);
    size2=core2.read_command(input_file2,size1);
    input_file1.close();
    input_file2.close();
    thread t1(opr_t1);
    thread t2(opr_t2);
    t1.join();
    t2.join();
    return 0;
}
void opr_t1()
{
    core1.opr(0,size1);
}
void opr_t2()
{
    core2.opr(size1,size2);
}