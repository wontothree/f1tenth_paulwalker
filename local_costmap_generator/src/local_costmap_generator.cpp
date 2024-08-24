#include "local_costmap_generator.hpp"

LocalCostmapGenerator::LocalCostmapGenerator() : Node("loca_costmap_generator_node")
{
    laserscan_topic = "/scan";

    sub_scan_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
        lidarscan_topic, 
        10, 
        std::bind(&LocalCostmapGenerator::scan_callback, this, std::placeholders::_1)
    );
}

void LocalCostmapGenerator::scan_callback(const sensor_msgs::msg::LaserScan::ConstSharedPtr scan_msg)
{
    print_laser_data(scan_msg);
}

void LocalCostmapGenerator::print_laser_data(const sensor_msgs::msg::LaserScan::ConstSharedPtr scan_msg)
{
    // Print some basic information
    RCLCPP_INFO(this->get_logger(), "Received LaserScan data:");
    RCLCPP_INFO(this->get_logger(), "Angle Min: %f, Angle Max: %f", scan_msg->angle_min, scan_msg->angle_max);
    RCLCPP_INFO(this->get_logger(), "Range Min: %f, Range Max: %f", scan_msg->range_min, scan_msg->range_max);

    // Print the range values
    for (size_t i = 0; i < scan_msg->ranges.size(); ++i) {
        RCLCPP_INFO(this->get_logger(), "Range[%zu]: %f", i, scan_msg->ranges[i]);
    }
}