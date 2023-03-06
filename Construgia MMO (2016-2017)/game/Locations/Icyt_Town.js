/*class Icyt_Town
{
	constructor(){
		this.title = "Icyt_Town";
	}
  
	Objects_Load(){
		// Defining
    
    // BARRIER
    this.barrier = new Barrier(1500, 1500);
    this.barrier.Load();
    // <--
    
		this.basim = new object(280, 94, 805, 350, "Resp_Basim", "graphics/buildings/_basim", false, 1, false);
		
		this.basim_barrier1 = new object(450, 80, 480, 15, "Resp_Basim_barrier1", "graphics/barrier", true, 0, false);
		this.basim_barrier2 = new object(450, 355, 480, 25, "Resp_Basim_barrier2", "graphics/barrier", true, 0, false);
		
		this.House1 = new object(-150, 240, 250, 310, "House_1", "graphics/buildings/shortHouse1",  true, 0.5, true, true); // x, y, w, h, name, graphics url, collider, colCut, hiding, offLight
		this.House2 = new object(400, 700, 250, 310, "House_2", "graphics/buildings/shortHouse2", true, 0.5);
		this.House3 = new object(400, -950, 250, 310, "House_3", "graphics/buildings/shortHouse3", true, 0.5);
		this.House4 = new object(1200, -350, 250, 310, "House_4", "graphics/buildings/shortHouse4", true, 0.5);
		
		this.Tree1 = new object(950, 550, 284.8, 476.8, "Tree_1", "graphics/buildings/Tree1", true, 0.5);
		this.Tree2 = new object(0, -450, 237.33, 397.33, "Tree_2", "graphics/buildings/Tree1", true, 0.5);
		this.Tree3 = new object(450, -470, 242.66, 309.33, "Tree_3", "graphics/buildings/Tree2", true, 0.5);
    
		this.Bush1 = new object(100, -150, 182.33, 110, "Bush_1", "graphics/building/bush1", true, 0.5);
		
		this.Grass1 = new object(250, 550, 79, 25.5, "Grass_1", "graphics/buildings/grass", false, 0, false);
    this.Grass2 = new object(650, -110, 79, 25.5, "Grass_2", "graphics/buildings/grass", false, 0, false);
    this.Grass3 = new object(700, -80, 79, 25.5, "Grass_3", "graphics/buildings/grass", false, 0, false);
		
		this.bulletin = new object(1400, 450, 90, 246, "Bulletin_1", "graphics/buildings/Bulletin", true, 0.5, true);
		
		this.Ground = new ground("Icyt_ground", 0, 0);
		
		this.Rantagir = new NPC("Rantagir - Comers Informator", 77, 700, 200, "graphics/theBasicKnowledgeGuardian.png", "Rantagir", 75, 210);
		this.Leahnna = new NPC("Leahnna", 77, 1200, 250, "graphics/leahnna.png", "Leahnna", 8, 62);
		
		this.Vernii = new NPC("Vernii", 77, 800, 600, "graphics/stephan.png", "Vernii");
		
		this.testEnemy = new Enemy("test_enemy", 200, 1100, 50, 50, "graphics/enemy1", 0.32, 100, 5, true, true, 5, 2000);
		
		// Load() / Start() functions
		this.basim.Load(false); // shadow off
		
		this.basim_barrier1.Load();
		this.basim_barrier2.Load();
		
		this.House1.Load();
		this.House2.Load();
		this.House3.Load();
		this.House4.Load();
		
		this.Tree1.Load();
		this.Tree2.Load();
    this.Tree3.Load();
		
		this.Bush1.Load();
		
		this.Grass1.Load();
    this.Grass2.Load();
    this.Grass3.Load();
		
		this.bulletin.Load();
		
		this.Ground.Load();
		
		this.Rantagir.Load(this.welcome);
		this.Leahnna.Load(this.leahnna_dialog);
		
		this.Vernii.Load(this.Vernii_Dialog);
		
		this.testEnemy.Load();
	}

	Objects_Update(){
    this.barrier.Update();
    
		this.Rantagir.Update();
		this.Leahnna.Update();
		
		this.Vernii.Update();
		
		this.basim.Draw();
		
		this.basim_barrier1.Draw();
		this.basim_barrier2.Draw();
		
		this.House1.Draw();
		this.House2.Draw();
		this.House3.Draw();
		this.House4.Draw();
		
		this.Tree1.Draw();
		this.Tree2.Draw();
    this.Tree3.Draw();
		
		this.Bush1.Draw();
		
		this.Grass1.Draw();
    this.Grass2.Draw();
    this.Grass3.Draw();
		
		this.bulletin.Draw();
		
		this.Ground.Work();
		
		this.testEnemy.Update();
	}

	Dialogs(){
		this.Vernii_Dialog2 = new Dialog("Duh...", "", "", "", "", 0, "", "Vernii_Dialog2");
		this.Vernii_Dialog = new Dialog("It is very nice weather today, isn't it?", "No, it isn't.", "", "", "", 1, "", "Vernii_Dialog", "Vernii_Dialog2");
		
    this.leahnna_dialog_nopac_howSpawn = new Dialog("Nobody knows. I mean, nobody of us - ordinary people. But there're people who know. They belong to the Great Council and they know all everything about this world. However, they keep in a secret some of this knowledge. ",
      "Do you think it's okay?", 
			"", 
			"", 
			"", 
			2, 
			"", // it has to be null
			"leahnna_dialog_nopac_howSpawn",
			"leahnna_dialog_nopac_isItOk",
			"",
			"",
		"stop", false);
    
    this.leahnna_dialog_nopac_finally_she_gotid_p4 = new Dialog("OK, so prepare for a lot of information. You're in Berrloa Creek - a small town in the south-center of the Dehrou Republic territory. It's probably gonna be your home for a few weeks. The guardians always spawn here on that platform that you woke up on a few seconds before. There's a carecenter in this town where most of your fellows had a chance to get over after the shock they had experienced. But I've  heard of ones who woke up completely conscious and not-shocked. ",
      "How is this that we just spawn here?", 
			"", 
			"", 
			"", 
			2, 
			"", // it has to be null
			"leahnna_dialog_nopac_finally_she_gotid_p4",
			"leahnna_dialog_nopac_howSpawn",
			"",
			"",
		"stop", false);     
    
    this.leahnna_dialog_nopac_easy_p2 = new Dialog("Oh, <b>sorry</b>.<br /><br />^300I’ve got a <b>crazy</b> day.<br /><br />So you’re probably one of the <b>Guardians</b>.<br /><br />Every guardian appear in <b>this place</b>, and they <b>never</b> remember anything of their <b>past life</b>. ",
      "What do you mean? And what is this ”place”?", 
			"", 
			"", 
			"", 
			2, 
			"", // it has to be null
			"leahnna_dialog_nopac_easy_p2",
			"leahnna_dialog_nopac_finally_she_gotid_p4",
			"",
			"",
		"stop", false);       
    
    this.leahnna_dialog_nopac_furry_sherlock_p3 = new Dialog("<b>You know?</b><br /><br />^500Being <b>rude</b> for someone who's trying to <b>help you</b> is really the opposite of <b>good</b>.",
      "No, I didn’t. I’m just being respectful for such an intelligent person. C’mon? How could you think I’m a courier?", 
			"", 
			"", 
			"", 
			2, 
			"", // it has to be null
			"leahnna_dialog_nopac_furry_sherlock_p3",
			"leahnna_dialog_nopac_finally_she_gotid_p4",
			"",
			"",
		"stop", false);                                        
    
    this.leahnna_dialog_nopac_furry_caman_p3 = new Dialog("<b>What?</b><br/><br/>^500Did I say something <b>wrong</b>?<br /><br />I'm just trying to figure out who you really <b>are</b>.",
      "Aghh. Well, I woke up on that platform up there and that yellow guy told me you can answer some of my questions.", 
			"Oh, so you were right. I was just kidding. I’m really a courier.", 
			"", 
			"", 
			2, 
			"", // it has to be null
			"leahnna_dialog_nopac_furry_caman_p3",
			"leahnna_dialog_nopac_easy_p2",
			"",
			"", // courier
		"stop", false);
    
    this.leahnna_dialog_nopac_furry_p2 = new Dialog("<b>HEY!<br /><br /> ^500CALM DOWN!<br /><br /></b>^500You're way more nervous than most of the <b>couriers</b> that I've met.<br /><br />You look even... ^200<b>shocked</b>.<br /><br />Is everything <b>OK</b>?",
      "Aghhh… C’mon!", 
			"<b>No shit sherlock!</b> It’s TRUE. I am shocked!", 
			"", 
			"", 
			2, 
			"", // it has to be null
			"leahnna_dialog_nopac_furry_p2",
			"leahnna_dialog_nopac_furry_caman_p3",
			"leahnna_dialog_nopac_furry_sherlock_p3",
			"",
		"stop", false);
    
		this.leahnna_dialog = new Dialog("Oh, <b>hello</b>.<br /><br />You look like you <b>don’t know</b> where you’ve come.<br /><br />If you’re here to deliver the package to the <b>Guardians Commitee</b> you should <b>go along</b> the street to the fountain and <b>turn right</b>.",
			"Do I look like I wanna deliver a package?!", 
			"No, I appeared on this platform up there<br />and that yellow guy told me you can answer some of my questions.", 
			"What packa… oh, a package. Sure, I just.<br />Well, it was addressed to you. ", 
			"So you work in the Guardians Committee?", 
			4, 
			"", // it has to be null
			"leahnna_dialog",
			"leahnna_dialog_nopac_furry_p2",
			"leahnna_dialog_nopac_easy_p2",
			"",
		"stop", true);
		
		{this.not_answer = new Dialog("<b>Rantagir</b> igores you.<br /><br />Now I should go to <b>Leahnna</b> and talk to her - <i>you thought</i>.",
			"Nevermind. See you later, Rant.", 
			"", 
			"", 
			"", 
			1, 
			"", // it has to be null
			"not_answer",
			"stop",
			"",
			"",
		"", true, function(){location_.Rantagir.Load(location_.not_answer);});}
		
		{this.welcome_part3_no = new Dialog("<b>No?</b> Haha, funny.<br /><br />I’m <b>sorry</b> to say that but you only have <b>choice</b> between <b>following</b> her or going to the world to let <b>monsters</b> eat you and throw the remains for <b>vultures</b> to finish.<br /><br />I think it’s <b>not</b> a tough choice. <b>Is it?</b>",
			"Oh no… What are vultures?", 
			"Yeah, maybe…", 
			"", 
			"", 
			2, 
			"", // it has to be null
			"welcome_part3_no",
			"not_answer",
			"not_answer",
			"",
		"", false);}
		
		{this.welcome_part3 = new Dialog("I am <b>too busy</b> to answer every <b>question</b> you ask!<br /><br />You’re <b>not</b> the <b>only</b> one.<br /><br /><br />The <b>others</b> will come soon.<br /><br />Ask <b>Leahnna</b>, she has more time.",
			"Okay...", 
			"No.", 
			"", 
			"", 
			2, 
			"", // it has to be null
			"welcome_part3",
			"stop",
			"welcome_part3_no",
			"",
		"", false, function(){location_.Rantagir.Load(location_.not_answer);});}
		
		{this.welcome_part2 = new Dialog("<b>Oh...</b><br />You’re so <b>confused</b> and <b>frightened</b>. As every <b>Comer</b>.<br /><br />You are in <b>Icyt Town</b>. It is the start town for all <b>Behindlight Comers</b>, you’ll probably stay here for a few weeks before you set off to see the <b>rest of the world</b>.<br /><br />You should go to find <b>Leahna</b>. She must be somewhere around.<br /><br /><i>Click on the <b>NPC (character)</b> to talk.</i>",
			"But wait… What is tha…", 
			"But you’ve just said you’re an informator.", 
			"No.", 
			"", 
			3, 
			"", // it has to be null
			"welcome_part2",
			"welcome_part3",
			"welcome_part3",
			"welcome_part3_no",
		"", false);}
		
		{this.welcome = new Dialog("Hey, <b>wake up</b>, <b>wake up</b>! It’s your time!<br /><br />Welcome to the world of <b>Construgia</b>!<br /><br />You look to be a little <b>confused</b> about all what you see. And you propably don't remember anything, don't worry, it's <b>normal</b>.<br /><br />By the way, my name is <b>Rantagir</b>, I am one of The Comers <b>Informators</b>, you can ask me about anything you want to know about <b>The Basic Knowledge</b>.",
			"Wa… wait! What?!", 
			"", 
			"", 
			"", 
			1, 
			"", // it has to be null
			"welcome",
			"welcome_part2",
			"",
			"",
		"", true);} // <-- false !!!
		
    if(firstTimePlay == 1)
		  this.welcome.On();
	}
	
	Start(){
		this.Dialogs();
		this.Objects_Load();
	}
	
	Update(){
		this.Objects_Update();
	}
}
*/