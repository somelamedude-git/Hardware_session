#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int playerRow = 0;
int obstaclePos = 15;
int obstacleRow = 0;

int score = 0;
unsigned long lastMoveTime = 0;
int gameSpeed = 200;

bool gameOver = false;
bool gameStarted = false;

int lastSpeedScore = -1;

void setup() {
  lcd.begin(16, 2);
  randomSeed(analogRead(1));
  showStartScreen();
}

void loop() {

  if(!gameStarted){
    checkStart();
    return;
  }

  if(gameOver){
    checkRestart();
    return;
  }

  readInput();

  if(millis() - lastMoveTime > gameSpeed){
    moveObstacle();
    lastMoveTime = millis();
  }

  drawFrame();
}

void showStartScreen(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME CUTIES!");
  lcd.setCursor(0, 1);
  lcd.print("Press UP to start");
}

void checkStart(){
  int x = analogRead(0);
  if(x < 200){   // UP pressed
    gameStarted = true;
    lcd.clear();
  }
}

void readInput(){
  int x = analogRead(0);

  if(x < 200 && x > 60){
    playerRow = 0;
  }
  else if(x < 400 && x > 200){
    playerRow = 1;
  }
}

void moveObstacle(){
  obstaclePos--;

  if(obstaclePos <= 0 && obstacleRow == playerRow){
    endGame();
    return;
  }

  if(obstaclePos < 0){
    obstaclePos = 15;
    obstacleRow = random(0,2);
    score++;
  }

  if(score % 5 == 0 && score != lastSpeedScore && gameSpeed > 50){
    gameSpeed -= 10;
    lastSpeedScore = score;
  }
}

void drawFrame(){
  lcd.clear();

  lcd.setCursor(0, playerRow);
  lcd.print(">");

  lcd.setCursor(obstaclePos, obstacleRow);
  lcd.print("#");

  lcd.setCursor(13, 0);
  if(obstaclePos < 12){
    lcd.print(score);
  }
}

void endGame(){
  gameOver = true;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GAME OVER!");
  lcd.setCursor(0, 1);
  lcd.print("Score: ");
  lcd.print(score);
}

void checkRestart(){
  int x = analogRead(0);

  if(x < 800 && x > 600){   
    score = 0;
    gameSpeed = 200;
    obstaclePos = 15;
    obstacleRow = 0;
    playerRow = 0;
    gameOver = false;
    gameStarted = false;
    lastSpeedScore = -1;
    showStartScreen();
  }
}
