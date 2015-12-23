#include "cEnemy.h"

cEnemy::cEnemy() : cModel()
{
	
}

//sets random spawn location, direction and speed of the enemy
void cEnemy::randomise()
{
	if (rand() % 2 == 0)
	{
		cModel::m_mdlPosition.x = -PLAYFIELDX;
	}
	else
	{
		cModel::m_mdlPosition.x = PLAYFIELDX;
	}
	cModel::m_mdlPosition.z = 0.0f; //make sure enemy is on 0 Z position
	cModel::m_mdlPosition.y = (rand() / (float)RAND_MAX) * 300.0f;   // random number as a float between 0 & 1
	cModel::m_mdlRotation = (rand() / (float)RAND_MAX) * 2 * 3.14f;  //random angle
	cModel::m_mdlDirection.x = (float)glm::cos(glm::radians(m_mdlRotation)); 
	cModel::m_mdlDirection.y = (float)glm::sin(cModel::m_mdlRotation); //calculate direction
	cModel::m_mdlSpeed = m_EnemyMinSpeed + rand() / (float)RAND_MAX * m_EnemyMaxSpeed; //random speed
	cModel::m_IsActive = true; //enemy is active
}

//Makes sure enemy position is inside the X and Y field specified
void cEnemy::update(float elapsedTime)
{
	cModel::m_mdlPosition += cModel::m_mdlDirection * cModel::m_mdlSpeed * elapsedTime;
	if (cModel::m_mdlPosition.x > PLAYFIELDX)
		cModel::m_mdlPosition.x -= 2 * PLAYFIELDX;
	if (cModel::m_mdlPosition.x < -PLAYFIELDX)
		cModel::m_mdlPosition.x += 2 * PLAYFIELDX;
	if (cModel::m_mdlPosition.y > PLAYFIELDZ)
		cModel::m_mdlPosition.y -= 2 * PLAYFIELDZ;
	if (cModel::m_mdlPosition.y < -PLAYFIELDZ)
		cModel::m_mdlPosition.y += 2 * PLAYFIELDZ;
}

cEnemy::~cEnemy()
{

}

