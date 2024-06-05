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
#include <vector>
#include <any>
#include <tuple>

class JsonObject {
    public:
        enum class Type {
            INT,
            DOUBLE,
            FLOAT,
            BOOL,
            OBJECT
        };

        JsonObject() = default;
        ~JsonObject() = default;
    private:
        std::unordered_map<std::string,
            std::variant<int, double, float,
            bool, std::string, JsonObject,
            std::tuple<std::vector<std::any>, Type>>> _obj;
};
