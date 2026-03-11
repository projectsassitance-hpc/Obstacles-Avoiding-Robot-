  // Required Libraries
#include <AFMotor.h>  

#include <NewPing.h>
#include <Servo.h> 

// Define Pins
#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 
#define MAX_SPEED 230  // DC motor speed
#define MAX_SPEED_OFFSET 20

// Initialize Sensor & Motors
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo myservo;   

// Variables
boolean goesForward = false;
int distance = 100;
int speedSet = 0;

// Adjustable Timing (Change these values as per your requirement)
int backwardDelay = 900;  // Time to move backward (increase/decrease as needed)
int turnDelay = 900;      // Time for turning (adjust to get correct turn angles)

void setup() {
  myservo.attach(10);  
  myservo.write(115); 
  delay(2000);

  // Initial Distance Readings
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  int distanceR = 0;
  int distanceL = 0;
  delay(40);
 
  if(distance <= 30) {
    moveStop();
    delay(100);
    moveBackward();
    delay(backwardDelay); // Backward movement time
    moveStop();
    delay(200);

    // Checking which direction is better
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);

    if(distanceR >= distanceL) {
      turnRight();
      moveStop();
    } else {
      turnLeft();
      moveStop();
    }
  } else {
    moveForward();
  }

  distance = readPing();
}

// Function to check Right Side Distance
int lookRight() {
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}

// Function to check Left Side Distance
int lookLeft() {
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
}

// Read Ultrasonic Sensor Data
int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm == 0) {
    cm = 250;
  }
  return cm;
}

// Stop the Car
void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
} 
  
// Move Forward
void moveForward() {
  if(!goesForward) {
    goesForward = true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD); 
    motor4.run(FORWARD);     

    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) { 
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
  }
}

// Move Backward
void moveBackward() {
    goesForward = false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);  

    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) { 
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
    delay(backwardDelay);  // Set backward delay time
}  

// Turn Right
void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);     
  delay(turnDelay);  // Adjust turning delay here

  motor1.run(FORWARD);      
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);      
} 
 
// Turn Left
void turnLeft() {
  motor1.run(BACKWARD);     
  motor2.run(BACKWARD);  
  motor3.run(FORWARD);
  motor4.run(FORWARD);   
  delay(turnDelay);  // Adjust turning delay here

  motor1.run(FORWARD);     
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}  
