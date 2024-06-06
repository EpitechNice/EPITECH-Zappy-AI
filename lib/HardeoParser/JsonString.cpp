/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** JsonString
*/

#include "JsonString.hpp"

namespace JSON {
    JsonString::JsonString(std::ifstream &file)
    {
        std::string str;

        file.get();
        std::getline(file, str, '"');
        this->value = str;
    }

    void JsonString::parse(__attribute__((unused)) std::ifstream &file)
    {
        return;
    }
}
