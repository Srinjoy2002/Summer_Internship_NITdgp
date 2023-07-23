
#include <ros.h>
#include <std_msgs/Float32.h>

ros::NodeHandle nh;
std_msgs::Float32 distance_msg;
ros::Publisher distance_pub("ultrasonic_distance", &distance_msg);
const int TRIG_PIN = 12;
const int ECHO_PIN = 13;



void setup() {
  nh.initNode();
  nh.advertise(distance_pub);
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  Serial.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIG_PIN,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;

  distance_msg.data = distance;
  distance_pub.publish(&distance_msg);

  nh.spinOnce();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);
}
