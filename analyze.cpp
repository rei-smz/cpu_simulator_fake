//
// Created by Administrator on 2020/4/11.
//
#include "header.h"
void command_to_operation(const string& command)
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
