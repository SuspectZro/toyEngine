function runState(id)
	-- body
		state = GetState(id).state
		--State that need a counter------------
		if( state == "Walking" or state == "Idle" or state == "Punch" or state == "Crouching" or state == "Dash" or state == "Slide" or state == "Straight" or state == "CrouchingPunch")
		then	
			
			if (state == "Walking" )
			then
				GetSprite(id).name = "lWalk2"
				GetState(id).counter = GetState(id).counter - 1
				GetFlag(id).f = GetFlag(id).f - 1
				if(GetFlag(id).f > 0 and GetFlag(id).f < 6)
				then
					
					print("combo")
				end
			end
			if(state == "Dash")
			then
				GetSprite(id).name = "lDash2"
				GetState(id).counter = GetState(id).counter - 1
				GetVelocity(id).vx = -1
			end
			if(state == "Slide")
			then
				GetSprite(id).name = "lSlide2"
				GetState(id).counter = GetState(id).counter - 1
				--GetVelocity(id).vx = GetVelocity(id).vx + 1
				if(GetState(id).counter == 0)
				then
					GetState(id).state = "Idle"
				end
			end

			if(state == "Punch")
			then
				GetSprite(id).name = "p2p"
				GetState(id).counter = GetState(id).counter - 1
			end
		
			if(state == "Straight")
			then
				GetState(id).counter = GetState(id).counter - 1
				if(GetState(id).counter < 30)
				then
					GetSprite(id).name = "p2s"
				end
			end
			if(state == "Crouching")
			then
				GetSprite(id).name = "lCrouch2"
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
				GetSprite(id).name = "lCrouchP2"
				GetState(id).counter = GetState(id).counter - 1			
				if(GetState(id).counter < 14)
				then
					GetSprite(id).name = "lCrouch2"
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
				GetSprite(id).name = "player2"
				if(GetState(id).counter > 0)
				then
				GetState(id).counter = GetState(id).counter - 1
				end
			end
		end
		-----state without counter--------------------
		
		if(state == "Jumping")
		then
			GetSprite(id).name = "lJ2"
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
if(KeyIsDown(KEYBOARD.P))
then
  GetScript(id).name = "player2"
end
--GetState(id).state = "Idle"

if(GetPosition(id).py < -30)
then
	GetVelocity(id).vy = 0
	GetPosition(id).py = -29.9
end
--GetState(id).state = "Idel"

