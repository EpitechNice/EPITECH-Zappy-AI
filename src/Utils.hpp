/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-clement.piasco [WSL: Ubuntu]
** File description:
** Utils
*/

#pragma once

#include <string>

namespace Utils {

    /**
     * @brief Trim the string (left)
     *
     * @param s The string to trim
     */
    inline void ltrim(std::string &s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
            { return !std::isspace(ch); }));
    }

    /**
     * @brief Trim the string (right)
     *
     * @param s The string to trim
     */
    inline void rtrim(std::string &s)
    {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
            { return !std::isspace(ch); }).base(), s.end());
    }

    /**
     * @brief Trim the string
     *
     * @param s The string to trim
     */
    inline void trim(std::string &s)
    {
        ltrim(s);
        rtrim(s);
    }
}
