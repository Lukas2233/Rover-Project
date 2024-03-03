#include <util/atomic.h> // For the ATOMIC_BLOCK macro
#include <Servo.h>

#define ENCA 2 // YELLOW
#define ENCB 3 // GREEN
#define PWM 8
#define IN2 24
#define IN1 22

Servo servo1;


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
  
 servo1.attach(36);

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
servo1.write(180);
delay(15);
}

void turnLeft() {
servo1.write(0);
delay(15);
}

void center() {
servo1.write(90);
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
