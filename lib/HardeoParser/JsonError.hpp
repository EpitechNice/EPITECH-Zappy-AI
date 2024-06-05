/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** JsonError
*/

#pragma once

#include <exception>
#include <string>

class JsonError: public std::exception {
    public:
        explicit JsonError(const std::string &msg);
        [[nodiscard]] const char *what() const noexcept override;
        ~JsonError() noexcept override = default;
    private:
        std::string _msg;
};
