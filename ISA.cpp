//
// Created by Administrator on 2020/4/11.
//
#include "header.h"
using namespace std;
void CPU::stop()
{
    register_output();
    mem_output();
}
void CPU::mov()
{
    if(last_object==0) //moving instant number
    {
        reg[first_object]=(int)instant_num;
    }
    else if(first_object>0&&first_object<=4&&last_object>=5&&last_object<=8) //moving data from memory
    {
        mt.lock();
        reg[first_object]=mem_data_area[(reg[last_object]-16384)/2];
        mt.unlock();
    }
    else if(first_object>=5&&first_object<=8&&last_object>0&&last_object<=4) //moving data from register
    {
        mt.lock();
        mem_data_area[(reg[first_object]-16384)/2]=reg[last_object];
        mt.unlock();
    }
}
void CPU::add()
{
    if(last_object==0) //add instant number to register
    {
        reg[first_object]+=(int)instant_num;
    }
    else if(last_object>=5) //add data in memory to register
    {
        mt.lock();
        reg[first_object]+=mem_data_area[(reg[last_object]-16384)/2];
        mt.unlock();
    }
}
void CPU::sub()
{
    if(last_object==0) //minus instant number with data in a register
    {
        reg[first_object]-=(int)instant_num;
    }
    else if(last_object>=5) //minus data in memory with data in a register
    {
        mt.lock();
        reg[first_object]-=mem_data_area[(reg[last_object]-16384)/2];
        mt.unlock();
    }
}
void CPU::mul()
{
    if(last_object==0) //multiply instant number with data in a register
    {
        reg[first_object]*=(int)instant_num;
    }
    else if(last_object>=5) //multiply data in memory with data in a register
    {
        mt.lock();
        reg[first_object]*=mem_data_area[(reg[last_object]-16384)/2];
        mt.unlock();
    }
}
void CPU::div()
{
    if(last_object==0) //divide data in a register with instant number
    {
        reg[first_object]/=(int)instant_num;
    }
    else if(last_object>=5) //divide data in a register with data in memory
    {
        mt.lock();
        reg[first_object]/=mem_data_area[(reg[last_object]-16384)/2];
        mt.unlock();
    }
}
void CPU::land()
{
    if(last_object==0)
        reg[first_object]=reg[first_object]&&instant_num;
    else
    {
        mt.lock();
        reg[first_object]=reg[first_object]&&mem_data_area[(reg[last_object]-16384)/2];
        mt.unlock();
    }
}
void CPU::lor()
{
    if(last_object==0)
        reg[first_object]=reg[first_object]||instant_num;
    else
    {
        mt.lock();
        reg[first_object]=reg[first_object]||mem_data_area[(reg[last_object]-16384)/2];
        mt.unlock();
    }
}
void CPU::lnot()
{
    if(last_object==0)
        reg[first_object]=!reg[first_object];
    if(first_object==0)
    {
        mt.lock();
        mem_data_area[(reg[last_object]-16384)/2]=!mem_data_area[(reg[last_object]-16384)/2];
        mt.unlock();
    }
}
void CPU::cmp()
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
        mt.lock();
        if(reg[first_object]==mem_data_area[(reg[last_object]-16384)/2])
            flag=0;
        else if (reg[first_object]<mem_data_area[(reg[last_object]-16384)/2])
            flag=-1;
        else
            flag=1;
        mt.unlock();
    }
}
void CPU::jmp()
{
    switch (last_object)
    {
        case 0: PC+=((int)instant_num-4);break;
        case 1: if(flag==0){PC+=((int)instant_num-4);}break;
        case 2: if(flag==1){PC+=((int)instant_num-4);}break;
        case 3: if(flag==-1){PC+=((int)instant_num-4);}break;
        default:return;
    }
}
void CPU::input()
{
    cout<<"in:"<<endl;
    cin>>reg[first_object];
}
void CPU::output()
{
    cout<<"out: "<<reg[first_object]<<endl;
}
