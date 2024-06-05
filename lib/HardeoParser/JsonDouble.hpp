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
            JsonDouble() = default;
            ~JsonDouble() override = default;
    };
}
