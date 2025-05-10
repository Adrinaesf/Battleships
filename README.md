# 🛳️ Battleship Game

A simplified one-player Battleship game implemented in C. 

## 💡 Key Features
- Represented ships using a custom `struct ship` with fields for name, symbol, orientation, position, length, and hit tracking
- Used **pointer-based interfaces** (`struct ship *`) to pass and mutate ship data efficiently within modular functions
- Modeled a 10×10 game board as a **1D `char` array**, accessed through both **pointer arithmetic** and **array indexing** (depending on function constraints)
- Implemented functions for:
  - Reading structured input with `scanf`
  - Placing ships with validation (no overlap, fits in grid)
  - Simulating gameplay via hit/miss logic and tracking when ships are sunk
- Operated under strict constraints: certain functions required **exclusive use of pointer arithmetic** or **array notation**, enforcing precision in memory access

## 🧠 Concepts Practiced
- Pointers and memory dereferencing
- Struct design and field access (`->`)
- 2D grid simulation using 1D arrays
- Terminal I/O with `scanf` and `printf`
- Defensive programming and modular design
