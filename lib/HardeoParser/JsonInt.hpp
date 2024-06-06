/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** JsonInt
*/

#pragma once

#include "AJsonValues.hpp"

namespace JSON {
    class JsonInt: public AJsonValues<int> {
        public:
            JsonInt(int value)
            {
                this->value = value;
            }

            ~JsonInt() override = default;
    };
}
