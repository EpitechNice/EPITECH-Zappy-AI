/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** JsonArray
*/

#pragma once

#include <vector>
#include <string>
#include "AJsonValues.hpp"

namespace JSON {
    template<typename T>
    class JsonArray : public IJsonValues {
        public:
            JsonArray() = default;
            ~JsonArray() = default;

        private:
            std::vector<T> _array;
    };
}
