//Libraries 
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Shifter.h>

#define SER_Pin 8 //SER_IN 14 on 74HC595
#define RCLK_Pin 9 //L_CLOCK 12 on 74HC595
#define SRCLK_Pin 10 //CLOCK 11 on 74HC595
#define NUM_REGISTERS 2 //how many registers are in the chain
//initaize shifter using the Shifter library
Shifter shifter(SER_Pin, RCLK_Pin, SRCLK_Pin, NUM_REGISTERS); 
 
LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Set the LCD I2C address

const int SourceButtonPin = 2;
int SourceButtonPinState = 0;
const int RecButtonPin = 3;
int RecButtonPinState = 0;
const int MuteButtonPin = 4;
int MuteButtonPinState = 0;
int RelaySource = 1;
int RelayRec = 1;
int RelayMute = 1;

byte inp[8] = {
  B00000,
  B00000,
  B01100,
  B10010,
  B10010,
  B01100,
  B00000,
  B00000
  };

byte inps[8] = {
B00000,
  B00000,
  B01100,
  B11110,
  B11110,
  B01100,
  B00000,
  B00000
};

byte mut[8] = {
  B00001,
  B00011,
  B00111,
  B11111,
  B11111,
  B00111,
  B00011,
  B00001
};


byte outp[8] = {
  B00000,
  B00100,
  B00110,
  B11111,
  B11111,
  B00110,
  B00100,
  B00000
};

byte upp[8] = {
  0b00000,
  0b00100,
  0b01110,
  0b11111,
  0b00100,
  0b00100,
  0b00100,
  0b00100
};

byte inpp[8] {
  0b00000,
  0b00100,
  0b01100,
  0b11111,
  0b11111,
  0b01100,
  0b00100,
  0b00000
};

void setup() {    

  lcd.begin(16,2);
  lcd.backlight();
  lcd.createChar(1, inp);
  lcd.createChar(2, inps);
  lcd.createChar(3, mut);
  lcd.createChar(4,outp);
  lcd.createChar(5, upp);
  lcd.createChar(6, inpp);
  pinMode(SourceButtonPin, INPUT); 
  pinMode(MuteButtonPin, INPUT);
  pinMode(RecButtonPin, INPUT);
  
  pinMode(13, OUTPUT);
 
  lcd.setCursor(0,0);
  lcd.print(" Audio Selector");
  lcd.setCursor(0,1);
  lcd.print(" V18.05.202001");
  delay(3000);
  lcd.clear(); 
}
 
