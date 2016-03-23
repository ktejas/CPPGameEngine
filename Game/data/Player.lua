
Player = 
{
	name = "Flappy BIrd",
	class = "Player",
	controller = "InputController",
	initial_position = { 0.0, 0.0, 0.0 },
	initial_velocity = { 0.0, 0.0, 0.0 },
	
	bounding_box = { 
			offset	= { 0.0, 0.0, 0.0 },
			size	= { 22.8, 19.6, 1.0 }
	},

	physics_settings = 
	{
		mass = 100.0,
		drag = 0.0
	},

	render_settings = 
	{
		sprite = {
			path	= "data\\bird.dds",
			offset	= { 0.0, 0.0 },
					-- left, top, right, bottom
			extents	= { -1.0, -1.0, 1.0, 1.0 }
		},
		sprite_color = { 255, 255, 255, 255 }
	}
}