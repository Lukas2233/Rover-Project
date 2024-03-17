#include <util/atomic.h> // For the ATOMIC_BLOCK macro
#include <Servo.h>

// Front left motor
#define ENCA_FL 2 // Interrupt pin
#define ENCB_FL 51
#define PWM_FL 10
#define IN2_FL 40
#define IN1_FL 41

// Middle left motor
#define ENCA_ML 20 // Interrupt pin
#define ENCB_ML 23
#define PWM_ML 8
#define IN2_ML 53
#define IN1_ML 52

//Define servos
Servo servo_fl;
Servo servo_ml;
Servo servo_bl;
Servo servo_fr;
Servo servo_mr;
Servo servo_br;


volatile int posi = 0; // specify posi as volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
long prevT = 0;
float eprev = 0;
float eintegral = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ENCA_FL, INPUT);
  pinMode(ENCB_FL, INPUT);
  
  pinMode(PWM_FL, OUTPUT);
  pinMode(IN1_FL, OUTPUT);
  pinMode(IN2_FL, OUTPUT);
  
  pinMode(ENCA_ML, INPUT);
  pinMode(ENCB_ML, INPUT);

  pinMode(PWM_ML, OUTPUT);
  pinMode(IN1_ML, OUTPUT);
  pinMode(IN2_ML, OUTPUT);
  
servo_fl.attach(31);
servo_ml.attach(33);
servo_bl.attach(32);
servo_fr.attach(28);
servo_mr.attach(29);
servo_br.attach(30);



  Serial.println("target pos");
}

void loop() {
  // Check if there's serial data available
  if (Serial.available() > 0) {
    // Read the incoming byte
    char incomingByte = Serial.read();
    // If the incoming byte is 'w', run the motor clockwise
    if (incomingByte == 'w') {
      clockwise();
    }
    // If the incoming byte is 's', run the motor counter-clockwise
    else if (incomingByte == 's') {
      counterClockwise();
    }
    // If the incoming byte is 'h', stop the motor
    else if (incomingByte == 'h') {
      stopMotor();
    }
    // If the incoming byte is 'd', turn right 45 degrees
    else if (incomingByte == 'l') {
      turnRight();
    }
    // If the incoming byte is 'j', turn left 45 degrees
    else if (incomingByte == 'j') {
      turnLeft();
    }
    // If the incoming byte is 'k', center
    else if (incomingByte == 'k') {
      center();
    }
  }
}

void clockwise() {
  // Set motor direction clockwise for front left and middle left motors
  setMotor(1, 255, PWM_FL, IN1_FL, IN2_FL);
  setMotor(1, 255, PWM_ML, IN1_ML, IN2_ML);
}

void counterClockwise() {
  // Run the motor counter-clockwise
  setMotor(-1, 255, PWM_FL, IN1_FL, IN2_FL);
  setMotor(-1, 255, PWM_ML, IN1_ML, IN2_ML);
}

void stopMotor() {
  // Stop the motor
  setMotor(0, 0, PWM_FL, IN1_FL, IN2_FL);
  setMotor(0, 0, PWM_ML, IN1_ML, IN2_ML);
}

void turnRight() {
servo_fl.write(120);
servo_ml.write(120);
servo_bl.write(120);
servo_fr.write(120);
servo_mr.write(120);
servo_br.write(120);



delay(15);
}

void turnLeft() {
servo_fl.write(60);
servo_ml.write(60);
servo_bl.write(60);
servo_fr.write(60);
servo_mr.write(60);
servo_br.write(60);
delay(15);
}

void center() {
servo_fl.write(90);
servo_ml.write(90);
servo_bl.write(90);
servo_fr.write(90);
servo_mr.write(90);
servo_br.write(90);
delay(15);
}

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2) {
  analogWrite(pwm, pwmVal);
  if (dir == 1) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (dir == -1) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }  
}


