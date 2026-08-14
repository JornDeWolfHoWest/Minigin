# Bubble Bobble (Minigin Engine)

Link to project: [https://github.com/JornDeWolfHoWest/Minigin.git](https://github.com/JornDeWolfHoWest/Minigin.git)

A recreation of the classic arcade game **Bubble Bobble**, built using the custom **Minigin game engine** in C++.

---

## About the Game

Bubble Bobble is a tile-based arcade game where the player controls a character that can hop up and down, move left and right and blow bubbles.  
the goal is to blow bubbles onto the enemies and trap them, then pop the bubbles to defeat the enemies. The game is played on a grid of platforms, and the player must navigate through the levels while avoiding enemies and obstacles.

This project recreates some of the core gameplay mechanics of Bubble Bobble, including movement, jumping, and bubble-blowing.
Such as:
Jumping between platforms, and falling off the platforms if the player steps into invalid space. The game is won by changing all the platforms to a target state.

---

## Built With

- C++
- Minigin Engine
- SDL3
- GLM

---

## Gameplay

Use the arrow keys to move, up to jump and space to shoot

use the D-PAD to move, A to jump and B to shoot


---

## Architecture Overview

This project is built using the Minigin ECS-style-esque architecture:

- GameObject -> container for components
- BaseComponent -> logic modules attached to objects
- SceneManager -> handles multiple scenes and switching
- Using Unique_ptr for memory management and ownership of components and game objects

---

## Project Structure


/Engine -> Minigin engine source
/Game -> Bubble Bobble game logic


---

## Key Systems

### Movement System
Uses semi-linear interpolation between walkable nodes transition between tiles.

### Scene System
Supports multiple scenes with safe switching using a deferred singleton scene manager.

### Walkable Grid
Each cube can be walked on, if you wish to walk off then that is also possible. you will fall and get an animation

### Observer Pattern
Used to notify systems when movement events occur (touching enemy, etc.).

### State pattern
Using states and a state pattern system for the animations & movement of enemy & bubble

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
- Recreation of the classic NES game Bubble Bobble with one enemy