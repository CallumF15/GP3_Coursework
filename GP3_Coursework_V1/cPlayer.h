#ifndef _CPLAYER_H
#define _CPLAYER_H

#include "GameConstants.h"
#include "tardisWarsGame.h"
#include "cModel.h"
#include "cInputMgr.h"
#include "ControllerHandler.h"

class cPlayer : public cModel
{
private:
	cInputMgr* m_InputMgr;
	ControllerHandler m_controlHandler;
public:

	bool isSoundOff;
	bool hasCollided;
	bool isConnected;

	float vibrateDelay, shootDelay, rechargeDelay, laserFadeDelay;

	int getFireEnergy();
	int fireEnergy;

	cPlayer();
	void attachInputMgr(cInputMgr* inputMgr);
	void attachControllerHander(ControllerHandler controllerHandler);
	virtual void update(float elapsedTime);
	void spawnLasers(float tcount);

	~cPlayer();

	bool getSoundOff();
	void setSoundOff(bool setSoundOff);
	void setControllerConnected(bool controlConnected);
};
#endif