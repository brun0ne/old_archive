var keyState = {};
var canMove = true;

var canRight = true;
var canLeft = true;
var canUp = true;
var canDown = true;

var delta_ = 0;

var limit = 300,
    lastFrameTimeMs = 0,
    maxFPS = 60,
    delta = 0,
    timestep = 1000 / 60,
    fps = 60,
    framesThisSecond = 0,
    lastFpsUpdate = 0;

var chat_in;

function movement(location_){
  chat_in = $("#chat_in");
  
	window.addEventListener('keydown',function(e){
		keyState[e.keyCode || e.which] = true;
		
		if (keyState[40]) // DOWN
			e.preventDefault();
		if (keyState[39]) // RIGHT
			e.preventDefault();
		if (keyState[37]) // LEFT
			e.preventDefault();
		if (keyState[38]) // UP
			e.preventDefault();
    if (keyState[32] && !chat_in.is(":focus") && !$("#input_console").is(":focus") && !$("#input_console2").is(":focus")) // SPACE
			e.preventDefault();
	},true);
	
	window.addEventListener('keyup',function(e){
		keyState[e.keyCode || e.which] = false;
	},true);

	x = 100;
	
	requestAnimationFrame(gameLoop);
}

function Update(delta){
	delta_ = delta;
	
	// PLAYER MOVE
	
	if(canMove){
    if ((keyState[38] || (keyState[87] && !chat_in.is(":focus"))) && canUp){ // UP
			player.pos_y -= player.speed * delta;
			
			if(player.isDamaged === false)
				player.playerGraphics.css("background", "url(graphics/player/player_back.png)");
			
			player.direction = "up";
			
			canon1.y += player.speed * delta;
			canon2.y += player.speed * delta;
			
			//ground
			if(location_.Ground != null)
				location_.Ground.y -= player.speed * delta;
		}
		if ((keyState[40] || (keyState[83] && !chat_in.is(":focus"))) && canDown){ // DOWN
			player.pos_y += player.speed * delta;
			
			if(player.isDamaged === false)
				player.playerGraphics.css("background", "url(graphics/player/player.png)");
			
			player.direction = "down";
			
			canon1.y -= player.speed * delta;
			canon2.y -= player.speed * delta;
			
			//ground
			if(location_.Ground != null)
				location_.Ground.y += player.speed * delta;
		}
		if ((keyState[39] || (keyState[68] && !chat_in.is(":focus"))) && canRight){ // RIGHT
			player.pos_x += player.speed * delta;
			
			if(player.isDamaged === false)
				player.playerGraphics.css("background", "url(graphics/player/player_right.png)");
			
			player.direction = "right";
			
			canon1.x -= player.speed * delta;
			canon2.x -= player.speed * delta;
			
			//ground
			if(location_.Ground != null)
				location_.Ground.x += player.speed * delta;
		}
		if ((keyState[37] || (keyState[65] && !chat_in.is(":focus"))) && canLeft){ // LEFT
			player.pos_x -= player.speed * delta;
			
			if(player.isDamaged === false)
				player.playerGraphics.css("background", "url(graphics/player/player_left.png)");
			
			player.direction = "left";
			
			canon1.x += player.speed * delta;
			canon2.x += player.speed * delta;
			
			//ground
			if(location_.Ground != null)
				location_.Ground.x -= player.speed * delta;
		}
		if(keyState[32] && canon1.is !== true && licznik <= 0 && !chat_in.is(":focus")){ // SPACE
			canon1.Launch();
			licznik2 = 40;
		}
		if(keyState[32] && canon1.is === true && canon2.is !== true && licznik2 <= 0 && !chat_in.is(":focus")){ // SPACE
			canon2.Launch();
			licznik = 40;
		}
	}
	
/*	if(mouseDown){
		if(canon1.is !== true && licznik <= 0 && !chat_in.is(":focus")){
			canon1.Launch();
			licznik2 = 40;
		}
		if(canon1.is === true && canon2.is !== true && licznik2 <= 0 && !chat_in.is(":focus")){
			canon2.Launch();
			licznik = 40;
		}
	}*/
	
	// UPDATE FUNCTIONS
	
	if(location_ != null)
		location_.Update();
	
	player.Update();
  Players_Update();
	
	canon1.Update(delta);
	canon2.Update(delta);
}

function panic() {
    delta = 0;
}

function gameLoop(timestamp) { 
    if (timestamp < lastFrameTimeMs + (1000 / maxFPS)) {
        requestAnimationFrame(gameLoop);
        return;
    }
    delta += timestamp - lastFrameTimeMs;
    lastFrameTimeMs = timestamp;

    if (timestamp > lastFpsUpdate + 1000) {
        fps = 0.25 * framesThisSecond + 0.75 * fps;

        lastFpsUpdate = timestamp;
        framesThisSecond = 0;
    }
    framesThisSecond++;

    var numUpdateSteps = 0;
    while (delta >= timestep) {
        Update(timestep);
		
        delta -= timestep;
        if (++numUpdateSteps >= 240) {
            panic();
            break;
        }
    }
	requestAnimationFrame(gameLoop);
}