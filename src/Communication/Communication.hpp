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
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstring>
#include <memory>
#include <queue>

#define DEAD_NO_BACKN "dead"

namespace IA
{
    class Communication {
        public:
            class CommunicationError : public std::exception {
                public:
                    /**
                     * @brief Construct a new Communication Error object
                     */
                    CommunicationError(const std::string &msg);

                    /**
                     * @brief The content of the error
                     *
                     * @return `const char*` The content of the error
                     */
                    [[nodiscard]] const char *what() const noexcept;
                private:
                    std::string _msg;
            };

            /**
             * @brief Construct a new Communication object
             */
            Communication(std::queue<std::pair<int, std::string>> &queue);

            /**
             * @brief Destroy the Communication object
             */
            ~Communication();


            /**
             * @brief Connect to the server
             *
             * @param ip The ip of the server
             * @param port The port of the server
             */
            void connectToServer(const std::string &ip, const int port);

            /**
             * @brief Receive data from the server
             *
             * @param setInQueue If the data has to be set in the queue
             * @param tryAgain The number of try to receive the data. (Default is 0)
             *
             * @return `std::string` The data received
             */
            [[nodiscard]] std::string receiveData(bool setInQueue, int tryAgain = 0);

            /**
             * @brief Get the number of bytes to read
             *
             * @return `size_t` The number of bytes to read
             */
            [[nodiscard]] size_t nbBytesToRead() const;

            /**
             * @brief Send data to the server
             *
             * @param data The data to send
             */
            void sendData(const std::string &data);
        private:

            /**
             * @brief Handle the message received
             *
             * @param setInQueue If the data has to be set in the queue
             * @param tryAgain The number of try to receive the data
             * @param str The data received
             *
             * @return `std::string` The data received
             */
            [[nodiscard]]
            std::string _handleMessage(bool setInQueue, int tryAgain, const std::string &str);
        private:
            int _port;
            int _socket;
            std::string _ip;
            std::queue<std::pair<int, std::string>> &_queue;
    };
}
