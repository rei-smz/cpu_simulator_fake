//
// Created by Administrator on 2020/4/15.
//

#ifndef CPU_SIMULATOR_HEAD_H
#define CPU_SIMULATOR_HEAD_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
ifstream input_file("dict.dic");
int mem_data_area[260];
vector<string> mem_command_area;
int reg[10]; //1 to 4 is data area and 5 to 8 is memory address area
int PC=0,flag=0,ir;
int operation,first_object,last_object;
long long instant_num;
void stop();
void mov();
void add();
void sub();
void mul();
void div();
void land();
void lor();
void lnot();
void cmp();
void jmp();
void input();
void output();
#endif //CPU_SIMULATOR_HEAD_H
