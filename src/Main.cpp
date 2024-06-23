/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Main
*/

#include "Parser/Parser.hpp"
#include "Trantor/Trantor.hpp"
#include "Macro.h"

#include <iostream>

int main(int argc, char *argv[])
{
    try {
        IA::Parser::Arguments parsedArgs = IA::Parser::ParseArgs(argc, argv);
        if (!parsedArgs.initialized)
            return SUCCESS;
        IA::Trantor::live(parsedArgs.port, parsedArgs.name, parsedArgs.machine);
    } catch (const IA::Parser::ParsingError &e) {
        std::cerr << RED << BOLD
                  << e.what() << RESET << std::endl;
        return ERROR;
    } catch (const std::exception &e) {
        std::cerr << RED << BOLD
                  << "Unexpected error occured on: "
                  << e.what() << RESET << std::endl;
        return ERROR;
    }
    return SUCCESS;
}
