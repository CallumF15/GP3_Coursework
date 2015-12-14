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
	float m_tCount;
	bool hasCollided;

	int fireEnergy;

	cPlayer();
	void attachInputMgr(cInputMgr* inputMgr);
	void attachControllerHander(ControllerHandler controllerHandler);
	virtual void update(float elapsedTime);
	void spawnLasers(float tcount);

	~cPlayer();

	bool getSoundOff();
	void setSoundOff(bool setSoundOff);


	int lastKey, currentKey;
	float oldtime, currentTime;

	//Mouse Related Variables
	int mouseX;
	int mouseY;

	void setMouseXPosition(int x);
	void setMouseYPosition(int y);
};
#endif