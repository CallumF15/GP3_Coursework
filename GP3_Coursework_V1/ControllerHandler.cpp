#include "ControllerHandler.h"

ControllerHandler::ControllerHandler(){
}

//Assigns controller number based of number of players
void ControllerHandler::setNumberPlayers(int playerNumber){
	m_controllerNumber = playerNumber - 1;
}

//Gets the state of the controller
bool ControllerHandler::getState(){


		DWORD dwResult;

		//XINPUT_STATE state;
		ZeroMemory(&m_controllerState, sizeof(XINPUT_STATE));

		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(m_controllerNumber, &m_controllerState);

		if (dwResult == ERROR_SUCCESS)
		{
			// Controller is connected 
			return true;
		}
		else
		{
			// Controller is not connected 
			return false;
		}
}

//Checks for what game pad button has been pressed
void ControllerHandler::CheckControllerInput(){

	switch (m_controllerState.Gamepad.wButtons){

	case XINPUT_GAMEPAD_A:
		//Vibrate(65000, 65000);
		break;
	case XINPUT_GAMEPAD_B:
		//Vibrate(65000, 65000);
		break;
	case XINPUT_GAMEPAD_Y:
		//Vibrate(65000, 65000);
		
		break;
	case XINPUT_GAMEPAD_X:
		//Vibrate(65000, 65000);
		break;
	}
}


void ControllerHandler::CheckDeadZones(){

	float INPUT_DEADZONE = 4000.0f;
	

	float LX = m_controllerState.Gamepad.sThumbLX;
	float LY = m_controllerState.Gamepad.sThumbLY;

	//determine how far the controller is pushed
	float magnitude = sqrt(LX*LX + LY*LY);

	//determine the direction the controller is pushed
	float normalizedLX = LX / magnitude;
	float normalizedLY = LY / magnitude;

	setNormalisedLX(normalizedLX);
	setNormalisedLY(normalizedLY);

	float normalizedMagnitude = 0;

	//check if the controller is outside a circular dead zone
	if (magnitude > INPUT_DEADZONE)
	{
		//clip the magnitude at its expected maximum value
		if (magnitude > 32767)
			magnitude = 32767;

		//adjust magnitude relative to the end of the dead zone
		magnitude -= INPUT_DEADZONE;

		//optionally normalize the magnitude with respect to its expected range
		//giving a magnitude value of 0.0 to 1.0
		normalizedMagnitude = magnitude / (32767 - INPUT_DEADZONE);
	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		magnitude = 0.0;
		normalizedMagnitude = 0.0;
	}



	//repeat for right thumb stick
	float RX = m_controllerState.Gamepad.sThumbRX;
	float RY = m_controllerState.Gamepad.sThumbRY;

	//determine how far the controller is pushed
	float magnitudeRXRY = sqrt(RX*RX + RY*RY);

	//determine the direction the controller is pushed
	float normalizedRX = RX / magnitudeRXRY;
	float normalizedRY = RY / magnitudeRXRY;

	setNormalisedRX(normalizedRX);
	setNormalisedRY(normalizedRY);

	float normalizedMagnitudeRXRY = 0;

	//check if the controller is outside a circular dead zone
	if (magnitudeRXRY > INPUT_DEADZONE)
	{
		//clip the magnitude at its expected maximum value
		if (magnitudeRXRY > 32767) magnitudeRXRY = 32767;

		//adjust magnitude relative to the end of the dead zone
		magnitudeRXRY -= INPUT_DEADZONE;

		//optionally normalize the magnitude with respect to its expected range
		//giving a magnitude value of 0.0 to 1.0
		normalizedMagnitudeRXRY = magnitudeRXRY / (32767 - INPUT_DEADZONE);
	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		//Add Stop player movement somewhere here

		magnitudeRXRY = 0.0;
		normalizedMagnitudeRXRY = 0.0;
	}
}

void ControllerHandler::Vibrate(int leftVal, int rightVal)
{
	// Create a Vibraton State
	XINPUT_VIBRATION Vibration;

	// Zeroise the Vibration
	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

	// Set the Vibration Values
	Vibration.wLeftMotorSpeed = leftVal;
	Vibration.wRightMotorSpeed = rightVal;

	// Vibrate the controller
	XInputSetState(m_controllerNumber, &Vibration);
}

//Setters

void ControllerHandler::setNormalisedLX(float normalisedLX){
	m_normalisedLX = normalisedLX;
}

void ControllerHandler::setNormalisedLY(float normalisedLY){
	m_normalisedLY = normalisedLY;
}

void ControllerHandler::setNormalisedRX(float normalisedRX){
	m_normalisedRX = normalisedRX;
}

void ControllerHandler::setNormalisedRY(float normalisedRY){
	m_normalisedRY = normalisedRY;
}

//Getters

float ControllerHandler::getNormalisedLX(){
	return m_normalisedLX;
}

float ControllerHandler::getNormalisedLY(){
	return m_normalisedLY;
}

float ControllerHandler::getNormalisedRX(){
	return m_normalisedRX;
}

float ControllerHandler::getNormalisedRY(){
	return m_normalisedRY;
}

