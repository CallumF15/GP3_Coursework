#include "cLaser.h"

cLaser::cLaser() : cModel()
{

}

//disables laser if it leaves play field. 
void cLaser::update(float elapsedTime)
{
	cModel::m_mdlPosition += cModel::m_mdlDirection * cModel::m_mdlSpeed * elapsedTime;
	if (cModel::m_mdlPosition.x > PLAYFIELDX ||
		cModel::m_mdlPosition.x < -PLAYFIELDX ||
		cModel::m_mdlPosition.y > PLAYFIELDZ ||
		cModel::m_mdlPosition.y < -PLAYFIELDZ)
		cModel::m_IsActive = false;
}

cLaser::~cLaser()
{

}
