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

    std::string Communication::receiveData()
    {
        char buffer[4096] = {0};
        int valread = read(_socket, buffer, 4096);

        if (valread == -1)
            throw CommunicationError("Error: read failed");
        return std::string(buffer);
    }

    void Communication::sendData(const std::string &data)
    {
        if (send(_socket, data.c_str(), data.size(), 0) == -1)
            throw CommunicationError("Error: send failed");
    }
}
