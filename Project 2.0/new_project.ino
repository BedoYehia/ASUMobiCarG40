#include<Servo.h>
#include<NewPing.h>

const int IN1 = 7;
const int IN2 = 6;
const int IN3 = 5;
const int IN4 = 4;
const int ENA = 9;
const int ENB = 3;
const int buzzer = 2 ;

#define trig A0
#define echo A1

void Forward(),Stop(),Backward(),Right(),Left();
int velocity,readping(),lookright(),lookleft();
char state;
float distance=100;

Servo myservo;
NewPing sonar(trig,echo,200);

void setup() {
 Serial.begin(9600);

  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  myservo.attach(10);
  
  myservo.write(68);
  delay(2000);
  distance=readping();
  delay(100);
  distance=readping();
    delay(100);
  distance=readping();
    delay(100);
  distance=readping();
}

void loop() {
  int distanceright=0;
  int distanceleft=0;
  delay(50);
  
if (Serial.available() > 0) {state = Serial.read();Serial.println(state);}


  if (state == '0'){
      velocity=0;}
    else if (state == '1'){
      velocity=100;}
    else if (state == '2'){
      velocity=150;}
    else if (state == '3'){
      velocity=200;}
    else if (state == '4'){
      velocity=255;}

    switch(state){
    case'F' : Forward(); break;
    case'B' : Backward(); break;
    case'L' : Left(); break;
    case'R' : Right(); break;
    case'S' : Stop(); break;
    case'V' : digitalWrite(buzzer, HIGH); break;
    case'U' : 
    if (distance<=15){
              Stop();
              delay(300);
              Backward();
              delay(400);
              Stop();
              delay(300);
              distanceright=lookright();
              delay(300);
              distanceleft=lookleft();
              delay(300);

              if(distance>=distanceleft){
              Right();
              Stop();
              }
              else{
              Left();
              Stop();
              }
    }
    else{
          Forward();
    }
          distance=readping();
}
}

void Stop() {
  analogWrite(ENA, LOW);
  analogWrite(ENB, LOW); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
} 
  
void Forward() {
  analogWrite(ENA, velocity);
  analogWrite(ENB, velocity); 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
}

void Backward() {
  analogWrite(ENA, velocity);
  analogWrite(ENB, velocity); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);     
}  

void Right() {
  analogWrite(ENA, velocity);
  analogWrite(ENB, velocity); 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);    
} 
 
void Left() {
  analogWrite(ENA, velocity);
  analogWrite(ENB, velocity); 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);   
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);     
}

int lookright(){
myservo.write(0);
delay(500);
int distance= readping();
delay(100);
myservo.write(68);
return distance;
delay(100);
}

int lookleft(){
myservo.write(140);
delay(500);
int distance= readping();
delay(100);
myservo.write(68);
return distance;
delay(100);
}

int readping()
{
delay(70);
int cm= sonar.ping_cm();
if(cm==0){
cm=250;
}
return cm;
}
