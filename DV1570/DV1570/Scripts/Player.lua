
function MovePlayer(speed, deltaT, keyFrameDur)
	local displacement = { x = 0, y = 0}
	local keyFrame 
	local kfDur = keyFrameDur
	if MOVE_RIGHT then
		displacement.x = speed * deltaT;
		keyFrame = 2
		kfDur = kfDur + deltaT
	end
	if MOVE_LEFT then
		displacement.x = speed * deltaT * -1;
		keyFrame = 1
		kfDur = kfDur + deltaT
	end
	if MOVE_DOWN then
		displacement.y = speed * deltaT;
		keyFrame = 0
		kfDur = kfDur + deltaT
	end
	if MOVE_UP then
		displacement.y = speed * deltaT * -1;
		keyFrame = 3
		kfDur = kfDur + deltaT
	end
	return displacement.x, displacement.y, keyFrame, kfDur
end