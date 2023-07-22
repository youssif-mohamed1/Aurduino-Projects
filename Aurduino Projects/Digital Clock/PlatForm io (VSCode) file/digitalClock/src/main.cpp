//////////////////////////Digital Clock Using Aurduino By Youssif Mohamed//////////////////
#include <Arduino.h>

#define SEG8 6
#define SEG7 7
#define SEG6 8
#define SEG5 9
#define SEG4 10
#define SEG3 11
#define SEG2 12
#define SEG1 13
#define MODESELECTOR 5
#define TIMESELECTOR 4
#define COUNTBTN 3
#define DP 2
#define StartPause 0

int arr [4]={0},brr[4]={0},crr[4]={0}, prevStateMODE=0, prevStateTS=1,prevStateCB=1, mode=0,prevMillis = 0;

bool risingEdge(int button,int &prevState);
void showDigit(int *a,int index);
void currentClockDisplay();
void stopWatchDisplay();
void pause(int *a);
void setup(int *brr);
void timerDisplay();
void increasingDisplay(int *arr,bool set);
void decreasingDisplay(int *brr);

void setup() {
  pinMode(StartPause,INPUT_PULLUP);
  pinMode(MODESELECTOR,INPUT_PULLUP);
  pinMode(TIMESELECTOR,INPUT_PULLUP);
  pinMode(COUNTBTN,INPUT_PULLUP);
  pinMode(DP,OUTPUT);
  pinMode(SEG1,OUTPUT);
  pinMode(SEG2,OUTPUT);
  pinMode(SEG3,OUTPUT);
  pinMode(SEG4,OUTPUT);
  pinMode(SEG5,OUTPUT);
  pinMode(SEG6,OUTPUT);
  pinMode(SEG7,OUTPUT);
  pinMode(SEG8,OUTPUT);
  digitalWrite(SEG1,LOW);
  digitalWrite(SEG2,LOW);
  digitalWrite(SEG3,LOW);
  digitalWrite(SEG4,LOW);
  digitalWrite(SEG5,LOW);
  digitalWrite(SEG6,LOW);
  digitalWrite(SEG7,LOW);
  digitalWrite(SEG8,LOW);
  digitalWrite(DP,HIGH);
}

void loop() {
    if(risingEdge(MODESELECTOR,prevStateMODE)){
      mode++;
    }
    if(mode%3==1){ 
      currentClockDisplay();
    }
    if(mode%3==2){ 
      timerDisplay();
    }
    if(mode%3==0){ 
      stopWatchDisplay();
    }
    brr[0]=0; brr[1]=0; brr[2]=0; brr[3]=0;
    crr[0]=0; crr[1]=0; crr[2]=0; crr[3]=0;
}

bool risingEdge(int button,int &prevState){
  int curState=digitalRead(button);
  if(curState && !prevState){
    prevState=curState;
    return true;
  }else{
    prevState=curState;
    return false;
  }
}

void currentClockDisplay(){
  setup(arr);
  increasingDisplay(arr,false);
  }

void timerDisplay(){
    setup(brr);
    decreasingDisplay(brr);
}

void stopWatchDisplay(){
  increasingDisplay(crr,true);
}

