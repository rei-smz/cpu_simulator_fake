//
// Created by Rei Shimizu on 2020/4/15.
//

#ifndef CPU_SIMULATOR_HEAD_H
#define CPU_SIMULATOR_HEAD_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>


typedef struct CPU{
    int id;
    int reg[10]; //1 to 4 is data area and 5 to 8 is memory address area
    long long instant_num;
    int PC,flag,ir;
    int operation,first_object,last_object;
}CPU;
typedef struct mem_lock{
    int mem_addr;
    pthread_mutex_t mutex;
    struct mem_lock* next;
}mem_lock;

FILE *fp1,*fp2;
//======================================declare memory
int mem_data_area[260];
char mem_command_area[128][35];
//======================================end declare memory
CPU *core1=NULL,*core2=NULL; //declare 2 cores
pthread_t thread1,thread2; //declare 2 threads
mem_lock* lock_chain_head=NULL;
pthread_mutex_t io_mutex;


//declare functions
CPU * new_cpu(int id)
{
    CPU *cpu;
    cpu=(CPU*)malloc(sizeof(CPU));
    cpu->id=id;
    memset(cpu->reg,0,sizeof(cpu->reg));
    cpu->instant_num=0;
    cpu->PC=0;
    cpu->ir=0;
    cpu->flag=0;
    cpu->operation=-1;
    cpu->first_object=-1;
    cpu->last_object=-1;
    return cpu;
}
void delete_cpu(CPU* cpu)
{
    free(cpu);
}
void destory_mem_lock(mem_lock* h)
{
    mem_lock *t,*p;
    p=h;
    while (p!=NULL)
    {
        t=p;
        p=p->next;
        free(t);
    }
}
long long stoi(int begin,int end,char* s)
{
    char *p=NULL;
    long long sum=0,power=1;
    unsigned long long length=strlen(s);
    if(end<=(int)length-1)
        p=s+end;
    else
        p=s+(int)length-1;
    while (p>=s+begin)
    {
        if(*p=='1')
        {
            sum+=power;
        }
        power*=2;
        p--;
    }
    return sum;
}
void read_command(FILE *f,CPU* cpu);
void opr(CPU* cpu,int begin,int size);
void command_to_operation(CPU* cpu,char* command);
static void mem_output();
void register_output(CPU* cpu);
void stop(CPU* cpu);
void mov(CPU* cpu);
void add(CPU* cpu);
void sub(CPU* cpu);
void mul(CPU* cpu);
void did(CPU* cpu);
void land(CPU* cpu);
void lor(CPU* cpu);
void lnot(CPU* cpu);
void cmp(CPU* cpu);
void jmp(CPU* cpu);
void input(CPU* cpu);
void output(CPU* cpu);
void lck(CPU* cpu);
void ulck(CPU* cpu);
void slp(CPU* cpu);
//end declare functions
#endif //CPU_SIMULATOR_HEAD_H
