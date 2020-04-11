//
// Created by Administrator on 2020/4/11.
//
#include "ISA.cpp"
void read_command()
{
    string original_command;
    while (input_file.peek()!=EOF)
    {
        getline(input_file,original_command);
        mem_command_area.push_back(original_command);
    }
    for(int i=mem_command_area.size();i<128;i++)
        mem_command_area.emplace_back("0");
}
void command_to_operation(const string& command)
{
    operation=stoi(command.substr(0,8),nullptr,2);
    first_object=stoi(command.substr(8,4),nullptr,2);
    last_object=stoi(command.substr(12,4), nullptr,2);
    instant_num=stoi(command.substr(16), nullptr,2);
    if(instant_num>32767)
        instant_num-=65536;
    PC+=4;
    ir=stoi(command.substr(0,16), nullptr,2);
}
void mem_output()
{
    cout<<endl<<"codeSegment :"<<endl;
    for(int i=0;i<mem_command_area.size();i++)
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
}
void register_output()
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
void stop()
{
    register_output();
    mem_output();
    input_file.close();
}
void opr()
{
    for(int i=0;i<mem_command_area.size();i++)
    {
        command_to_operation(mem_command_area[i]);
        switch (operation)
        {
            case 0: stop();return ;
            case 1: mov();break;
            case 2: add();break;
            case 3: sub();break;
            case 4: mul();break;
            case 5: div();break;
            case 6: land();break;
            case 7: lor();break;
            case 8: lnot();break;
            case 9: cmp();break;
            case 10: jmp();i=PC/4-1;break;
            case 11: input();break;
            case 12: output();break;
        }
        register_output();
    }
}
