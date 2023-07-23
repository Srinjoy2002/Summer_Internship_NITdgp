#include <ros.h>
#include <std_msgs/UInt16.h>
#include <Servo.h>
#include <NewPing.h>

#define TRIG_PIN 12  
#define ECHO_PIN 13  
#define MAX_DISTANCE 200

#define SERVO_PIN 9  

Servo myservo;
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

ros::NodeHandle nh;
std_msgs::UInt16 distance_msg;
ros::Publisher distance_pub("distance", &distance_msg);

#define MOTOR1_PIN1 4  
#define MOTOR1_PIN2 5   
#define MOTOR2_PIN1 1  
#define MOTOR2_PIN2 2   
// #define MOTOR_SPEED 250 

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
  int obstacleThreshold = 30; //ei distance asle left turn
  
  
  for (int angle = 0; angle <= 180; angle += 30) {
    myservo.write(angle);
    delay(500);
    distance = readPing();
    distance_msg.data = distance;
    distance_pub.publish(&distance_msg);
    nh.spinOnce();

    
    if (distance <= obstacleThreshold) { //dekhbe je obstacle ache nki
     
      moveStop();
      delay(500);
      turnLeft();
      delay(500);
      break;
    }
  }

  
  moveForward();
  delay(1000);
  
  // stop kore left ghurbe
  moveStop();
  delay(500);
  turnLeft();
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

void turnLeft() {
  digitalWrite(MOTOR1_PIN1, LOW);
  digitalWrite(MOTOR1_PIN2, HIGH);
  digitalWrite(MOTOR2_PIN1, HIGH);
  digitalWrite(MOTOR2_PIN2, LOW);
 
}
void turnRight() {
  digitalWrite(MOTOR1_PIN1, HIGH);
  digitalWrite(MOTOR1_PIN2, LOW);
  digitalWrite(MOTOR2_PIN1, LOW);
  digitalWrite(MOTOR2_PIN2, HIGH);
}
