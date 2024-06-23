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
            Inventory(bool food, bool players);
            Inventory(std::string inv, bool food, bool players);
            ~Inventory() = default;

            void add(const std::string &elem, size_t nb = 1);
            void remove(const std::string &elem, size_t nb = 1);
            [[nodiscard]] bool isEmpty() const;
            [[nodiscard]] bool isEnough() const;
            [[nodiscard]] int get(const std::string &elem) const;
            [[nodiscard]] int getNeededValue(const std::string &elem) const;
            [[nodiscard]] double getTotalValue(const Inventory &inv) const;
            std::unordered_map<std::string, int>::iterator begin();
            std::unordered_map<std::string, int>::iterator end();
            std::unordered_map<std::string, int>::const_iterator begin() const;
            std::unordered_map<std::string, int>::const_iterator end() const;
        private:
            void _quantitiveFilling(std::stringstream &inv, bool food, bool players);
            double _recalculateWeight(double x) const;
        private:
            std::unordered_map<std::string, int> _inventory;
    };
}
