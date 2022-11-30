local x = ...
Play("complete")
--print("executing master script")
--LoadScript("test2", "C:\\Users\\ruiz_\\toyEngine\\toyEngine\\src\\player1.lua")
--LoadScript("test1", "C:\\Users\\ruiz_\\toyEngine\\toyEngine\\src\\player1.lua")

-- load bg
id = GetUnusedId()
GetPosition(id).px = 0
GetPosition(id).py = 39
GetSprite(id).name = "bg"
GetSprite(id).size = 140

id = GetUnusedId()
--print(id)
--EntityID ID = GetUnusedID();
GetPosition(id).px = 20
GetPosition(id).py = 50
GetSprite(id).name = "rbow"
GetSprite(id).size = 10
GetScript(id).name = "test1"
----Player1-------------------------
id = GetUnusedId()
GetPosition(id).px = -90
GetPosition(id).py = -30
GetVelocity(id).vx = 0.0
GetVelocity(id).vy = 0.0
GetGravity(id).mps = -0.08
GetSprite(id).name = "player1"
GetSprite(id).size = 50
GetFlag(id).f = 0.0
GetScript(id).name = "player1"
GetState(id).state = "Idle"
GetPushBox(id).width = 30
GetPushBox(id).height = 30
---Player2---------------------------
id = GetUnusedId()
GetPosition(id).px = 90
GetPosition(id).py = -30
GetVelocity(id).vx = 0.0
GetVelocity(id).vy = 0.0
GetGravity(id).mps = -0.08
GetSprite(id).name = "player2"
GetSprite(id).size = 50
GetFlag(id).f = 0.0
GetScript(id).name = "player2"
GetState(id).state = "Idle"
GetPushBox(id).width = 30
GetPushBox(id).height = 30
---FireBall----------
id = GetUnusedId()
GetVelocity(id).vx = 0.0
GetVelocity(id).vy = 0.0
GetSprite(id).name = "fireBall"
GetSprite(id).size = 50
GetFlag(id).f = 0.0
GetHitBox(id).hit = false 
--GetScript(id).name = "fireBall"
GetPushBox(id).width = 30
GetPushBox(id).height = 30
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