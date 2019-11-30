int up[][8]={
  {1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1},
  {1,1,1,0,0,1,1,1},
  {1,1,0,0,0,0,1,1},
  {1,0,0,1,1,0,0,1},
  {0,0,1,1,1,1,0,0},
  {0,1,1,1,1,1,1,0}
};
int down[][8]={
  {0,1,1,1,1,1,1,0},
  {0,0,1,1,1,1,0,0},
  {1,0,0,1,1,0,0,1},
  {1,1,0,0,0,0,1,1},
  {1,1,1,0,0,1,1,1},
  {1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1}
};
int temp_arr[8]={};

int nums[][8]={
  {1,1,1,1,1,1,0,0},//0
  {0,1,1,0,0,0,0,0},//1
  {1,1,0,1,1,0,1,0},//2
  {1,1,1,1,0,0,1,0},//3
  {0,1,1,0,0,1,1,0},//4
  {1,0,1,1,0,1,1,0},//5
  {1,0,1,1,1,1,1,0},//6
  {1,1,1,0,0,0,0,0},//7
  {1,1,1,1,1,1,1,0},//8
  {1,1,1,1,0,1,1,0} //9
};
int sw[2] = {12,13};
// 도트 매트릭스 핀 설정
int row_pins[8]={30,31,32,33,34,35,36,37};
int col_pins[8]={40,41,42,43,44,45,46,47};

// 7_segment 핀 설정
int sel_pins[2] = {22,23};
int seg_pins[8] = {4,5,6,7,8,9,10,11};
int flr[2] = {0,8};  //1~10

// click event 처리를 위한 변수
int cur[2]={0}, prev[2]={0};

int t=0, a=0;
void setup() {
  for(int i=0;i<2;i++) pinMode(sw[i],INPUT);
  for(int i=0;i<8;i++) pinMode(seg_pins[i],OUTPUT);
  for(int i=0;i<8;i++) pinMode(row_pins[i],OUTPUT);
  for(int i=0;i<8;i++) pinMode(col_pins[i],OUTPUT);
  for(int i=0;i<2;i++) pinMode(sel_pins[i],OUTPUT);
    
  for(int i=0;i<8;i++) digitalWrite(seg_pins[i],LOW);
  for(int i=0;i<8;i++) digitalWrite(row_pins[i],LOW);
  for(int i=0;i<8;i++) digitalWrite(col_pins[i],HIGH);
  for(int i=0;i<2;i++) digitalWrite(sel_pins[i],HIGH);

}
void loop() {
  prev[0] = cur[0];
  prev[1] = cur[1];
  cur[0]=digitalRead(sw[0]);
  cur[1]=digitalRead(sw[1]);
  if(click(cur[0],prev[0])){    
    printUpDot();
    goUp();
  }
  if(click(cur[1],prev[1])){    
    printDownDot();
    goDown();
  }
  printFloor();
}
void printUpDot(){
  int i, j;
  int mov=0;
  for(int k=0;k<25;k++){
    for(i=0;i<8;i++){
      digitalWrite(row_pins[i], HIGH);
      for(j=0;j<8;j++){
        digitalWrite(col_pins[j],up[i][j]);
      }
      delay(1);
      digitalWrite(row_pins[i],LOW);
    }
    for(i=0;i<8;i++){
      temp_arr[i] = up[0][i];
    }
    for(i=0;i<7;i++){
      for(j=0;j<8;j++){
        up[i][j] = up[i+1][j];
      }
    }
    for(i=0;i<8;i++){
      up[7][i] = temp_arr[i];
    }
    delay(250);
    mov++;
    if(mov==8) return;
  }  
}
void printDownDot(){
  int i, j; 
  int mov=0;
  for(int k=0;k<25;k++){
    for(i=0;i<8;i++){
      digitalWrite(row_pins[i], HIGH);
      for(j=0;j<8;j++){
        digitalWrite(col_pins[j],down[i][j]);
      }
      delay(1);
      digitalWrite(row_pins[i],LOW);
    }
    for(i=0;i<8;i++){
      temp_arr[i] = down[7][i];
    }
    for(i=7;i>=0;i--){
      for(j=0;j<8;j++){
        down[i][j] = down[i-1][j];
      }
    }
    for(i=0;i<8;i++){
      down[0][i] = temp_arr[i];
    }
    delay(250);
    mov++;
    if(mov==8) return;
  }  
}
int click(int cur,int prev){
  if(cur==0 && prev == 1) return 1;
  return 0;
}
void goUp(){
  if(flr[0]==1) return;  
  else if(flr[1]+1 == 10) {
    flr[0]++;
    flr[1]=0;
    return ;
  }
  flr[1]++;  
  
}
void goDown(){
  if(flr[0]==0 && flr[1]==1) return;
  else if(flr[0]==1){
    flr[0]=0;
    flr[1]=9;
    return;
  }
  else if((flr[0]-1) != 0){
    flr[1]--;    
  }  
}
void printFloor(){
   for(int i=0;i<2;i++){    
    digitalWrite(sel_pins[i],LOW);
    for(int j=0;j<8;j++){
      if(flr[0]==0) digitalWrite(seg_pins[j],nums[flr[1-i]][j]);
      else if(flr[0]==1) {
        if(i==0) digitalWrite(seg_pins[j],nums[i][j]);
        if(i==1) digitalWrite(seg_pins[j],nums[i][j]);       
      }
    }
    delayMicroseconds(2500);
    digitalWrite(sel_pins[i],HIGH);
  }
}
