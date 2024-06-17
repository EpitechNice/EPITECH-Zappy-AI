/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-clement.piasco [WSL: Ubuntu]
** File description:
** Trantor
*/

#pragma once

#include "Communication/Communication.hpp"
#include <cmath>
#include <map>

#define JOIN_GAME "WELCOME\n"
#define KO "ko\n"

namespace IA {
    class Trantor {
        public:
            class TrantorException : public std::exception {
                public:
                    TrantorException(const std::string &message);
                    [[nodiscard]] const char *what() const noexcept override;
                private:
                    std::string _message;
            };

            Trantor();
            ~Trantor() = default;

            void clearQueue();
            void connectToServer(const std::string &ip, const int port);
            void join(const std::string &team);
            void doAction(const std::string &action, bool ignoreResp = true, bool useBackslashN = true);

        private:
            int _id;
            int _idMax;
            int _maxSlots;
            int _ticks = 1260;
            int _maxTicksNeeded = 0;
            int _nbChilds = 0;
            int _childsTarget = 0;
            std::string _team;
            std::pair<size_t, size_t> _mapSize;
            std::unique_ptr<IA::Communication> _communication;
            std::queue<std::pair<int, std::string>> _queue;
    };
}
