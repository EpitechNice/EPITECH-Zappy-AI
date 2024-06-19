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
            Inventory(bool includeFood = false, bool includePlayers = false);
            Inventory(const std::string &inv, bool includeFood = false, bool includePlayers = false);
            ~Inventory() = default;

            void add(const std::string &item, int nb = 1);
            int get(const std::string &elem) const;
            std::unordered_map<std::string, int>::iterator begin();
            std::unordered_map<std::string, int>::iterator end();
            std::unordered_map<std::string, int>::const_iterator begin() const;
            std::unordered_map<std::string, int>::const_iterator end() const;
            int getNeededValue(const std::string &elem) const;
            double getTotalValue(const Inventory &inv) const;
        private:
            double _recalculateWeight(double x, double bias = 0.75) const;
        private:
            std::unordered_map<std::string, int> _inventory;
    };
}
