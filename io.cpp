//
// Created by Administrator on 2020/4/15.
//
#include "header.h"
using namespace std;
int CPU::read_command(ifstream &file,int begin)
{
    string original_command;
    int i=begin;
    while (file.peek()!=EOF)
    {
        getline(file,original_command);
        mem_command_area[begin+i]=original_command;
        i++;
    }
    return i;
}
void CPU::mem_output()
{
    mt.lock();
    cout<<endl<<"codeSegment :"<<endl;
    for(int i=0;i<128;i++)
    {
        if((i+1)%8==0)
            cout<<stoi(mem_command_area[i],nullptr,2)<<endl;
        else
            cout<<stoi(mem_command_area[i],nullptr,2)<<" ";
    }
    cout<<endl<<"dataSegment :"<<endl;
    for(int i=0;i<256;i++)
    {
        if((i+1)%16==0)
            cout<<mem_data_area[i]<<endl;
        else
            cout<<mem_data_area[i]<<" ";
    }
    mt.unlock();
}
void CPU::register_output()
{
    cout<<"ip = "<<PC<<endl;
    cout<<"flag = "<<flag<<endl;
    cout<<"ir = "<<ir<<endl;
    for(int i=1;i<=8;i++)
    {
        if(i%4==0)
            printf("ax%d = %d\n",i,reg[i]);
        else
            printf("ax%d = %d ",i,reg[i]);
    }
}
