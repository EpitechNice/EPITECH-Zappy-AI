/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-clement.piasco [WSL: Ubuntu]
** File description:
** Communication
*/

#pragma once

#include <string>

namespace IA
{
    class Communication
    {
        public:
            Communication(const std::string &ip, const int port);
            ~Communication() = default;
        private:
            std::string _ip;
            int _port;
    };
}
