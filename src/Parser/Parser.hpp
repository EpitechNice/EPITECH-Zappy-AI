/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Parser
*/

#pragma once

#include <string>
#include <exception>
#include <any>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <functional>
#include "Macro.h"

namespace IA {

    class Parser {
        public:
            class ParsingError : public std::exception {
                public:
                    explicit ParsingError(const std::string &msg);
                    ~ParsingError() noexcept override = default;
                    [[nodiscard]] const char *what() const noexcept override;
                private:
                    std::string _msg;
            };

            ~Parser() = default;
            static Parser &getInstance(const std::string &filepath = "");
            void parseFile(int argc, char **argv);

            private:
                Parser() = default;
                void _openFile(const std::string &filepath);
                void _clearParsedArgs();
                void _trimLine(std::string &line);
                void _gotoStart(size_t &lineNb);
                void _buildArgs(int argc, char **argv);
                void _parseValues(const std::string &line, const std::string &key);
            private:
                std::unordered_map<std::string, std::any> _parsedArgs;
                std::unordered_map<std::string, std::string> _args;
                std::ifstream _file;
                bool _flagsFound = false;
    };
}
