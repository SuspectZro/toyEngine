local id = ...
dt = 4
--if (flag == 1)
--then
--print(KeyIsDown(KEYBOARD.A))
--print()
if(GetHitBox(id).hit == "False")
then
if( GetFlag(id).f == 0)
then
	GetPosition(id).px = GetPosition(id).px + dt
	if(GetPosition(id).px > 80)
	then
	GetFlag(id).f = 0
	--print(flag)
	end
end

if(GetFlag(id).f == 1)
then
	GetPosition(id).px = GetPosition(id).px - dt
	if(GetPosition(id).px < -80)
	then
	GetFlag(id).f = 1
	--print(GetFlag(id).f)
	end
end
--GetPosition(id).py = -200
end
if(GetHitBox(id).hit == "True")
then
GetHitBox(id).hit = "False"
 
end