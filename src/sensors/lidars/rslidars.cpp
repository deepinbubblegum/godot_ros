#include "godot_ros/sensors/lidars/rslidars.hpp"

RSlidars::RSlidars()
{
    rclcpp::init(0, nullptr);
    node = std::make_shared<rclcpp::Node>("godot_lidars_node");
    rclcpp::QoS qos(rclcpp::KeepLast(7));
    pub = node->create_publisher<sensor_msgs::msg::PointCloud2>("rslidar", qos);
}

RSlidars::~RSlidars()
{
    rclcpp::shutdown();
}

void RSlidars::spin_some()
{
    rclcpp::spin_some(node);
}

void RSlidars::publisher(const Array ray_cast_array)
{
    auto msg = std::make_unique<sensor_msgs::msg::PointCloud2>();
    msg->header.frame_id = "rslidar";
    msg->header.stamp = rclcpp::Clock().now();
    
    sensor_msgs::PointCloud2Modifier modifier(*msg);
    modifier.setPointCloud2FieldsByString(1, "xyz");
    modifier.resize(ray_cast_array.size());
    
    sensor_msgs::PointCloud2Iterator<float> iter_x(*msg, "x");
    sensor_msgs::PointCloud2Iterator<float> iter_y(*msg, "y");
    sensor_msgs::PointCloud2Iterator<float> iter_z(*msg, "z");
    
    for (int i = 0; i < ray_cast_array.size(); ++i, ++iter_x, ++iter_y, ++iter_z) {
        Vector3 new_position = ray_cast_array[i];
        *iter_x = new_position.x;
        *iter_y = new_position.z;
        *iter_z = new_position.y;
    }
    
    pub->publish(std::move(msg));
}

void RSlidars::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("spin_some"), &RSlidars::spin_some);
    ClassDB::bind_method(D_METHOD("publisher", "ray_cast_array"), &RSlidars::publisher);
}
