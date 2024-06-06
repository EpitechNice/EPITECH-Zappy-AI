/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** JsonDouble
*/

#pragma once

#include "AJsonValues.hpp"

namespace JSON {
    class JsonDouble: public AJsonValues<double> {
        public:
            JsonDouble(double value)
            {
                this->value = value;
            }

            ~JsonDouble() override = default;

            void parse(__attribute__((unused)) std::ifstream &file) override {};
    };
}
