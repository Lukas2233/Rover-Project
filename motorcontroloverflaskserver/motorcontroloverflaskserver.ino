#include <util/atomic.h> // For the ATOMIC_BLOCK macro
#include <Servo.h>

//front left motor
#define ENCA 2 // YELLOW
#define ENCB 51 // GREEN
#define PWM 10
#define IN2 40
#define IN1 41

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
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
  
  pinMode(PWM, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
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
  // Set motor direction clockwise
  setMotor(1, 255, PWM, IN1, IN2);
}

void counterClockwise() {
  // Run the motor counter-clockwise
  setMotor(-1, 255, PWM, IN1, IN2);
}

void stopMotor() {
  // Stop the motor
  setMotor(0, 0, PWM, IN1, IN2);
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

void readEncoder() {
  int b = digitalRead(ENCB);
  if (b > 0) {
    posi++;
  } else {
    posi--;
  }
}
