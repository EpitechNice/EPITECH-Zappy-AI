/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** JsonError
*/

#include "JsonError.hpp"

JsonError::JsonError(const std::string &msg) : _msg(msg)
{
}

const char *JsonError::what() const noexcept
{
    return _msg.c_str();
}
