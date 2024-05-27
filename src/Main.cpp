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
        IA::Parser::ParseArgs(argc, argv);
    } catch (const IA::Parser::ParsingError &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}
