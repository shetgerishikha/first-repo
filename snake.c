#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <stdbool.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 20
#define NUM_COLORS 6
const char *colors[NUM_COLORS] = {"\033[0;31m", "\033[0;32m", "\033[0;33m", "\033[0;34m", "\033[0;35m", "\033[0;36m"};
int colorIndex = 0;
#define RESET_COLOR "\033[0m"

// Game variables
int gameOver;
int x, y;           // Snake head coordinates
int fruitX, fruitY; // Fruit coordinates
int score;
int tailX[100], tailY[100]; // Snake tail coordinates
int nTail;          // Length of tail
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum Direction dir;

// Function declarations
void Setup();
void Draw();
void Input();
void Logic();
void ClearScreen();
char GetKey();

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        usleep(100000); // Control game speed (100ms)
    }
    return 0;
}

void Setup() {
    gameOver = false;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    srand(time(NULL));
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
}

void ClearScreen() {
    printf("\033[H\033[J");
}

void Draw() {
    ClearScreen();
    
    // Draw top wall
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    // Draw game area
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("#");
            
            if (i == y && j == x)
                printf("%sO%s", colors[colorIndex], RESET_COLOR); // Snake head
            else if (i == fruitY && j == fruitX)
                printf("F"); // Fruit
            else {
                bool printTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("%so%s", colors[colorIndex], RESET_COLOR); // Snake tail
                        printTail = true;
                    }
                }
                if (!printTail)
                    printf(" ");
            }

            if (j == WIDTH - 1)
                printf("#");
        }
        printf("\n");
    }

    // Draw bottom wall
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    // Display score
    printf("Score: %d\n", score);
    printf("Controls: ↑ (up), ← (left), ↓ (down), → (right), X (exit)\n");
}

char GetKey() {
    char c;
    struct termios oldt, newt;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    c = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    return c;
}

void Input() {
    char key = GetKey();
    if (key == '\033') { // Escape sequence
        GetKey(); // Skip '['
        key = GetKey(); // Get the actual key
        switch (key) {
            case 'A': // Up arrow
                if (dir != DOWN) dir = UP;
                break;
            case 'B': // Down arrow
                if (dir != UP) dir = DOWN;
                break;
            case 'C': // Right arrow
                if (dir != LEFT) dir = RIGHT;
                break;
            case 'D': // Left arrow
                if (dir != RIGHT) dir = LEFT;
                break;
        }
    } else if (key == 'x' || key == 'X') {
        gameOver = true;
    }
}

void Logic() {
    // Save previous tail positions
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    // Update tail positions
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Move snake head
    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }

    // Wall collision
    if (x >= WIDTH) x = 0;
    else if (x < 0) x = WIDTH - 1;
    if (y >= HEIGHT) y = 0;
    else if (y < 0) y = HEIGHT - 1;

    // Self collision
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    // Fruit collision
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++;
        colorIndex = (colorIndex + 1) % NUM_COLORS; // Change color
    }
} 