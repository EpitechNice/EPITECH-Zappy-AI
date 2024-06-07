#include "Communication.hpp"
/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-clement.piasco [WSL: Ubuntu]
** File description:
** Communication
*/

#include "Communication.hpp"

namespace IA {

    Communication::CommunicationError::CommunicationError(const std::string &msg) : _msg(msg)
    {}

    const char *Communication::CommunicationError::what() const noexcept
    {
        return _msg.c_str();
    }

    Communication::Communication(const std::string &ip, const int port)
    {
        _ip = ip;
        _port = port;
        _socket = socket(AF_INET, SOCK_STREAM, 0);
        if (_socket == -1)
            throw CommunicationError("Error: socket creation failed");
        _server_addr.sin_family = AF_INET;
        _server_addr.sin_port = htons(port);
        if (inet_pton(AF_INET, ip.c_str(), &_server_addr.sin_addr) <= 0)
            throw CommunicationError("Error: invalid address");
        if (connect(_socket, (struct sockaddr *)&_server_addr, sizeof(_server_addr)) < 0)
            throw CommunicationError("Error: connection failed");
    }
}
