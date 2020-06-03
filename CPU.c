//
// Created by Rei Shimizu on 2020/4/21.
//
#include "ISA.c"
#include "io.c"
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
#define LOCK 13
#define UNLOCK 14
#define SLP 15
void opr(CPU* cpu,int begin,int end)
{
    int i;
    for(i=begin;i<end;i++)
    {
        command_to_operation(cpu,mem_command_area[i]);
        switch (cpu->operation)
        {
            case STOP: stop(cpu);return ;
            case MOV: mov(cpu);break;
            case ADD: add(cpu);break;
            case SUB: sub(cpu);break;
            case MUL: mul(cpu);break;
            case DIV: did(cpu);break;
            case LAND: land(cpu);break;
            case LOR: lor(cpu);break;
            case LNOT: lnot(cpu);break;
            case CMP: cmp(cpu);break;
            case JMP: jmp(cpu);i=begin+cpu->PC/4-1;break;
            case INPUT: input(cpu);break;
            case OUTPUT: output(cpu);break;
            case LOCK: lck(cpu);break;
            case UNLOCK: ulck(cpu);break;
            case SLP: slp(cpu);break;
            default: return;
        }
        register_output(cpu);
    }

}
void command_to_operation(CPU* cpu,char* command)
{
    cpu->operation = (int)bstoi(0,7,command);
    cpu->first_object = (int)bstoi(8,11,command);
    cpu->last_object = (int)bstoi(12,15,command);
    cpu->instant_num = bstoi(16,31,command);
    if (cpu->instant_num > 32767)
        cpu->instant_num -= 65536;
    cpu->PC += 4;
    cpu->ir = (int)bstoi(0,15,command);
}
