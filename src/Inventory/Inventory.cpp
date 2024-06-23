/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-clement.piasco [WSL: Ubuntu]
** File description:
** Inventory
*/

#include "Inventory.hpp"

namespace IA {

    Inventory::Inventory(bool food, bool players)
    {
        _inventory["linemate"] = 0;
        _inventory["deraumere"] = 0;
        _inventory["sibur"] = 0;
        _inventory["mendiane"] = 0;
        if (food)
            _inventory["food"] = 0;
        _inventory["phiras"] = 0;
        _inventory["thystame"] = 0;
        if (players)
            _inventory["player"] = 0;
    }

    Inventory::Inventory(std::string inv, bool food, bool players)
    {
        if (inv.size() <= 2)
            return;
        inv.erase(std::remove_if(inv.begin(), inv.end(),
            [](char c)
            {
                return c == '[' || c == ']';
            }), inv.end());
        std::stringstream ss(inv);
        if (inv.find_first_of("0123456789") != std::string::npos) {
            _quantitiveFilling(ss, food, players);
            return;
        }
        std::string str;
        while (std::getline(ss, str, ' ')) {
            if (perfectInv.find(str) != perfectInv.end())
                _inventory[str] += 1;
            if (food && str == "food")
                _inventory[str] += 1;
            if (players && str == "player")
                _inventory[str] += 1;
        }
    }

    void Inventory::_quantitiveFilling(std::stringstream &inv, bool food, bool players)
    {
        std::string str;

        while (std::getline(inv, str, ',')) {
            if (str.size() < 2)
                continue;
            Utils::trim(str);
            std::string elem = str.substr(0, str.find(' '));
            int value = std::stoi(str.substr(str.find(' ') + 1));
            if (perfectInv.contains(elem))
                _inventory[elem] = value;
            if (food && elem == "food")
                _inventory[elem] = value;
            if (players && elem == "player")
                _inventory[elem] = value;
        }
    }

    void Inventory::add(const std::string &elem, size_t nb)
    {
        if (!_inventory.contains(elem) && elem != "food" && elem != "player")
            return;
        _inventory[elem] += nb;
    }

    void Inventory::remove(const std::string &elem, size_t nb)
    {
        if (_inventory[elem] >= nb)
            _inventory[elem] -= nb;
    }

    bool Inventory::isEmpty() const
    {
        for (auto &[name, nb] : _inventory) {
            if (nb > 0)
                return false;
        }
        return true;
    }

    bool Inventory::isEnough() const
    {
        for (auto &[name, nb] : perfectInv) {
            if (!_inventory.contains(name))
                return false;
            if (_inventory.at(name) < nb)
                return false;
        }
        return true;
    }

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
        int res = 0;

        if (!perfectInv.contains(elem))
            return 0;
        res = perfectInv.at(elem) - get(elem);
        return res < 0 ? 0 : res;
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
        double weight = 0.0;

        for (auto &elem : _inventory) {
            int needed = inv.getNeededValue(elem.first);
            if (needed == 0)
                continue;
            int stoneAvailable = std::min(needed, elem.second);
            weight += stoneAvailable * importances.at(elem.first);
        }
        return weight;
    }

    double Inventory::_recalculateWeight(double x) const
    {
        double k = std::pow(0.25, 3);
        double l = 1.0 - x;

        return (l * k) / (l * k - l + 1.0);
    }
}
