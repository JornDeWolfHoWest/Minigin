# Q*bert (Minigin Engine)

Link to project: [https://github.com/JornDeWolfHoWest/Minigin.git](https://github.com/JornDeWolfHoWest/Minigin.git)

A recreation of the classic arcade game **Q*bert**, built using the custom **Minigin game engine** in C++.

---

## About the Game

Q*bert is a tile-based arcade game where the player controls a character that hops across a pyramid of cubes.  
The goal is to change all cubes to the target color while avoiding enemies and hazards.

This project recreates the core gameplay mechanics including:
- Grid-based movement on a pyramid
- Tile state changes
- Falling mechanics
- Scene-based structure using the Minigin engine

---

## Built With

- C++
- Minigin Engine
- SDL3
- GLM

---

## Gameplay

- Move Q*bert using directional input (Up, Down, Left, Right)
- Jump across the pyramid of cubes
- Change cube states by landing on them
- Fall off the pyramid if stepping into invalid space
- Winning if all cubes are changed to the target color

---

## Architecture Overview

This project is built using the Minigin ECS-style-esque architecture:

- GameObject -> container for components
- BaseComponent -> logic modules attached to objects
- SceneManager -> handles multiple scenes and switching

---

## Project Structure


/Engine -> Minigin engine source
/Game -> Q*bert game logic


---

## Key Systems

### Movement System
Uses semi-linear interpolation between walkable nodes transition between tiles.

### Scene System
Supports multiple scenes with safe switching using a deferred singleton scene manager.

### Walkable Grid
Each cube can be walked on, if you wish to walk off then that is also possible.

### Observer Pattern
Used to notify systems when movement events occur (falling, stepping, etc.).

---

## Build Instructions

### Requirements
- Visual Studio 2026 or later
- C++20 or higher
- cmake compatible build system

### Steps
1. Clone repository
2. Open solution file (`.sln`)
3. Build in Debug or Release
4. Run executable

---

## Extra

- Developed using the Minigin Engine
- Recreation of the classic arcade game Q*bert without enemies
