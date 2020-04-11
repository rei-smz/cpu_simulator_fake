//
// Created by Administrator on 2020/4/11.
//
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
void mov()
{
    if(last_object==0) //moving instant number
    {
        reg[first_object]=(int)instant_num;
    }
    else if(first_object>0&&first_object<=4&&last_object>=5&&last_object<=8) //moving data from memory
    {
        reg[first_object]=mem_data_area[(reg[last_object]-16384)/2];
    }
    else if(first_object>=5&&first_object<=8&&last_object>0&&last_object<=4) //moving data from register
    {
        mem_data_area[(reg[first_object]-16384)/2]=reg[last_object];
    }
}
void add()
{
    if(last_object==0) //add instant number to register
    {
        reg[first_object]+=(int)instant_num;
    }
    else if(last_object>=5) //add data in memory to register
    {
        reg[first_object]+=mem_data_area[(reg[last_object]-16384)/2];
    }
}
void sub()
{
    if(last_object==0) //minus instant number with data in a register
    {
        reg[first_object]-=(int)instant_num;
    }
    else if(last_object>=5) //minus data in memory with data in a register
    {
        reg[first_object]-=mem_data_area[(reg[last_object]-16384)/2];
    }
}
void mul()
{
    if(last_object==0) //multiply instant number with data in a register
    {
        reg[first_object]*=(int)instant_num;
    }
    else if(last_object>=5) //multiply data in memory with data in a register
    {
        reg[first_object]*=mem_data_area[(reg[last_object]-16384)/2];
    }
}
void div()
{
    if(last_object==0) //divide data in a register with instant number
    {
        reg[first_object]/=(int)instant_num;
    }
    else if(last_object>=5) //divide data in a register with data in memory
    {
        reg[first_object]/=mem_data_area[(reg[last_object]-16384)/2];
    }
}
void land()
{
    if(last_object==0)
        reg[first_object]=reg[first_object]&&instant_num;
    else
        reg[first_object]=reg[first_object]&&mem_data_area[(reg[last_object]-16384)/2];
}
void lor()
{
    if(last_object==0)
        reg[first_object]=reg[first_object]||instant_num;
    else
        reg[first_object]=reg[first_object]||mem_data_area[(reg[last_object]-16384)/2];
}
void lnot()
{
    if(last_object==0)
        reg[first_object]=!reg[first_object];
    if(first_object==0)
        mem_data_area[(reg[last_object]-16384)/2]=!mem_data_area[(reg[last_object]-16384)/2];
}
void cmp()
{
    if(last_object==0) //compare data in register with instant number
    {
        if(reg[first_object]==instant_num)
            flag=0;
        else if (reg[first_object]<instant_num)
            flag=-1;
        else
            flag=1;
    }
    else //compare data in register with data in memory
    {
        if(reg[first_object]==mem_data_area[(reg[last_object]-16384)/2])
            flag=0;
        else if (reg[first_object]<mem_data_area[(reg[last_object]-16384)/2])
            flag=-1;
        else
            flag=1;
    }
}
void jmp()
{
    switch (last_object)
    {
        case 0: PC+=((int)instant_num-4);break;
        case 1: if(flag==0){PC+=((int)instant_num-4);}break;
        case 2: if(flag==1){PC+=((int)instant_num-4);}break;
        case 3: if(flag==-1){PC+=((int)instant_num-4);}break;
    }
}
void input()
{
    cout<<"in:"<<endl;
    cin>>reg[first_object];
}
void output()
{
    cout<<"out:"<<endl;
    cout<<reg[first_object]<<endl;
}
