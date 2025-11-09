#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Game variables
    int gameOver = 0;
    int score = 0;
    
    // Snake position
    int snakeX = 10;
    int snakeY = 5;
    
    // Fruit position
    int fruitX = 5;
    int fruitY = 3;
    
    // Snake direction (1=up, 2=down, 3=left, 4=right)
    int direction = 4;
    
    // Game area size
    int width = 20;
    int height = 10;
    
    // Snake tail
    int tailX[100], tailY[100];
    int tailLength = 0;
    
    printf("=== SIMPLE SNAKE GAME ===\n");
    printf("Controls: W=Up, S=Down, A=Left, D=Right\n");
    printf("Snake moves automatically and grows when eating fruit!\n");
    printf("Press 'x' to quit\n");
    printf("Press Enter to start...");
    getchar();
    
    // Main game loop
    while(!gameOver) {
        // Clear screen
        system("clear");
        
        // Draw top border
        for(int i = 0; i < width + 2; i++) {
            printf("#");
        }
        printf("\n");
        
        // Draw game area
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                // Draw left border
                if(x == 0) {
                    printf("#");
                }
                
                // Draw snake head
                if(x == snakeX && y == snakeY) {
                    printf("O");
                }
                // Draw fruit
                else if(x == fruitX && y == fruitY) {
                    printf("F");
                }
                // Draw snake tail or empty space
                else {
                    int isTail = 0;
                    for(int i = 0; i < tailLength; i++) {
                        if(tailX[i] == x && tailY[i] == y) {
                            printf("o");
                            isTail = 1;
                        }
                    }
                    if(!isTail) {
                        printf(" ");
                    }
                }
                
                // Draw right border
                if(x == width - 1) {
                    printf("#");
                }
            }
            printf("\n");
        }
        
        // Draw bottom border
        for(int i = 0; i < width + 2; i++) {
            printf("#");
        }
        printf("\n");
        
        printf("Score: %d\n", score);
        printf("Snake Length: %d\n", tailLength + 1);
        printf("Press WASD to change direction, X to quit\n");
        
        // Check for input WITHOUT stopping (simple method)
        system("/bin/stty raw");  // Make terminal read keys immediately
        char input = ' ';
        if(read(STDIN_FILENO, &input, 1) > 0) {
            if(input == 'w' || input == 'W') {
                if(direction != 2) direction = 1; // Up
            }
            else if(input == 's' || input == 'S') {
                if(direction != 1) direction = 2; // Down
            }
            else if(input == 'a' || input == 'A') {
                if(direction != 4) direction = 3; // Left
            }
            else if(input == 'd' || input == 'D') {
                if(direction != 3) direction = 4; // Right
            }
            else if(input == 'x' || input == 'X') {
                gameOver = 1;
            }
        }
        system("/bin/stty cooked");  // Return terminal to normal
        
        // Move snake tail
        if(tailLength > 0) {
            // Shift all tail positions forward
            for(int i = tailLength - 1; i > 0; i--) {
                tailX[i] = tailX[i - 1];
                tailY[i] = tailY[i - 1];
            }
            // First tail segment follows head
            tailX[0] = snakeX;
            tailY[0] = snakeY;
        }
        
        // Move snake head based on direction
        if(direction == 1) {
            snakeY--; // Move up
        }
        else if(direction == 2) {
            snakeY++; // Move down
        }
        else if(direction == 3) {
            snakeX--; // Move left
        }
        else if(direction == 4) {
            snakeX++; // Move right
        }
        
        // Check if snake ate fruit
        if(snakeX == fruitX && snakeY == fruitY) {
            score += 10;
            tailLength++; // Snake grows!
            
            // Move fruit to new random position
            fruitX = rand() % width;
            fruitY = rand() % height;
        }
        
        // Check wall collision (wrap around)
        if(snakeX >= width) snakeX = 0;
        if(snakeX < 0) snakeX = width - 1;
        if(snakeY >= height) snakeY = 0;
        if(snakeY < 0) snakeY = height - 1;
        
        // Check self collision (game over if hit own tail)
        for(int i = 0; i < tailLength; i++) {
            if(tailX[i] == snakeX && tailY[i] == snakeY) {
                gameOver = 1;
            }
        }
        
        // Slow down the game (automatic movement)
        usleep(200000); // 200ms delay
    }
    
    system("clear");
    printf("=== GAME OVER ===\n");
    printf("Final Score: %d\n", score);
    printf("Final Snake Length: %d\n", tailLength + 1);
    printf("Thanks for playing!\n");
    
    return 0;
}