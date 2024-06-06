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

            void parse(std::ifstream &file) override
            {
                std::string line;
                std::getline(file, line);
                if (line.find("[") == std::string::npos)
                    throw std::invalid_argument("Invalid JsonArray");
                line.erase(0, 1);
                line.pop_back();
                std::string delimiter = ",";
                size_t pos = 0;
                std::string token;
                while ((pos = line.find(delimiter)) != std::string::npos) {
                    token = line.substr(0, pos);
                    _array.push_back(token);
                    line.erase(0, pos + delimiter.length());
                }
                _array.push_back(line);
            }

        private:
            std::vector<T> _array;
    };
}
