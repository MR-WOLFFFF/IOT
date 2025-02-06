#include <Wire.h>
#include "SSD1306Wire.h"  // OLED display library
#include "pins_arduino.h"

#define WIDTH 128
#define HEIGHT 64
#define GRID_SIZE 4  // Snake moves in steps of 4 pixels
#define MAX_LENGTH 50 // Max length of the snake

SSD1306Wire display(0x3c, SDA_OLED, SCL_OLED);  // Initialize OLED display

// Snake Variables
int snakeX[MAX_LENGTH], snakeY[MAX_LENGTH];  // Store snake body positions
int snakeLength = 3;  // Initial snake length
char direction = 'R';  // Default direction (R = Right)

// Food Position
int foodX, foodY;

// Function to generate random food location
void generateFood() {
  foodX = (random(WIDTH / GRID_SIZE)) * GRID_SIZE;
  foodY = (random(HEIGHT / GRID_SIZE)) * GRID_SIZE;
}

// Function to update the snake position
void updateSnake() {
  // Move the body
  for (int i = snakeLength; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  // Move the head in the current direction
  if (direction == 'U') snakeY[0] -= GRID_SIZE;
  if (direction == 'D') snakeY[0] += GRID_SIZE;
  if (direction == 'L') snakeX[0] -= GRID_SIZE;
  if (direction == 'R') snakeX[0] += GRID_SIZE;

  // Implement wall portal effect
  if (snakeX[0] < 0) snakeX[0] = WIDTH - GRID_SIZE; // Left wall → Right portal
  if (snakeX[0] >= WIDTH) snakeX[0] = 0;            // Right wall → Left portal
  if (snakeY[0] < 0) snakeY[0] = HEIGHT - GRID_SIZE; // Top wall → Bottom portal
  if (snakeY[0] >= HEIGHT) snakeY[0] = 0;           // Bottom wall → Top portal
}

// Function to check self-collision
bool checkSelfCollision() {
  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      return true;
    }
  }
  return false;
}

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(100); }

  Serial.println("Snake Game Started! Use W (Up), A (Left), S (Down), D (Right)");

  // Power on the OLED
  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, LOW);
  pinMode(RST_OLED, OUTPUT);
  digitalWrite(RST_OLED, HIGH);
  delay(1);
  digitalWrite(RST_OLED, LOW);
  delay(1);
  digitalWrite(RST_OLED, HIGH);
  delay(1);

  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);

  // Initialize snake position
  snakeX[0] = 40; snakeY[0] = 30;
  snakeX[1] = 36; snakeY[1] = 30;
  snakeX[2] = 32; snakeY[2] = 30;

  generateFood();
}

void loop() {
  if (Serial.available()) {
    char input = Serial.read();
    input = toupper(input);  // Convert to uppercase
    
    if (input == 'W' && direction != 'D') direction = 'U';
    if (input == 'S' && direction != 'U') direction = 'D';
    if (input == 'A' && direction != 'R') direction = 'L';
    if (input == 'D' && direction != 'L') direction = 'R';
  }

  updateSnake();

  // Check if snake eats itself
  if (checkSelfCollision()) {
    Serial.println("Game Over! Restarting...");
    snakeLength = 3;
    snakeX[0] = 40; snakeY[0] = 30;
    snakeX[1] = 36; snakeY[1] = 30;
    snakeX[2] = 32; snakeY[2] = 30;
    generateFood();
    delay(1000);
  }

  // Check if food is eaten
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    if (snakeLength < MAX_LENGTH) {
      snakeLength++;
    }
    generateFood();
  }

  // Draw the game
  display.clear();

  // Draw snake
  for (int i = 0; i < snakeLength; i++) {
    display.fillRect(snakeX[i], snakeY[i], GRID_SIZE, GRID_SIZE);
  }

  // Draw food
  display.fillRect(foodX, foodY, GRID_SIZE, GRID_SIZE);

  display.display();

  delay(200);  // Adjust speed of movement
}
