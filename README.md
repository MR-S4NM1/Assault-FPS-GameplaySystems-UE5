# Assault-FPS-GameplaySystems-UE5

Authors  
I. Miguel Angel Garcia Elizalde (Gameplay & AI Programmer)

---

# Overview
This repository contains a First-Person Shooter gameplay prototype developed in Unreal Engine 5 using C++.
The goal of this project is to demonstrate core gameplay programming concepts such as shooting systems, interaction, and modular gameplay architecture.

---

# Implemented Systems

# Player Movement & Input
- Movement using Enhanced Input system
- Camera control (mouse look)
- Jump functionality

# Shooting System (Hitscan)
- Shooting implemented using line traces (raycasting)
- Collision queries for hit detection
- Debug visualization for hit feedback

# Interaction System
- Interface-based interaction system (`FPSInterface`)
- Line trace detection for interactable objects
- Examples include:
  - Door interaction
  - Keypad interaction

# Pickup System
- Component-based pickup system (`PickupComponent`)
- Overlap-based interaction using collision components
- Weapon pickup implementation

# Weapon System
- Modular weapon component (`FPSWeaponComponent`)
- Basic firing logic
- Designed to support future extensions (projectile or hitscan)

---

# Architecture
The project follows a modular and component-based design:
- Separation of gameplay systems (Weapon, Interaction, Pickup)
- Use of Interfaces for decoupling gameplay logic
- Folder organization based on gameplay domains (Door, Keypad, etc.)

---

# Technical Focus
This project focuses on:
- Clean and readable C++ code
- Core gameplay systems implementation
- Understanding of Unreal Engine gameplay framework

---

# Notes
- This is a prototype project intended for technical evaluation
- Systems are intentionally simple and not production-ready
- Focus is on clarity, structure, and gameplay fundamentals

---

# Future Improvements
- Damage system integration
- Stagger / feedback systems
- Weapon variations and fire modes
- Integration with data-driven systems
