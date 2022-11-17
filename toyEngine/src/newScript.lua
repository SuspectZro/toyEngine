function runState(id)
	-- body
		state = GetState(id).state
		--State that need a counter------------
		if( state == "Walking" or state == "Idle" or state == "Punch" or state == "Crouching" or state == "Dash" or state == "Slide")
		then	
			
			if (state == "Walking" )
			then
			--	print(GetState(id).counter)
			--	print(GetState(id).state)
				GetSprite(id).name = "rWalk"
				GetState(id).counter = GetState(id).counter - 1
				--print(GetFlag(id).f)
				GetFlag(id).f = GetFlag(id).f - 1
				if(GetFlag(id).f > 0 and GetFlag(id).f < 6)
				then
					
					print("combo")
				end
			end
			if(state == "Dash")
			then
				--print(GetState(id).counter)
				--print(GetState(id).state)
				GetSprite(id).name = "rDash"
				GetState(id).counter = GetState(id).counter - 1
				GetVelocity(id).vx = 1
			end
			if(state == "Slide")
			then
				--print(GetState(id).counter)
				--print(GetState(id).state)
				GetSprite(id).name = "rSlide"
				GetState(id).counter = GetState(id).counter - 1
				--GetVelocity(id).vx = GetVelocity(id).vx + 1
				if(GetState(id).counter == 0)
				then
					GetState(id).state = "Idle"
				end
				--print(GetState(id).counter)
			end

			if(state == "Punch")
			then
				--print(GetState(id).counter)
				--print(GetState(id).state)
				GetSprite(id).name = "p1p"
				GetState(id).counter = GetState(id).counter - 1
			end
			if(state == "Crouching")
			then
				--print(GetState(id).counter)
				GetSprite(id).name = "rCrouch"
				GetState(id).counter = GetState(id).counter - 1
				if(GetState(id).counter == 0)
				then
					GetState(id).state = "Idle"
				end

			end
			if(GetState(id).counter < 8 and state ~= "Crouching" and state ~= "Slide")
			then
				--print(state)
				GetState(id).state = "Idle"
				GetSprite(id).name = "player1"
				if(GetState(id).counter > 0)
				then
				GetState(id).counter = GetState(id).counter - 1
				end
			end
		end
		-----state without counter--------------------
		
		if(state == "Jumping")
		then
			GetSprite(id).name = "rJ"
			if(GetPosition(id).py < -27)
			then
				GetState(id).state = "Idle"
				GetState(id).counter = 1
				--GetSprite(id).name = "player1"
			end
		end
		
end

local id = ...

runState(id)
--print(GetVelocity(id).vy)
--print(GetVelocity(id).vx)
--Punch------------------------
if(KeyIsDown(KEYBOARD.E))
then
	if(GetState(id).counter == 0)
	then
		GetState(id).state = "Punch"
		GetState(id).counter = 20
	end
end
--print(GetState(id).state)
if( GetState(id).state ~= "Jumping" and GetState(id).state ~= "Slide")
then
	if(GetState(id).state ~= "Dash")
	then

GetVelocity(id).vx = 0.0
end
--GetVelocity(id).vy = 0.0
-----walk back and forth -----------------
if(KeyIsDown(KEYBOARD.A)  and GetState(id).state ~= "Crouching" and GetState(id).state ~= "Punch" and GetState(id).state ~= "Dash")
then
	if(GetState(id).counter == 0)
	then
		GetState(id).state = "Walking"
		GetState(id).counter = 20		
	end
	GetVelocity(id).vx = GetVelocity(id).vx - 1
	GetFlag(id).f = 8
end
---walk foward or double foward will Dash---------------------
if(KeyIsDown(KEYBOARD.D) and GetState(id).state ~= "Punch" and GetState(id).state ~= "Crouching")
then
	if(GetState(id).counter == 0 and GetPosition(id).py < -26 )
	then
		GetState(id).state = "Walking"
		GetState(id).counter = 20	
		--print(GetFlag(id).f)
	end
	
	GetVelocity(id).vx = GetVelocity(id).vx + 1
	if(GetFlag(id).f > 0 and GetFlag(id).f < 6)
	then
		--print("Dash")	
		
		--GetVelocity(id).vx - 3
		GetState(id).state = "Dash"
		GetState(id).counter = 20
		--GetVelocity(id).vx = GetVelocity(id).vx - 2
	end
	GetFlag(id).f = 8
end

--Crouching--------------------
if(KeyIsDown(KEYBOARD.S))
then
	if(GetState(id).state ~= "Dash")
	then
		GetState(id).state = "Crouching"
		GetState(id).counter = 2
	end
	if(GetState(id).state == "Dash" and GetVelocity(id).vx ~= 0.0)
	then
		print("SLIDE")
		GetState(id).state = "Slide"
		GetState(id).counter = 30
	end
end

--Jumping------------------------
if(KeyIsDown(KEYBOARD.W))
then
		GetState(id).state = "Jumping"
	GetVelocity(id).vy = GetVelocity(id).vy + 1.8
end

--end
end
--Ground----------------
if(GetPosition(id).py < -30)
then
	GetVelocity(id).vy = 0
	GetPosition(id).py = -29.9
end

