function runState(id)
	-- body
		state = GetState(id).state
		--State that need a counter------------
		if( state == "Walking" or state == "Idle" or state == "Punch" or state == "Crouching" or state == "Dash" or state == "Slide" or state == "Straight" or state == "CrouchingPunch" or state == "Crouching" or state == "Dash" or state == "Slide" or state == "Straight" or state == "CrouchingPunch" or state == "FireBall")
		then	
			
			if (state == "Walking" )
			then
				GetSprite(id).name = "rWalk"
				GetState(id).counter = GetState(id).counter - 1
				GetFlag(id).f = GetFlag(id).f - 1
				if(GetFlag(id).f > 0 and GetFlag(id).f < 6)
				then
					
					print("combo")
				end
			end
			if(state == "Dash")
			then
				GetSprite(id).name = "rDash"
				GetState(id).counter = GetState(id).counter - 1
				GetVelocity(id).vx = 1
			end
			if(state == "Slide")
			then
				GetSprite(id).name = "rSlide"
				GetState(id).counter = GetState(id).counter - 1
				GetVelocity(id).vx = GetVelocity(id).vx + 0.25
				if(GetState(id).counter == 0)
				then
					GetState(id).state = "Idle"
				end
			end
			if(state == "FireBall")
			then
			GetState(id).counter = GetState(id).counter - 1
				if(GetState(id).counter > 19)
				then
					GetSprite(id).name = "fireBall1"
				end	
				if(GetState(id).counter < 20)
				then
					GetSprite(id).name = "fireBall2"
						--GetState(id).state = "Idle"
				end
				if(GetState(id).counter == 0)
				then
					GetState(id).state = "Idle"
					GetState(id).charge = false
					GetFlag(id).charge = 0
				end
			end
			if(state == "Punch")
			then
				GetSprite(id).name = "p1p"
				GetState(id).counter = GetState(id).counter - 1
			end
		
			if(state == "Straight")
			then
				GetState(id).counter = GetState(id).counter - 1
				if(GetState(id).counter < 30)
				then
					GetSprite(id).name = "p1s"
				end
			end
			if(state == "Crouching")
			then
				GetSprite(id).name = "rCrouch"
				GetState(id).counter = GetState(id).counter - 1
				GetPushBox(id).width = 0
				GetPushBox(id).height = 15
				if(GetState(id).counter == 0)
				then
					GetPushBox(id).width = 30
					GetPushBox(id).height = 30
					GetState(id).state = "Idle"
				end

			end
			if(state == "CrouchingPunch")
			then
				GetSprite(id).name = "rCrouchP"
				GetState(id).counter = GetState(id).counter - 1			
				if(GetState(id).counter < 14)
				then
					GetSprite(id).name = "rCrouch"
					if(GetState(id).counter > 2)
					then
						GetState(id).counter = GetState(id).counter - 1
					end
					if(GetState(id).counter == 2)
					then
						GetState(id).state = "Crouching"
					end
				end
			end
			if(GetState(id).counter < 8 and state ~= "Crouching" and state ~= "CrouchingPunch" and state ~= "Slide")
			then
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
			GetPushBox(id).width = 0
			GetPushBox(id).height = 15
			if(GetPosition(id).py < -27)
			then
				GetPushBox(id).width = 30
				GetPushBox(id).height = 30
				GetState(id).state = "Idle"
				GetState(id).counter = 1
			end
		end
		
end

local id = ...

runState(id)

--Punch------------------------
if(KeyIsDown(KEYBOARD.E) and GetState(id).state ~= "FireBall")
then
	if(GetState(id).counter == 0 and GetState(id).charge == false)
	then
		GetState(id).state = "Punch"
		GetState(id).counter = 20
	end
	if(GetState(id).charge == true and GetState(id).state ~= "Jumping")
	then
		print("FireBall")
		GetState(id).state = "FireBall"
		GetState(id).counter = 40
	end
end

if(KeyIsDown(KEYBOARD.R))
then
	if(GetState(id).counter == 0)
	then
		GetState(id).state = "Straight"
		GetState(id).counter = 40
	end
end
--------charge move for FireBall---------
if(KeyIsDown(KEYBOARD.A) and GetState(id).state ~= "FireBall")
then
	GetFlag(id).charge = GetFlag(id).charge + 1
	if(GetFlag(id).charge > 60)
	then
		GetState(id).charge = true
		--GetState(id).counter = 20
	end
--else
	--GetFlag(id).charge = 0
	--GetState(id).charge = false
else
	GetFlag(id).charge = 0
	GetState(id).charge = false
end
--print(GetState(id).state)
if( GetState(id).state ~= "Jumping" and GetState(id).state ~= "Slide")
then
	if(GetState(id).state ~= "Dash")
	then
	--GetVelocity(id).vx = 0.0
GetVelocity(id).vx = GetVelocity(id).vx * 0.75 
end
--GetVelocity(id).vy = 0.0
-----walk back and forth -----------------
if(KeyIsDown(KEYBOARD.A)  and GetState(id).state ~= "Crouching" and GetState(id).state ~= "Punch" and GetState(id).state ~= "Dash" and GetState(id).state ~= "Straight" and GetState(id).state ~= "CrouchingPunch" and GetState(id).state ~= "FireBall")
then
	if(GetState(id).counter == 0)
	then
		GetState(id).state = "Walking"
		GetState(id).counter = 20		
	end
	GetVelocity(id).vx = GetVelocity(id).vx - 0.25
	GetFlag(id).f = 0
end
---walk foward or double foward will Dash---------------------
if(KeyIsDown(KEYBOARD.D) and GetState(id).state ~= "Punch" and GetState(id).state ~= "Crouching" and GetState(id).state ~= "Straight" and GetState(id).state ~= "CrouchingPunch" and GetState(id).state ~= "FireBall")
then
	if(GetState(id).counter == 0 and GetPosition(id).py < -26 )
	then
		GetState(id).state = "Walking"
		GetState(id).counter = 20	
		--print(GetFlag(id).f)
	end
	
	GetVelocity(id).vx = GetVelocity(id).vx + 0.25
	if(GetFlag(id).f > 0 and GetFlag(id).f < 6)
	then
		GetState(id).state = "Dash"
		GetState(id).counter = 20
		--GetVelocity(id).vx = GetVelocity(id).vx - 2
	end
	GetFlag(id).f = 8
	GetFlag(id).charge = 0
end

--Crouching--------------------
if(KeyIsDown(KEYBOARD.S) and GetState(id).state ~= "FireBall")
then
	if(GetState(id).state ~= "Dash" and GetState(id).state ~= "CrouchingPunch")
	then
		GetState(id).state = "Crouching"
		GetState(id).counter = 2
		
		if(KeyIsDown(KEYBOARD.E) and GetState(id).state == "Crouching")
		then
			GetState(id).counter = 26
			GetState(id).state = "CrouchingPunch"
		end
	end
	--print(GetState(id).state)
	----combo from dash foward to slide kick------------------
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

