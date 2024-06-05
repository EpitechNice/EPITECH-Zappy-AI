/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** IJsonValues
*/

#pragma once

#include <memory>
#include <fstream>

namespace JSON {
    class IJsonValues {
        public:
            virtual ~IJsonValues() = default;
            virtual void parse(std::ifstream &file) = 0;
    };
}
