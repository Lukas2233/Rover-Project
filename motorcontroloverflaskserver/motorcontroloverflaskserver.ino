#include <util/atomic.h> // For the ATOMIC_BLOCK macro
#include <Servo.h>
#include <Wire.h>
#define SLAVE_ADDRESS 0x08

char incomingByte;

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
#define IN2_FR 42
#define IN1_FR 43

// middle right motor
#define ENCA_MR 18 // Interrupt pin
#define ENCB_MR 46
#define PWM_MR 6
#define IN2_MR 50
#define IN1_MR 49

// back right motor
#define ENCA_BR 21 // Interrupt pin
#define ENCB_BR 45
#define PWM_BR 11
#define IN2_BR 39
#define IN1_BR 38


//Define servos
Servo servo_fl;
Servo servo_ml;
Servo servo_bl;
Servo servo_fr;
Servo servo_mr;
Servo servo_br;

//define servo offset values
int fr_ofst = 5; 
int mr_ofst = 4;
int br_ofst = -1;
int fl_ofst = -9;
int ml_ofst = 2;
int bl_ofst = -5;


//define servo starting position
int start_angle = 90;


//I THINK I CAN REMOVE THESE LINES HERE
volatile int posi = 0; // specify posi as volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
long prevT = 0;
float eprev = 0;
float eintegral = 0;

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);

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

  servo_fl.write(start_angle+fl_ofst);
  servo_ml.write(start_angle+ml_ofst);
  servo_bl.write(start_angle+bl_ofst);
  servo_fr.write(start_angle+fr_ofst);
  servo_mr.write(start_angle+mr_ofst);
  servo_br.write(start_angle+br_ofst);


}

void loop() {
}

void receiveData(int byteCount) {
  while (Wire.available()) {
    incomingByte = Wire.read();

    // Process the incoming byte
    switch (incomingByte) {
      case 'w':
        forward();
        break;
      case 's':
        reverse();
        break;
      case 'h':
        stopMotor();
        break;
      case 'l':
        bigRight();
        break;
      case 'j':
        bigLeft();
        break;
      case 'r':
        diagonalRight();
        break;
      case 'f':
        diagonalLeft();
        break;
      case 'k':
        center();
        break;
      case 'i':
        center();
        break;        
      case 'q':
        rotateleft();
        break;
      case 'e':
        rotateright();
        break;
      case 'a':
        crableft();
        break;
      case 'd':
        crabright();
        break;
      case 'u':
        smallLeft();
        break;
      case 'o':
        smallRight();
        break;

      default:
        break;
    }
  }
}

void forward() {
  // Run the motor clockwise
  setMotor(1, 255, PWM_FL, IN1_FL, IN2_FL);
  setMotor(1, 255, PWM_ML, IN1_ML, IN2_ML);
  setMotor(1, 255, PWM_BL, IN1_BL, IN2_BL);
  setMotor(1, 255, PWM_FR, IN1_FR, IN2_FR);
  setMotor(1, 255, PWM_MR, IN1_MR, IN2_MR);
  setMotor(1, 255, PWM_BR, IN1_BR, IN2_BR);
}

