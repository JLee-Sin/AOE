#include <Servo.h>

#define servo_1_pin 2
#define servo_2_pin 3
#define servo_3_pin 4
#define servo_4_pin 5
#define servo_5_pin 6
int sensor_1_pin = A0;
int sensor_2_pin = A1;
int sensor_3_pin = A2;
int sensor_4_pin = A3;
int sensor_5_pin = A4;
#define power_pin 7
#define reset_pin 8

Servo s1;
Servo s2;
Servo s3;
Servo s4;
Servo s5;

boolean started = false;

void setup() {
  Serial.begin(9600);
  s1.attach(servo_1_pin);
  s2.attach(servo_2_pin);
  s3.attach(servo_3_pin);
  s4.attach(servo_4_pin);
  s5.attach(servo_5_pin);
  pinMode(sensor_1_pin, INPUT);
  pinMode(sensor_2_pin, INPUT);
  pinMode(sensor_3_pin, INPUT);
  pinMode(sensor_4_pin, INPUT);
  pinMode(sensor_5_pin, INPUT);
  pinMode(power_pin, INPUT);
  while(!started) {
    if(digitalRead(power_pin) == HIGH) {
      started = true;
      Serial.println("started");
    }
  }
  Servo servos[5] = {s1, s2, s3, s4, s5};
  for(int i = 0; i < 5; i++) {
    servos[i].write(0);
    delay(15);
  }
  reset();
  Serial.println("finished setup");
}

//implement reset pin
void loop() {
  level_1();
  reset();
}

void reset() {
  Servo servos[5] = {s1, s2, s3, s4, s5};
  for(int i = 0; i < 5; i++) {
    sweep(servos[i]);
  }
  Serial.println("reset complete");
}

void sweep(Servo servo) {
  for(int i = 0; i <= 180; i++) {
    servo.write(i);
    delay(10);
  }
  for(int i = 180; i >= 0; i--) {
    servo.write(i);
    delay(10);
  }
  for(int i = 0; i < 90; i++) {
    servo.write(i);
    delay(10);
  }
}

void level_1(){
  Serial.println("starting level 1");
  bool playing = true;
  bool triggered[5] = {false, false, false, false, false}; 
  while(playing) {
    if(analogRead(sensor_1_pin)  < 930 && triggered[0] == false) {
      s1.write(0);
      delay(15);
      triggered[0] = true;
      Serial.println("1 triggered");
    }
     if(analogRead(sensor_2_pin) < 930 && triggered[1] == false) {
      s2.write(0);
      triggered[1] = true;
      Serial.println("2 triggered");
    }
     if(analogRead(sensor_3_pin) < 930 && triggered[2] == false) {
      s3.write(0);
      triggered[2] = true;
      Serial.println("3 triggered");
    }
     if(analogRead(sensor_4_pin) < 930 && triggered[3] == false) {
      s4.write(0);
      triggered[3] = true;
      Serial.println("4 triggered");
    }
     if(analogRead(sensor_5_pin) < 930 && triggered[4] == false) {
      s5.write(0);
      triggered[4] = true;
      Serial.println("5 triggered");
    }
    if(triggered[0] && triggered[1] && triggered[2] && triggered[3] && triggered[4]) {
      playing = false;
      Serial.println("level complete");
    }
    if(digitalRead(power_pin) == HIGH || digitalRead(reset_pin) == HIGH) {
      Serial.println("manual reset activated");
      playing = false;
    }
  }
}
