/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Parser
*/

#pragma once

#include <string>
#include <exception>
#include <iostream>
#include <algorithm>
#include <vector>

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

            struct Arguments {
                bool initialized = false;
                int port;
                std::string name;
                std::string machine = "localhost";
            };

            [[nodiscard]] static Arguments ParseArgs(int argc, char **argv);
        private:
            [[nodiscard]] static Arguments getFlags(int argc, char **argv);
    };
}
