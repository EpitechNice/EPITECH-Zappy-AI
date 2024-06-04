/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** JsonObject
*/

#pragma once

#include <unordered_map>
#include <string>
#include <variant>

class JsonObject {
    public:
        JsonObject();
        ~JsonObject() = default;

    private:
        std::unordered_map<std::string, std::variant<int, double, float, bool, std::string>> _json;
};
