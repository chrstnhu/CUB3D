# cub3d 🕹️

![Demo Camagru](assets/CUB3D-visual.gif)

A **raycasting-based 3D engine** inspired by *Wolfenstein 3D*, developed in **C**

## 📋 Table of Contents  

- [About](#-about)  
- [Features](#-features)  
- [Prerequisites](#-prerequisites)  
- [Installation](#-installation)  
- [Usage](#-usage)  
- [Controls](#-controls)  
- [Map](#-map)  
- [Screenshots](#-screenshots)  
- [Contributors](#-contributors)  
- [Resources](#-resources)  

## 🎯 About  

This project implements a **raycasting rendering engine**, allowing the player to move inside a 3D world generated from a 2D map.  

**Key :**  
- 🎮 Real-time raycasting engine  
- 🧭 Smooth movement with rotation and move  
- 🏰 Custom map loading  
- 🎨 Customizable wall textures and floor/ceiling colors

## ✨ Features  

### Core Features
- **Raycasting Engine** : real-time 3D rendering from 2D maps  
- **Texturing** : load and display custom wall textures  
- **Floor & Ceiling Colors** : RGB configurable values  
- **Map Parsing** : `.cub` configuration file with textures and layout  
- **Player Navigation** : movement and rotation handling
- **Error Handling** : invalid maps, missing textures, wrong parameters, etc.

### Bonus Features
- **Wall Collision** : Collision handling
- **Rotate with mouse** : Rotate the point of view with the mouse

## 🔧 Prerequisites  

- **cc**  
- **make**  
- **MiniLibX** (included in the project)  
- **Linux**  

## 🚀 Installation  

1. **Clone the repository**  
   ```bash
   git clone git@github.com:chrstnhu/cub3d.git && cd cub3d
   ```  

2. **Compile the project**  
   ```bash
   make
   ```  

3. **Clean object files (optional)**  
   ```bash
   make clean
   ```  
4. **Compile bonus**  
   ```bash
   make bonus
   ```  
   
## 🎮 Usage  

Run the program with a `.cub` configuration file:  

```bash
./cub3d maps/example.cub
```  

**Parameters:**  
- `maps/example.cub` → path to a valid `.cub` map file  

## 🎮 Controls  

- `W / S` → move forward / backward  
- `A / D` → strafe left / right  
- `← / →` → rotate view left / right  
- `ESC` → exit game  

## 🗺️ Map  

A `.cub` map defines:  
- Textures for each direction (NO, SO, EA, WE)  
- Floor and ceiling colors in RGB format  
- Map layout with walls and player position  

**Example:**  

```
NO ./textures/wall_north.xpm
SO ./textures/wall_south.xpm
WE ./textures/wall_west.xpm
EA ./textures/wall_east.xpm

F 220,100,0
C 225,30,0

111111
100001
1000N1
100001
111111
```  

## 👥 Contributors  

[**chrhu**](https://github.com/chrstnhu) & [**xchen34**](https://github.com/xchen34)  

---  

## 📚 Resources  

- [Raycasting Tutorial - Lode Vandevenne](https://lodev.org/cgtutor/raycasting.html)  
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)  
- [Wolfenstein 3D](http://users.atw.hu/wolf3d/)  
