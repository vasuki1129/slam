#include <stdexcept>
#include <cstdio>
#include <array>
#include <memory>
#include <time.h>
#include <cstring>
#include <iostream>
#include <filesystem>
#include <string>
namespace fs = std::filesystem;

std::string strings[] =
{
    "are you actually an idiot?",
    "come on, this really isn't that complicated.",
    "if you can't figure this out get me somebody competent instead."
};

void insultError(std::string message)
{
    int len  = sizeof(strings) / sizeof(std::string);
    int random = (rand() % len);
    std::cout << message << strings[random] << "\n";
}

void printHelp()
{                     //nyaaaaaaaaaaaaaaa
    std::cout << "HELP:\nya don't get no help buddy, figure it out\n";
}


std::string exec(const char* cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd,"r"),pclose);
    if(!pipe)
    {
        throw std::runtime_error("popen() failed");
    }
    while(fgets(buffer.data(), static_cast<int>(buffer.size()),pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result;
}


void slamUp()
{
    std::string c = "git add .";
    std::cout << exec(c.c_str()) << "\n";
    //load dis jawn from the config
    std::string command;
    command = "git commit -a -m \"SLAMMING!\"";
    std::cout << "Slamming UP!\n";
    std::cout << exec(command.c_str()) << "\n";
    std::string command2;
    command2 = "git push";
    std::cout << exec(command2.c_str()) << "\n";
}

void slamDown()
{
    std::string command;
    command = "git pull";
    std::cout << "Slamming DOWN!\n";
    std::cout << exec(command.c_str()) << "\n";
}

int main(int argc, char** argv)
{
    //seed the rng, purely for the insults
    time_t tm;
    time(&tm);
    srand((int)tm);
    if(argc < 2)
    {
        printHelp();
    }
    else
    {
        char* command = argv[1];
        if(strcmp(command,"up") == 0)
        {
            slamUp();
        }
        else if(strcmp(command,"down") == 0)
        {
            slamDown();
        }
        else
        {
            insultError("invalid command. ");
        }
    }
    return 0;
}
