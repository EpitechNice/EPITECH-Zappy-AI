/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-clement.piasco [WSL: Ubuntu]
** File description:
** Communication
*/

#pragma once

#include <string>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <memory>

namespace IA
{
    class Communication {
        public:
            class CommunicationError : public std::exception {
                public:
                    CommunicationError(const std::string &msg) : _msg(msg) {}
                    const char *what() const noexcept { return _msg.c_str(); }
                private:
                    std::string _msg;
            };

            Communication(const std::string &ip, const int port);
            ~Communication() = default;
        private:
            std::string _ip;
            int _port;
            int _socket;
            struct sockaddr_in _server_addr;
    };
}
