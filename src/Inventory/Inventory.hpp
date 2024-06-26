/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-clement.piasco [WSL: Ubuntu]
** File description:
** Inventory
*/

#pragma once

#include <unordered_map>
#include <map>
#include <cmath>
#include <algorithm>
#include <sstream>

#include "Utils.hpp"

namespace IA {

    const static std::unordered_map<std::string, int> perfectInv = {
        {"linemate", 10},
        {"deraumere", 9},
        {"sibur", 11},
        {"mendiane", 6},
        {"phiras", 7},
        {"thystame", 2}
    };

    class Inventory {
        public:
            /**
             * @brief Construct a new Inventory object
             *
             * @param food If the inventory is for food
             * @param players If the inventory is for players
             */
            Inventory(bool food, bool players);

            /**
             * @brief Construct a new Inventory object
             *
             * @param inv The inventory to fill
             * @param food If the inventory is for food
             * @param players If the inventory is for players
             */
            Inventory(std::string inv, bool food, bool players);
            ~Inventory() = default;

            /**
             * @brief Add an element to the inventory
             *
             * @param elem The element to add
             * @param nb The number of element to add
             */
            void add(const std::string &elem, size_t nb = 1);

            /**
             * @brief Remove an element from the inventory
             *
             * @param elem The element to remove
             * @param nb The number of element to remove
             */
            void remove(const std::string &elem, size_t nb = 1);

            /**
             * @brief Get the weight of the inventory
             *
             * @return `double` The weight of the inventory
             */
            [[nodiscard]] double getWeight() const;

            /**
             * @brief Check if the inventory is empty
             *
             * @return `bool` True if the inventory is empty
             */
            [[nodiscard]] bool isEmpty() const;

            /**
             * @brief Check if the inventory is enough
             *
             * @return `bool` True if the inventory is enough
             */
            [[nodiscard]] bool isEnough() const;

            /**
             * @brief Get the number of element in the inventory
             *
             * @param elem The element to get
             *
             * @return `int` The number of element
             */
            [[nodiscard]] int get(const std::string &elem) const;

            /**
             * @brief Get the number of needed element
             *
             * @param elem The element to get
             *
             * @return `int` The number of needed element
             */
            [[nodiscard]] int getNeededValue(const std::string &elem) const;

            /**
             * @brief Get the total value of the inventory
             *
             * @param inv The inventory to get the total value
             *
             * @return `double` The total value of the inventory
             */
            [[nodiscard]] double getTotalValue(const Inventory &inv) const;

            /**
             * @brief Get the beginning iterator of the inventory
             */
            std::unordered_map<std::string, int>::iterator begin();

            /**
             * @brief Get the end iterator of the inventory
             */
            std::unordered_map<std::string, int>::iterator end();

            /**
             * @brief Get the beginning const iterator of the inventory
             */
            std::unordered_map<std::string, int>::const_iterator begin() const;

            /**
             * @brief Get the end const iterator of the inventory
             */
            std::unordered_map<std::string, int>::const_iterator end() const;
        private:
            void _quantitiveFilling(std::stringstream &inv, bool food, bool players);
            double _recalculateWeight(double x) const;
        private:
            std::unordered_map<std::string, int> _inventory;
    };
}
