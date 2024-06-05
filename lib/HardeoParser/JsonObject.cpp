/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** JsonObject
*/

#include "Utils.hpp"
#include "JsonObject.hpp"
#include "JsonString.hpp"
#include "JsonError.hpp"

namespace JSON {
    void JsonObject::parse(std::ifstream &file)
    {
        std::string line;

        std::getline(file, line);
        while (std::getline(file, line)) {
            Utils::trimLine(line);
            if (line.empty())   continue;
            if (line == "}")    break;
            if (line.find(':') == std::string::npos)
                throw JsonError("Invalid JsonObject");
            _values[line.substr(1, line.find("\""))] = _getValues(file);
        }
    }

    std::unique_ptr<IJsonValues> JsonObject::_getValues(std::ifstream &file)
    {
        while (std::isspace(file.get()));
        std::unique_ptr<JsonObject> obj = nullptr;

        switch (file.peek()) {
            case '{':
                obj = std::make_unique<JsonObject>();
                obj->parse(file);
                return obj;
            case '\"':
                return std::make_unique<JsonString>();
            default:
                break;
        }
    }
}
