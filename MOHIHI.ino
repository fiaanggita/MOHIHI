#include <Servo.h>  // library Motor Servo        
#include <NewPing.h>  // library Sensor Ultrasonic   

//pin Driver L298N
const int MotorKiriMaju = 7;
const int MotorKiriMundur = 6;
const int MotorKananMaju = 4;
const int MotorKananMundur = 5;

//pin Sensor Ultrasonic
#define trig_pin 12 
#define echo_pin 13

#define maximum_distance 200
boolean maju = false;
int jarak = 100;

//fungsi sensor ultrasonic
NewPing sonar(trig_pin, echo_pin, maximum_distance); 
Servo servo_motor;


void setup(){
  pinMode(MotorKananMaju, OUTPUT);
  pinMode(MotorKiriMaju, OUTPUT);
  pinMode(MotorKiriMundur, OUTPUT);
  pinMode(MotorKananMundur, OUTPUT);
  
  servo_motor.attach(10); //pin motor servo

  servo_motor.write(115);
  delay(900);
  jarak = readPing();
  delay(100);
  jarak = readPing();
  delay(100);
  jarak = readPing();
  delay(100);
  jarak = readPing();
  delay(100);
}

void loop(){
  int jarakKanan = 0;
  int jarakKiri = 0;
  delay(50);

  if (jarak <= 20){
    Berhenti();
    delay(300);
    gerakMundur();
    delay(400);
    Berhenti();
    delay(300);
    jarakKanan = lihatKanan();
    delay(400);
    jarakKiri = lihatKiri();
    delay(400);

    if (jarak >= jarakKiri){
      belokKanan();
      Berhenti();
    }
    else{
      belokKiri();
      Berhenti();
    }
  }
  else{
    gerakMaju(); 
  }
    jarak = readPing();
}

//CodeLihatKanan
int lihatKanan(){  
  servo_motor.write(50);
  delay(500);
  int jarak = readPing();
  delay(100);
  servo_motor.write(115);
  return jarak;
}

//CodeLihatKiri
int lihatKiri(){
  servo_motor.write(170);
  delay(500);
  int jarak = readPing();
  delay(100);
  servo_motor.write(115);
  return jarak;
  delay(100);
}

//CodeJarak
int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

//CodeBerhenti
void Berhenti(){
  digitalWrite(MotorKananMaju, LOW);
  digitalWrite(MotorKiriMaju, LOW);
  digitalWrite(MotorKananMundur, LOW);
  digitalWrite(MotorKiriMundur, LOW);
}

//CodeBergerakMaju
void gerakMaju(){
  if(!maju){

    maju=true;
    
    digitalWrite(MotorKiriMaju, HIGH);
    digitalWrite(MotorKananMaju, HIGH);
  
    digitalWrite(MotorKiriMundur, LOW);
    digitalWrite(MotorKananMaju, LOW); 
  }
}

//CodeBergerak Mundur
void gerakMundur(){
  maju=false;

  digitalWrite(MotorKiriMundur, HIGH);
  digitalWrite(MotorKananMundur, HIGH);
  
  digitalWrite(MotorKiriMaju, LOW);
  digitalWrite(MotorKananMaju, LOW);
  
}

//CodeBelokKanan
void belokKanan(){
  digitalWrite(MotorKiriMaju, HIGH);
  digitalWrite(MotorKananMundur, HIGH);
  
  digitalWrite(MotorKiriMundur, LOW);
  digitalWrite(MotorKananMaju, LOW);
  
  delay(400);
  
  digitalWrite(MotorKiriMaju, HIGH);
  digitalWrite(MotorKananMaju, HIGH);
  
  digitalWrite(MotorKiriMundur, LOW);
  digitalWrite(MotorKananMundur, LOW);
  
}

//CodeBelokKiri
void belokKiri(){
  digitalWrite(MotorKiriMundur, HIGH);
  digitalWrite(MotorKananMaju, HIGH);
  
  digitalWrite(MotorKiriMaju, LOW);
  digitalWrite(MotorKananMundur, LOW);

  delay(400);
  
  digitalWrite(MotorKiriMaju, HIGH);
  digitalWrite(MotorKananMaju, HIGH);
  
  digitalWrite(MotorKiriMundur, LOW);
  digitalWrite(MotorKananMundur, LOW);
}