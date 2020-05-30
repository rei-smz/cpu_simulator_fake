//
// Created by Rei Shimizu on 2020/4/11.
//
#include "header.h"
void stop(CPU* cpu)
{
    register_output(cpu);
    mem_output();
}
void mov(CPU* cpu)
{
    if(cpu->last_object==0) //moving instant number
    {
        cpu->reg[cpu->first_object]=(int)cpu->instant_num;
    }
    else if(cpu->first_object>0&&cpu->first_object<=4&&cpu->last_object>=5&&cpu->last_object<=8) //moving data from memory
    {
        cpu->reg[cpu->first_object]=mem_data_area[(cpu->reg[cpu->last_object]-16384)/2];
    }
    else if(cpu->first_object>=5&&cpu->first_object<=8&&cpu->last_object>0&&cpu->last_object<=4) //moving data from register
    {
        mem_data_area[(cpu->reg[cpu->first_object]-16384)/2]=cpu->reg[cpu->last_object];
    }
}
void add(CPU* cpu)
{
    if(cpu->last_object==0) //add instant number to register
    {
        cpu->reg[cpu->first_object]+=(int)cpu->instant_num;
    }
    else if(cpu->last_object>=5) //add data in memory to register
    {
        cpu->reg[cpu->first_object]+=mem_data_area[(cpu->reg[cpu->last_object]-16384)/2];
    }
}
void sub(CPU* cpu)
{
    if(cpu->last_object==0) //minus instant number with data in a register
    {
        cpu->reg[cpu->first_object]-=(int)cpu->instant_num;
    }
    else if(cpu->last_object>=5) //minus data in memory with data in a register
    {
        cpu->reg[cpu->first_object]-=mem_data_area[(cpu->reg[cpu->last_object]-16384)/2];
    }
}
void mul(CPU* cpu)
{
    if(cpu->last_object==0) //multiply instant number with data in a register
    {
        cpu->reg[cpu->first_object]*=(int)cpu->instant_num;
    }
    else if(cpu->last_object>=5) //multiply data in memory with data in a register
    {
        cpu->reg[cpu->first_object]*=mem_data_area[(cpu->reg[cpu->last_object]-16384)/2];
    }
}
void did(CPU* cpu)
{
    if(cpu->last_object==0) //divide data in a register with instant number
    {
        cpu->reg[cpu->first_object]/=(int)cpu->instant_num;
    }
    else if(cpu->last_object>=5) //divide data in a register with data in memory
    {
        cpu->reg[cpu->first_object]/=mem_data_area[(cpu->reg[cpu->last_object]-16384)/2];
    }
}
void land(CPU* cpu)
{
    if(cpu->last_object==0)
        cpu->reg[cpu->first_object]=cpu->reg[cpu->first_object]&&cpu->instant_num;
    else
    {
        cpu->reg[cpu->first_object]=cpu->reg[cpu->first_object]&&mem_data_area[(cpu->reg[cpu->last_object]-16384)/2];
    }
}
void lor(CPU* cpu)
{
    if(cpu->last_object==0)
        cpu->reg[cpu->first_object]=cpu->reg[cpu->first_object]||cpu->instant_num;
    else
    {
        cpu->reg[cpu->first_object]=cpu->reg[cpu->first_object]||mem_data_area[(cpu->reg[cpu->last_object]-16384)/2];
    }
}
void lnot(CPU* cpu)
{
    if(cpu->last_object==0)
        cpu->reg[cpu->first_object]=!cpu->reg[cpu->first_object];
    if(cpu->first_object==0)
    {
        mem_data_area[(cpu->reg[cpu->last_object]-16384)/2]=!mem_data_area[(cpu->reg[cpu->last_object]-16384)/2];
    }
}
void cmp(CPU* cpu)
{
    if(cpu->last_object==0) //compare data in register with instant number
    {
        if(cpu->reg[cpu->first_object]==cpu->instant_num)
            cpu->flag=0;
        else if (cpu->reg[cpu->first_object]<cpu->instant_num)
            cpu->flag=-1;
        else
            cpu->flag=1;
    }
    else //compare data in register with data in memory
    {
        if(cpu->reg[cpu->first_object]==mem_data_area[(cpu->reg[cpu->last_object]-16384)/2])
            cpu->flag=0;
        else if (cpu->reg[cpu->first_object]<mem_data_area[(cpu->reg[cpu->last_object]-16384)/2])
            cpu->flag=-1;
        else
            cpu->flag=1;
    }
}
void jmp(CPU* cpu)
{
    switch (cpu->last_object)
    {
        case 0: cpu->PC+=((int)cpu->instant_num-4);break;
        case 1: if(cpu->flag==0){cpu->PC+=((int)cpu->instant_num-4);}break;
        case 2: if(cpu->flag==1){cpu->PC+=((int)cpu->instant_num-4);}break;
        case 3: if(cpu->flag==-1){cpu->PC+=((int)cpu->instant_num-4);}break;
        default:return;
    }
}
void input(CPU* cpu)
{
    printf(("in:\n"));
    scanf("%d",&cpu->reg[cpu->first_object]);
    //cin>>reg[first_object];
}
void output(CPU* cpu)
{
    pthread_mutex_trylock(&io_mutex);
    printf("id = %d    out: %d\n",cpu->id,cpu->reg[cpu->first_object]);
    //cout<<"out: "<<reg[first_object]<<endl;
    pthread_mutex_unlock(&io_mutex);
}
void lck(CPU* cpu)
{
    mem_lock *l,*p,*t;
    p=lock_chain_head;
    while (p!=NULL)
    {
        if(p->mem_addr==(int)cpu->instant_num)
        {
            pthread_mutex_trylock(&p->mutex);
            return;
        }
        t=p;
        p=p->next;
    }
    l=(mem_lock*)malloc(sizeof(mem_lock));
    pthread_mutex_init(&l->mutex,NULL);
    l->mem_addr=(int)cpu->instant_num;
    pthread_mutex_trylock(&l->mutex);
    l->next=NULL;
    if(lock_chain_head==NULL)
        lock_chain_head=l;
    else
        t->next=l;
}
void ulck(CPU* cpu)
{
    mem_lock *p;
    p=lock_chain_head;
    while (p!=NULL)
    {
        if(p->mem_addr==(int)cpu->instant_num)
        {
            pthread_mutex_unlock(&p->mutex);
            return;
        }
    }
}
void slp(CPU* cpu)
{
    usleep(1000*cpu->instant_num);
}
