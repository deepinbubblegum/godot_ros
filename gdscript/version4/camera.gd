extends Camera3D

var timer: Timer = Timer.new()
var camera_ros: CameraRos = CameraRos.new()
var sub_viewport: SubViewport = SubViewport.new()
var sub_camera: Camera3D = Camera3D.new()

func _ready() -> void:
	camera_ros.init(name + "_node", name.to_lower() + "/image_raw", name.to_lower()) # init ROS camera node_name
	setup_sub_viewport()
	setup_sub_camera()
	synchronize_camera_settings()
	setup_timer()

func setup_sub_viewport() -> void:
	sub_viewport.size = Vector2(1920, 1080)
	sub_viewport.render_target_update_mode = SubViewport.UPDATE_ALWAYS
	sub_viewport.render_target_clear_mode = SubViewport.CLEAR_MODE_ALWAYS
	add_child(sub_viewport)

func setup_sub_camera() -> void:
	sub_camera.current = true
	sub_viewport.add_child(sub_camera)

func setup_timer() -> void:
	add_child(timer)
	timer.timeout.connect(_on_timer_timeout)
	timer.wait_time = 0.01666666666 # 60 Hz
	timer.start()

func synchronize_camera_settings() -> void:
	sub_camera.transform = transform
	sub_camera.fov = fov
	sub_camera.near = near
	sub_camera.far = far
	sub_camera.projection = projection

func _process(_delta: float) -> void:
	synchronize_camera_settings()
	camera_ros.spin_some()

func _on_timer_timeout() -> void:
	await RenderingServer.frame_post_draw

	var texture = sub_viewport.get_texture()
	if texture:
		var img = texture.get_image()
		img.convert(Image.FORMAT_RGB8)
		camera_ros.publish(img)
