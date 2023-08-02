#include <Arduino.h>
#include<liquidCrystal.h>

#define SETUP 3
#define rs 13 
#define en 12
#define d4 7
#define d5 6
#define d6 5
#define d7 4
#define s1 8
#define s2 9
#define REDLED 2
#define GREENLED 10
#define YELLOWLED 11
#define fpi0(n) for(int i=0;i<n;i++)
#define fpj0(n) for(int j=0;j<n;j++)

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int cnt=60,def=60;

void pause();
void set();
void showDigit();

void setup() {
  for(int i=2;i<11;i++){
    if(i==2 || i==3)
      pinMode(i,INPUT_PULLUP);
    else
      pinMode(i,OUTPUT);
  }
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A7,INPUT);
  lcd.begin(16,2);
  attachInterrupt(digitalPinToInterrupt(SETUP),set,FALLING);
  digitalWrite(YELLOWLED,HIGH);
  digitalWrite(REDLED,LOW);
  digitalWrite(GREENLED,LOW);
}

void loop() {
  digitalWrite(REDLED,LOW);
  digitalWrite(YELLOWLED,HIGH);
  delay(5000);
  digitalWrite(YELLOWLED,LOW);
  digitalWrite(GREENLED,HIGH);
  lcd.print("Cars");
  pause();
  lcd.clear();
  digitalWrite(GREENLED,LOW);
  digitalWrite(YELLOWLED,HIGH);
  delay(5000);
  digitalWrite(YELLOWLED,LOW);
  digitalWrite(REDLED,HIGH);
  lcd.print("Passangers");
  pause();
}

void set(){
  if(cnt>30)
    cnt=30,
    def=30;
  else
    cnt=60,
    def=30;
  showDigit();
}

void showDigit(){
  fpi0(90){
    fpj0(2){
      if(j)
          PORTC=cnt/10,          
          digitalWrite(s1,HIGH);
      else
          PORTC=cnt%10,
          digitalWrite(s2,HIGH);
        delay(5); 
        digitalWrite(s1,LOW);
        digitalWrite(s2,LOW);
      }
    if(i%10==0)
      lcd.scrollDisplayRight();
  }
}

void pause(){
  while(cnt>0){
  cnt--;
  showDigit();
  }
  cnt=def;
}