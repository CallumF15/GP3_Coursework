#include "cModelLoader.h"


cModelLoader::cModelLoader()
{
	m_model = NULL;
}


void cModelLoader::loadModel(const char* mdlFilename)
{
	m_model = glmReadOBJ(mdlFilename);
	glmUnitize(m_model);
	glmFacetNormals(m_model);
	glmVertexNormals(m_model, 180.0,false);
}

void cModelLoader::loadModel(const char* mdlFilename, GLuint textureID)
{
	m_model = glmReadOBJ(mdlFilename); //reads model description
	glmUnitize(m_model);
	glmFacetNormals(m_model);
	glmVertexNormals(m_model, 180.0,false);
	m_TextureID = textureID;
	m_model->textures[m_model->numtextures - 1].id = m_TextureID;
}


void cModelLoader::loadModel(const char* mdlFilename, cTexture mdlTexture)
{
	m_model = glmReadOBJ(mdlFilename); //reads model description

	//glmUnitize(m_model);  // This will rescale the object to fit into the unity matrix
	glmFacetNormals(m_model); //set face normals
	glmVertexNormals(m_model, 180.0f, false); //set vertex normals
	m_TextureID = mdlTexture.getTexture(); //get texture id
		
	m_model->textures[m_model->numtextures - 1].id = m_TextureID;
	m_model->textures[m_model->numtextures - 1].width = mdlTexture.getTWidth();
	m_model->textures[m_model->numtextures - 1].height = mdlTexture.getTHeight();
}

void cModelLoader::renderMdl(glm::vec3 mdlPosition, float mdlRotationAngle, glm::vec3 mdlScale, int xRot, int yRot, int zRot)
{
	glPushMatrix();
	//transformations here...
	glTranslatef(mdlPosition.x, mdlPosition.y, -mdlPosition.z);
	glRotatef(mdlRotationAngle, xRot, yRot, zRot);
	glScalef(mdlScale.x, mdlScale.y, mdlScale.z);
	glmDraw(m_model, GLM_TEXTURE | GLM_MATERIAL);  // GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL
	glPopMatrix();
}

mdlDimensions cModelLoader::getModelDimensions()
{
	mdlDimensions mdl_Dims;
	GLfloat mdlDims[3];
	glmDimensions(m_model, mdlDims);
	mdl_Dims.s_mdlWidth = mdlDims[0];
	mdl_Dims.s_mdlheight = mdlDims[1];
	mdl_Dims.s_mdldepth = mdlDims[2];
	return mdl_Dims;
}

cModelLoader::~cModelLoader()
{
	glmDelete(m_model);
}
