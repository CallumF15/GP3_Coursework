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

	cPlayer();
	void attachInputMgr(cInputMgr* inputMgr);
	void attachControllerHander(ControllerHandler controllerHandler);
	virtual void update(float elapsedTime);

	~cPlayer();

	bool getSoundOff();
	void setSoundOff(bool setSoundOff);


	int lastKey, currentKey;

	//Mouse Related Variables
	int mouseX;
	int mouseY;

	void setMouseXPosition(int x);
	void setMouseYPosition(int y);

	//Controller Related Variables/Setters
	float m_normalisedRX;
	float m_normalisedRY;
	float m_normalisedLX;
	float m_normalisedLY;

	void setNormalisedRX(float normalisedRX);
	void setNormalisedRY(float normalisedRY);

	void setNormalisedLX(float normalisedLX);
	void setNormalisedLY(float normalisedLY);
};
#endif