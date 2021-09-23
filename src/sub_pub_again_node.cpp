#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt16.h"
#include "sensor_msgs/Joy.h"
/*
class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    //mission
    nuc2_mission_pub = n_.advertise<std_msgs::UInt16>("/nuc2/mission", 1);
    mission_sub = n_.subscribe("/mission", 1, &SubscribeAndPublish::mission_callback, this);
    //joy
    nuc2_joy_pub = n_.advertise<sensor_msgs::Joy>("/nuc2/joy", 1);
    joy_sub = n_.subscribe("/joy", 1, &SubscribeAndPublish::joy_callback, this);
  }

  void mission_callback(const std_msgs::UInt16& input)
  {
    //PUBLISHED_MESSAGE_TYPE output;
    //callback 함수에서 받은 input을 사용해서 output을 만들고 이를 pub한다.
    nuc2_mission_pub.publish(input);
  }
  void joy_callback(const sensor_msgs::Joy& input)
  {
    nuc2_joy_pub.publish(input);
  }

private: //private으로 NodeHandle과 publisher, subscriber를 선언한다.
  //mission
  ros::NodeHandle n_;
  ros::Publisher nuc2_mission_pub;
  ros::Subscriber mission_sub;
  //joy
  ros::Publisher nuc2_joy_pub;
  ros::Subscriber joy_sub;

};
*//*
int main(int argc, char **argv)
{
  ros::init(argc, argv, "sub_pub_again_node");
  SubscribeAndPublish SAPObject; //클래스 객체 선을 하게 되면 모든게 된다.
  ros::spin();
  return 0;
}*/

std_msgs::UInt16 msg;
bool pub_flag = false;
void mission_callback(const std_msgs::UInt16& input)
{
  //PUBLISHED_MESSAGE_TYPE output;
  //callback 함수에서 받은 input을 사용해서 output을 만들고 이를 pub한다.
  msg = input;
  pub_flag = true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "sub_pub_again_node");
  ros::NodeHandle nh;

  ros::Subscriber mission_sub = nh.subscribe("/mission", 1, mission_callback);
  ros::Publisher chatter_pub = nh.advertise<std_msgs::UInt16>("/nuc2/mission", 1);

  ros::Rate loop_rate(100);
  while (ros::ok())
  {
    //std_msgs::String msg;
    //msg.data = "hello world";
    if(pub_flag){
    chatter_pub.publish(msg);
    }

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