void reverse() {
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

void diagonalRight() {
  servo_fl.write(120 + fl_ofst);
  servo_ml.write(120 + ml_ofst);
  servo_bl.write(120 + bl_ofst);
  servo_fr.write(120 + fr_ofst);
  servo_mr.write(120 + mr_ofst);
  servo_br.write(120 + br_ofst);

  delay(15);
}

void diagonalLeft() {
  servo_fl.write(60 + fl_ofst);
  servo_ml.write(60 + ml_ofst);
  servo_bl.write(60 + bl_ofst);
  servo_fr.write(60 + fr_ofst);
  servo_mr.write(60 + mr_ofst);
  servo_br.write(60 + br_ofst);

  delay(15);
}

void bigRight() {
  servo_fl.write(120 + fl_ofst);
  servo_ml.write(90 + ml_ofst);
  servo_bl.write(60 + bl_ofst);
  servo_fr.write(120 + fr_ofst);
  servo_mr.write(90 + mr_ofst);
  servo_br.write(60 + br_ofst);

  delay(15);
}

void smallRight() {
  servo_fl.write(110 + fl_ofst);
  servo_ml.write(90 + ml_ofst);
  servo_bl.write(70 + bl_ofst);
  servo_fr.write(110 + fr_ofst);
  servo_mr.write(90 + mr_ofst);
  servo_br.write(70 + br_ofst);

  delay(15);
}

void bigLeft() {
  servo_fl.write(60 + fl_ofst);
  servo_ml.write(90 + ml_ofst);
  servo_bl.write(120 + bl_ofst);
  servo_fr.write(60 + fr_ofst);
  servo_mr.write(90 + mr_ofst);
  servo_br.write(120 + br_ofst);

  delay(15);
}

void smallLeft() {
  servo_fl.write(70 + fl_ofst);
  servo_ml.write(90 + ml_ofst);
  servo_bl.write(110 + bl_ofst);
  servo_fr.write(70 + fr_ofst);
  servo_mr.write(90 + mr_ofst);
  servo_br.write(110 + br_ofst);

  delay(15);
}


void center() {
  servo_fl.write(90+fl_ofst);
  servo_ml.write(90+ml_ofst);
  servo_bl.write(90+bl_ofst);
  servo_fr.write(90+fr_ofst);
  servo_mr.write(90+mr_ofst);
  servo_br.write(90+br_ofst);

  delay(15);
}

void rotateright() {
  servo_fl.write(160 + fl_ofst);
  servo_ml.write(90 + ml_ofst);
  servo_bl.write(20 + bl_ofst);
  servo_fr.write(20 + fr_ofst);
  servo_mr.write(90 + mr_ofst);
  servo_br.write(160 + br_ofst);

  delay(15);

  setMotor(1, 255, PWM_FL, IN1_FL, IN2_FL);
  setMotor(1, 127, PWM_ML, IN1_ML, IN2_ML);
  setMotor(1, 255, PWM_BL, IN1_BL, IN2_BL);
  setMotor(-1, 255, PWM_FR, IN1_FR, IN2_FR);
  setMotor(-1, 127, PWM_MR, IN1_MR, IN2_MR);
  setMotor(-1, 255, PWM_BR, IN1_BR, IN2_BR);
}

void rotateleft() {
  servo_fl.write(160 + fl_ofst);
  servo_ml.write(90 + ml_ofst);
  servo_bl.write(20 + bl_ofst);
  servo_fr.write(20 + fr_ofst);
  servo_mr.write(90 + mr_ofst);
  servo_br.write(160 + br_ofst);

  delay(15);

  setMotor(-1, 255, PWM_FL, IN1_FL, IN2_FL);
  setMotor(-1, 127, PWM_ML, IN1_ML, IN2_ML);
  setMotor(-1, 255, PWM_BL, IN1_BL, IN2_BL);
  setMotor(1, 255, PWM_FR, IN1_FR, IN2_FR);
  setMotor(1, 127, PWM_MR, IN1_MR, IN2_MR);
  setMotor(1, 255, PWM_BR, IN1_BR, IN2_BR);
}

void crabright() {
  setMotor(1, 255, PWM_FL, IN1_FL, IN2_FL);
  setMotor(1, 127, PWM_ML, IN1_ML, IN2_ML);
  setMotor(1, 255, PWM_BL, IN1_BL, IN2_BL);
  setMotor(1, 255, PWM_FR, IN1_FR, IN2_FR);
  setMotor(1, 127, PWM_MR, IN1_MR, IN2_MR);
  setMotor(1, 255, PWM_BR, IN1_BR, IN2_BR);

  delay(100);
  
  servo_fl.write(180 + fl_ofst);
  servo_ml.write(180 + ml_ofst);
  servo_bl.write(180 + bl_ofst);
  servo_fr.write(180 + fr_ofst);
  servo_mr.write(180 + mr_ofst);
  servo_br.write(180 + br_ofst);


}

void crableft() {
  setMotor(1, 255, PWM_FL, IN1_FL, IN2_FL);
  setMotor(1, 127, PWM_ML, IN1_ML, IN2_ML);
  setMotor(1, 255, PWM_BL, IN1_BL, IN2_BL);
  setMotor(1, 255, PWM_FR, IN1_FR, IN2_FR);
  setMotor(1, 127, PWM_MR, IN1_MR, IN2_MR);
  setMotor(1, 255, PWM_BR, IN1_BR, IN2_BR);

  delay(100);

  servo_fl.write(0 + fl_ofst);
  servo_ml.write(0 + ml_ofst);
  servo_bl.write(0 + bl_ofst);
  servo_fr.write(0 + fr_ofst);
  servo_mr.write(0 + mr_ofst);
  servo_br.write(0 + br_ofst);
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

