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
#include <queue>

namespace IA
{
    class Communication {
        public:
            class CommunicationError : public std::exception {
                public:
                    CommunicationError(const std::string &msg) : _msg(msg) {}
                    [[nodiscard]] const char *what() const noexcept { return _msg.c_str(); }
                private:
                    std::string _msg;
            };

            Communication(std::queue<std::pair<int, std::string>> &queue);
            ~Communication();

            void connectToServer(const std::string &ip, const int port);
            [[nodiscard]] std::string receiveData(bool setInQueue, int tryAgain = 0);
            void sendData(const std::string &data);
        private:
            int _port;
            int _socket;
            std::string _ip;
            std::queue<std::pair<int, std::string>> &_queue;
    };
}
