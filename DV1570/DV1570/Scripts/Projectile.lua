
function UpdateProjectile(projectile)
	REMOVE_PROJECTILE = false
	local mt = getmetatable(projectile)
	local dirX, dirY = mt.GetDir(projectile)
	local velX = dirX * PROJECTILE_SPEED
	local velY = dirY * PROJECTILE_SPEED
	local radius = mt.GetRadius(projectile);
	local offsetX, offsetY = 0, 0
	local run = true
	print(PROJECTILE_SPEED);
	while run do
		
		local posX, posY = mt.GetPos(projectile)
		if (posX + radius*2) < 0 or (posX - radius) > WINDOW_WIDTH then run = false end
		if (posY + radius*2) < 0 or (posY - radius) > WINDOW_HEIGHT then run = false end
		
		local speed = (dirX^2 + dirY^2)^0.5
		
		local angle = math.atan(dirY/dirX)
		local accX = speed^2 * math.cos(angle)
		local accY = speed^2 * math.sin(angle) - GRAVITY
		velX = velX + (accX * FRAME_DELTA_TIME)
		velY = velY + (accY * FRAME_DELTA_TIME)
		offsetX = velX * FRAME_DELTA_TIME
		offsetY = velY * FRAME_DELTA_TIME
		
		mt.Move(projectile, offsetX, offsetY)
		coroutine.yield()
	end
	REMOVE_PROJECTILE = true
	print("Projectile thread dead now\n")
end

function RunUpdateThread(projectile)
	projectileCoroutine = coroutine.create(UpdateProjectile)
end 

function ResumeUpdate(projectile)
	coroutine.resume(projectileCoroutine, projectile)
end
	