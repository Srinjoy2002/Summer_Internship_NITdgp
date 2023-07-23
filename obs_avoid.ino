#include <ros.h>
#include <std_msgs/UInt16.h>
#include <Servo.h>
#include <NewPing.h>

#define TRIG_PIN 12  // Connect the Trig pin of the ultrasonic sensor to digital pin 2
#define ECHO_PIN 13  // Connect the Echo pin of the ultrasonic sensor to digital pin 3
#define MAX_DISTANCE 200

#define SERVO_PIN 9  // Connect the signal pin of the servo motor to digital pin 9

Servo myservo;
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

ros::NodeHandle nh;
std_msgs::UInt16 distance_msg;
ros::Publisher distance_pub("distance", &distance_msg);

#define MOTOR1_PIN1 4   // Connect the pin1 of motor 1 to digital pin 4
#define MOTOR1_PIN2 5   // Connect the pin2 of motor 1 to digital pin 5
#define MOTOR2_PIN1 6   // Connect the pin1 of motor 2 to digital pin 6
#define MOTOR2_PIN2 7   // Connect the pin2 of motor 2 to digital pin 7
#define MOTOR_SPEED 150 // Set the speed of the motors

void setup() {
  myservo.attach(SERVO_PIN);

  pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);

  nh.initNode();
  nh.advertise(distance_pub);

  delay(2000);
}

void loop() {
  int distance;
  
  // Rotate the servo-mounted ultrasonic sensor from 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle += 10) {
    myservo.write(angle);
    delay(500);
    distance = readPing();
    distance_msg.data = distance;
    distance_pub.publish(&distance_msg);
    nh.spinOnce();
  }

  // Rotate the servo-mounted ultrasonic sensor from 180 to 0 degrees
  for (int angle = 180; angle >= 0; angle -= 10) {
    myservo.write(angle);
    delay(500);
    distance = readPing();
    distance_msg.data = distance;
    distance_pub.publish(&distance_msg);
    nh.spinOnce();
  }
  
  // Move forward for 1 second
  moveForward();
  delay(1000);
  
  // Stop for 1 second
  moveStop();
  delay(1000);
  
  // Move backward for 1 second
  moveBackward();
  delay(1000);
  
  // Stop for 1 second
  moveStop();
  delay(1000);
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  digitalWrite(MOTOR1_PIN1, LOW);
  digitalWrite(MOTOR1_PIN2, LOW);
  digitalWrite(MOTOR2_PIN1, LOW);
  digitalWrite(MOTOR2_PIN2, LOW);
}

void moveForward() {
  digitalWrite(MOTOR1_PIN1, HIGH);
  digitalWrite(MOTOR1_PIN2, LOW);
  digitalWrite(MOTOR2_PIN1, HIGH);
  digitalWrite(MOTOR2_PIN2, LOW);
}

void moveBackward() {
  digitalWrite(MOTOR1_PIN1, LOW);
  digitalWrite(MOTOR1_PIN2, HIGH);
  digitalWrite(MOTOR2_PIN1, LOW);
  digitalWrite(MOTOR2_PIN2, HIGH);
}

void turnRight() {
  digitalWrite(MOTOR1_PIN1, HIGH);
  digitalWrite(MOTOR1_PIN2, LOW);
  digitalWrite(MOTOR2_PIN1, LOW);
  digitalWrite(MOTOR2_PIN2, HIGH);
  delay(500);
  moveStop();
}

void turnLeft() {
  digitalWrite(MOTOR1_PIN1, LOW);
  digitalWrite(MOTOR1_PIN2, HIGH);
  digitalWrite(MOTOR2_PIN1, HIGH);
  digitalWrite(MOTOR2_PIN2, LOW);
  delay(500);
  moveStop();
}
