# save_odom
**该项目支持订阅里程计话题并将读取的里程计数据以tum格式写入txt文件**


# system
ubuntu18.04 or ubuntu20.04
ROS1

# install
mkdir -p catkin_ws/src  
cd catkin_ws/src  
git clone git@github.com:tx-lidar/odom2txt.git  
cd ..  
catkin_make  

# param
```
<param name="aloam_topic" value="yourtopic1"/>  
<param name="liosam_topic" value="yourtopic2"/>  
<param name="ALOAM_file" value="/xxx/xxx/1.txt"/>  
<param name="LIOSAM_file" value="/xxx/xxx/2.txt"/>
```
