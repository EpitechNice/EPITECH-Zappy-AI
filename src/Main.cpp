/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Main
*/

#include "Parser/Parser.hpp"

int main(int argc, char *argv[])
{
    try {
        IA::Parser::Arguments parsedArgs = IA::Parser::ParseArgs(argc, argv);
        if (!parsedArgs.initialized)
            return 0;
        std::cout << "Port: " << parsedArgs.port << std::endl;
        std::cout << "Name: " << parsedArgs.name << std::endl;
        std::cout << "Machine: " << parsedArgs.machine << std::endl;
    } catch (const IA::Parser::ParsingError &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}
