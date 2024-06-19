/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-clement.piasco [WSL: Ubuntu]
** File description:
** Inventory
*/

#include "Inventory.hpp"

namespace IA {

    int Inventory::get(const std::string &elem) const
    {
        return (!_inventory.contains(elem)) ? 0 : _inventory.at(elem);
    }

    std::unordered_map<std::string, int>::iterator Inventory::begin()
    {
        return _inventory.begin();
    }

    std::unordered_map<std::string, int>::iterator Inventory::end()
    {
        return _inventory.end();
    }

    std::unordered_map<std::string, int>::const_iterator Inventory::begin() const
    {
        return _inventory.begin();
    }

    std::unordered_map<std::string, int>::const_iterator Inventory::end() const
    {
        return _inventory.end();
    }

    int Inventory::getNeededValue(const std::string &elem) const
    {
        int current = get(elem);
        int needed = 0;

        if (!perfectInv.contains(elem))
            return 0;
        needed = perfectInv.at(elem);
        if (current >= needed)
            return 0;
        return needed - current;
    }

    double Inventory::getTotalValue(const Inventory &inv) const
    {
        static const std::map<std::string, double> importances = {
            {"linemate", _recalculateWeight(0.384615385)},
            {"deraumere", _recalculateWeight(0.192307692)},
            {"sibur", _recalculateWeight(0.128205128)},
            {"mendiane", _recalculateWeight(0.128205128)},
            {"phiras", _recalculateWeight(0.102564103)},
            {"thystame", _recalculateWeight(0.064102564)}
        };
        double weightedTotal = 0.0;

        for (auto &elem : _inventory) {
            int needed = inv.getNeededValue(elem.first);
            if (needed == 0)
                continue;
            int stoneAvailable = std::min(needed, elem.second);
            weightedTotal += stoneAvailable * importances.at(elem.first);
        }
        return weightedTotal;
    }

    double Inventory::_recalculateWeight(double x, double bias) const
    {
        double k = std::pow(1.0 - bias, 3);

        x = 1.0 - x;
        return (x * k) / (x * k - x + 1.0);
    }
}
