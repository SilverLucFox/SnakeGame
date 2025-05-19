# 🐍 Snake Game in C++ with OpenGL

This is a feature-rich Snake game built using **C++** and **OpenGL (GLUT)**. The game includes colorful levels, food and rock spawning, a leaderboard system, and pop-up messages using GLUT windows.

## 🎮 Features

- Classic Snake game mechanics
- Dynamic **rock spawning** as obstacles
- Color-coded **levels** eat your tail to increase a level
- Real-time **score and time tracking**
- **Leaderboard system** that saves top players to a `leader.txt` file
- Fun **facts** about snakes between levels
- Pop-up **game over messages**
- **Multithreading** for timed events using `std::thread`

## 🛠️ Requirements

- Windows OS (uses `<windows.h>` and `Sleep()`)
- OpenGL Utility Toolkit (GLUT)
- C++11 or higher
- Compatible compiler (e.g., MinGW, MSVC)

## 🧱 Code Structure

### Classes

- `snake` - Represents a segment of the snake
- `obj` - Represents the food
- `rock` - Represents obstacles
- `pp` - Player profile for leaderboard

### Key Variables

- `a` - Main stack structure containing the snake and food
- `rocks[]` - Array of rocks
- `leader[]`, `lnames[]`, etc. - Arrays used for leaderboard management

### Threads

- `autowalk`, `moving`, `timeee` - Handle food movement and timer updates

## 🗂️ Files

- `main.cpp` - Game logic and rendering
- `leader.txt` - Stores the leaderboard data (auto-generated)

## 📦 How to Build and Run

### Using g++ (MinGW on Windows)

```bash
g++ main.cpp -o SnakeGame -lglut32cu -lopengl32 -lglu32 -std=c++11
./SnakeGame
```

> Note: Ensure that you have installed GLUT and set up your OpenGL environment properly.

### Or use any IDE (e.g., Code::Blocks, Visual Studio) and link OpenGL & GLUT libraries.

## 📝 Leaderboard Format

Each line in `leader.txt` is structured as:

```
<username> <stars> <level> <points> <time>
```

This is parsed and sorted based on star count, level, points, and time.

## 💡 Trivia & Hints

Between levels, players receive interesting snake facts to make gameplay fun and informative.

## 🧪 Development Notes

- Rocks are added with increasing frequency as time progresses.
- Food appears at random positions every few seconds.
- Snake wraps around screen edges.
- Popups are separate GLUT windows triggered on events.

## 🧑‍💻 Author Note

This project was made when I was still at the beginning of my programming journey.  
I didn’t use `.h` header files or split classes into multiple files simply due to lack of knowledge at the time.  
I *do* plan to clean and improve the structure—**maybe in 5 to 10 years if I find time 😛**.

## 📌 Future Improvements (Ideas)

- Add support for music and sound effects
- Cross-platform compatibility (remove `windows.h`) no worries will I make sure it unplayable on mac 😛
- GUI menus for game settings
- Multiplayer mode or AI snakes

## 📄 License

This project is for educational and recreational use.

---

Enjoy the game and keep improving your C++/OpenGL skills! 🐍
