//
// Created by Rei Shimizu on 2020/4/1.
//
#include "header.h"
#include "CPU.c"

void opr_t1(CPU* cpu);
void opr_t2(CPU* cpu);
int main()
{
    core1=new_cpu(1);
    core2=new_cpu(2);
    //read files
    fp1=fopen("dict1.dic","r");
    read_command(fp1,core1);
    fclose(fp1);
    fp2=fopen("dict2.dic","r");
    read_command(fp2,core2);
    fclose(fp2);
    //initialization
    mem_data_area[0]=100;
    int i;
    for(i=0;i<128;i++)
        strcpy(mem_command_area[i],"0");
    pthread_mutex_init(&io_mutex,NULL);

    pthread_create(&thread1,NULL,(void*)&opr_t1,core1);
    pthread_create(&thread2,NULL,(void*)&opr_t2,core2);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    delete_cpu(core1);
    delete_cpu(core2);
    destory_mem_lock(lock_chain_head);
    return 0;
}
void opr_t1(CPU* cpu)
{
    opr(cpu,0,64);
}
void opr_t2(CPU* cpu)
{
    opr(cpu,64,128);
}