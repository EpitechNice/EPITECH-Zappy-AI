/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** *
*/

#pragma once

#include "AJsonValues.hpp"
#include <string>

namespace JSON {
    class JsonString: public AJsonValues<std::string> {
        public:
            JsonString(std::ifstream &file);
            ~JsonString() override = default;

            void parse(std::ifstream &file) override;
    };
}
