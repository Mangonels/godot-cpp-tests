extends Main

func _ready():
	if (FileAccess.file_exists("res://file-access/Scene.tscn")):
		print("gdscript (A) FileAccess returned existing file.")
	else:
		print("gdscript (A) FileAccess returned NON existing file.")
