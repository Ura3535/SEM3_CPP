#include "common.h"

Command::Command(const std::string& command_line)
    : command(RWS::UNCERTAIN), arg1(-1), arg2(-1)
{
    std::istringstream iss(command_line);
    std::string word;

    iss >> word;
    if (word == "read") {
        command = RWS::READ;
        iss >> word;
        arg1 = std::stoi(word);
    }

    if (word == "write") {
        command = RWS::WRITE;
        iss >> word;
        arg1 = std::stoi(word);
        iss >> word;
        arg2 = std::stoi(word);
    }

    if (word == "string") {
        command = RWS::STRING;
    }
}