--all object type functions are in its metatable so get it first
function MovePlayer(player)
	local mt = getmetatable(player)
	local displacement = { x = 0, y = 0}
	local keyFrame = mt.GetAniKey(player)
	local kfDur = mt.GetKeyFrameDur(player)
	local speed = mt.GetMS(player)

	if MOVE_RIGHT then
		displacement.x = speed * FRAME_DELTA_TIME;
		keyFrame = 2
		kfDur = kfDur + FRAME_DELTA_TIME
	end
	if MOVE_LEFT then
		displacement.x = speed * FRAME_DELTA_TIME * -1;
		keyFrame = 1
		kfDur = kfDur + FRAME_DELTA_TIME
	end

	mt.SetAniKey(player, keyFrame)
	mt.SetKeyFrameDur(player, kfDur)
	mt.MoveSprite(player, displacement.x, displacement.y)

	return 
end

function OnShoot(player, cursorX, cursorY)
	local mt = getmetatable(player)
	local pX, pY = mt.GetCenterPos(player)

	local dirX = cursorX - pX
	local dirY = cursorY - pY

	local length = (dirX^2 + dirY^2)^0.5

	dirX = dirX / length;
	dirY = dirY / length;

	projectile = Projectile(pX, pY, dirX, dirY)

	CAN_SHOOT = false

	return projectile
end

function OnJump(player)
	local mt = getmetatable(player)

	local max_velocity = -150.0
	local max_airtime = 0.2

	local timeInAir = 0.0
	local impusleTime = 0.02
	local impulseVelocity = -300.0
	local jumpAcceleration = 4.0

	local accY = 0.0
	local velY = 0.0

	local run = true
	while run do
		if mt.IsTouchingGround(player) then run = false end
		local posX, posY = mt.GetCenterPos(player)
		if (posX + 16) < 0 or (posX - 16) > WINDOW_WIDTH then run = false end
		if (posY + 16) < 0 or (posY - 16) > WINDOW_HEIGHT then run = false end

		timeInAir = timeInAir + FRAME_DELTA_TIME
		if timeInAir < impusleTime then
			velY = impulseVelocity
		elseif timeInAir < max_airtime then
			accY = jumpAcceleration
		else
			accY = -GRAVITY*5
		end

		velY = velY + accY * FRAME_DELTA_TIME
		local offset = velY * FRAME_DELTA_TIME
		mt.MoveSprite(player, 0, offset)
		coroutine.yield()
	end

	print("Player jump thread dead now\n")       
end

function CreateJumpThread(player)
	jumpThread = coroutine.create(OnJump)
end

function ResumeJumpThread(player)
	coroutine.resume(jumpThread, player)
end

