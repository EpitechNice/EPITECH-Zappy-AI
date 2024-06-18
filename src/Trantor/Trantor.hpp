/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-clement.piasco [WSL: Ubuntu]
** File description:
** Trantor
*/

#pragma once

#include "Communication/Communication.hpp"
#include "Inventory/Inventory.hpp"

#include <cmath>
#include <functional>
#include <map>

#define JOIN_GAME "WELCOME\n"
#define KO "ko\n"
#define DEAD "dead\n"
#define OK "ok\n"

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
            void waitFriends();
            void wander(bool refreshWorld, bool eat);
            void getItems();
            void getFood(int nbFood);
            void waitOrders(std::string &msg, const std::string &waitingFor);
            [[nodiscard]] bool handleBroadcast();
            [[nodiscard]] int getNbrOfItemsNeeded(const std::string &itemName, int available) const;
            [[nodiscard]] double progressionPercentage() const;

        private:
            void _manageObjective(bool eat);
        private:
            int _id;
            int _idMax;
            int _maxSlots;
            int _ticks = 1260;
            int _maxTicksNeeded = 0;
            int _nbChilds = 0;
            int _childsTarget = 0;
            size_t _onSamePlace = 0;
            size_t _nbFriends = 0;
            bool _enoughFriends = false;
            bool _isFull = false;
            bool _isRetired = false;
            Inventory _inventory;
            std::string _team;
            std::string _worldInfo;
            std::pair<size_t, Inventory> _target;
            std::pair<size_t, size_t> _mapSize;
            std::unique_ptr<IA::Communication> _communication;
            std::queue<std::pair<int, std::string>> _queue;
    };
}
