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

    Communication::Communication(std::queue<std::pair<int, std::string>> &queue): _queue(queue)
    {}

    void Communication::connectToServer(const std::string &ip, const int port)
    {
        struct sockaddr_in server_addr;

        _port = port;
        _ip = ip;
        _socket = socket(AF_INET, SOCK_STREAM, 0);
        if (_socket == -1)
            throw CommunicationError("Error: socket creation failed");
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        if (inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) <= 0)
            throw CommunicationError("Error: invalid address");
        if (connect(_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
            throw CommunicationError("Error: connection failed");
    }

    Communication::~Communication()
    {
        std::cout << "Disconnected from "
                  << _ip << " port "
                  << _port << std::endl;
        shutdown(_socket, SHUT_RDWR);
        close(_socket);
    }

    std::string Communication::_handleMessage(bool setInQueue, int tryAgain, const std::string &str)
    {
        char buf[1024] = {0};
        int soudDir = 0;

        sscanf(str.c_str(), "message %d, %s\n", &soudDir, buf);
        if (setInQueue) {
            if (_queue.size()) {
                std::pair<int, std::string> &front = _queue.front();
                if (front.first == soudDir && front.second == buf) {
                    if (tryAgain == 0)
                        return "";
                    return receiveData(setInQueue, tryAgain - 1);
                }
            }
            _queue.push(std::pair(soudDir, str));
        }
        if (tryAgain == 0)
            return setInQueue ? "" : str;
        return receiveData(setInQueue, tryAgain - 1);
    }

    std::string Communication::receiveData(bool setInQueue, int tryAgain)
    {
        char buffer[4096] = {0};
        int valread = read(_socket, buffer, 4096);
        std::string str;

        if (valread == -1 || tryAgain < 0)
            throw CommunicationError("Error: read failed");
        str = std::string(buffer);
        if (str.find(DEAD_NO_BACKN) != std::string::npos)
            throw CommunicationError("Tranto has been killed");
        if (str.find("message ") != std::string::npos)
            return _handleMessage(setInQueue, tryAgain, str);
        return std::string(buffer);
    }

    void Communication::sendData(const std::string &data)
    {
        if (send(_socket, data.c_str(), data.size(), 0) == -1)
            throw CommunicationError("Error: send failed");
    }

    size_t Communication::nbBytesToRead() const
    {
        return ioctl(_socket, FIONREAD);
    }
}
