/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Utils
*/

#pragma once

#include <string>

namespace Utils {
    inline void trimLine(std::string &line)
    {
        size_t start = line.find_first_not_of(" \t");
        size_t end = line.find_last_not_of(" \t");

        if (start == std::string::npos || end == std::string::npos)
            line.clear();
        else
            line = line.substr(start, end - start + 1);
    }
}
