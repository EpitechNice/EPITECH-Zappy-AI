#include "Communication.hpp"
/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-clement.piasco [WSL: Ubuntu]
** File description:
** Communication
*/

#include "Communication.hpp"

namespace IA {
    Communication::Communication(const std::string &ip, const int port)
    {
        _ip = ip;
        _port = port;
    }
}
