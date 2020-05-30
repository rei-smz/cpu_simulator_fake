//
// Created by Rei Shimizu on 2020/4/15.
//
#include "header.h"
void read_command(FILE *f,CPU* cpu)
{
    char original_command[35];
    int i;
    if(cpu->id==1)
        i=0;
    else
        i=64;
    while (!feof(f))
    {
        fscanf(f,"%s",original_command);
        strcpy(mem_command_area[i],original_command);
        i++;
    }
}
void mem_output()
{
    pthread_mutex_trylock(&io_mutex);
    printf("\ncodeSegment :\n");
    int i;
    for(i=0;i<128;i++)
    {
        if((i+1)%8==0)
            printf("%lld\n",stoi(0,31,mem_command_area[i]));
            //cout<<stoi(mem_command_area[i],nullptr,2)<<endl;
        else
            printf("%lld ",stoi(0,31,mem_command_area[i]));
            //cout<<stoi(mem_command_area[i],nullptr,2)<<" ";
    }
    printf("\ndataSegment :\n");
    for(i=0;i<256;i++)
    {
        if((i+1)%16==0)
            printf("%d\n",mem_data_area[i]);
            //cout<<mem_data_area[i]<<endl;
        else
            printf("%d ",mem_data_area[i]);
            //cout<<mem_data_area[i]<<" ";
    }
    pthread_mutex_unlock(&io_mutex);
}
void register_output(CPU* cpu)
{
    pthread_mutex_trylock(&io_mutex);
    printf("id = %d\nip = %d\nflag = %d\nir = %d\n",cpu->id,cpu->PC,cpu->flag,cpu->ir);
    int i;
    for(i=1;i<=8;i++)
    {
        if(i%4==0)
            printf("ax%d = %d\n",i,cpu->reg[i]);
        else
            printf("ax%d = %d ",i,cpu->reg[i]);
    }
    pthread_mutex_unlock(&io_mutex);
}
