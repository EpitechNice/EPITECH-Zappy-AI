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
            int get(const std::string &elem) const
            {
                if (_inventory.find(elem) == _inventory.end())
                    return (0);
                return (_inventory.at(elem));
            }

            std::unordered_map<std::string, int>::iterator begin()
            {
                return (_inventory.begin());
            }

            std::unordered_map<std::string, int>::iterator end()
            {
                return (_inventory.end());
            }

            std::unordered_map<std::string, int>::const_iterator begin() const
            {
                return (_inventory.begin());
            }

            std::unordered_map<std::string, int>::const_iterator end() const
            {
                return (_inventory.end());
            }

            int getRemainingValue(const std::string &elem) const
            {
                if (!perfectInv.contains(elem))
                    return (0);
                int current = get(elem);
                int needed = perfectInv.at(elem);
                if (current >= needed)
                    return (0);
                return (needed - current);
            }

            int getNeededValue(const std::string &elem) const
            {
                if (perfectInv.find(elem) == perfectInv.end())
                    return (0);
                int current = get(elem);
                int needed = perfectInv.at(elem);
                if (current >= needed)
                    return (0);
                return (needed - current);
            }

            double getTotalValue(const Inventory &inv) const
            {
                static const std::map<std::string, double> importances = {
                    {"linemate", remap(0.384615385)},
                    {"deraumere", remap(0.192307692)},
                    {"sibur", remap(0.128205128)},
                    {"mendiane", remap(0.128205128)},
                    {"phiras", remap(0.102564103)},
                    {"thystame", remap(0.064102564)}};
                double weightedTotal = 0.0;
                for (auto &elem : _inventory)
                {
                    int needed = inv.getNeededValue(elem.first);
                    if (needed == 0)
                        continue;
                    int stoneAvailable = std::min(needed, elem.second);
                    weightedTotal += stoneAvailable * importances.at(elem.first);
                }
                return weightedTotal;
            }
        private:
            double remap(double x, double bias = 0.75) const
            {
                double k = std::pow(1.0 - bias, 3);

                x = 1.0 - x;
                return (x * k) / (x * k - x + 1.0);
            }

        private:
            std::unordered_map<std::string, int> _inventory;
    };
}