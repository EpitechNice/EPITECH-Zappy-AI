/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Parser
*/

#pragma once

#include "Macro.h"

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
                    /**
                     * @brief Construct a new Parsing Error object
                     */
                    explicit ParsingError(const std::string &msg);
                    ~ParsingError() noexcept override = default;

                    /**
                     * @brief The content of the error
                     *
                     * @return `const char*` The content of the error
                     */
                    [[nodiscard]] const char *what() const noexcept override;
                private:
                    std::string _msg;
            };

            struct Arguments {
                bool initialized = false;
                int port;
                std::string name;
                std::string machine = "127.0.0.1";
            };

            /**
             * @brief Construct a new Parser object
             */
            [[nodiscard]] static Arguments ParseArgs(int argc, char **argv);
        private:
            /**
             * @brief Get the flags object
             *
             * @param argc The number of arguments
             * @param argv The arguments
             * @return Arguments The arguments
             */
            [[nodiscard]] static Arguments getFlags(int argc, char **argv);
    };
}
