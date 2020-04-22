//
// Created by Rei Shimizu on 2020/4/21.
//
#include "header.h"
#include "ISA.cpp"
#include "io.cpp"
#define STOP 0
#define MOV 1
#define ADD 2
#define SUB 3
#define MUL 4
#define DIV 5
#define LAND 6
#define LOR 7
#define LNOT 8
#define CMP 9
#define JMP 10
#define INPUT 11
#define OUTPUT 12
using namespace std;
void CPU::opr()
{
    for(int i=0;i<mem_command_area.size();i++)
    {
        command_to_operation(mem_command_area[i]);
        switch (operation)
        {
            case STOP: stop();return ;
            case MOV: mov();break;
            case ADD: add();break;
            case SUB: sub();break;
            case MUL: mul();break;
            case DIV: div();break;
            case LAND: land();break;
            case LOR: lor();break;
            case LNOT: lnot();break;
            case CMP: cmp();break;
            case JMP: jmp();i=PC/4-1;break;
            case INPUT: input();break;
            case OUTPUT: output();break;
            default: return;
        }
        register_output();
    }
}
void CPU::command_to_operation(const string &command)
{
    operation = stoi(command.substr(0, 8), nullptr, 2);
    first_object = stoi(command.substr(8, 4), nullptr, 2);
    last_object = stoi(command.substr(12, 4), nullptr, 2);
    instant_num = stoi(command.substr(16), nullptr, 2);
    if (instant_num > 32767)
        instant_num -= 65536;
    PC += 4;
    ir = stoi(command.substr(0, 16), nullptr, 2);
}