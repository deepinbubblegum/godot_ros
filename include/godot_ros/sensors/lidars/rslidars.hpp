#ifndef GODOT_ROS__SENSORS__LIDARS__RSLIDARS_HPP
#define GODOT_ROS__SENSORS__LIDARS__RSLIDARS_HPP

#include "core/object/ref_counted.h"

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "sensor_msgs/point_cloud2_iterator.hpp"

class RSlidars : public RefCounted
{
    GDCLASS(RSlidars, RefCounted);
public:
    RSlidars(); 
    ~RSlidars();

    void spin_some();
    void publisher(const Array ray_cast_array);

protected:
    static void _bind_methods();

private:
    std::string node_name_;
    std::string topic_name_;
    std::string frame_id_;
    std::shared_ptr<rclcpp::Node> node;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub;
};

#endif // GODOT_ROS__SENSORS__LIDARS__RSLIDARS_HPP
