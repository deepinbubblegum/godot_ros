#include "godot_ros/sensors/lidars/rslidars.hpp"

RSlidars::RSlidars()
{
    try{
        rclcpp::init(0, nullptr);
    } catch (...) {}
}

RSlidars::~RSlidars()
{
    rclcpp::shutdown();
}

void RSlidars::init(const String &node_name, const String &topic_name, const String &frame_id)
{
    node_name_ = node_name;
    topic_name_ = topic_name;
    frame_id_ = frame_id;

    m_node = std::make_shared<rclcpp::Node>(node_name.utf8().get_data());
    rclcpp::QoS qos(rclcpp::KeepLast(1));
    m_pub = m_node->create_publisher<sensor_msgs::msg::PointCloud2>(topic_name.utf8().get_data(), qos);
}

void RSlidars::spin_some()
{
    rclcpp::spin_some(m_node);
}

void RSlidars::publisher(const Array ray_cast_array)
{
    auto msg = std::make_unique<sensor_msgs::msg::PointCloud2>();
    msg->header.frame_id = frame_id_.utf8().get_data();
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
        *iter_y = new_position.z; // In Godot X = X Axis, but Y and Z are inverted
        *iter_z = new_position.y; // In Godot X = X Axis, but Y and Z are inverted
    }
    
    m_pub->publish(std::move(msg));
}

void RSlidars::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("init", "node_name", "topic_name", "frame_id"), &RSlidars::init);
    ClassDB::bind_method(D_METHOD("spin_some"), &RSlidars::spin_some);
    ClassDB::bind_method(D_METHOD("publisher", "ray_cast_array"), &RSlidars::publisher);
}
