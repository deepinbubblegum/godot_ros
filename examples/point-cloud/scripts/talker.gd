extends Node3D

# Calls rclcpp::init(0, nullptr) to make sure ROS is started up
var ros_talker = Talker.new()

var g_timer: Timer = null
var count: int = 1

# Called when the node enters the scene tree for the first time.
func _ready():
	# Initialize ROS node
	ros_talker.spin_some()
	
	# Create and configure the timer
	g_timer = Timer.new()
	add_child(g_timer)
	
	# Connect the timeout signal to the callback
	g_timer.timeout.connect(_on_Timer_timeout)
	g_timer.wait_time = 1.0
	g_timer.one_shot = false
	g_timer.start()

# Called on timeout signal
func _on_Timer_timeout():
	# print("Godot is talking: " + str(count))
	# Talk callback publishes to ROS
	ros_talker.talk(count)
	count += 1
