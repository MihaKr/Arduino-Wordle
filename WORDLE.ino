#include <Wire.h> 
#include <LiquidCrystal.h>

const int buttonPin1 = 5;    
const int buttonPin2 = 4;     
const int buttonPin3 = 3;     
const int buttonPin4 = 2;   
const int buttonPin5 = 6;     

const char chars[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','.',',','1','2','3','4','5','6','7','8','9','0','-','*','@'};//add any additional characters
char selected[16]; 
int curr[16];
char res[16];

const String words[] = {"VIN", "WORDLE", "ARDUINO", "STM32", "12345678", "TEST"};
const int num_words = 6;
  
int charindex = -1;
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;

int charsSize = 0;
int cx = 0;
int cy = 0; 
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int at = 0;

String w;

void setup() {
  randomSeed(analogRead(A0));
  w = words[random(num_words)];

  for(int i = 0; i < 16; i++) {
    selected[i] = ' ';
    curr[i] = 0;
    res[i] = ' ';
  }

  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.blink();

  Serial.begin(9600);
  Serial.print(w);


  charsSize = sizeof(chars);

  for(int i = 0; i < w.length() ; i++) {
    lcd.print("_");
  }
  
  String vmes = String(String(at) + "/5");
  
  lcd.print(" ");
  lcd.print(vmes);

  lcd.setCursor(cx, cy);
  
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);

}

void loop() {

  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  buttonState5 = digitalRead(buttonPin5);

  if (buttonState1 == HIGH) {
    charindex++;

    if(charindex == charsSize){
      charindex = 0;
    }
    lcd.print(chars[charindex]);
    selected[cx] = chars[charindex];
    curr[cx] = charindex;
    lcd.setCursor(cx, cy);
    }

  if (buttonState2 == HIGH) {
    charindex--;

    if(charindex == -1){
      charindex = 0;
    }
    lcd.print(chars[charindex]);
    selected[cx] = chars[charindex];
    curr[cx] = charindex;
    lcd.setCursor(cx, cy);
  }

  if (buttonState3 == HIGH) {
    cx++;
    charindex = curr[cx]-1;
    if(cx == w.length()){
      cx = 0;
    }
    lcd.setCursor(cx, cy);
  }

  if (buttonState4 == HIGH) {
    cx--;
    charindex = curr[cx]-1;
    if(cx == -1){
      cx = w.length() - 1;
    }
    lcd.setCursor(cx, cy);
  }

  if (buttonState5 == HIGH) {
    boolean endd = false;

     for(int i = 0; i < w.length(); i++) {
       for(int n = 0; n < sizeof(selected); n++) {
        if(w[i] == selected[n]) {
          res[n] = 'O';
          }
       }
       
      if (w[i] == selected[i]) {
        res[i] = 'C';
      } 

      else {
        if(res[i] != 'O') {
          res[i] = 'X';
        }
      }

      Serial.print(res[i]);
  
     }
    
    at++;
    lcd.clear();

    int cnt = 0;

    for(int i = 0; i < 16; i++) {
         if(selected[i] != ' ') {
         lcd.print(selected[i]);
         Serial.print(selected[i]);
         cnt++;
       }
     }

    for(int i = 0; i < w.length(); i++) {
      if(w[i] == selected[i]) {
        endd = true;
      }
      else {
        endd = false;
      }
    }

     int rem = w.length() - cnt;

     for(int i = 0; i < rem; i++) {
       lcd.print("_"); 
      }
  
     String vmes = String(String(at) + "/5");
      
     lcd.print(" ");
     lcd.print(vmes);
    
     lcd.setCursor(0, 2);
      
     
     for(int i = 0; i <  w.length(); i++) {
        lcd.print(res[i]);
      }

    if(at > 5) {
      lcd.clear();
      lcd.print("KONEC");
      lcd.setCursor(0, 2);
      lcd.print(w);
    }

    if(endd) {
      lcd.clear();
      lcd.print("BRAVO");
      lcd.setCursor(0, 2);
      lcd.print(at);
      lcd.print(" ");
      lcd.print("POSKUSOV");
    }
    
  lcd.setCursor(cx, cy);
  }

  delay(200);
}
