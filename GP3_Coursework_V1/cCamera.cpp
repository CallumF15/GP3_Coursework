/*
==========================================================================
ccCamera.h
==========================================================================
*/

#include "cCamera.h"

cCamera::cCamera()
{
	m_viewPort = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	m_cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_ProjectionMatrix = glm::mat4(1.0);
	m_camViewMatrix = glm::mat4(1.0);
}


cCamera::cCamera(int screenWidth, int screenHeight)
{
	m_viewPort = glm::vec4(0, 0, screenWidth, screenHeight);
	m_cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_ProjectionMatrix = glm::mat4(1.0);
	m_camViewMatrix = glm::mat4(1.0);
}

cCamera::~cCamera()
{

}

void cCamera::setTheViewPort(int x, int y, int width, int height)
{
	m_viewPort = glm::vec4(x, y, width, height);
	glViewport(x, y, width, height);
}

const glm::vec4 cCamera::getTheViewPort()
{
	return m_viewPort;
}

void cCamera::setTheProjectionMatrix(float fov, float aspectRatio, float nearCP, float farCP)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearCP, farCP);
}

void cCamera::setTheCameraPos(glm::vec3 pos)
{
	m_cameraPos = pos;
}

glm::vec3 cCamera::getTheCameraPos()
{
	return m_cameraPos;
}

void cCamera::setTheCameraUpVector(glm::vec3 camPosUpVec)
{
	m_cameraUpVector = camPosUpVec;
}

glm::vec3 cCamera::getTheCameraUpVector()
{
	return m_cameraUpVector;
}

void cCamera::setTheCameraLookAt(glm::vec3 camLookAt)
{
	m_cameraLookAt = camLookAt;
}

glm::vec3 cCamera::getTheCameraLookAt()
{
	return m_cameraLookAt;
}

void cCamera::setTheCameraDirection()
{
	m_cameraDirection = glm::normalize(m_cameraPos - m_cameraLookAt);
}

glm::vec3 cCamera::getTheCameraDirection()
{
	return m_cameraDirection;
}

void cCamera::setTheCameraStrafe()
{
	m_cameraStrafe = glm::normalize(glm::cross(m_cameraUpVector, m_cameraDirection));
}

glm::vec3 cCamera::getTheCameraStrafe()
{
	return m_cameraStrafe;
}

void cCamera::setTheCameraAspectRatio(GLfloat width, GLfloat height)
{
	m_AspectRatio = width / height;
}

GLfloat cCamera::getTheCameraAspectRatio()
{
	return m_AspectRatio;
}

glm::mat4 cCamera::getTheProjectionMatrix()
{
	return m_ProjectionMatrix;
}

glm::mat4 cCamera::getTheViewMatrix()
{
	return m_camViewMatrix;
}

void cCamera::setCamViewMatrix()
{												//changed code below
	m_camViewMatrix = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraDirection, m_cameraUpVector);
}

glm::mat4 cCamera::getCamViewMatrix()
{
	return m_camViewMatrix;
}

void cCamera::update()
{
	setTheCameraDirection();
	setTheCameraStrafe();
	setTheCameraUpVector(glm::cross(m_cameraDirection, m_cameraStrafe));
	setTheProjectionMatrix(45.0f, getTheCameraAspectRatio(), 0.1f, 1000.0f);
	setCamViewMatrix();
}

void cCamera::Update2(){
	setTheProjectionMatrix(45.0f, getTheCameraAspectRatio(), 0.1f, 1000.0f);
	setCamViewMatrix();
}

void cCamera::mouseUpdate(const glm::vec2& newMousePos)
{
	glm::vec2 mouseDelta = newMousePos - oldMousePos;

	if (glm::length(mouseDelta) > 50.0f){
		oldMousePos = newMousePos;
		return;
	}

	const float ROTATIONAL_SPEED = 0.01f;

	strafedirection = glm::normalize(glm::cross(m_cameraDirection, m_cameraUpVector));
	glm::mat4 rotator = glm::rotate(glm::mat4(1.0f), -mouseDelta.x * ROTATIONAL_SPEED, m_cameraUpVector) *
		glm::rotate(glm::mat4(1.0f), -mouseDelta.y * ROTATIONAL_SPEED, strafedirection);

	m_cameraDirection = glm::mat3(rotator) * m_cameraDirection;

	oldMousePos = newMousePos;
}

//Passed in variable determines which sort of movement occurs and
//calls the appropriate enum of type MovementType and either calculates
//or calls appropriate method
void cCamera::movement(cInputMgr* inputMgr)
{
	if (inputMgr->isKeyDown(VK_UP))//forward
	{
		m_cameraPos += 1.0f * m_cameraDirection;
	}
	if (inputMgr->isKeyDown(VK_DOWN)) //backward
	{
		m_cameraPos += -1.0f * m_cameraDirection;
	}

	if (inputMgr->isKeyDown(VK_RIGHT))
	{
		strafeRight();
	}
	if (inputMgr->isKeyDown(VK_LEFT))
	{
		strafeLeft();
	}


	if (inputMgr->isKeyDown(VK_INSERT)) //up movement
	{
		m_cameraPos += 1.0f * m_cameraUpVector;
	}
	if (inputMgr->isKeyDown(VK_DELETE)) //down movement
	{
		m_cameraPos -= 1.0f * m_cameraUpVector;
	}
	if (inputMgr->isKeyDown(VK_HOME)){
		m_cameraPos = glm::vec3(0, 0, 0);
		m_cameraDirection = glm::vec3(0.0, 0.0, -1.0f);
	}
}

//Calculates movement to the left
void cCamera::strafeLeft(){
	m_cameraPos -= 1.0f * strafedirection;
}

//Calculates movement to the Right
void cCamera::strafeRight()
{
	m_cameraPos += 1.0f * strafedirection;
}

void cCamera::trackPlayer(glm::vec3 playerPosition){

	m_cameraPos = glm::vec3(playerPosition.x, playerPosition.y, playerPosition.z);
}
