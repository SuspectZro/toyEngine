local id = ...
--print(KeyIsDown(KEYBOARD.A))

if(KeyIsDown(KEYBOARD.A))
then
	GetVelocity(id).vx = GetVelocity(id).vx - .2
end

if(KeyIsDown(KEYBOARD.D))
then
	GetVelocity(id).vx = GetVelocity(id).vx + .2
end

if(KeyIsDown(KEYBOARD.S))
then
	--GetPosition(id).py = GetPosition(id).py - 2
	GetSprite(id).name = "p1p"
end

if(KeyIsDown(KEYBOARD.W))
then
	GetVelocity(id).vy = GetVelocity(id).vy + 1
end

if(GetPosition(id).py < -30)
then
	GetVelocity(id).vy = 0
	GetPosition(id).py = -29.5
end