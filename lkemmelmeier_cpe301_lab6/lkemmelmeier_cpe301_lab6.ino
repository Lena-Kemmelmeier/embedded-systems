// Name: Lena Kemmelmeier
// Assignment: CPE 301 1104 Lab 6
// Partner: Emma Cornia
// Date: March 20 2024 

#include <LiquidCrystal.h>
#include <Keypad.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {48, 46, 44, 42}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {40, 38, 36, 34}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

// LCD pins <--> Arduino pins
const int RS = 11, EN = 12, D4 = 2, D5 = 3, D6 = 4, D7 = 5;
int right=0,up=0;
int dir1=0,dir2=0;
byte customChar[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};

byte customChar2[8] = {
  0b00000,
  0b00000,
  0b01110,
  0b01110,
  0b01110,
  0b00000,
  0b00000,
  0b00000
};
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup()

{
  Serial.begin(9600);
  lcd.begin(16, 2); // set up number of columns and rows

  lcd.createChar(1, customChar); // create a new custom character

  lcd.setCursor(0, 0); // move cursor to (2, 0)
  lcd.write((byte)1);  // print the custom char at (2, 0)
  
  lcd.createChar(2, customChar2); // create a new custom character
  lcd.setCursor(5, 1); // move cursor to (2, 0)
  lcd.write((byte)2);  // print the custom char at (2, 0)

    lcd.setCursor(9, 1); // move cursor to (2, 0)
  lcd.write((byte)2);  // print the custom char at (2, 0)

    lcd.setCursor(6, 0); // move cursor to (2, 0)
  lcd.write((byte)2);  // print the custom char at (2, 0)
    lcd.setCursor(15, 1); // move cursor to (2, 0)
  lcd.write((byte)2);  // print the custom char at (2, 0)
  
}

int cursorX = 0; // initial x pos for heart
int cursorY = 0; // initial y pos for heart

// Positions of the square characters
const int squareX[] = {5, 9, 6, 15}; // x positions for the square characters
const int squareY[] = {1, 1, 0, 1};  // y positions for the square characters

void loop() {
  char key = keypad.getKey();

  if (key) {

    int prevX = cursorX;
    int prevY = cursorY;

    switch (key) {

      case '4': // move left
        if (cursorX > 0) {
          cursorX--;
        } 
        else {
          cursorX = 15; // wrap around to the end of the row
        }

        break;
    
      case '6': // move right
        if (cursorX < 15) {
          cursorX++;
        } 
        else {
          cursorX = 0; // wrap around to the beginning of the row
        }

        break;

      case '2': // move up
        if (cursorY > 0) {
          cursorY--;
        } 
        else {
          cursorY = 1; // wrap around to the bottom of the column
        }

        break;

      case '8': // move down
        if (cursorY < 1) {
          cursorY++;
        } 
        else {
          cursorY = 0; // wrap around to the top of the column
        }

        break;

    }

    // does the heart character's position coincides with any of the square characters' positions?
    for (int i = 0; i < sizeof(squareX) / sizeof(squareX[0]); i++) { //check the squares' positions one at a time
      if (cursorX == squareX[i] && cursorY == squareY[i]) {
        Serial.println("You scored!"); // print to serial monitor
        break;
      }
      
    }

    // clear previous position of the heart character
    lcd.setCursor(prevX, prevY);
    lcd.print(" ");

    // set cursor to new position/redraw heart
    lcd.setCursor(cursorX, cursorY);
    lcd.write((byte)1);
  }
}