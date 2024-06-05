/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AJsonValues
*/

#pragma once

#include "IJsonValues.hpp"

namespace JSON {
    template<typename T>
    class AJsonValues: public IJsonValues {
        public:
            T value;
    };
}
