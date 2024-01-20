local x = ...
Play("complete")

-- Load bg
id = GetUnusedId()
GetPosition(id).px = 0
GetPosition(id).py = 39
GetSprite(id).name = "bg"
GetSprite(id).size = 140
GetIsFlipped(id).isFlipped = false

id = GetUnusedId()
GetPosition(id).px = 20
GetPosition(id).py = 50
GetSprite(id).name = "rbow"
GetSprite(id).size = 10
GetScript(id).name = "aiRbow.lua"
GetPhysics(id).velocityX = 0.0
GetPhysics(id).velocityY = 0.0
GetFlag(id).f = 1
GetIsFlipped(id).isFlipped = false
-- floor--
id = GetUnusedId()
GetPosition(id).px = 0
GetPosition(id).py = -220
GetCollision(id).isStatic = true
--this is  used to see the boxes for collision detection
GetSprite(id).name = "rainb" 
GetSprite(id).size = 140
GetIsFlipped(id).isFlipped = false
GetCollision(id).width = 150
GetCollision(id).height = 130
GetPhysics(id).velocityX = 0.0
GetPhysics(id).velocityY = 0.0
GetPhysics(id).gravity = 0
GetPhysics(id).friction = 0.90
--GetShape(id).scale = 10
--GetShape(id).color = {1,0,0,1}
--GetPushBox(id).pushW = 10
--GetPushBox(id).pushH = 10
--GetPushBox(id).pushX = 10
--GetPushBox(id).pushY = 10
--GetPushBox(id).color = {r = 1.0, g = 0.0, b = 0.0, a = 1.0}

--GetPushBox(id).color = {1.0,0.0,0.0,1.0}
--GetScript(id).name = "player1.lua"
-- Player1
id = GetUnusedId()
GetPosition(id).px = 0
GetPosition(id).py = 140
GetPhysics(id).velocityX = 0.0
GetPhysics(id).velocityY = 0.0
GetPhysics(id).gravity = -9.8
--GetSprite(id).name = "rainb"
GetSprite(id).name = "player1"
GetSprite(id).size = 50
GetIsFlipped(id).isFlipped = false
GetFlag(id).f = 1
GetScript(id).name = "player1.lua"
GetState(id).state = "Idle"
GetState(id).counter = 0
GetCollision(id).width = 10
GetCollision(id).height = 30
GetCollision(id).isStatic = false


-- Player2
id = GetUnusedId()
GetPosition(id).px = 90
GetPosition(id).py = -30
GetPhysics(id).velocityX = 0.0
GetPhysics(id).velocityY = 0.0
GetPhysics(id).gravity = -9.8
--GetSprite(id).name = "rainb"
GetSprite(id).name = "player2"
GetSprite(id).size = 50
GetIsFlipped(id).isFlipped = false
GetFlag(id).f = 0.0
GetScript(id).name = "player2.lua"
GetState(id).state = "Idle"
GetCollision(id).width = 10
GetCollision(id).height = 30
GetCollision(id).isStatic = false
---FireBall----------
--id = GetUnusedId()
--GetVelocity(id).vx = 2.5
--GetVelocity(id).vy = 0.0
--GetSprite(id).name = "fireBall"
--GetSprite(id).size = 50
--GetFlag(id).f = 0.0
--GetHitBox(id).hit = false 
--GetScript(id).name = "fireBall"
--GetPushBox(id).width = 30
--GetPushBox(id).height = 30
		--Position p;
	---	p.x = 20;
	--	p.y = 50;
	--	//Flag f;
	--	//f = 1.0;
	--	Get<Position>(ID) = p;
		
	--	std::cout << Get<Position>(ID).x << " \n";
	--	ID = GetUnusedID();
	--	Get<Sprite>(ID) = Sprite({ "rbow",10.0 });
	--	p.x = -50;
	--	p.y = -10;
	--	Get<Flag>(ID) = Flag({ 1.0 });
	--	Get<Script>(ID) = Script({ "test1" });
	--	Get<Position>(ID) = p;
		
	--	ID = GetUnusedID();
	--	Get<Sprite>(ID) = Sprite({ "pink",30.0 });
	--	p.x = 100;
	--	p.y = 0;
	--	Get<Position>(ID) = p;
	-- wall--
id = GetUnusedId()
GetPosition(id).px = -280
GetPosition(id).py = -50
GetCollision(id).isStatic = true
--this is  used to see the boxes for collision detection
--GetSprite(id).name = "rainb" 
--GetSprite(id).size = 130
GetIsFlipped(id).isFlipped = false
GetCollision(id).width = 150
GetCollision(id).height = 300
GetPhysics(id).velocityX = 0.0
GetPhysics(id).velocityY = 0.0
GetPhysics(id).gravity = 0
GetPhysics(id).friction = 0.90

	-- wall--
id = GetUnusedId()
GetPosition(id).px = 280
GetPosition(id).py = -50
GetCollision(id).isStatic = true
--this is  used to see the boxes for collision detection
--GetSprite(id).name = "rainb" 
--GetSprite(id).size = 130
GetIsFlipped(id).isFlipped = false
GetCollision(id).width = 150
GetCollision(id).height = 300
GetPhysics(id).velocityX = 0.0
GetPhysics(id).velocityY = 0.0
GetPhysics(id).gravity = 0
GetPhysics(id).friction = 0.90