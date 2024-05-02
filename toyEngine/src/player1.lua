

function runState(id)
	local physics = GetPhysics(id)
	local hitboxes = GetHitBoxes(id)

	-- body
		state = GetState(id).state
		window = GetFlag(id).f

		--print(window)
		if(window > 0 )
		then
			GetFlag(id).f = GetFlag(id).f - 1
		end
		
		--State that need a counter------------
		if( state == "Walking" or state == "Idle" or state == "Punch" or state == "Crouching" or state == "Dash" or state == "Slide" or state == "Straight" or state == "CrouchingPunch" or state == "Crouching" or state == "Dash" or state == "Slide" or state == "Straight" or state == "CrouchingPunch" or state == "FireBall")
		then	
			
			if (state == "Walking" )
			then
				--GetFlag(id).f = 30
				GetSprite(id).name = "rWalk"
				GetState(id).counter = GetState(id).counter - 1
				GetFlag(id).f = GetFlag(id).f - 1
				
				if(GetFlag(id).f > 0 and GetFlag(id).f < 6)
				then
					
					print("combo")
				end
			--	GetFlag(id).f = 30
			end
			if(state == "Dash")
			then
			--GetFlag(id).f = 35	
			GetSprite(id).name = "rDash"
				GetState(id).counter = GetState(id).counter - 1
				--GetPhysics(id).velocityX = GetPhysics(id).velocityX + 0.10
				
				--physics.velocityX = 1
			end
			if(state == "Slide")
			then
				GetSprite(id).name = "rSlide"
				GetState(id).counter = GetState(id).counter - 1
				physics.velocityX = physics.velocityX
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
				if(GetState(id).counter < 60)
				then
					GetSprite(id).name = "p1s"
				end
			end
			if(state == "Crouching")
			then
			
				GetSprite(id).name = "rCrouch"
				GetState(id).counter = GetState(id).counter - 1
				--GetPushBox(id).width = 0
				--GetPushBox(id).height = 15
				if(GetState(id).counter == 0)
				then
					--GetPushBox(id).width = 30
					--GetPushBox(id).height = 30
					GetState(id).state = "Idle"
				end

			end
			if(state == "CrouchingPunch")
			then
				GetSprite(id).name = "rCrouchP"
				GetState(id).counter = GetState(id).counter - 1			
				if(GetState(id).counter < 30)
				then
					GetSprite(id).name = "rCrouch"
					if(GetState(id).counter > 20)
					then
						GetState(id).counter = GetState(id).counter - 1
					end
					if(GetState(id).counter == 20)
					then
						GetState(id).state = "Crouching"
					end
				end
			end
			if(GetState(id).counter > 0)
			then
			GetState(id).counter = GetState(id).counter - 1
				if(GetState(id).counter < 8 )
				then
				
				GetState(id).state = "Idle"
				GetSprite(id).name = "player1"

				--if(GetState(id).counter > 0)
				--then
				--GetState(id).counter = GetState(id).counter - 1
				--end
				end
			end
		end
		-----state without counter--------------------
		
		if(state == "Jumping")
		then
			GetSprite(id).name = "rJ"
			--GetPushBox(id).width = 0
			--GetPushBox(id).height = 15
			
			if(GetPhysics(id).velocityY == 0.0)
			then
				--GetPushBox(id).width = 30
				--GetPushBox(id).height = 30
				GetState(id).state = "Idle"
				GetSprite(id).name = "player1"
				--GetState(id).counter = 1
			end
		end

		
end

local id = ...

runState(id)

--Punch------------------------
if KeyIsDown(KEYBOARD.E) then
    
    if GetState(id).counter == 0 
	then
		hitboxes = GetHitBoxes(id)
        GetState(id).state = "Punch"
		hitboxIndex = 1
        hitboxes[1].offsetX = 20
        hitboxes[1].offsetY = -10
		hitboxes[1].hit = true
        GetState(id).counter = 40
		print("Before modification:")
		UpdateHitBox(id, hitboxIndex, { hit = true, offsetX = 20, offsetY = -10 })
		PrintHitBoxes(hitboxes)

		--GetHitBoxes(id) = hitboxes
    end
	print("After modification:")
    --PrintHitBoxes(hitboxes)
