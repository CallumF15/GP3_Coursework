/*
==================================================================================
cStarfield.cpp
==================================================================================
*/

#include "cStarfield.h"


cStarfield::cStarfield()
{
	srand((unsigned)time(NULL));
	setRotAngle(0.0f);
	m_TextureID = 0;
	m_FieldVolume = glm::vec3(1.0f,1.0f,1.0f);
	m_StarPos = glm::vec3(0.0f, 0.0f, 0.0f);

}

cStarfield::cStarfield(GLint theTextureID, glm::vec3 theFieldVolume)
{
	srand((unsigned)time(NULL));
	setRotAngle(0.0f);
	m_TextureID = theTextureID;
	m_FieldVolume = theFieldVolume;
	m_StarPos = glm::vec3(0.0f, 0.0f, 80.0f);
}

void cStarfield::render(float rotAngle)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glDepthMask(GL_FALSE);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDisable(GL_TEXTURE_2D);
	glDepthMask(GL_TRUE);
	glPopMatrix();
}

void cStarfield::initialise(cTexture theTexture)
{
	srand((unsigned)time(NULL));
	glBindTexture(GL_TEXTURE_2D, theTexture.getTexture());
}

void cStarfield::initialise(GLint theTextureID, glm::vec3 theFieldVolume)
{
	srand((unsigned)time(NULL));
	m_TextureID = theTextureID;
	m_FieldVolume = theFieldVolume;
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

}
