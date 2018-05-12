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
	if MOVE_DOWN then
		displacement.y = speed * FRAME_DELTA_TIME;
		keyFrame = 0
		kfDur = kfDur + FRAME_DELTA_TIME
	end
	if MOVE_UP then
		displacement.y = speed * FRAME_DELTA_TIME * -1;
		keyFrame = 3
		kfDur = kfDur + FRAME_DELTA_TIME
	end

	mt.SetAniKey(player, keyFrame)
	mt.SetKeyFrameDur(player, kfDur)
	mt.MoveSprite(player, displacement.x, displacement.y)

	return 
end