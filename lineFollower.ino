#define motorAE 3
#define motorA1 4
#define motorA2 5
#define motorBE 9
#define motorB1 7
#define motorB2 6 
#define r_sensor A0
#define m_sensor A1
#define l_sensor A2
#define MAX 90
#define kp 15
#define kd 5

int lasterror = 0;
int error = 0;

void setup() {
  pinMode(motorAE,OUTPUT);
  pinMode(motorA1,OUTPUT);
  pinMode(motorA2,OUTPUT);
  pinMode(motorBE,OUTPUT);
  pinMode(motorB1,OUTPUT);
  pinMode(motorB2,OUTPUT);
  Serial.begin(9600);
  digitalWrite(motorAE,HIGH);
  digitalWrite(motorBE,HIGH);
}

void loop() {
  followLine();
}

void followLine(){
  
  int8_t sensor_R = 0, sensor_M = 0, sensor_L = 0;
  
  sensor_R = digitalRead(r_sensor);
  sensor_M = digitalRead(m_sensor);
  sensor_L = digitalRead(l_sensor);
  lasterror = error;
  forward();
  if(sensor_R == 1 && sensor_M == 1 && sensor_L == 0){
    error = 2;
  }else if(sensor_R == 1 && sensor_M == 0 && sensor_L == 0){
    error = 1;
  }else if(sensor_R == 1 && sensor_M == 0 && sensor_L == 1){
    error = 0;
  }else if(sensor_R == 0 && sensor_M == 0 && sensor_L == 1){
    error = -1;
  }else if(sensor_R == 0 && sensor_M == 1 && sensor_L == 1){
    error = -2;
  }else{
    if(error == -2){
      right();
    }else if (error == 2){
      left();
    }else{
      stop_m();
    }
  }
  
 ////////////////////////////////  INVERTED LOGIC     MOTORA --- > right
  analogWrite(motorAE , MAX - error*kp - kd*lasterror);
  analogWrite(motorBE , MAX + error*kp + kd*lasterror);  
}


void forward(){
  digitalWrite(motorA1,HIGH);
  digitalWrite(motorA2,LOW);
  digitalWrite(motorB1,HIGH);
  digitalWrite(motorB2,LOW);
}

void backword(){
  digitalWrite(motorA1,LOW);
  digitalWrite(motorA2,HIGH);
  digitalWrite(motorB1,LOW);
  digitalWrite(motorB2,HIGH);
}

void left(){
  digitalWrite(motorA1,LOW);
  digitalWrite(motorA2,HIGH);
  digitalWrite(motorB1,HIGH);
  digitalWrite(motorB2,LOW);
}

void right(){
  digitalWrite(motorA1,HIGH);
  digitalWrite(motorA2,LOW);
  digitalWrite(motorB1,LOW);
  digitalWrite(motorB2,HIGH);
}

void stop_m(){
  digitalWrite(motorA1,LOW);
  digitalWrite(motorA2,LOW);
  digitalWrite(motorB1,LOW);
  digitalWrite(motorB2,LOW);
}




