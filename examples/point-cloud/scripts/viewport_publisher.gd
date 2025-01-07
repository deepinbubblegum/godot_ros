extends Node3D

var timer = null
var count = 1

# initialize ROS viewport node
var ros_viewport = ViewPort.new()

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	ros_viewport.create("godot_image_node", name)
	# Create and configure the timer
	timer = Timer.new()
	add_child(timer)
	# Spin ros node
	ros_viewport.spin_some()

	timer.timeout.connect(_on_timer_timeout)
	timer.wait_time = 0.01666666666
	timer.start()

func _on_timer_timeout() -> void:
	# Wait until the frame has finished before getting the texture.
	#RenderingServer.call()
	await RenderingServer.frame_post_draw
	# Retrieve the captured image.
	var img = get_viewport().get_texture().get_image()
	img.convert(Image.FORMAT_RGB8)
	# publish image to ROS
	ros_viewport.pubImage(img)
	#ros_viewport.spin_some()