void loop() {

 // shifter.clear(); //set all pins on the shift register chain to LOW
  shifter.write(); //send changes to the chain and display them
  //check button states
  RecButtonPinState = digitalRead(RecButtonPin);
  SourceButtonPinState = digitalRead(SourceButtonPin);
  MuteButtonPinState = digitalRead(MuteButtonPin);
   
  if(RecButtonPinState == HIGH) {
    RelayRec = RelayRec + 1;
  }
  if(RelayRec > 8) {  //put a max of 3 for relay number
    RelayRec = 1;
  }
  if(RelayRec < 1) {  //put a min of 1 for relay number
    RelayRec = 8;
  }

  if(SourceButtonPinState == HIGH) {
    RelaySource = RelaySource + 1;
  }
  if(RelaySource > 8) {  //put a max of 3 for relay number
    RelaySource = 1;
  }
  if(RelaySource < 1) {  //put a min of 1 for relay number
    RelaySource = 8;
  }

  if(MuteButtonPinState == HIGH) {
    RelayMute = RelayMute + 1;

  }
  if(RelayMute > 2) {  //put a max of 3 for relay number
    RelayMute = 1;
  }
  if(RelayMute < 1) {  //put a min of 1 for relay number
    RelayMute = 2;
  } 

  //check relay number and activate outputs according to number
  
if(RelaySource == 1) {
  shifter.setPin(0, HIGH); //set pin 1 in the chain(second pin) HIGH
  shifter.setPin(1, LOW);
  shifter.setPin(2, LOW);
  shifter.setPin(3, LOW);
  shifter.setPin(4, LOW);
  shifter.setPin(5, LOW);
  shifter.setPin(6, LOW);
  shifter.setPin(7, LOW);
  shifter.write();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write(4);
  lcd.setCursor(2,0);
  lcd.print("AUX 1");
  }

  if(RelaySource == 2) {
 shifter.setPin(0, LOW); //set pin 1 in the chain(second pin) HIGH
  shifter.setPin(1, HIGH);
  shifter.setPin(2, LOW);
  shifter.setPin(3, LOW);
  shifter.setPin(4, LOW);
  shifter.setPin(5, LOW);
  shifter.setPin(6, LOW);
  shifter.setPin(7, LOW);
  shifter.write();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write(4);
  lcd.setCursor(2,0);  
  lcd.print("AUX 2");
  }
   
   
if(RelaySource == 3) {
shifter.setPin(0, LOW); //set pin 1 in the chain(second pin) HIGH
  shifter.setPin(1, LOW);
  shifter.setPin(2, HIGH);
  shifter.setPin(3, LOW);
  shifter.setPin(4, LOW);
  shifter.setPin(5, LOW);
  shifter.setPin(6, LOW);
  shifter.setPin(6, LOW);
  shifter.write();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write(4);
  lcd.setCursor(2,0);
  lcd.print("CD 1");
  }
  
  
  if(RelaySource == 4) {
 
  shifter.setPin(0, LOW); //set pin 1 in the chain(second pin) HIGH
  shifter.setPin(1, LOW);
  shifter.setPin(2, LOW);
  shifter.setPin(3, HIGH);
  shifter.setPin(4, LOW);
  shifter.setPin(5, LOW);
  shifter.setPin(6, LOW);
  shifter.setPin(6, LOW);
  shifter.write();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write(4);
  lcd.setCursor(2,0);
  lcd.print("CD 2");
  }
   
  if(RelaySource == 5) {
  shifter.setPin(0, LOW); //set pin 1 in the chain(second pin) HIGH
  shifter.setPin(1, LOW);
  shifter.setPin(2, LOW);
  shifter.setPin(3, LOW);
  shifter.setPin(4, HIGH);
  shifter.setPin(5, LOW);
  shifter.setPin(6, LOW);
  shifter.setPin(7, LOW);
  shifter.write();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write(4);
  lcd.setCursor(2,0);
  lcd.print("Tape 1");
  }
   
  if(RelaySource == 6) {
  shifter.setPin(0, LOW); //set pin 1 in the chain(second pin) HIGH
  shifter.setPin(1, LOW);
  shifter.setPin(2, LOW);
  shifter.setPin(3, LOW);
  shifter.setPin(4, LOW);
  shifter.setPin(5, HIGH);
  shifter.setPin(6, LOW);
  shifter.setPin(7, LOW);
  shifter.write();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write(4);
  lcd.setCursor(2,0);
  lcd.print("Tape 2/DCC");;
  }
 
  if(RelaySource == 7) {
  shifter.setPin(0, LOW); //set pin 1 in the chain(second pin) HIGH
  shifter.setPin(1, LOW);
  shifter.setPin(2, LOW);
  shifter.setPin(3, LOW);
  shifter.setPin(4, LOW);
  shifter.setPin(5, LOW);
  shifter.setPin(6, HIGH);
  shifter.setPin(7, LOW);
  shifter.write();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write(4);
  lcd.setCursor(2,0);
  lcd.print("Tape 3/DAT");
  }
 
  if(RelaySource == 8) {
  shifter.setPin(0, LOW); //set pin 1 in the chain(second pin) HIGH
  shifter.setPin(1, LOW);
  shifter.setPin(2, LOW);
  shifter.setPin(3, LOW);
  shifter.setPin(4, LOW);
  shifter.setPin(5, LOW);
  shifter.setPin(6, LOW);
  shifter.setPin(7, HIGH);
  shifter.write();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write(4);
  lcd.setCursor(2,0);
  lcd.print("MD");
  }

if(RelayRec == 1) {
  lcd.setCursor(0,1);
  lcd.write(6);
  lcd.setCursor(2,1);
  lcd.print("AUX 1");
  shifter.setPin(8, HIGH); 
  shifter.setPin(9, LOW);
  shifter.setPin(10, LOW); 
  shifter.setPin(11, LOW);
  shifter.setPin(12, LOW);
  shifter.setPin(13, LOW); 
  shifter.setPin(14, LOW);
  shifter.setPin(15, LOW);
  shifter.write();
  }
  
if(RelayRec == 2) {
  lcd.setCursor(0,1);
  lcd.write(6);
  lcd.setCursor(2,1);
  lcd.print("AUX 2");
  shifter.setPin(8, LOW); 
  shifter.setPin(9, HIGH);
  shifter.setPin(10, LOW); 
  shifter.setPin(11, LOW);
  shifter.setPin(12, LOW);
  shifter.setPin(13, LOW); 
  shifter.setPin(14, LOW);
  shifter.setPin(15, LOW);
  shifter.write();
  }
  
if(RelayRec == 3) {
  lcd.setCursor(0,1);
  lcd.write(6);
  lcd.setCursor(2,1);
  lcd.print("CD 1");
  shifter.setPin(8, LOW); 
  shifter.setPin(9, LOW);
  shifter.setPin(10, HIGH); 
  shifter.setPin(11, LOW);
  shifter.setPin(12, LOW);
  shifter.setPin(13, LOW); 
  shifter.setPin(14, LOW);
  shifter.setPin(15, LOW);
  shifter.write();
  }

if(RelayRec == 4) {
  lcd.setCursor(0,1);
  lcd.write(6);
  lcd.setCursor(2,1);
  lcd.print("CD 2");
  shifter.setPin(8, LOW); 
  shifter.setPin(9, LOW);
  shifter.setPin(10, LOW); 
  shifter.setPin(11, HIGH);
  shifter.setPin(12, LOW);
  shifter.setPin(13, LOW); 
  shifter.setPin(14, LOW);
  shifter.setPin(15, LOW);
  shifter.write();
  }

  if(RelayRec == 5) {
  lcd.setCursor(0,1);
  lcd.write(6);
  lcd.setCursor(2,1);
  lcd.print("Tape 1-2,3");
  shifter.setPin(8, LOW); 
  shifter.setPin(9, LOW);
  shifter.setPin(10, LOW); 
  shifter.setPin(11, LOW);
  shifter.setPin(12, HIGH);
  shifter.setPin(13, LOW); 
  shifter.setPin(14, LOW);
  shifter.setPin(15, LOW);
  shifter.write();
  }

if(RelayRec == 6) {
  lcd.setCursor(0,1);
  lcd.write(6);
  lcd.setCursor(2,1);
  lcd.print("Tape 2-1,3");
  shifter.setPin(8, LOW); 
  shifter.setPin(9, LOW);
  shifter.setPin(10, LOW); 
  shifter.setPin(11, LOW);
  shifter.setPin(12, LOW);
  shifter.setPin(13, HIGH); 
  shifter.setPin(14, LOW);
  shifter.setPin(15, LOW);
  shifter.write();
  }

if(RelayRec == 7) {
  lcd.setCursor(0,1);
  lcd.write(6);
  lcd.setCursor(2,1);
  lcd.print("Tape 3-1,2");
  shifter.setPin(8, LOW); 
  shifter.setPin(9, LOW);
  shifter.setPin(10, LOW); 
  shifter.setPin(11, LOW);
  shifter.setPin(12, LOW);
  shifter.setPin(13, LOW); 
  shifter.setPin(14, HIGH);
  shifter.setPin(15, LOW);
  shifter.write();
  }

if(RelayRec == 8) {
  lcd.setCursor(0,1);
  lcd.write(6);
  lcd.setCursor(2,1);
  lcd.print("MD");
  shifter.setPin(8, LOW); 
  shifter.setPin(9, LOW);
  shifter.setPin(10, LOW); 
  shifter.setPin(11, LOW);
  shifter.setPin(12, LOW);
  shifter.setPin(13, LOW); 
  shifter.setPin(14, LOW);
  shifter.setPin(15, HIGH);
  shifter.write();
  }

if(RelayMute == 1) {
  digitalWrite(13, LOW);
  lcd.setCursor(12,1);
  lcd.print("");
  }
  
if(RelayMute == 2) {
  digitalWrite(13, HIGH);
  lcd.setCursor(14,1);
  lcd.write(3);
  lcd.setCursor(15,1);
  lcd.print("X");
  }
 
 delay(150);
   
}
