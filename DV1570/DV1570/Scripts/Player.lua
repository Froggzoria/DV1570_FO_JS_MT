function Move(key)
	local var
	if key == 71 or key == 73 then  
		print(key) 
		var = -0.5
	end
	if key == 72 or key == 74 then 
		print(key)
		var = 0.5
	end
	return var
end
