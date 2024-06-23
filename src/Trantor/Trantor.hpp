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
#include <list>
#include <functional>
#include <map>
#include <regex>

#include "Macro.h"

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
            void meetUp();
            void dropAll(std::string inv);
            void goToTarget();
            void setTick(const int tick);
            void findGuard();
            bool handleBroadcast();
            [[nodiscard]] bool hasEnoughTicks() const;
            [[nodiscard]] bool checkFull() const;
            [[nodiscard]] bool tryBirth(bool &finished);
            [[nodiscard]] int updateObjectives();
            [[nodiscard]] int getNbrOfItemsNeeded(const std::string &itemName, int available) const;
            [[nodiscard]] int getTicks() const;
            [[nodiscard]] int getNbFriends() const;
            [[nodiscard]] double progressionPercentage() const;
            [[nodiscard]] std::pair<int, Inventory> getTarget() const;

            static void harvest(Trantor &trantor);
            static void groupTrantor(Trantor &trantor);
        private:
            void _fillMoves(std::list<std::string> &res, int &currentX, int &currentY);
            void _applyMove(std::list<std::string> &moves, const double nbSteps, int allMovesNb);
            void _manageObjective(bool eat);
            int _makeChoice(std::vector<std::pair<int, Inventory>> &res);
            int _howMany();
            [[nodiscard]] std::queue<std::pair<int, std::string>> _removeUselessAled();
            [[nodiscard]] bool _haveToMove(std::string &msg, int dir, char *buf);
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
            bool _inGroup = false;
            Inventory _inventory;
            std::string _team;
            std::string _worldInfo;
            std::pair<size_t, Inventory> _target;
            std::pair<size_t, size_t> _mapSize;
            std::unique_ptr<IA::Communication> _communication;
            std::queue<std::pair<int, std::string>> _queue;
    };
}
