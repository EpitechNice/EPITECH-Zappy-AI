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
#include <unordered_map>

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

            private:
                std::unordered_map<std::string, std::string> _args;
    };
}
