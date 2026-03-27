# 🎮 First-Person Movement System (C++ / raylib)

## 📌 Overview
This project implements a custom first-person player controller using **raylib**.  
It focuses on smooth, responsive movement with advanced mechanics like sprinting, sliding, air control, and camera effects.

The goal is to build a **clean, extensible FPS movement system** from scratch.

---

## 🚀 Features

### 🎯 Core Movement
- WASD movement (forward, backward, strafing)
- Mouse-based camera look (yaw + pitch)
- Ground and air acceleration
- Friction-based stopping
- Speed clamping

### 🏃 Sprint System
- Hold **Shift** to sprint
- Dynamic max speed switching (walk vs sprint)

### 🪂 Air Control
- Controlled mid-air movement
- Directional influence based on current velocity
- Prevents unrealistic speed gain

### 🧗 Jump System
- Space to jump
- Gravity-based falling
- Ground detection

### 🛷 Sliding Mechanic
- Press **C** to slide
- Speed-based activation
- Direction locking during slide
- Reduced friction while sliding
- Smooth camera height drop during slide

### 🎥 Camera System
- First-person camera with:
  - Smooth mouse look
  - Stable target (no WASD interference)
  - Head bob (movement-based)
  - Dynamic FOV (speed-based)
  - Slide height effect

---

## 🧠 Technical Highlights

- Separation of:
  - **Movement logic (yaw-based)**
  - **Camera direction (yaw + pitch)**
- Stable camera system:
  - Visual effects (bob, slide) do NOT affect aim
- Frame-rate independent movement using `dt`
- Modular structure for easy expansion

---

## 📂 Project Structure

```
project/
│
├── main.cpp          # Entry point (game loop)
├── player.h          # Player struct and function declarations
├── player.cpp        # Movement + camera logic
│
├── assets/           # (Optional) textures, models, etc.
│
└── README.md         # Project documentation
```

---

## ⚙️ Controls

| Key        | Action              |
|-----------|-------------------|
| W A S D   | Movement           |
| Mouse     | Look around        |
| Shift     | Sprint             |
| Space     | Jump               |
| C         | Slide              |

---

## 🛠️ Current Limitations

- No collision system (only ground plane)
- No animations (camera-only effects)
- No crouch/lean system yet
- No weapon or interaction system

---

## 🔮 Future Improvements

- Crouching system
- Leaning (Q/E)
- Weapon system (shooting mechanics)
- Advanced camera smoothing
- Sound effects (footsteps, slide)
- Collision with environment
- Multiplayer support (long-term)

---

## 🧪 Build & Run

Make sure you have **raylib installed**.

### Compile (example with g++)
```
g++ main.cpp player.cpp -o game -lraylib -lopengl32 -lgdi32 -lwinmm
```

### Run
```
./game
```

---

## 💡 Notes

This project is designed as a **learning-focused implementation**, emphasizing:
- Clean logic
- Understandable structure
- Incremental feature building

---

## 👤 Author

Built by **Fantum**

---

## ⭐ Acknowledgment

Inspired by classic FPS movement systems and modern game feel design.
