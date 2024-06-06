/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** JsonObject
*/

#include "Utils.hpp"
#include "JsonObject.hpp"
#include "JsonString.hpp"
#include "JsonInt.hpp"
#include "JsonDouble.hpp"
#include "JsonBool.hpp"
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
        std::string line;
        std::unique_ptr<JsonObject> obj = nullptr;

        std::getline(file, line, ':');
        file.get();
        while (std::isspace(file.get()));

        switch (file.get()) {
            case '{':
                obj = std::make_unique<JsonObject>();
                obj->parse(file);
                return obj;
            case '\"':
                return std::make_unique<JsonString>(file);
            case 'f':
                if (file.get() == 'a' && file.get() == 'l' && file.get() == 's' && file.get() == 'e')
                    return std::make_unique<JsonBool>(false);
                throw JsonError("Invalid JsonObject");
            case 't':
                if (file.get() == 'r' && file.get() == 'u' && file.get() == 'e')
                    return std::make_unique<JsonBool>(true);
                throw JsonError("Invalid JsonObject");
            case '-':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                return _handleNumbers(file);
            case '[':
                return _handleArray(file);
            default:
                throw JsonError("Invalid JsonObject");
                break;
        }
    }

    std::unique_ptr<IJsonValues> JsonObject::_handleArray(std::ifstream &file)
    {
        return nullptr;
    }

    std::unique_ptr<IJsonValues> JsonObject::_handleNumbers(std::ifstream &file)
    {
        std::string nb;

        if (file.peek() == '-')
            nb += file.get();
        while (std::isdigit(file.peek()) || file.peek() == '.')
            nb += file.get();
        if (nb.find_first_of('.') != nb.find_last_of('.'))
            throw JsonError("Invalid number format");
        if (nb.find('.') != std::string::npos)
            return std::make_unique<JsonDouble>(std::stod(nb));
        else if (nb.find('.') == std::string::npos)
            return std::make_unique<JsonInt>(std::stoi(nb));
        throw JsonError("Invalid number format");
    }
}