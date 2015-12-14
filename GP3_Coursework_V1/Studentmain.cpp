#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


//#include <windows.h>
#include "GameConstants.h"
#include "windowOGL.h"
#include "cWNDManager.h"
#include "cColours.h"
#include "cShapes.h"
#include "cPyramid.h"
#include "cCube.h"
#include "cSphere.h"
#include "cMaterial.h"
#include "cLight.h"
#include "cStarfield.h"
#include "cFontMgr.h"
#include "cCamera.h"
#include "cInputMgr.h"
#include "cSoundMgr.h"
#include "cModelLoader.h"
#include "cModel.h"
#include "cPlayer.h"
#include "cEnemy.h"
#include "cLaser.h"
#include "tardisWarsGame.h"

#include "ControllerHandler.h"


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow){

    //Set our window settings
    const int windowWidth = 1024;
    const int windowHeight = 768;
    const int windowBPP = 16;


    //This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

	// This is the sound manager
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();
	
	//The example OpenGL code
    windowOGL theOGLWnd;

    //Attach our example to our window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);


    //Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
    {
        //If it fails

        MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
    {
        MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }


	cCube cube;

	// Create Texture map
	cTexture tardisTexture;
	tardisTexture.createTexture("Models/tardis.png");
	cTexture spaceShipTexture;
	spaceShipTexture.createTexture("Models/SpaceShip/sh3.jpg");
	cTexture laserTexture;
	laserTexture.createTexture("Models/laser.tga");
	cTexture starTexture;
	starTexture.createTexture("Images/background.png");


	cTexture cubeTexture;
	cubeTexture.createTexture("Images/diceFaces.png");

	// Create Materials for lights
	cMaterial sunMaterial(lightColour4(0.0f, 0.0f, 0.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(0, 0, 0, 1.0f), 5.0f);

	// Create Light
	cLight sunLight(GL_LIGHT0, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(0, 0, 20, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	cLight lfLight(GL_LIGHT1, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(30, 0, 100, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	cLight rfLight(GL_LIGHT2, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(-30, 0, 100, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	cLight cbLight(GL_LIGHT3, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(0, 0, -100, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	//Define Ambient light for scene
	GLfloat g_Ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, g_Ambient);

	// load game fonts
	// Load Fonts
	LPCSTR gameFonts[3] = { "Fonts/digital-7.ttf", "Fonts/space age.ttf", "Fonts/doctor_who.ttf" };

	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("Space", gameFonts[1], 24);
	theFontMgr->addFont("DrWho", gameFonts[2], 48);

	// load game sounds
	// Load Sound
	LPCSTR gameSounds[3] = { "Audio/who10Edit.wav", "Audio/shot007.wav", "Audio/explosion2.wav" };

	theSoundMgr->add("Theme", gameSounds[0]);
	theSoundMgr->add("Shot", gameSounds[1]);
	theSoundMgr->add("Explosion", gameSounds[2]);

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	// Model
	cModelLoader tardisMdl;
	tardisMdl.loadModel("Models/tardis.obj", tardisTexture); // Player
	//tardisMdl.loadModel("Models/Stormtrooper/Stormtrooper.obj", tardisTexture); // Player

	cModelLoader spaceShipMdl;
	spaceShipMdl.loadModel("Models/SpaceShip/Sample_Ship.obj", spaceShipTexture); // Enemy
	
	cModelLoader theLaser;
	theLaser.loadModel("Models/laser.obj", laserTexture);

	for (int loop = 0; loop < 5; loop++)
	{
		theEnemy.push_back(new cEnemy);
		theEnemy[loop]->randomise();
		theEnemy[loop]->setMdlDimensions(spaceShipMdl.getModelDimensions());
		theEnemy[loop]->setScale(glm::vec3(5, 5, 5));
	}


	cPlayer thePlayer;                                                                    //speed
	thePlayer.initialise(glm::vec3(0, 0, 0), 0.0f, glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), 1.0f, true);
	thePlayer.setMdlDimensions(tardisMdl.getModelDimensions());
	thePlayer.attachInputMgr(theInputMgr);
	thePlayer.attachSoundMgr(theSoundMgr);

	cCamera debugCamera, gameCamera;
	gameCamera.setTheCameraPos(glm::vec3(0.0f, 0.0f, 75.0f));
	gameCamera.setTheCameraLookAt(glm::vec3(0.0f, 0.0f, 90.0f)); //rotate to face tardis/player
	gameCamera.setTheCameraUpVector(glm::vec3(0.0f, 1.0f, 0.0f)); // pointing upwards in world space
	gameCamera.setTheCameraAspectRatio(windowWidth, windowHeight);
	gameCamera.setTheProjectionMatrix(45.0f, gameCamera.getTheCameraAspectRatio(), 0.1f, 1000.0f);
	gameCamera.update();

	debugCamera = gameCamera;

	float tCount = 0.0f;
	string outputMsg;

	theSoundMgr->getSnd("Theme")->playAudio(AL_LOOPING);
	std::vector<cLaser*> laserList;
	std::vector<cLaser*>::iterator index;


	cube.initialise(cubeTexture);

	bool toggleCamera = false;
	ControllerHandler cHandler;
	cHandler.setNumberPlayers(1);

	cSphere theEarth(3, 30, 30);

	cTexture earthTexture;
	earthTexture.createTexture("Images/Earth.png");
	
	theEarth.initialise(earthTexture.getTexture(), glm::vec3(0, 0, -10), glm::vec3(0, 0, 0));
	float earthRotSpeed = 3.0f;

	// cMaterial sunMaterial(lightColour4(0.0f, 0.0f, 0.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(0, 0, 0, 1.0f), 5.0f);
	//cMaterial earthMaterial(lightColour4(0.2f, 0.2f, 0.2f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(0, 0, 0, 1.0f), 50.f);
	cMaterial earthMaterial(lightColour4(0.2f, 0.2f, 0.2f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(0, 0, 0, 1.0f), .1f);

   //This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
    {
		pgmWNDMgr->processWNDEvents(); //Process any window events

		if (cHandler.getState() == true){ //check controller is connected
			//cHandler.Vibrate(65000.0f, 65000.0f);
			thePlayer.attachControllerHander(cHandler);
			cHandler.CheckDeadZones();
			//cHandler.CheckControllerInput();
		}
		else{
			//turn off vibrations
		}

		thePlayer.setMouseXPosition(theInputMgr->getMouseXPos());
		thePlayer.setMouseYPosition(theInputMgr->getMouseYPos());

		if (theInputMgr->isKeyDown(VK_END)){ //toggleCamera to debug or game camera
			toggleCamera = !toggleCamera;
		}else
		if (theInputMgr->isKeyDown(VK_TAB) && thePlayer.getSoundOff() != true){ //turns off sound or pauses it
			thePlayer.setSoundOff(true);
			theSoundMgr->getSnd("Theme")->pauseAudio();
			theSoundMgr->getSnd("Shot")->stopAudio();
			theSoundMgr->getSnd("Explosion")->stopAudio();
		}else
		if (theInputMgr->isKeyDown(VK_CAPITAL) && thePlayer.getSoundOff() != false){
				thePlayer.setSoundOff(false); //turns sound back on for player actions
				theSoundMgr->getSnd("Theme")->resumeAudio(); //resumes audio 
		}

		if (toggleCamera == true){
			int mouseX = theInputMgr->getMouseXPos(); //get mouse position
			int mouseY = theInputMgr->getMouseYPos();
			glm::vec2 mousePos = glm::vec2(mouseX, mouseY); 
			debugCamera.movement(theInputMgr); 
			debugCamera.mouseUpdate(mousePos);
			debugCamera.Update2(); //update camera
		}
		else{ //use default game camera behavior instead
			gameCamera.trackPlayer(glm::vec3(thePlayer.getPosition().x, thePlayer.getPosition().y, 75.0f));
			gameCamera.Update2();
		}
        //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();
		
		// Lab code goes here
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		theOGLWnd.initOGL(windowWidth,windowHeight);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		if (toggleCamera)
			glLoadMatrixf((GLfloat*)&debugCamera.getTheViewMatrix());
		else
			glLoadMatrixf((GLfloat*)&gameCamera.getTheViewMatrix());

		sunMaterial.useMaterial();
		sunLight.lightOn();
		lfLight.lightOn();
		rfLight.lightOn();
		cbLight.lightOn();

		theEarth.setRotAngle(theEarth.getRotAngle() + (earthRotSpeed*elapsedTime));
		theEarth.prepare(theEarth.getRotAngle()); //Do any pre-rendering logic
		earthMaterial.useMaterial();				// Set the material for use
		theEarth.render(theEarth.getRotAngle()); //Render the scene

		for (vector<cEnemy*>::iterator enemyIterator = theEnemy.begin(); enemyIterator != theEnemy.end(); ++enemyIterator)
		{
			if ((*enemyIterator)->isActive())
			{
				spaceShipMdl.renderMdl(glm::vec3((*enemyIterator)->getPosition().x, (*enemyIterator)->getPosition().y, 0.0f), (*enemyIterator)->getRotation(), (*enemyIterator)->getScale());
				//spaceShipMdl.renderMdl((*enemyIterator)->getPosition(), (*enemyIterator)->getRotation(), (*enemyIterator)->getScale());
				(*enemyIterator)->update(elapsedTime);
			}
		}

		tardisMdl.renderMdl(thePlayer.getPosition(), thePlayer.getRotation(), thePlayer.getScale());
		if (!toggleCamera)
		thePlayer.update(elapsedTime);
		
		for (vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin(); laserIterartor != theTardisLasers.end(); ++laserIterartor)
		{
			if ((*laserIterartor)->isActive())
			{
				theLaser.renderMdl((*laserIterartor)->getPosition(), (*laserIterartor)->getRotation(), (*laserIterartor)->getScale());
				(*laserIterartor)->update(elapsedTime);
			}
		}

		outputMsg = to_string(theEnemy.size()); // convert float to string
		
		glPushMatrix();
		theOGLWnd.setOrtho2D(windowWidth, windowHeight);
		theFontMgr->getFont("DrWho")->printText("Tardis Wars", FTPoint(10, 35, 0.0f), colour3f(0.0f,255.0f,0.0f));
		theFontMgr->getFont("DrWho")->printText(outputMsg.c_str(), FTPoint(850, 35, 0.0f), colour3f(255.0f, 255.0f, 0.0f)); // uses c_str to convert string to LPCSTR
		glPopMatrix();


		pgmWNDMgr->swapBuffers();
		
		tCount += elapsedTime;

		//Clear key buffers
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	}

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}

