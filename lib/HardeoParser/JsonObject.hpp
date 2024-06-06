/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** JsonObject
*/

#pragma once

#include <unordered_map>
#include "Utils.hpp"
#include "JsonArray.hpp"

namespace JSON {
    class JsonObject: public IJsonValues {
        public:
            JsonObject() = default;
            ~JsonObject() = default;

            void parse(std::ifstream &file) override;

        private:
            std::unique_ptr<IJsonValues> _getValues(std::ifstream &file);
            std::unique_ptr<IJsonValues> _handleArray(std::ifstream &file);
            std::unique_ptr<IJsonValues> _handleNumbers(std::ifstream &file);
        private:
            std::unordered_map<std::string, std::unique_ptr<IJsonValues>> _values;
    };
}
