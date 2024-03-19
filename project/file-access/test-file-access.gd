extends Main

func _ready():
	var file = FileAccess.file_exists("res://file-access/Scene.tscn")
	print("GDS (A) error result: " + error_string(FileAccess.get_open_error()))
