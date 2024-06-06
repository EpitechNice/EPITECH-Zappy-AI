/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** JsonBool
*/

#pragma once

#include "AJsonValues.hpp"

namespace JSON {
    class JsonBool: public AJsonValues<bool>{
        public:
            JsonBool(bool value)
            {
                this->value = value;
            }

            ~JsonBool() override = default;

            void parse(__attribute__((unused)) std::ifstream &file) override {};
    };
}
