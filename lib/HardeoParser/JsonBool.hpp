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
            JsonBool() = default;
            ~JsonBool() override = default;
    };
}
