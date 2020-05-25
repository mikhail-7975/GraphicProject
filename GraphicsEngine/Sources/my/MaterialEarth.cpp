#include "MaterialEarth.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"


MaterialEarth::MaterialEarth()
{
	m_vsFileName = "ShaderEarth";
	m_psFileName = "ShaderEarth";
	texture = NULL;
}

// TODO: Реализовать переключение Graphics API при нажатии на кнопки (1 - DirectX 11, 2 - OpenGL 2.0, 9 - DirectX 9)
// и отладить на этом механизм использования функций Init() и Deinit()
void MaterialEarth::Init()
{
	Material::Init();

	texture = new Texture2D("Earth_Albedo.jpg");
	//texture = new Texture2D("kek.jpg");
	// TODO: Нужно при компиляции скопировать папку с шейдерами
	// Google it: "visual studio during build copy files into application folder"
	texture->SetWrapMode(TEXTURE_WRAP_MODE_CLAMP_TO_EDGE);
	texture->SetFilterMode(TEXTURE_FILTER_MODE_ANISOTROPIC);
}

void MaterialEarth::Deinit()
{
	Material::Deinit();
}

void MaterialEarth::SetMaterial(const Object * pObject)
{
	// Заполняем матрицы World, View, Proj
	const Matrix4x4 & matWorld	= SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4 & matView	= SceneUtils::GetMatrixView();
	const Matrix4x4 & matProj	= SceneUtils::GetMatrixProj();
	
	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);

	SetMaterialBegin();
	{	
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderVector4	("constColor", m_color);
		SetVertexShaderEnd();

		SetPixelShaderBegin();
		SetPixelShaderTexture2d("texture", texture);
		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}
