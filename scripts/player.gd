# Player controller — top-down 2D movement + interaction + hiding
extends CharacterBody2D

@export var speed: float = 120.0

var can_hide: bool = false
var is_hidden: bool = false

func _physics_process(_delta):
	if is_hidden:
		return  # Lock movement while hiding

	var dir = Vector2(
		Input.get_axis("ui_left", "ui_right"),
		Input.get_axis("ui_up", "ui_down")
	).normalized()

	velocity = dir * speed
	move_and_slide()

func _unhandled_input(event):
	if event.is_action_pressed("hide"):
		if can_hide and not is_hidden:
			_enter_hide()
		elif is_hidden:
			_exit_hide()

func _enter_hide():
	is_hidden = true
	modulate.a = 0.3

func _exit_hide():
	is_hidden = false
	modulate.a = 1.0

func die():
	GameManager.lose()
