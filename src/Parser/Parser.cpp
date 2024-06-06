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

    Parser &Parser::getInstance(const std::string &filepath)
    {
        static Parser instance;

        if (filepath.empty())
            return instance;
        instance._clearParsedArgs();
        instance._openFile(filepath);
        return instance;
    }

    void Parser::parseFile(int argc, char **argv)
    {
        std::string line;
        size_t lineNb = 0;
        std::string key;
        std::string value;

        _buildArgs(argc, argv);
        _gotoStart(lineNb);

    }

    void Parser::_openFile(const std::string &filepath)
    {
        if (!filepath.ends_with(".json"))
            throw ParsingError("HardeoParser: File format not supported");
        _file.open(filepath);
        if (!_file.is_open() || !_file.good())
            throw ParsingError("HardeoParser: Could not open file");
    }

    void Parser::_clearParsedArgs()
    {
        _parsedArgs.clear();
    }

    void Parser::_trimLine(std::string &line)
    {
        size_t start = line.find_first_not_of(" \t");
        size_t end = line.find_last_not_of(" \t");

        if (start == std::string::npos || end == std::string::npos)
            line.clear();
        else
            line = line.substr(start, end - start + 1);
    }

    void Parser::_gotoStart(size_t &lineNb)
    {
        std::string line;

        while (std::getline(_file, line)) {
            _trimLine(line);
            lineNb++;
            if (line == "{")    break;
        }
        lineNb++;
    }

    void Parser::_buildArgs(int argc, char **argv)
    {
        for (size_t i = 1; (int)i < argc; i++) {
            if (argv[i][0] != '-') {
                i++;
                continue;
            }
            _args[argv[i]] = argv[i + 1];
            i++;
        }
    }

    void Parser::_parseValues(const std::string &line, const std::string &key)
    {
        if (key == "flags") {
            if (_flagsFound)
                throw ParsingError("HardeoParser: Duplicate key: " + key);
            _flagsFound = true;
        } else if (key == "usageFlags") {
            return;
        } else if (key == "usage") {
            return;
        } else {
            throw ParsingError("HardeoParser: Invalid key: " + key);
        }
    }
}
