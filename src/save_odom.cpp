#include <iostream>
#include <string>
#include <fstream>
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/PointCloud2.h>

std::fstream aloam_file;
std::fstream liosam_file;

void aloam_handler(const nav_msgs::Odometry::ConstPtr& msgIn)
{
    nav_msgs::Odometry data = *msgIn;
    static int flag=1;
    static double stamp_init;
    if(flag==1){
        stamp_init = data.header.stamp.toSec();
        flag=0;
    }
    aloam_file << std::fixed << data.header.stamp.toSec()-stamp_init   << " "   << data.pose.pose.position.x    << " " << data.pose.pose.position.y << " " 
            << data.pose.pose.position.z    << " "   << data.pose.pose.orientation.x << " " << data.pose.pose.orientation.y << " " 
            << data.pose.pose.orientation.z << " " << data.pose.pose.orientation.w   << std::endl;
}
 
void liosam_handler(const nav_msgs::Odometry::ConstPtr& liosam_msg)
{
    nav_msgs::Odometry data = *liosam_msg;
    static int flag=1;
    static double stamp_init;
    if(flag==1){
        stamp_init = data.header.stamp.toSec();
        flag=0;
    }
    liosam_file << std::fixed << data.header.stamp.toSec()-stamp_init   << " "   << data.pose.pose.position.x    << " " << data.pose.pose.position.y << " " 
            << data.pose.pose.position.z    << " "   << data.pose.pose.orientation.x << " " << data.pose.pose.orientation.y << " " 
            << data.pose.pose.orientation.z << " " << data.pose.pose.orientation.w   << std::endl;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "odom2txt");
    ros::NodeHandle nh;

    //参数服务器获取参数
    std::string ALOAM_file;
    std::string LIOSAM_file;
    std::string aloam_topic;
    std::string liosam_topic;
    nh.param<std::string>("ALOAM_file", ALOAM_file, "/home/tx/odom2txt_ws/src/save_odom/odom_evo/aloam_odom.txt"); 
    nh.param<std::string>("LIOSAM_file", LIOSAM_file, "/home/tx/odom2txt_ws/src/save_odom/odom_evo/liosam_odom.txt"); 
    nh.param<std::string>("aloam_topic", aloam_topic, "/laser_odom_to_init"); 
    nh.param<std::string>("liosam_topic", liosam_topic, "/lio_sam_6axis/mapping/odometry");

    //以写的方式打开文件
    aloam_file.open(ALOAM_file, std::ios::out);
    liosam_file.open(LIOSAM_file, std::ios::out);
 
    ros::Subscriber sub_aloam = nh.subscribe<nav_msgs::Odometry>(aloam_topic, 1000, &aloam_handler, ros::TransportHints().tcpNoDelay());
    ros::Subscriber sub_liosam = nh.subscribe<nav_msgs::Odometry>(liosam_topic, 1000, &liosam_handler, ros::TransportHints().tcpNoDelay());

    ROS_INFO("\033[1;32m----> odom2txt start.\033[0m");
    ros::spin();
 
    return 0;
}