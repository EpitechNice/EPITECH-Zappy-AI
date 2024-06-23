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

    Trantor::Trantor(): _inventory(false, false), _target(0, Inventory(false, false))
    {
        size_t longestAxis = std::max(_mapSize.first, _mapSize.second);
        double diag = std::ceil(longestAxis * std::sqrt(2)) + longestAxis;

        _communication = std::make_unique<IA::Communication>(_queue);
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

    std::queue<std::pair<int, std::string>> Trantor::_removeUselessAled()
    {
        std::queue<std::pair<int, std::string>> newQueue;

        while (!_queue.empty()) {
            auto &[dir, msg] = _queue.front();
            if (msg.find("ALEEEEEEED") == std::string::npos)
                newQueue.push({dir, msg});
            _queue.pop();
        }
        return newQueue;
    }

    bool Trantor::_haveToMove(std::string &msg, int dir, char *buf)
    {
        const static std::unordered_map<int, std::pair<int, std::string>> possibleMove = {
            {1, {1, "Forward\n"}},
            {2, {1, "Forward\n"}},
            {3, {2, "Left\nForward\n"}},
            {4, {2, "Left\nForward\n"}},
            {5, {3, "Left\nLeft\nForward\n"}},
            {6, {2, "Right\nForward\n"}},
            {7, {2, "Right\nForward\n"}},
            {8, {1, "Forward\n"}}
        };
        const std::pair<int, std::string> move = possibleMove.at(dir);

        msg.clear();
        _isFull = true;
        waitOrders(msg, "ALEEEEEEED");
        sscanf(msg.c_str(), "message %d, %s\n", &dir, buf);
        if (dir == 0) {
            _inGroup = true;
            doAction("Broadcast Coucou", false);
            return true;
        }
        doAction(move.second, true, false);
        for (int i = 0; i < move.first; i++) {
            while (msg.find(OK) == std::string::npos)
                msg = _communication->receiveData(false);
            _queue = _removeUselessAled();
        }
        return false;
    }

    void Trantor::meetUp()
    {
        std::string msg = "";
        int dir = 0;
        char buffer[256] = {0};

        waitOrders(msg, "ALEEEEEEED");
        while (!_inGroup) {
            sscanf(msg.c_str(), "message %d, %s\n", &dir, buffer);
            if (dir == 0) {
                _inGroup = true;
                doAction("Broadcast Coucou", false);
            } else if (_haveToMove(msg, dir, buffer))
                break;
            waitOrders(msg, "ALEEEEEEED");
        }
    }

    int Trantor::_makeChoice(std::vector<std::pair<int, Inventory>> &res)
    {
        auto to_remove = std::remove_if(res.begin(), res.end(), [this](const auto &a)
            {
                return a.second.getTotalValue(_inventory) <= 0.0001 || a.first == 0;
            }
        );
        res.erase(to_remove, res.end());
        if (res.size() == 0)
            return 0;
        std::sort(res.begin(), res.end(), [this](const auto &a, const auto &b)
            {
                return a.second.getTotalValue(_inventory) > b.second.getTotalValue(_inventory);
            }
        );
        _target = res.front();
        return 1;
    }

    int Trantor::_howMany()
    {
        std::string response;
        std::regex regex("player");
        std::smatch match;

        doAction("Look");
        do
            response = _communication->receiveData(true, 256);
        while (response == OK);
        for (int i = 0; i < 2; i++)
            response = response.substr(response.find(","));
        std::regex_search(response, match, regex);
        return match.size();
    }

    int Trantor::updateObjectives()
    {
        static const std::regex regex = std::regex("([A-Za-z ]+(?= |,))|(?=,[ ]*,)");

        doAction("Look");
        std::string msg = _communication->receiveData(true, 256);
        _worldInfo = msg;
        std::smatch match;
        std::vector<std::pair<int, Inventory>> res;
        int i = 0;
        while (std::regex_search(msg, match, regex)) {
            res.emplace_back(std::pair(i, Inventory(match[1], true, false)));
            if (match[1].length()) {
                msg = match.suffix();
            } else {
                msg = msg.c_str() + 1;
            }
            i++;
        }
        return _makeChoice(res);
    }

    std::pair<int, Inventory> Trantor::getTarget() const
    {
        return _target;
    }

    void Trantor::harvest(Trantor &trantor)
    {
        trantor.doAction("Broadcast Faut loot un truc ?", false);
        while (!trantor._isFull) {
            trantor.handleBroadcast();
            if (trantor.updateObjectives() == 0) {
                trantor.wander(false, false);
            } else {
                trantor.goToTarget();
                trantor.getItems();
            }
            trantor.handleBroadcast();
        }
    }

    void Trantor::groupTrantor(Trantor &trantor)
    {
        while (true) {
            if (trantor._idMax == trantor._id) {
                trantor.doAction("Broadcast ALEEEEEEED", false);
                while (trantor._communication->nbBytesToRead() > 0)
                    (void)trantor._communication->receiveData(true, 0);
                trantor.handleBroadcast();
                if (trantor._onSamePlace >= trantor._nbFriends)
                    break;
            } else
                trantor.meetUp();
        }
        trantor.dropAll("");
    }

    int Trantor::getNbFriends() const
    {
        return _nbFriends + 1;
    }

    void Trantor::join(const std::string &team)
    {
        std::string data = _communication->receiveData(true, 256);

        if (data != JOIN_GAME)
            throw TrantorException("Invalid server response");
        _team = team;
        doAction(_team);
        data = _communication->receiveData(true, 256);
        while (data == KO) {
            doAction(team);
            data = _communication->receiveData(true, 256);
            sleep(1);
        }
        _id = std::stoi(data);
        _maxSlots = _id;
        _idMax = _id;
        data = _communication->receiveData(true, 256);
        if (data.find(' ') == std::string::npos)
            throw TrantorException("Invalid map size format");
        if (sscanf(data.c_str(), "%zu %zu", &_mapSize.first, &_mapSize.second) != 2)
            throw TrantorException("Invalid map size format");
        doAction("Broadcast Je suis seul", false);
        doAction("Broadcast Mon ID max est " + std::to_string(_id), false);
    }

    void Trantor::_fillMoves(std::list<std::string> &res, int &currentX, int &currentY)
    {
        currentX = currentX < 0 ? -currentX : currentX;

        for (int i = 0; i < currentY; i++)
            res.push_back("Forward");
        if (currentX) {
            if (currentX < 0)
                res.push_back("Left");
            else
                res.push_back("Right");
        }
        for (int i = 0; i < currentX; i++)
            res.push_back("Forward");
    }

    void Trantor::_applyMove(std::list<std::string> &moves, const double nbSteps, int allMovesNb)
    {
        int nbMoves = 0;

        for (int i = 0; i < nbSteps; i++) {
            nbMoves = std::min(10, allMovesNb);
            for (int i = 0; i < nbMoves; i++) {
                doAction(moves.front());
                allMovesNb--;
                moves.pop_front();
            }
            for (int i = 0; i < nbMoves; i++)
                std::string msg = _communication->receiveData(true, 256);
        }
    }

    void Trantor::dropAll(std::string inv)
    {
        Inventory newInv(inv, false, false);

        if (inv == "") {
            doAction("Inventory");
            inv = _communication->receiveData(true, 256);
        }
        if (newInv.isEmpty())
            return;
        for (auto const &[name, nb] : newInv) {
            if (name == "food")
                continue;
            for (int i = 0; i < nb; i++) {
                doAction("Set " + name);
                std::string msg = _communication->receiveData(true, 256);
                if (msg == OK)
                    _inventory.remove(name);
            }
        }
    }

    bool Trantor::hasEnoughTicks() const
    {
        return _ticks >= _maxTicksNeeded;
    }

    bool Trantor::checkFull() const
    {
        return _inventory.isEnough();
    }

    bool Trantor::tryBirth(bool &finished)
    {
        if (_childsTarget == 0) {
            finished = false;
            return finished;
        }
        doAction("Fork");
        std::string msg = _communication->receiveData(true, 256);
        if (msg == OK) {
            _nbChilds++;
            _ticks -= 42;
            _childsTarget--;
            doAction("Broadcast J'ai fais un enfant", false);
            return true;
        }
        return false;
    }

    void Trantor::goToTarget()
    {
        int tmpI = _target.first, offset = 1, currentX = -1, currentY = 1;
        std::list<std::string> moves;

        while (tmpI) {
            if (currentX >= offset) {
                offset++;
                currentY++;
                currentX = -offset;
            } else {
                currentX++;
            }
            tmpI--;
        }
        _fillMoves(moves, currentX, currentY);
        int allMovesNb = currentX + currentY + (currentX > 0);
        double nbSteps = std::ceil(allMovesNb / 10.0);
        _applyMove(moves, nbSteps, allMovesNb);
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
        auto doing = costs.find(actionName);

        if (doing != costs.end()) {
            _ticks -= doing->second;
        }
        if (actionName == "Broadcast") {
            std::string data = action.substr(action.find(' ') + 1);
            _communication->sendData(actionName + " " + data + (useBackslashN ? "\n" : ""));
        } else {
            _communication->sendData(action + (useBackslashN ? "\n" : ""));
        }
        if (ignoreResp)
            return;
        (void)_communication->receiveData(true, 5);
    }

    void Trantor::waitOrders(std::string &msg, const std::string &waitingFor)
    {
        std::string str = "";
        std::string parsedMsg = "";

        while (parsedMsg.find(waitingFor) == std::string::npos) {
            str = _communication->receiveData(false);
            parsedMsg = str;
            if (str.find("message") != std::string::npos) {
                parsedMsg = str.substr(11);
                parsedMsg.erase(std::remove(parsedMsg.begin(), parsedMsg.end(), '\n'), parsedMsg.end());
            }
        }
        msg = msg.substr(0, msg.find(",")) + " " + parsedMsg;
    }

    void Trantor::waitFriends()
    {
        _childsTarget = 0;
        while (_nbFriends < 10 && !_enoughFriends) {
            handleBroadcast();
            wander(true, true);
        }
        _enoughFriends = true;
        doAction("Broadcast Tous le monde est là", false);
    }

    void Trantor::findGuard()
    {
        const int player = _howMany();

        if (player == 0) {
            doAction("Forward");
            (void)_communication->receiveData(false);
        } else {
            doAction("Left");
            (void)_communication->receiveData(false);
            findGuard();
        }
    }

    void Trantor::getFood(int nbFood)
    {
        int neededTicks = _maxTicksNeeded - _ticks;
        int nb = std::ceil(nbFood / 10.0);
        int nbStep = 0;

        if (_ticks >= _maxTicksNeeded)
            return;
        if (nbFood * 126 > neededTicks)
            nbFood = std::ceil(neededTicks / 126.0);
        for (int i = 0; i < nb; i++) {
            nbStep = std::min(10, nbFood);
            for (int i = 0; i < nbStep; i++) {
                doAction("Take food");
                nbFood--;
            }
            for (int i = 0; i < nbStep; i++) {
                std::string msg = _communication->receiveData(true, 256);
                if (msg == OK) {
                    _inventory.add("food");
                    _ticks += 126;
                }
            }
        }
    }

    void Trantor::setTick(const int tick)
    {
        _ticks = tick;
    }

    int Trantor::getTicks() const
    {
        return _ticks;
    }

    int Trantor::getNbrOfItemsNeeded(const std::string &itemName, int available) const
    {
        int needed = _inventory.getNeededValue(itemName);

        if (available == 0)
            return 0;
        return std::min(needed, available);
    }

    void Trantor::getItems()
    {
        getFood(_target.second.get("food"));
        for (auto &elem : _inventory) {
            int elemToGet = getNbrOfItemsNeeded(elem.first, _target.second.get(elem.first));
            for (int i = 0; i < elemToGet; i++) {
                doAction("Take " + elem.first);
                auto msg = _communication->receiveData(true, 256);
                if (msg == OK) {
                    _inventory.add(elem.first);
                    doAction("Broadcast J'ai loot du " + elem.first, false);
                    if (progressionPercentage() >= 1.0) {
                        _isFull = true;
                        return;
                    }
                }
            }
        }
    }

    void Trantor::_manageObjective(bool eat)
    {
        std::string str = _worldInfo.find(",") == std::string::npos ? _worldInfo : _worldInfo.substr(0, _worldInfo.find(","));
        Inventory cellInventory = Inventory(str, true, false);

        _target.second = cellInventory;
        if (eat) {
            if (cellInventory.get("food"))
                getFood(cellInventory.get("food"));
        } else {
            getItems();
        }
    }

    void Trantor::wander(bool refreshWorld, bool eat)
    {
        static int time = 0;
        static int longextAxis = std::max(_mapSize.first, _mapSize.second);
        std::string msg = "";

        time++;
        if (time > longextAxis) {
            doAction("Left", false);
            doAction("Forward", false);
            doAction("Right", false);
            time = 0;
        }
        doAction("Forward", false);
        if (refreshWorld) {
            doAction("Look");
            while (msg[0] != '[')
                msg = _communication->receiveData(true, 256);
            _worldInfo = msg;
        }
        _manageObjective(eat);
    }

    double Trantor::progressionPercentage() const
    {
        double totalPercent = 0.0;
        int nbItems = 0;

        for (auto const &[key, value]: _inventory) {
            if (key == "food" || perfectInv.find(key) == perfectInv.end())
                continue;
            int total = perfectInv.at(key);
            int current = std::min(value, total);
            totalPercent += current / total;
            nbItems++;
        }
        return totalPercent / nbItems;
    }

    bool Trantor::handleBroadcast()
    {
        static const std::unordered_map<std::string, std::function<void(const std::string &msg)>> actions = {
            {"Travail terminéééé", [this](UNUSED const std::string &msg)
                {
                   _isFull = true;
                   _isRetired = true;
                }
            },
            {"Faut faire des gosses ?", [this](UNUSED const std::string &msg)
                {
                    if (!_childsTarget) {
                        doAction("Broadcast C'est bon on a les allocs !", false);
                    } else {
                        int remains = std::min(0, 12 - (11 - _maxSlots + _childsTarget));
                        remains = std::max(0, remains);
                        doAction("Broadcast Toujours plus il manque " + std::to_string(remains) + " gosses !", false);
                    }
                }
            },
            {"Tous le monde est là", [this](UNUSED const std::string &msg)
                {
                    _enoughFriends = true;
                }
            },
            {"Mon ID max est ", [this](const std::string &msg)
                {
                    int tmpMaxInt = std::atoi(msg.c_str() + 15);

                    if (tmpMaxInt >= _idMax) {
                        _idMax = tmpMaxInt;
                    } else {
                        doAction("Broadcast T'es tarpin con c'est " + std::to_string(_idMax), false);
                    }
                }
            },
            {"T'es tarpin con c'est ", [this](const std::string &msg)
                {
                    int tmpMaxInt = std::atoi(msg.c_str() + 22);

                    _idMax = std::max(_idMax, tmpMaxInt);
                }
            },
            {"Je suis seul", [this](UNUSED const std::string &msg)
                {
                    _nbFriends++;
                    if (_nbFriends > 1) {
                        doAction("Broadcast Tu dis du n'importe quoi on est " + std::to_string(_nbFriends), false);
                    }
                }
            },
            {"Tu dis du n'importe quoi on est ", [this](const std::string &msg)
                {
                    size_t tmp = std::atoi(msg.c_str() + 32);

                    _nbFriends = std::max(_nbFriends, tmp);
                }
            },
            {"C'est bon on a les allocs !", [this](UNUSED const std::string &msg)
                {
                    _childsTarget = 0;
                }
            },
            {"Toujours plus il manque ", [this](const std::string &msg)
                {
                    _childsTarget = std::atoi(msg.c_str() + 24);
                }
            },
            {"J'ai loot du ", [this](const std::string &msg)
                {
                    std::string elem = msg.substr(13);

                    _inventory.add(elem);
                    if (progressionPercentage() >= 1.0) {
                        _isFull = true;
                    }
                }
            },
            {"On a ce qui faut", [this](UNUSED const std::string &msg)
                {
                    _isFull = true;
                }
            },
            {"Faut loot un truc ?", [this](UNUSED const std::string &msg)
                {
                    if (_isFull) {
                        doAction("Broadcast On a ce qui faut", false);
                    }
                }
            },
            {"Coucou", [this](UNUSED const std::string &msg)
                {
                    if (_idMax == _id)
                        _onSamePlace++;
                }
            },
            {"J'ai fais un enfant", [this](UNUSED const std::string &msg)
                {
                    _id++;
                    _idMax++;
                }
            },
            {"ALEEEEEEED", [this](UNUSED const std::string &msg)
                {
                    _isFull = true;
                }
            }
        };

        while (!_queue.empty()) {
            auto &[soudDir, msg] = _queue.back();
            _queue.pop();
            std::string message = msg.replace(msg.find('\n'), 1, "").c_str() + 11;
            if (message.find("J'ai loot du ") != std::string::npos) {
                std::string elem = message.substr(13);
                _inventory.add(elem);
                if (progressionPercentage() >= 1.0)
                {
                    _isFull = true;
                    return true;
                }
            } else {
                for (auto const &[key, action] : actions)
                    if (message.find(key) != std::string::npos)
                        action(message);
            }
        }
        return false;
    }
}
