local id = ...

dt = 1
--if (flag == 1)
--then
--print(KeyIsDown(KEYBOARD.A))
--print()

if( GetFlag(id).f == 1)
then
	GetPosition(id).px = GetPosition(id).px + dt
	-- py = sin wave
	GetPosition(id).py = 39 + 10 * math.sin(GetPosition(id).px * 0.1)

	if(GetPosition(id).px > 99)
	then
	GetFlag(id).f = 0
	--print(flag)
	end
end

if(GetFlag(id).f == 0)
then
	GetPosition(id).px = GetPosition(id).px - dt
	GetPosition(id).py = 39 + 10 * math.sin(GetPosition(id).px * 0.1)
	if(GetPosition(id).px < -99)
	then
	GetFlag(id).f = 1
	--print(GetFlag(id).f)
	end
end
--print(GetFlag(id).f)
--if(KeyIsDown(KEYBOARD.A))
--then
--	Play("complete")
--	GetPosition(id).px = GetPosition(id).px - dt
	
--end
--a = GetUnusedID()
--GetPosition(a) = 


--	if (GetPosition(id).px > 99) 
--	then
--		flag = 0
--	end	
--end

	
--end

--while(flag < 1)
--do
--	if GetPosition(id).px == -100 then
--		flag = 1
--	end
--	GetPosition(id).px = GetPosition(id).px - dt
--end
