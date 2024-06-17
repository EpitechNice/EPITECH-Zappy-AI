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

    void Trantor::waitFriends()
    {
        _childsTarget = 0;
        while (_nbFriends < 10 && !_enoughfriends) {
            handleBroadcast();
            wander(true, true);
        }
        _enoughfriends = true;
        doAction("Broadcast Tous le monde est là", false);
    }

    void Trantor::wander(bool refreshLook, bool onlyFood)
    {
        static int timeWondered = 0;
        static int maxMapSize = std::max(_mapSize.first, _mapSize.second);
        timeWondered++;
        if (timeWondered > maxMapSize)
        {
            perform("Left", false);
            perform("Forward", false);
            perform("Right", false);
            timeWondered = 0;
        }
        perform("Forward", false);
        if (refreshLook)
        {
            perform("Look");
            std::string msg = "";
            while (msg.c_str()[0] != '[')
            {
                msg = _socket->receive();
            }
            _lastLooked = msg;
        }
        auto cCellStr = _lastLooked.find(",") == std::string::npos ? _lastLooked : _lastLooked.substr(0, _lastLooked.find(","));
        auto cCell = Inventory(cCellStr, true);
        _targetCell.second = cCell;
        if (onlyFood)
        {
            if (cCell.get("food"))
                pickupFood(cCell.get("food"));
        }
        else
        {
            purgeResources();
        }
    }

    bool Trantor::handleBroadcast()
    {
        bool changed = false;

        while (!_queue.empty()) {
            auto &[soudDir, msg] = _queue.back();
            _queue.pop();
            auto soundMsg = msg.c_str() + 11;
            auto messageStr = Cryptic::decrypt(std::string(soundMsg).replace(std::string(soundMsg).find("\n"), 1, ""), _teamName);
            if (messageStr.find("J'ai chope du ") != std::string::npos) {
                auto elem = messageStr.substr(14);
                _inventory.add(elem);
                if (checkAdvancement() >= 1.0)
                {
                    isFull = true;
                    return true;
                }
            } else if (messageStr.find("On a finiiii") != std::string::npos) {
                isFull = true;
                allFinished = true;
            } else if (messageStr.find("On a besoin de partisants ?") != std::string::npos) {
                if (!_forkTarget)
                {
                    perform("Broadcast Non c'est bon on est assez", false);
                }
                else
                {
                    int remains = std::min(0, 12 - (getNeededComrades() + _forkTarget));
                    remains = std::max(0, remains);
                    perform("Broadcast Bien sur que oui on a besoin de " + std::to_string(remains) + " partisants", false);
                }
            } else if (messageStr.find("On est tous làà") != std::string::npos) {
                enoughComrades = true;
            } else if (messageStr.find("Pour moi mon id max c'est ") != std::string::npos) {
                int tmpMaxInt = std::atoi(messageStr.c_str() + 26);
                if (tmpMaxInt >= _idMax)
                {
                    std::cout << "\tPrevious idmax: " << _idMax;
                    std::cout << "\tTmp idmax: " << messageStr.c_str() + 26;
                    std::cout << "\tNew idmax: " << tmpMaxInt << std::endl;
                    _idMax = tmpMaxInt;
                }
                else
                {
                    perform("Broadcast Nonon debilus l'id max est " + std::to_string(_idMax), false);
                }
            } else if (messageStr.find("Nonon debilus l'id max est ") != std::string::npos) {
                int tmpMaxInt = std::atoi(messageStr.c_str() + 27);
                _idMax = std::max(_idMax, tmpMaxInt);
            } else if (messageStr.find("Pour moi on est ") != std::string::npos) {
                auto tmpMax = messageStr.c_str() + 16;
                _nbAllies++;
                int tmpMaxInt = std::atoi(tmpMax);
                if (tmpMaxInt < _nbAllies)
                {
                    perform("Broadcast Mais bien evidemment que non toto on est " + std::to_string(_nbAllies), false);
                }
            } else if (messageStr.find("Mais bien evidemment que non toto on est ") != std::string::npos) {
                int tmpMaxInt = std::atoi(messageStr.c_str() + 41);
                _nbAllies = std::max(_nbAllies, tmpMaxInt);
            } else if (messageStr.find("Non c'est bon on est assez") != std::string::npos) {
                _forkTarget = 0;
            } else if (messageStr.find("Bien sur que oui on a besoin de ") != std::string::npos) {
                _forkTarget = std::atoi(messageStr.c_str() + 32);
            } else if (messageStr.find("Nan plus besoin dcailloux") != std::string::npos) {
                isFull = true;
            } else if (messageStr.find("On a besoin de cailloux lo ?") != std::string::npos) {
                if (isFull)
                {
                    perform("Broadcast Nan plus besoin dcailloux", false);
                }
            } else if (messageStr.find("I am here") != std::string::npos) {
                if (_idMax == _id)
                    _joinedAllies++;
            } else if (messageStr.find("Jviens de pondre") != std::string::npos) {
                _id++;
                _idMax++;
            } else if (messageStr.find("rejoignez moiiiii") != std::string::npos) {
                isFull = true;
            }
        }
        return changed;
    }
}
