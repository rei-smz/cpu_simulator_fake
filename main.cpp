//
// Created by Rei Shimizu on 2020/4/1.
//
#include "analyze.cpp"
#include "io.cpp"
#include "ISA.cpp"
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
void opr();
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
void opr()
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
