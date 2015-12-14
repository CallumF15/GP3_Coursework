#ifndef _CONTROLLERHANDLER_H
#define _CONTROLLERHANDLER_H

#include <Windows.h>
#include <Xinput.h>
#include <math.h>

#pragma comment(lib, "Xinput.lib")


#define _AMD64_

class ControllerHandler{

private:
	int m_controllerNumber;

public:

	//Variables
	XINPUT_STATE m_controllerState;

	//Constructor
	ControllerHandler();

	//Methods
	void setNumberPlayers(int playerNumber);
	bool getState();

	void CheckDeadZones();
	void Vibrate(int leftVal, int rightVal);

	void CheckControllerInput();

	//Getters & Setters
	float getRightTriggerValue();

	float m_normalizedMagnitudeLXLY;
	float m_normalizedMagnitudeRXRY;

	void setNormalizedLXLY(float normalizedLXLY);
	void setNormalizedRXRY(float normalizedRXRY);

	float getNormalizedLXLY();
	float getNormalizedRXRY();

	float m_normalisedRX;
	float m_normalisedRY;
	float m_normalisedLX;
	float m_normalisedLY;

	float getNormalisedRX();
	float getNormalisedRY();

	float getNormalisedLX();
	float getNormalisedLY();

	void setNormalisedRX(float normalisedRX);
	void setNormalisedRY(float normalisedRY);

	void setNormalisedLX(float normalisedLX);
	void setNormalisedLY(float normalisedLY);
};


#endif