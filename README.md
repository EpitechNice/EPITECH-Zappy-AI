# 🤖 Zappy AI Submodule 🤖

Welcome to the **Zappy AI** submodule! This submodule provides the artificial intelligence for the Zappy game, controlling players as they navigate the map, collect resources, and evolve.

## 📖 Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [License](#license)

## 🌟 Introduction

The Zappy AI is responsible for controlling the players in the Zappy game. It makes decisions on movement, resource collection, and evolution based on the game state.

## ✨ Features

- **Autonomous Control**: AI players make decisions independently.
- **Strategic Resource Collection**: Efficient resource gathering and management.
- **Adaptive Evolution**: AI evolves based on collected resources and game conditions.

## 🛠️ Installation

1. **Clone the Repository**:
   ```bash
   git clone git@github.com:EpitechNice/EPITECH-Zappy-AI.git zappy_ai
   cd zappy_ai
   ```

2. **Build the Project**:
   ```bash
   make
   ```

## 🚀 Usage

To launch the Zappy AI, use the following command:

```bash
./zappy_ai -p port -n name -h machine
```

### DESCRIPTION

- **-p**: Port number of the server to connect to.
- **-n**: Name of the AI player.
- **-h**: Name of the machine (server) to connect to.

### Example

```bash
./zappy_ai -p 12345 -n AI_Player -h localhost
```

This command will start the AI and connect it to the server running on `localhost` at port `12345` with the AI player named `AI_Player`.

---

Feel free to reach out for any further questions or contributions!
