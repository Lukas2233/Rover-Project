#include <util/atomic.h> // For the ATOMIC_BLOCK macro
#include <Servo.h>

// front left motor
#define ENCA_FL 2 // Interrupt pin
#define ENCB_FL 51
#define PWM_FL 10
#define IN2_FL 40
#define IN1_FL 41

// middle left motor
#define ENCA_ML 20 // Interrupt pin
#define ENCB_ML 23
#define PWM_ML 8
#define IN2_ML 53
#define IN1_ML 52

// back left motor
#define ENCA_BL 19 // Interrupt pin
#define ENCB_BL 47
#define PWM_BL 12
#define IN2_BL 36
#define IN1_BL 37

// front right motor
#define ENCA_FR 3 // Interrupt pin
#define ENCB_FR 48
#define PWM_FR 9
#define IN2_FR 43
#define IN1_FR 42

// middle right motor
#define ENCA_MR 18 // Interrupt pin
#define ENCB_MR 46
#define PWM_MR 6
#define IN2_MR 49
#define IN1_MR 50

// back right motor
#define ENCA_BR 21 // Interrupt pin
#define ENCB_BR 45
#define PWM_BR 11
#define IN2_BR 38
#define IN1_BR 39


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

  //set up for front left
  pinMode(ENCA_FL, INPUT);
  pinMode(ENCB_FL, INPUT);
  pinMode(PWM_FL, OUTPUT);
  pinMode(IN1_FL, OUTPUT);
  pinMode(IN2_FL, OUTPUT);
  
//set up for middle left
  pinMode(ENCA_ML, INPUT);
  pinMode(ENCB_ML, INPUT);
  pinMode(PWM_ML, OUTPUT);
  pinMode(IN1_ML, OUTPUT);
  pinMode(IN2_ML, OUTPUT);

//set up for back left
  pinMode(ENCA_BL, INPUT);
  pinMode(ENCB_BL, INPUT);
  pinMode(PWM_BL, OUTPUT);
  pinMode(IN1_BL, OUTPUT);
  pinMode(IN2_BL, OUTPUT);

//set up for front right
  pinMode(ENCA_FR, INPUT);
  pinMode(ENCB_FR, INPUT);
  pinMode(PWM_FR, OUTPUT);
  pinMode(IN1_FR, OUTPUT);
  pinMode(IN2_FR, OUTPUT);

//set up for middle right
  pinMode(ENCA_MR, INPUT);
  pinMode(ENCB_MR, INPUT);
  pinMode(PWM_MR, OUTPUT);
  pinMode(IN1_MR, OUTPUT);
  pinMode(IN2_MR, OUTPUT);

  //set up for back right
  pinMode(ENCA_BR, INPUT);
  pinMode(ENCB_BR, INPUT);
  pinMode(PWM_BR, OUTPUT);
  pinMode(IN1_BR, OUTPUT);
  pinMode(IN2_BR, OUTPUT);




//setup for servos
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
  setMotor(1, 255, PWM_BL, IN1_BL, IN2_BL);
  setMotor(1, 255, PWM_FR, IN1_FR, IN2_FR);
  setMotor(1, 255, PWM_MR, IN1_MR, IN2_MR);
  setMotor(1, 255, PWM_BR, IN1_BR, IN2_BR);
}

void counterClockwise() {
  // Run the motor counter-clockwise
  setMotor(-1, 255, PWM_FL, IN1_FL, IN2_FL);
  setMotor(-1, 255, PWM_ML, IN1_ML, IN2_ML);
  setMotor(-1, 255, PWM_BL, IN1_BL, IN2_BL);
  setMotor(-1, 255, PWM_FR, IN1_FR, IN2_FR);
  setMotor(-1, 255, PWM_MR, IN1_MR, IN2_MR);
  setMotor(-1, 255, PWM_BR, IN1_BR, IN2_BR);
}

void stopMotor() {
  // Stop the motor
  setMotor(0, 0, PWM_FL, IN1_FL, IN2_FL);
  setMotor(0, 0, PWM_ML, IN1_ML, IN2_ML);
  setMotor(0, 0, PWM_BL, IN1_BL, IN2_BL);
  setMotor(0, 0, PWM_FR, IN1_FR, IN2_FR);
  setMotor(0, 0, PWM_MR, IN1_MR, IN2_MR);
  setMotor(0, 0, PWM_BR, IN1_BR, IN2_BR);
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


