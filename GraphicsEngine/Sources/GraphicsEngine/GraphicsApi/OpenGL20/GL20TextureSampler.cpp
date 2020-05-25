#include "GL20TextureSampler.h"
//#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20GraphicsEngineContext.h"


GL20TextureSampler::GL20TextureSampler(TextureFilterMode filterMode, TextureWrapMode wrapMode)
{
	SetFilterMode( filterMode );
	SetWrapMode  ( wrapMode );
}

GL20TextureSampler::~GL20TextureSampler()
{

}

void GL20TextureSampler::SetFilterMode(TextureFilterMode filterMode)
{
	// http://www.learnopengles.com/android-lesson-six-an-introduction-to-texture-filtering/
	// https://www.opengl.org/wiki/Sampler_Object
	// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/
	// http://opengl-master.ru/view_post.php?id=78
	// http://www.araku.ac.ir/~d_comp_engineering/88892/1323108/OpenGL%20Game%20Development.pdf

	if (filterMode == TEXTURE_FILTER_MODE_POINT)
	{
		// TODO: Task05_01
		m_minFilterMode = GL_NEAREST;
		m_magFilterMode = GL_NEAREST;
		m_useAniso = false;//for anisotropic filter; defined in 
	}
	else if (filterMode == TEXTURE_FILTER_MODE_BILINEAR)
	{
		// TODO: Task05_01
		m_minFilterMode = GL_LINEAR_MIPMAP_NEAREST;//from 1 link
		m_magFilterMode = GL_LINEAR;
		m_useAniso = false;
	}
	else if (filterMode == TEXTURE_FILTER_MODE_TRILINEAR)
	{
		// TODO: Task05_01]
		m_minFilterMode = GL_LINEAR_MIPMAP_LINEAR;//from 1 link
		m_magFilterMode = GL_LINEAR;
		m_useAniso = false;
	}
	else if (filterMode == TEXTURE_FILTER_MODE_ANISOTROPIC)
	{
		// TODO: Task05_01
		m_minFilterMode = GL_LINEAR_MIPMAP_LINEAR;
		m_magFilterMode = GL_LINEAR;
		m_useAniso = true;
	}
}


//как размещаем текстуру на объекте 
void GL20TextureSampler::SetWrapMode(TextureWrapMode wrapMode)
{
	// http://gamedev.stackexchange.com/questions/62548/what-does-changing-gl-texture-wrap-s-t-do

	if (wrapMode == TEXTURE_WRAP_MODE_CLAMP)
	{
		// TODO: Task05_01
		m_wrapMode = GL_CLAMP;//последние пиксели растягиваем до конца объекта
	}
	else if (wrapMode == TEXTURE_WRAP_MODE_REPEAT)
	{
		// TODO: Task05_01
		m_wrapMode = GL_REPEAT;//повторяем текстуру 
	}
	else if (wrapMode == TEXTURE_WRAP_MODE_CLAMP_TO_EDGE) {
		m_wrapMode = GL_CLAMP_TO_EDGE;
	}
}
/*
void GL20TextureSampler::PassParamsToShader(int textureRegister, bool toPixelShader) const
{
	// TODO: Task05_01

	// Set wrap mode (Clamp, Repeat).
	// TODO: Task05_01
		
	
	// Set filter mode (Point, Bilinear, Trilinear, Anisotropic).
	// TODO: Task05_01
	

	
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minFilterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magFilterMode);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapMode); //t - X axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapMode); //s - Y axis

	// Enable/disable anisotropic filter.
	if (m_useAniso)
	{
		float aniso = 0.f; //https://www.bfilipek.com/2012/06/aniso.html
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);//return the value or values of a selected parameter
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);// set texture parameters/ TODO: Task05_01
	}
	else
	{
		// TODO: Task05_01
	}
}
*/

void GL20TextureSampler::PassParamsToShader(int textureRegister, bool toPixelShader) const
{
	// TODO: Task05_01

	// Set wrap mode (Clamp, Repeat).
	// TODO: Task05_01

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapMode);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapMode);

	if (m_useAniso)
	{
		// TODO: Task05_01
		float aniso = 0.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);//return the value or values of a selected parameter
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);// set texture parameters
	}
	else
	{
		// TODO: Task05_01
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minFilterMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magFilterMode);
	}
}