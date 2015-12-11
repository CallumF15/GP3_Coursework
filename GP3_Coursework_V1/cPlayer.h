#ifndef _CPLAYER_H
#define _CPLAYER_H

#include "GameConstants.h"
#include "tardisWarsGame.h"
#include "cModel.h"
#include "cInputMgr.h"

#include <math.h>

class cPlayer : public cModel
{
private:
	cInputMgr* m_InputMgr;
public:

	bool isSoundOff;

	cPlayer();
	void attachInputMgr(cInputMgr* inputMgr);
	virtual void update(float elapsedTime);

	~cPlayer();

	bool getSoundOff();
	void setSoundOff(bool setSoundOff);

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