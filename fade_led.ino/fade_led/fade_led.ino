
#include <ros.h>
#include <std_msgs/UInt8.h>


ros::NodeHandle nh;

std_msgs::UInt8 brightness_msg;
ros::Publisher led_pub("led", &brightness_msg);

int ledPin = 11;           
int brightness = 0;    
int fadeAmount = 5;    


void setup() {
  
  pinMode(ledPin, OUTPUT);
  nh.initNode();
  nh.advertise(led_pub);
  Serial.begin(9600);
}


void loop() {
  brightness = brightness + fadeAmount;
  if (brightness <= 0 || brightness >= 255)
  {
    fadeAmount = -fadeAmount;
  }
  Serial.println(brightness);
  analogWrite(ledPin, brightness);
  brightness_msg.data = brightness;
  led_pub.publish(&brightness_msg);

  nh.spinOnce();

  delay(1000);

}
  
 
