/*
** EPITECH PROJECT, 2024
** B-YEP-400-NCE-4-1-zappy-clement.piasco [WSL: Ubuntu]
** File description:
** Trantor
*/

#include "Trantor.hpp"

namespace IA {

    Trantor::TrantorException::TrantorException(const std::string &message) : _message(message)
    {
    }

    const char *Trantor::TrantorException::what() const noexcept
    {
        return _message.c_str();
    }

    Trantor::Trantor()
    {
        size_t longestAxis = std::max(_mapSize.first, _mapSize.second);
        double diag = std::ceil(longestAxis * std::sqrt(2)) + longestAxis;

        _communication = std::make_unique<IA::Communication>();
        _maxTicksNeeded = 2520 + diag * 7;
    }

    void Trantor::clearQueue()
    {
        while (!_queue.empty())
            _queue.pop();
    }

    void Trantor::connectToServer(const std::string &ip, const int port)
    {
        _communication->connectToServer(ip, port);
    }

    void Trantor::join(const std::string &team)
    {
        std::string data = _communication->receiveData();

        if (data != JOIN_GAME)
            throw TrantorException("Invalid server response");
        _team = team;
        doAction(_team);
        data = _communication->receiveData();
        while (data == KO) {
            doAction(team);
            data = _communication->receiveData();
            sleep(1);
        }
        _id = std::stoi(data);
        _maxSlots = _id;
        _idMax = _id;
        data = _communication->receiveData();
        if (data.find(' ') == std::string::npos)
            throw TrantorException("Invalid map size format");
        if (sscanf(data.c_str(), "%zu %zu", &_mapSize.first, &_mapSize.second) != 2)
            throw TrantorException("Invalid map size format");
        doAction("Broadcast Je suis seul", false);
        doAction("Broadcast Mon ID max est " + std::to_string(_id), false);
    }

    void Trantor::doAction(const std::string &action, bool ignoreResp, bool useBackslashN)
    {
        static const std::map<std::string, int> costs = {
            {"Forward", 7},
            {"Right", 7},
            {"Left", 7},
            {"Look", 7},
            {"Inventory", 1},
            {"Broadcast", 7},
            {"Connect_nbr", 0},
            {"Fork", 42},
            {"Eject", 7},
            {"Take", 7},
            {"Set", 7},
            {"Incantation", 300}
        };
        std::string actionName = action.substr(0, action.find(' '));
        auto performedAction = costs.find(actionName);

        if (performedAction != costs.end()) {
            _ticks -= performedAction->second;
        }
        if (actionName == "Broadcast") {
            std::string data = action.substr(action.find(' ') + 1);
            _communication->sendData(actionName + " " + data + (useBackslashN ? "\n" : ""));
        } else {
            _communication->sendData(action + (useBackslashN ? "\n" : ""));
        }
        if (ignoreResp)
            return;
        (void)_communication->receiveData();
    }
}
