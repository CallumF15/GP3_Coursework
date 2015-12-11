#include "cPlayer.h"

cPlayer::cPlayer() : cModel()
{
	isSoundOff = false;
}

void cPlayer::attachInputMgr(cInputMgr* inputMgr)
{
	m_InputMgr = inputMgr;
}

void cPlayer::update(float elapsedTime)
{
	if (m_InputMgr->isKeyDown(VK_RIGHT)|| m_normalisedRX > 0.95f)
	{
		//translationZ += 1.0f;
		rotationAngle += 5.0f;
	}else
	if (m_InputMgr->isKeyDown(VK_LEFT) || m_normalisedRX < -0.99f)
	{
		//translationZ -= 1.0f;
		rotationAngle -= 5.0f;
	}else
	if (m_InputMgr->isKeyDown(VK_UP) || m_normalisedRY > 0.99f)
	{
		translationZ += 1.0f;
	}else

	if (m_InputMgr->isKeyDown(VK_DOWN) || m_normalisedRY < -0.99f)
	{
		translationZ -= 1.0f;
	}

	if (m_InputMgr->isKeyDown(VK_SPACE))
	{
		glm::vec3 mdlLaserDirection;
		mdlLaserDirection.x = -(float)glm::sin(glm::radians(this->getRotation()));
		mdlLaserDirection.y = 0.0f;
		mdlLaserDirection.z = (float)glm::cos(glm::radians(this->getRotation()));
		mdlLaserDirection *= -1;

		// Add new bullet sprite to the vector array
		theTardisLasers.push_back(new cLaser);
		int numLasers = theTardisLasers.size() - 1;
		theTardisLasers[numLasers]->setDirection(mdlLaserDirection);
		theTardisLasers[numLasers]->setRotation(0.0f);
		theTardisLasers[numLasers]->setScale(glm::vec3(1, 1, 1));
		theTardisLasers[numLasers]->setSpeed(5.0f);
		theTardisLasers[numLasers]->setPosition(this->getPosition() + mdlLaserDirection);
		theTardisLasers[numLasers]->setIsActive(true);
		//theTardisLasers[numLasers]->setMdlDimensions(theLaser.getModelDimensions());
		theTardisLasers[numLasers]->update(elapsedTime);
		// play the firing sound
		if (!isSoundOff)
		m_SoundMgr->getSnd("Shot")->playAudio(AL_TRUE);
	}

	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/
	for (vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin(); laserIterartor != theTardisLasers.end(); ++laserIterartor)
	{
		(*laserIterartor)->update(elapsedTime);
		for (vector<cEnemy*>::iterator enemyIterator = theEnemy.begin(); enemyIterator != theEnemy.end(); ++enemyIterator)
		{
			if ((*enemyIterator)->SphereSphereCollision((*laserIterartor)->getPosition(), (*laserIterartor)->getMdlRadius()))
			{
				// if a collision set the bullet and spaceship to false
				(*enemyIterator)->setIsActive(false);
				(*laserIterartor)->setIsActive(false);
				// play the explosion sound.
				if (!isSoundOff)
				m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
			}
		}
	}

	vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin();
	while (laserIterartor != theTardisLasers.end())
	{
		if ((*laserIterartor)->isActive() == false)
		{
			laserIterartor = theTardisLasers.erase(laserIterartor);
		}
		else
		{
			++laserIterartor;
		}
	}

	vector<cEnemy*>::iterator enemyIterartor = theEnemy.begin();
	while (enemyIterartor != theEnemy.end())
	{
		if ((*enemyIterartor)->isActive() == false)
		{
			enemyIterartor = theEnemy.erase(enemyIterartor);
		}
		else
		{
			++enemyIterartor;
		}
	}

	// Find out what direction we should be thrusting, using rotation.
	glm::vec3 mdlVelocityAdd;
	float angle = glm::atan(mouseY - m_mdlPosition.y, mouseX - m_mdlPosition.x);
	mdlVelocityAdd.x = (float)glm::cos(glm::radians(m_mdlRotation));  // Remember to adjust for radians
	mdlVelocityAdd.y = (float)glm::sin(glm::radians(m_mdlRotation));
	mdlVelocityAdd.z = 0.0f;

	m_mdlRotation -= rotationAngle;
	mdlVelocityAdd *= translationZ;
	//mdlVelocityAdd.x *= translationZ;
	//mdlVelocityAdd.y *= translationY;
	m_mdlDirection += mdlVelocityAdd;

	m_mdlPosition += m_mdlDirection * m_mdlSpeed *elapsedTime;
	//m_mdlPosition.x += m_mdlDirection.x * m_mdlSpeed * elapsedTime;
	//m_mdlPosition.y += m_mdlDirection.y * m_mdlSpeed * elapsedTime;
	//m_mdlPosition.z = 0.0f;
	m_mdlDirection *= 0.95f;

	rotationAngle = 0;
	translationZ = 0;
	translationY = 0;
}

cPlayer::~cPlayer()
{

}

void cPlayer::setMouseXPosition(int x){
	mouseX = x;
}

void cPlayer::setMouseYPosition(int y){
	mouseY = y;
}

bool cPlayer::getSoundOff(){
	return isSoundOff;
}

void cPlayer::setSoundOff(bool setSoundOff){
	isSoundOff = setSoundOff;
}

//Setters
void cPlayer::setNormalisedLX(float normalisedLX){
	m_normalisedLX = normalisedLX;
}

void cPlayer::setNormalisedLY(float normalisedLY){
	m_normalisedLY = normalisedLY;
}

void cPlayer::setNormalisedRX(float normalisedRX){
	m_normalisedRX = normalisedRX;
}

void cPlayer::setNormalisedRY(float normalisedRY){
	m_normalisedRY = normalisedRY;
}