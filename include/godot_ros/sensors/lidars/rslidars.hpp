#ifndef GODOT_ROS__SENSORS__LIDARS__RSLIDARS_HPP
#define GODOT_ROS__SENSORS__LIDARS__RSLIDARS_HPP

#include "core/object/ref_counted.h"
#include "core/string/ustring.h"

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "sensor_msgs/point_cloud2_iterator.hpp"

class RSlidars : public RefCounted
{
    GDCLASS(RSlidars, RefCounted);
public:
    RSlidars(); 
    ~RSlidars();

    void init(const String &node_name, const String &topic_name, const String &frame_id);
    void spin_some();
    void publisher(const Array ray_cast_array);

protected:
    static void _bind_methods();

private:
    String node_name_;
    String topic_name_;
    String frame_id_;
    std::shared_ptr<rclcpp::Node> m_node;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr m_pub;
};

#endif // GODOT_ROS__SENSORS__LIDARS__RSLIDARS_HPP