end


if(KeyIsDown(KEYBOARD.R))
then
	if(GetState(id).counter == 0)
	then
		GetState(id).state = "Straight"
		GetState(id).counter = 80
	end
end

--Ground----------------


if(KeyIsDown(KEYBOARD.D) and GetState(id).state ~= "Jumping" and GetState(id).state ~= "Dash" )
then
    if GetPhysics(id).velocityX < 0
	then
		GetPhysics(id).velocityX = 0.0
	end
	if( GetState(id).counter == 0)
	then
		GetState(id).state = "Walking"
		GetState(id).counter = 20
		GetPhysics(id).velocityX = GetPhysics(id).velocityX + 0.25

	end
	if(GetFlag(id).f > 0 and GetFlag(id).f < 18 and GetState(id).state == "Walking" and GetIsFlipped(id).isFlipped == false )
	then
		GetState(id).state = "Dash"
		GetState(id).counter = 30
		GetPhysics(id).velocityX = 1.5
	end

	GetFlag(id).f = 20

end

if(KeyIsDown(KEYBOARD.A) and GetState(id).state ~= "Jumping" and GetState(id).state ~= "Dash")
then
	if GetPhysics(id).velocityX > 0
	then
		GetPhysics(id).velocityX = 0.0
	end
if( GetState(id).counter == 0)
	then
		GetState(id).state = "Walking"
		GetState(id).counter = 20
		GetPhysics(id).velocityX = GetPhysics(id).velocityX - 0.25

	end
		if(GetFlag(id).f > 0 and GetFlag(id).f < 18 and GetState(id).state == "Walking" and GetIsFlipped(id).isFlipped == true )
	then
		GetState(id).state = "Dash"
		GetState(id).counter = 30
		GetPhysics(id).velocityX = -1.5
	end

	GetFlag(id).f = 20
end

--Crouching-----------
if(KeyIsDown(KEYBOARD.S) )
then
	if(GetState(id).state ~= "Jumping" and GetState(id).state ~= "CrouchingPunch" )
	then
	GetState(id).state = "Crouching"
	GetState(id).counter = 20
	GetPhysics(id).velocityX = 0.0
	if(KeyIsDown(KEYBOARD.E) and GetState(id).state == "Crouching" )
		then
			GetState(id).counter = 60
			GetState(id).state = "CrouchingPunch"
		end
	end
end

if(KeyIsDown(KEYBOARD.W) and GetState(id).state ~= "Jumping" )
then
	GetState(id).state = "Jumping"
	GetPhysics(id).velocityY = GetPhysics(id).velocityY + 5.0
	--GetState(id).counter = 20
	--GetVelocity(id).vy = GetVelocity(id).vy + 1.8
end
-- Set velocity to zero when neither A nor D is pressed
if  ( not KeyIsDown(KEYBOARD.A) and  not KeyIsDown(KEYBOARD.D) and GetState(id).state ~= "Jumping" and GetState(id).state ~= "Dash"  or GetState(id).state == "Punch" ) then
    GetPhysics(id).velocityX = 0.0
end

function PrintHitBoxes(hitboxes)
print("in function")
    --local hitboxes = GetHitBoxes(id)

    -- Print some debug information
    print("Entity ID: " .. id)
    print("Hitboxes count: " .. #hitboxes)

    -- Iterate over the hitboxes and print their details
    for i, hitboxData in ipairs(hitboxes) do
    print("Hitbox " .. i .. ":")
    print("Width: " .. hitboxData.width)
    print("Height: " .. hitboxData.height)
    print("Hit: " .. tostring(hitboxData.hit))
    print("OffsetX: " .. hitboxData.offsetX)  
    print("OffsetY: " .. hitboxData.offsetY)  
    print("-------------------------")
end

end
