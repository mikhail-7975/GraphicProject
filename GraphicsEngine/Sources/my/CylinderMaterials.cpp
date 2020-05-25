#include "CylinderMaterials.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"

#include <GraphicsEngine/Time.h>

MaterialUnlitCylinder::MaterialUnlitCylinder()
{
	m_vsFileName = "ShaderUnlitCylinder";//название шейдеров   вершинный шейдер.vs
	m_psFileName = "ShaderUnlitCylinder";//						пиксельный.fs . не трогаем, такой и остаётся
}

// TODO: Реализовать переключение Graphics API при нажатии на кнопки (1 - DirectX 11, 2 - OpenGL 2.0, 9 - DirectX 9)
// и отладить на этом механизм использования функций Init() и Deinit()
void MaterialUnlitCylinder::Init()
{
	Material::Init(); //не трогать

	// TODO: Нужно при компиляции скопировать папку с шейдерами
	// Google it: "visual studio during build copy files into application folder"
}

void MaterialUnlitCylinder::Deinit()
{
	Material::Deinit(); //не трогать
}

void MaterialUnlitCylinder::SetMaterial(const Object* pObject)
{
	// Заполняем матрицы World, View, Proj
	const Matrix4x4& matWorld = SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4& matView = SceneUtils::GetMatrixView();
	const Matrix4x4& matProj = SceneUtils::GetMatrixProj();

	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);
	const Vector4 time(Time::GetTime()/2, 0, 0, 0);
	
	
	//максимальный угол поворота
	const Matrix4x4 matWorldViewProjTopMatrix = MathUtils::GetMatrixWorldViewProjT(Matrix4x4::RotationY(-90 * (cos(time.x))) * matWorld, matView, matProj);
	const Matrix4x4 matWorldViewProjBottomMatrix = MathUtils::GetMatrixWorldViewProjT(Matrix4x4::RotationY(90 * (cos(time.x))) * matWorld, matView, matProj);


	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderVector4("time", time);//  раскомменчено
		//установить значение в вертексном шейдере; название, значение
		SetVertexShaderMatrix4x4("matrixWorldViewProjTopMatrix", matWorldViewProjTopMatrix);
		SetVertexShaderMatrix4x4("matrixWorldViewProjBottomMatrix", matWorldViewProjBottomMatrix);
		SetVertexShaderVector4("constColor", Vector4(1, 1, 1, 1));
		SetVertexShaderEnd();

		SetPixelShaderBegin();
		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}