void showDigit(int *a,int index) {
  int nanosec = a[0], sec = a[1], min = a[2], hour = a[3];
  bool segState = false;
  const int interval =60;

  for (int i = 0; i < 8; i++) {
    switch (i){
          case 0:
          digitalWrite(SEG8,LOW);
          PORTC=nanosec%10;
          break;

          case 1:
          digitalWrite(SEG7,LOW);
          PORTC=(nanosec/10)%10;
          break;

          case 2:
          PORTC=(sec)%10;
          digitalWrite(DP, HIGH);
          if(index % 6 != 1 || index==-1){
          digitalWrite(SEG6,LOW);
          }else{
              if (segState) {
                digitalWrite(SEG6, LOW);
              } else {
                digitalWrite(SEG6, HIGH);
              }
          }
          break;

          case 3:
          PORTC=(sec/10)%10;
          if(index % 6 != 2 || index==-1 ){
          digitalWrite(SEG5,LOW);
          }else{
              if (segState) {
                digitalWrite(SEG5, LOW);
              } else {
                digitalWrite(SEG5, HIGH);
              }
          }
          break;

          case 4:
          digitalWrite(DP,HIGH);
          PORTC=(min)%10;
          if(index % 6 != 3 || index==-1 ){
          digitalWrite(SEG4,LOW);
          }else{
              if (segState) {
                digitalWrite(SEG4, LOW);
              } else {
                digitalWrite(SEG4, HIGH);
              }
          }
          break;

          case 5:
          PORTC=(min/10)%10;
          if(index % 6 != 4 || index==-1 ){
          digitalWrite(SEG3,LOW);
          }else{
              if (segState) {
                digitalWrite(SEG3, LOW);
              } else {
                digitalWrite(SEG3, HIGH);
              }
          }
          break;

          case 6:
          digitalWrite(DP,HIGH);
          PORTC=(hour)%10;
          if(index % 6 != 5 || index==-1 ){
          digitalWrite(SEG2,LOW);
          }else{
              if (segState) {
                digitalWrite(SEG2, LOW);
              } else {
                digitalWrite(SEG2, HIGH);
              }
          }
          break;

          case 7:
          PORTC=(hour/10)%10;
          if(index % 6 != 0 || index==-1 ){
          digitalWrite(SEG1,LOW);
          }else{
              if (segState) {
                digitalWrite(SEG1, LOW);
              } else {
                digitalWrite(SEG1, HIGH);
              }
          }
          break;

    }

    delay(2.5);
    digitalWrite(SEG1, HIGH);
    digitalWrite(SEG2, HIGH);
    digitalWrite(SEG3, HIGH);
    digitalWrite(SEG4, HIGH);
    digitalWrite(SEG5, HIGH);
    digitalWrite(SEG6, HIGH);
    digitalWrite(SEG7, HIGH);
    digitalWrite(SEG8, HIGH);
    digitalWrite(DP, LOW);

    unsigned long currentMillis = millis();
    if (currentMillis - prevMillis >= interval) {
      prevMillis = currentMillis;
      segState = !segState; 
    }
  }
}


void pause(int *a){
  while(digitalRead(StartPause)){
    showDigit(a,-1);
    if(risingEdge(MODESELECTOR,prevStateMODE)){
        mode++;
        loop();
    }
  }
}

void setup(int *brr){
int index=0;
  while(digitalRead(StartPause)){
    showDigit(brr,index);
    if(risingEdge(TIMESELECTOR,prevStateTS)){
      index++;
    }
    if(risingEdge(COUNTBTN,prevStateCB)){
      if(index%6==0){
        brr[3]+=10;
      }else if(index%6==5){
        brr[3]++;
      }else if(index%6==4){
        brr[2]+=10;
      }else if(index%6==3){
        brr[2]++;
      }else if(index%6==2){
        brr[1]+=10;
      }else if(index%6==1){
        brr[1]++;
      }
    }
    if(risingEdge(MODESELECTOR,prevStateMODE)){
      mode++;
      loop();
    }
  }
  index=-1;
}

void increasingDisplay(int *arr,bool set){
  while(1){
    showDigit(arr,-1);
    if(arr[0]==60){
      arr[1]++;
      arr[0]=0;
    }
    if(arr[1]==60){
      arr[2]++;
      arr[1]=0;
    }
    if(arr[2]==60){
      arr[3]++;
      arr[2]=0;
    }
    if(arr[3]==24){
      arr[0]=0;
      arr[1]=0;
      arr[2]=0;
      arr[3]=0;
    }
    if(risingEdge(MODESELECTOR,prevStateMODE)){
      mode++;
      loop();
    }
    if(digitalRead(StartPause)){
      if(!set){
      setup(arr);
      }
      else{
        pause(arr);
      }
    }
    arr[0]++;
  }
}

void decreasingDisplay(int *brr){
while(1){
    showDigit(brr,-1);
    if(brr[0]==0){
      if(brr[1]>0){
        brr[1]--;
        brr[0]=59;
      }
    }
    if(brr[0]==0 && brr[1]==0){
      if(brr[2]>0){
        brr[1]=59;
        brr[0]=59;
        brr[2]--;
      }
    }
      if(brr[0]==0 && brr[1]==0 && brr[2]==0){
      if(brr[3]>0){
        brr[2]=59;
        brr[1]=59;
        brr[0]=59;
        brr[3]--;
      }
    }
    brr[0]--;
    if(brr[0]==0 && brr[1]==0 && brr[2]==0 && brr[3]==0){
      pause(brr);
      setup(brr);
    }
    if(digitalRead(StartPause)){
      setup(brr);
    }
    if(risingEdge(MODESELECTOR,prevStateMODE)){
      mode++;
      loop();
    }
  }
}