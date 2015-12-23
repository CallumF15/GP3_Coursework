#include "cPlayer.h"

cPlayer::cPlayer() : cModel()
{
	isSoundOff = false;
	vibrateDelay = 0;
	shootDelay = 0;
	fireEnergy = 100;
}

void cPlayer::attachInputMgr(cInputMgr* inputMgr)
{
	m_InputMgr = inputMgr; //assign manager object
}

void cPlayer::attachControllerHander(ControllerHandler controllerHandler){
	m_controlHandler = controllerHandler; //assign controller object
}

void cPlayer::update(float elapsedTime)
{
	//if right key is pressed or if controller analog stick is facing right direction and is fully pushed.
	if (m_InputMgr->isKeyDown(VK_RIGHT) || (m_controlHandler.getNormalisedRX() > 0.0f && m_controlHandler.getNormalizedRXRY() >= 1.f)) 
	{
		translationZ += 1.0f; //needs to be minus since model inverted position
	}else
		//if left key is pressed or if controller analog stick is facing left direction and is fully pushed.
	if (m_InputMgr->isKeyDown(VK_LEFT) || (m_controlHandler.getNormalisedRX() < 0.0f && m_controlHandler.getNormalizedRXRY() >= 1.f))
	{
		translationZ -= 1.0f;
	}else
	//if left mouse button is clicked and there is energy left to fire
	if (m_InputMgr->getLeftMouseBtn() && fireEnergy > 0)
	{
		if (shootDelay > .5){ //if delay is past time
			spawnLasers(elapsedTime); 
			fireEnergy -= 2; //reduce fire energy
			shootDelay = 0;  //reset delay
		}
	}
	//if controller back right trigger (RT for 360) is pressed past half way
	if (m_controlHandler.getRightTriggerValue() > .5f && fireEnergy > 0){
		if (shootDelay > .5){ //if delay is past time
			fireEnergy -= 4;  //reduce fire energy
			spawnLasers(elapsedTime); //spawn lasers
			shootDelay = 0; //reset delay
		}
	}
	//if controller back right trigger (RT for 360) is pressed below half way
	if (m_controlHandler.getRightTriggerValue() < .5f && m_controlHandler.getRightTriggerValue() > .0f && fireEnergy > 0){
		if (shootDelay > 1){
			fireEnergy -= 2;
			spawnLasers(elapsedTime);
			shootDelay = 0;
		}
	}

	if (fireEnergy <= 0) //make sure fireEnergy doesn't go below zero
		fireEnergy = 0; 
	
	if (fireEnergy >= 100) //make sure fireEnergy doesn't go above 100
		fireEnergy = 100;
	//if the right trigger isn't pressed, or if the left mouse click isn't pressed
	if ((isConnected && m_controlHandler.getRightTriggerValue() == 0) || !m_InputMgr->getLeftMouseBtn())
		if (rechargeDelay > .5){ //delay 
			fireEnergy += 2;  //increment fire energy
			rechargeDelay = 0; //reset delay
		}


	//Check for collisions
	for (vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin(); laserIterartor != theTardisLasers.end(); ++laserIterartor)
	{
		(*laserIterartor)->update(elapsedTime);
		for (vector<cEnemy*>::iterator enemyIterator = theEnemy.begin(); enemyIterator != theEnemy.end(); ++enemyIterator)
		{
			if ((*enemyIterator)->SphereSphereCollision((*laserIterartor)->getPosition(), (*laserIterartor)->getMdlRadius()))
			{
				// if a collision set the laser and spaceship to false
				(*enemyIterator)->setIsActive(false);
				(*laserIterartor)->setIsActive(false);
				// play the explosion sound.
				if (!isSoundOff)
					m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);

				if (isConnected == true)
					m_controlHandler.Vibrate(30000, 30000); //vibrate controller

				hasCollided = true;
			}
		}
	}

	if (vibrateDelay > 2){ //delay timer for how long until vibration is stopped
		if (isConnected == true && hasCollided == true){ //check if collision has occured
			m_controlHandler.Vibrate(0, 0); //turn off controller vibration
			hasCollided = false;
		}
		vibrateDelay = 0; //reset delay
	}

	vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin();
	while (laserIterartor != theTardisLasers.end())
	{
		if ((*laserIterartor)->isActive() == false) //check if laser is active
		{
			laserIterartor = theTardisLasers.erase(laserIterartor); //delete laser from collection
		}
		else
		{
			++laserIterartor; //increment collection
		}
	}

	vector<cEnemy*>::iterator enemyIterartor = theEnemy.begin();
	while (enemyIterartor != theEnemy.end()) //make sure not at end of collection
	{
		if ((*enemyIterartor)->isActive() == false) //check if enemy is active
		{
			enemyIterartor = theEnemy.erase(enemyIterartor); //delete laser from collection
		}
		else
		{ 
			++enemyIterartor; //increment collection
		}
	}


	float angle;

	if (isConnected == true) //check controller connected
		angle = glm::atan(m_controlHandler.getNormalisedLY(), m_controlHandler.getNormalisedLX()) * (180 / 3.14); //calculate left thumbstick angle
	else
		angle = -glm::atan(m_InputMgr->getMouseYPos() - 768.f / 2, m_InputMgr->getMouseXPos() - 1024.f / 2) * (180 / 3.14); //calculate angle from screen width height and mouse position

	glm::vec3 mdlVelocityAdd;
	mdlVelocityAdd.x = (float)glm::cos(glm::radians(m_mdlRotation));  // Remember to adjust for radians
	mdlVelocityAdd.y = (float)glm::sin(glm::radians(m_mdlRotation));  //calculate direction
	mdlVelocityAdd.z = 0.0f;

	m_mdlRotation = angle; //pass angle to rotate model
	mdlVelocityAdd *= translationZ; //change direction
	m_mdlDirection += mdlVelocityAdd;

	m_mdlPosition += m_mdlDirection * m_mdlSpeed * elapsedTime;
	m_mdlDirection *= 0.95f;

	translationZ = 0;

	vibrateDelay += elapsedTime;
	shootDelay += elapsedTime;
	rechargeDelay += elapsedTime;
}

