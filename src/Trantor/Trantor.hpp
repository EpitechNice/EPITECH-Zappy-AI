/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-clement.piasco [WSL: Ubuntu]
** File description:
** Trantor
*/

#pragma once

#include "Communication/Communication.hpp"

class Trantor {
    public:
        Trantor() = default;
        ~Trantor() = default;
    private:
        IA::Communication _communication;
};