# Colorful Snake Game

A classic Snake game implementation in C with colorful graphics and smooth controls. The game features a dynamic color-changing snake that changes its color each time it eats a fruit.

## Author
- **Shikha Shetgeri** ([@shetgerishikha](https://github.com/shetgerishikha))

## Features

- 🎮 Intuitive arrow key controls
- 🎨 Dynamic color-changing snake (6 different colors)
- 🍎 Random fruit generation
- 📊 Score tracking
- 🎯 Collision detection (walls and self)
- 🏃 Smooth snake movement
- 🎯 Wrap-around walls (snake can pass through walls)

## Controls

- ↑ (Up Arrow): Move Up
- ↓ (Down Arrow): Move Down
- ← (Left Arrow): Move Left
- → (Right Arrow): Move Right
- X: Exit Game

## Game Elements

- O: Snake Head
- o: Snake Body
- F: Fruit
- #: Walls

## How to Play

1. Compile the game:
   ```bash
   gcc snake.c -o snake
   ```

2. Run the game:
   ```bash
   ./snake
   ```

3. Use arrow keys to control the snake
4. Eat fruits to grow longer and increase your score
5. Avoid hitting yourself
6. Press 'X' to exit the game

## Requirements

- C compiler (gcc)
- Unix-like terminal (macOS/Linux)
- Terminal that supports ANSI color codes

## Game Rules

- Each fruit eaten increases your score by 10 points
- The snake grows longer with each fruit eaten
- The snake changes color with each fruit eaten
- Game ends if the snake hits itself
- Snake can pass through walls and appear on the opposite side

## Technical Details

- Written in C
- Uses ANSI escape codes for colors and screen manipulation
- Implements non-blocking keyboard input
- Terminal-based graphics
