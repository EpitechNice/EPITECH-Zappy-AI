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

    Parser::Arguments Parser::ParseArgs(int argc, char **argv)
    {
        std::vector<std::string> helpFlags = {"-help", "--help", "-h"};

        switch (argc) {
            case 5:
            case 7:
                return getFlags(argc, argv);
            case 2:
                if (std::find(helpFlags.begin(), helpFlags.end(), argv[1]) != helpFlags.end()) {
                    std::cout << "USAGE: ./zappy_ai -p port -n name -h machine" << std::endl;
                    return {};
                }
                throw ParsingError("Invalid number of arguments");
            default:
                throw ParsingError("Invalid number of arguments");
        }
    }

    Parser::Arguments Parser::getFlags(int argc, char **argv)
    {
        Arguments args;
        bool alreadySetPort = false, alreadySetName = false, alreadySetMachine = false;

        for (int i = 1; i < argc; i += 2) {
            if (std::string(argv[i]) == "-p") {
                if (alreadySetPort)
                    throw ParsingError("Port already set");
                args.port = std::stoi(argv[i + 1]);
                alreadySetPort = true;
            } else if (std::string(argv[i]) == "-n") {
                if (alreadySetName)
                    throw ParsingError("Name already set");
                args.name = argv[i + 1];
                alreadySetName = true;
            } else if (std::string(argv[i]) == "-h") {
                if (alreadySetMachine)
                    throw ParsingError("Machine already set");
                args.machine = argv[i + 1];
                alreadySetMachine = true;
            } else {
                throw ParsingError("Invalid flag");
            }
        }
        args.initialized = true;
        return args;
    }
}