cPlayer::~cPlayer()
{

}

void cPlayer::spawnLasers(float elapsedTime){

	glm::vec3 mdlLaserDirection;
	float angle = this->getRotation();
	mdlLaserDirection.x = (float)glm::cos(glm::radians(m_mdlRotation));  // Remember to adjust for radians
	mdlLaserDirection.y = (float)glm::sin(glm::radians(m_mdlRotation));
	mdlLaserDirection.z = 0.0f;

	mdlDimensions dimensions;
	dimensions.s_mdldepth = 1;
	dimensions.s_mdlheight = 0;
	dimensions.s_mdlWidth = 0;

	// Add new laser  to the vector array
	theTardisLasers.push_back(new cLaser);
	int numLasers = theTardisLasers.size() - 1;
	theTardisLasers[numLasers]->setDirection(mdlLaserDirection);
	theTardisLasers[numLasers]->setRotation(90.0f);
	theTardisLasers[numLasers]->setScale(glm::vec3(2, 2, 2));
	theTardisLasers[numLasers]->setSpeed(20.0f);
	theTardisLasers[numLasers]->setPosition(this->getPosition() + mdlLaserDirection);
	theTardisLasers[numLasers]->setIsActive(true);
	theTardisLasers[numLasers]->setMdlDimensions(dimensions);
	theTardisLasers[numLasers]->update(elapsedTime);

	// play the firing sound
	if (!isSoundOff)
		m_SoundMgr->getSnd("Shot")->playAudio(AL_TRUE);
}

bool cPlayer::getSoundOff(){
	return isSoundOff;
}

void cPlayer::setSoundOff(bool setSoundOff){
	isSoundOff = setSoundOff;
}

int cPlayer::getFireEnergy(){
	return fireEnergy;
}

void cPlayer::setControllerConnected(bool controlConnected){
	isConnected = controlConnected;
}
