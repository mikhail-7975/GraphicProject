#include "CubeMaterials.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"

#include <GraphicsEngine/Time.h>

MaterialUnlitCube::MaterialUnlitCube()
{
	m_vsFileName = "ShaderUnlitCube";//название шейдеров   вершинный шейдер.vs
	m_psFileName = "ShaderUnlitCube";//						пиксельный.fs . не трогаем, такой и остаётся
}

// TODO: Реализовать переключение Graphics API при нажатии на кнопки (1 - DirectX 11, 2 - OpenGL 2.0, 9 - DirectX 9)
// и отладить на этом механизм использования функций Init() и Deinit()
void MaterialUnlitCube::Init()
{
	Material::Init(); //не трогать

	// TODO: Нужно при компиляции скопировать папку с шейдерами
	// Google it: "visual studio during build copy files into application folder"
}

void MaterialUnlitCube::Deinit()
{
	Material::Deinit(); //не трогать
}

void MaterialUnlitCube::SetMaterial(const Object* pObject)
{
	// Заполняем матрицы World, View, Proj
	const Matrix4x4& matWorld = SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4& matView = SceneUtils::GetMatrixView();
	const Matrix4x4& matProj = SceneUtils::GetMatrixProj();

	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);
	double time_ = sin(Time::GetTime()) * sin(Time::GetTime());
	const Vector4 time(time_, 0, 0, 0);//    раскомменчено; 

	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderVector4("time", time);//  раскомменчено  
		SetVertexShaderVector4("constColor", Vector4(1, 1, 1, 1));
		SetVertexShaderEnd();

		SetPixelShaderBegin();
		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}
