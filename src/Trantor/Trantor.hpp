/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-clement.piasco [WSL: Ubuntu]
** File description:
** Trantor
*/

#pragma once

#include "Communication/Communication.hpp"
#include "Inventory/Inventory.hpp"
#include "Macro.h"

#include <cmath>
#include <iostream>
#include <list>
#include <functional>
#include <map>
#include <regex>

#define JOIN_GAME "WELCOME\n"
#define KO "ko\n"
#define DEAD "dead\n"
#define OK "ok\n"

namespace IA {
    class Trantor {
        public:
            class TrantorException : public std::exception {
                public:
                    /**
                     * @brief Construct a new Trantor Exception object
                     */
                    TrantorException(const std::string &message);

                    /**
                     * @brief The content of the error
                     *
                     * @return `const char*` The content of the error
                     */
                    [[nodiscard]] const char *what() const noexcept override;
                private:
                    std::string _message;
            };

            /**
             * @brief Construct a new Trantor object
             */
            Trantor();
            ~Trantor() = default;

            /**
             * @brief Clear the queue
             */
            void clearQueue();

            /**
             * @brief Connect to the server
             *
             * @param ip The ip of the server
             * @param port The port of the server
             */
            void connectToServer(const std::string &ip, const int port);

            /**
             * @brief Join a team
             *
             * @param team The team to join
             */
            void join(const std::string &team);

            /**
             * @brief Do an action
             *
             * @param action The action to do
             * @param ignoreResp If the response should be ignored, default is true
             * @param useBackslashN If the action should end with a backslash n, default is true
             */
            void doAction(const std::string &action, bool ignoreResp = true, bool useBackslashN = true);

            /**
             * @brief Wait for a friend
             */
            void waitFriends();

            /**
             * @brief Wander around the world
             *
             * @param refreshWorld If the world should be refreshed
             * @param eat If the trantor should eat
             */
            void wander(bool refreshWorld, bool eat);

            /**
             * @brief Get the items
             */
            void getItems();

            /**
             * @brief Get the food
             *
             * @param nbFood The number of food to get
             */
            void getFood(int nbFood);

            /**
             * @brief Wait for orders
             *
             * @param msg The message to send
             * @param waitingFor The message to wait for
             */
            void waitOrders(std::string &msg, const std::string &waitingFor);

            /**
             * @brief Meet up with friends
             */
            void meetUp();

            /**
             * @brief Drop all the items
             *
             * @param inv The inventory to drop
             */
            void dropAll(std::string inv);

            /**
             * @brief Go to a specific target
             */
            void goToTarget();

            /**
             * @brief Set the tick
             *
             * @param tick The tick to set
             */
            void setTick(const int tick);

            /**
             * @brief Find a guard
             */
            void findGuard();

            /**
             * @brief Handle the broadcast
             *
             * @return `bool` True if the broadcast has been handled
             */
            bool handleBroadcast();

            /**
             * @brief Check if the trantor has enough ticks
             *
             * @return `bool` True if the trantor has enough ticks
             */
            [[nodiscard]] bool hasEnoughTicks() const;

            /**
             * @brief Check if the trantor is full
             *
             * @return `bool` True if the trantor is full
             */
            [[nodiscard]] bool checkFull() const;

            /**
             * @brief Check if the trantor can give birth
             *
             * @param finished The finished boolean
             *
             * @return `bool` True if the trantor can give birth
             */
            [[nodiscard]] bool tryBirth(bool &finished);

            /**
             * @brief Update the objectives
             *
             * @return `int` The number of objectives updated
             */
            [[nodiscard]] int updateObjectives();

            /**
             * @brief Get the number of items needed
             *
             * @param itemName The item name
             * @param available The number of available items
             *
             * @return `int` The number of items needed
             */
            [[nodiscard]] int getNbrOfItemsNeeded(const std::string &itemName, int available) const;

            /**
             * @brief Get the number of ticks
             *
             * @return `int` The number of ticks
             */
            [[nodiscard]] int getTicks() const;

            /**
             * @brief Get the number of friends
             *
             * @return `int` The number of friends
             */
            [[nodiscard]] int getNbFriends() const;

            /**
             * @brief Check for the progression percentage
             *
             * @return `double` The progression percentage
             */
            [[nodiscard]] double progressionPercentage() const;

            /**
             * @brief Get the target of the trantor
             *
             * @return `std::pair<int, Inventory>` The target of the trantor
             */
            [[nodiscard]] std::pair<int, Inventory> getTarget() const;

            /**
             * @brief Say if the trantor is alive
             *
             * @param port The port of the server
             * @param team The team
             * @param ip The ip of the server
             */
            static void live(const int port, const std::string &team, const std::string &ip);
        private:
            void _fillMoves(std::list<std::string> &res, int &currentX, int &currentY);
            void _applyMove(std::list<std::string> &moves, const double nbSteps, int allMovesNb);
            void _manageObjective(bool eat);
            int _makeChoice(std::vector<std::pair<int, Inventory>> &res);
            int _howMany();
            [[nodiscard]] std::queue<std::pair<int, std::string>> _removeUselessAled();
            [[nodiscard]] bool _haveToMove(std::string &msg, int dir, char *buf);

            static void _childhood(Trantor &trantor, const int port, const std::string &team, const std::string &ip);
            static void _adulthood(Trantor &trantor);
            static void _elderhood(Trantor &trantor);
            static void _harvest(Trantor &trantor);
            static void _groupTrantor(Trantor &trantor);
            static void _guardsPos(Trantor &robot);
            static void _guardAction(Trantor &trantor);
            static void _clearComms(Trantor &trantor);
            static void _tryLvlUp(Trantor &trantor, int idT);
            static void _giveBirth(Trantor &robot);
            static int _getNbofIncantations(Trantor &trantor);
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
