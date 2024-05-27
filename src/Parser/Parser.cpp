/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Parser
*/

#include "Parser.hpp"

namespace IA {

    Parser::ParsingError::ParsingError(const std::string &msg) : _msg(msg)
    {}

    const char *Parser::ParsingError::what() const noexcept
    {
        return _msg.c_str();
    }

    int Parser::ParseArgs(int argc, char **argv)
    {
        std::vector<std::string> helpFlags = {"-help", "--help", "-h"};

        switch (argc) {
            case 5:
                break;
            case 7:
                break;
            case 2:
                if (std::find(helpFlags.begin(), helpFlags.end(), argv[1]) != helpFlags.end()) {
                    std::cout << "USAGE: ./zappy_ai -p port -n name -h machine" << std::endl;
                    return 0;
                }
                throw ParsingError("Invalid number of arguments");
            default:
                throw ParsingError("Invalid number of arguments");
        }
        return 0;
    }
}