//
// Created by Administrator on 2020/4/15.
//

#ifndef CPU_SIMULATOR_HEAD_H
#define CPU_SIMULATOR_HEAD_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
using namespace std;
ifstream input_file1("dict.dic");
ifstream input_file2("dict1.dic");
//======================================define memory
int mem_data_area[260];
vector<string> mem_command_area(128,"0");
//======================================end define memory
mutex mt;
class CPU
{
    public:
        void opr(int begin,int size);
        int read_command(ifstream &file,int begin);
    private:
        int reg[10]={0}; //1 to 4 is data area and 5 to 8 is memory address area
        long long instant_num=0;
        int PC=0,flag=0,ir=0;
        int operation,first_object,last_object;
        void command_to_operation(const string& command);
        static void mem_output();
        void register_output();
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
};
#endif //CPU_SIMULATOR_HEAD_H
