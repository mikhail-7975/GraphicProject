#include "my/HighwayMaterials.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"

#include <GraphicsEngine/Time.h>

MaterialHighway::MaterialHighway()
{
	m_vsFileName = "ShaderHighway";//название шейдеров   вершинный шейдер.vs
	m_psFileName = "ShaderHighway";//						пиксельный.fs . не трогаем, такой и остаётся

	m_pTexture1 = NULL;
	m_pTexture2 = NULL;
	m_pTexture3 = NULL;
	m_filterMode = TEXTURE_FILTER_MODE_ANISOTROPIC;
}

MaterialHighway::MaterialHighway(TextureFilterMode filterMode)
{
	m_vsFileName = "ShaderHighway";//название шейдеров   вершинный шейдер.vs
	m_psFileName = "ShaderHighway";//						пиксельный.fs . не трогаем, такой и остаётся
	
	m_pTexture1 = NULL;
	m_pTexture2 = NULL;
	m_pTexture3 = NULL;
	m_filterMode = filterMode;
}

// TODO: Реализовать переключение Graphics API при нажатии на кнопки (1 - DirectX 11, 2 - OpenGL 2.0, 9 - DirectX 9)
// и отладить на этом механизм использования функций Init() и Deinit()
void MaterialHighway::Init()
{
	Material::Init(); //не трогать

	
					  
	m_pTexture1 = new Texture2D("Earth_Albedo1.jpg");
	m_pTexture2 = new Texture2D("road_2.jpg");
	m_pTexture3 = new Texture2D("road_3.jpg");//

	m_pTexture1->SetFilterMode(m_filterMode);// TODO: Нужно при компиляции скопировать папку с шейдерами
	m_pTexture2->SetFilterMode(m_filterMode);
	m_pTexture3->SetFilterMode(m_filterMode);
											 // Google it: "visual studio during build copy files into application folder"
}

void MaterialHighway::Deinit()
{
	delete m_pTexture1;
	delete m_pTexture2;
	delete m_pTexture3;

	m_pTexture1 = NULL;
	m_pTexture2 = NULL;
	m_pTexture3 = NULL;

	Material::Deinit(); //не трогать
}

void MaterialHighway::SetMaterial(const Object* pObject)
{
	// Заполняем матрицы World, View, Proj
	const Matrix4x4& matWorld = SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4& matView = SceneUtils::GetMatrixView();
	const Matrix4x4& matProj = SceneUtils::GetMatrixProj();

	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);


	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderVector4("constColor", m_color);
		SetVertexShaderEnd();

		SetPixelShaderBegin();
		SetPixelShaderTexture2d("texture1", m_pTexture1);
		//SetPixelShaderTexture2d("texture2", m_pTexture2);
		//SetPixelShaderTexture2d("texture3", m_pTexture3);
		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}
