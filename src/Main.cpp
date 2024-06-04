/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Main
*/

#include "Parser/Parser.hpp"
#include "Macro.h"
#include <iostream>

int main(UNUSED int argc, UNUSED char *argv[])
{
    try {
        IA::Parser::getInstance("assets/ArgsParser.json").parseFile(argc, argv);
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
}
