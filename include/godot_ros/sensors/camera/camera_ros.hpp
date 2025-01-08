#ifndef GODOT_ROS__SENSORS__CAMERA__CAMERA_HPP
#define GODOT_ROS__SENSORS__CAMERA__CAMERA_HPP

#include "core/object/ref_counted.h"
#include "core/io/image.h"
#include "core/string/ustring.h"

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"

class CameraRos : public RefCounted {
    GDCLASS(CameraRos, RefCounted);

private:
    std::shared_ptr<rclcpp::Node> m_node;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr m_pub;
    std::unique_ptr<sensor_msgs::msg::Image> m_msg;
    
    String node_name_;
    String topic_name_;
    String frame_id_;

protected:
    static void _bind_methods();

public:
    CameraRos();
    ~CameraRos();
    void init(const String &node_name, const String &topic_name, const String &frame_id);
    void publish(const Ref<Image> &img);
    void spin_some();
};

#endif // GODOT_ROS__SENSORS__CAMERA__CAMERA_HPP
