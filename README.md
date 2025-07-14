# 🐍 Snake Game in C++ with OpenGL

This is a feature-rich Snake game built using **C++** and **OpenGL (GLUT)**. The game includes colorful levels, food and rock spawning, a leaderboard system, and pop-up messages using GLUT windows.

## 🎮 Features

- Classic Snake game mechanics with wrap-around screen edges
- Dynamic **rock spawning** as obstacles with increasing frequency over time
- Color-coded **levels** (10 unique colors) - eat your tail to advance levels
- **Star system** - complete 10 levels to earn a star and restart level progression
- Real-time **score and time tracking** with persistent high scores
- **Leaderboard system** that saves top 10 players to a `leader.txt` file
- Interactive **snake facts** displayed via pop-up windows between levels
- Pop-up **game over messages** and notifications
- **Multithreading** for timed events using `std::thread`
- Mouse-driven **menu system** for game navigation

## 🛠️ Requirements

- Windows OS (uses `<windows.h>` and `Sleep()`)
- OpenGL Utility Toolkit (GLUT)
- C++11 or higher
- Compatible compiler (e.g., MinGW, MSVC)

## 🧱 Code Structure

### Classes

- `snake` - Represents a segment of the snake with movement methods (up, down, left, right)
- `obj` - Represents the food object with position coordinates
- `rock` - Represents obstacle objects with position coordinates
- `pp` - Player profile class for leaderboard with star, level, points, time, and name fields

### Key Variables

- `a` - Main stack structure containing the snake and food
- `rocks[]` - Array of rock obstacles
- `leader[]`, `lnames[]`, `lstar[]`, `llevels[]`, `lpoints[]`, `ltime[]` - Arrays used for leaderboard management
- `levels[][]` - RGB color values for different levels
- `hints[]` - Array of snake facts displayed between levels
- `maxsize` - Maximum snake length (currently set to 6)

### Threads

- `autowalk` - Handles automatic snake movement
- `moving` - Manages food movement mechanics
- `timeee` - Updates game timer

## 🗂️ Files

- `snake_v3.cpp` - Main game logic and rendering
- `leader.txt` - Stores the leaderboard data (auto-generated)

## 📦 How to Build and Run

### Using g++ (MinGW on Windows)

```bash
g++ snake_v3.cpp -o SnakeGame -lglut32cu -lopengl32 -lglu32 -std=c++11
./SnakeGame
```

> Note: Ensure that you have installed GLUT and set up your OpenGL environment properly.

### Or use any IDE (e.g., Code::Blocks, Visual Studio) and link OpenGL & GLUT libraries.

## 📝 Leaderboard Format

Each line in `leader.txt` is structured as:

```
<username> <stars> <level> <points> <time>
```

The leaderboard is automatically sorted by:

1. Stars (descending)
2. Level (descending)
3. Points (descending)
4. Time (ascending - faster is better)

## 🎯 Game Controls

- **Arrow Keys**: Control snake movement (Up, Down, Left, Right)
- **Mouse**: Navigate main menu and interact with buttons
- **Text Input**: Enter username before starting the game

## 🎲 Game Mechanics

- **Snake Growth**: Eating food increases snake length and score
- **Level Progression**: Complete levels by eating your own tail (when length > 0)
- **Star System**: Every 10 levels completed earns you a star
- **Obstacles**: Rocks spawn over time - avoid them or game ends
- **Wrapping**: Snake wraps around screen edges for continuous play
- **Speed**: Game speed increases as you progress

## 💡 Trivia & Hints

Between levels, players receive interesting snake facts via pop-up windows:

- "Not all snakes lay eggs."
- "Snakes don't have eyelids"
- "Snakes smell with their tongues."
- "Snakes are shy, secretive animals"
- "Snakes are dichromatic"
- "Snakes are active at night"
- "Snakes are deaf to all airborne sounds"

## 🧪 Development Notes

- Rocks spawn with increasing frequency as time progresses (controlled by `rockadder` variable)
- Food spawning rate increases based on points scored (`foodjump` mechanism)
- Snake wraps around screen edges seamlessly
- Pop-up windows are separate GLUT windows triggered on game events
- Game uses a stack-based structure for snake body management
- Leaderboard sorting prioritizes stars > level > points > time (ascending)
- Color levels cycle through 10 predefined RGB values

## 🧑‍💻 Author Note

This project was made when I was still at the beginning of my programming journey.  
I didn’t use `.h` header files or split classes into multiple files simply due to lack of knowledge at the time.  
I _do_ plan to clean and improve the structure—**maybe in 5 to 10 years if I find time 😛**.

## 📌 Future Improvements (Ideas)

- Add support for music and sound effects
- Cross-platform compatibility (remove `windows.h`) no worries will I make sure it unplayable on mac 😛
- GUI menus for game settings
- Multiplayer mode or AI snakes

## 📄 License

This project is for educational and recreational use.

---

Enjoy the game and keep improving your C++/OpenGL skills! 🐍
