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

void MaterialUnlitCylinder::Init()
{
	Material::Init(); //не трогать

}

void MaterialUnlitCylinder::Deinit()
{
	Material::Deinit();
}

void MaterialUnlitCylinder::SetMaterial(const Object* pObject)
{
	// Заполняем матрицы World, View, Proj
	const Matrix4x4& matWorld = SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4& matView = SceneUtils::GetMatrixView();
	const Matrix4x4& matProj = SceneUtils::GetMatrixProj();

	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);
	const Vector4 time(Time::GetTime(), 0, 0, 0);
	
	
	//максимальный угол поворота
	const Matrix4x4 matWorldViewProjTopMatrix = MathUtils::GetMatrixWorldViewProjT(Matrix4x4::RotationY(-90 * (cos(time.x))) * matWorld, matView, matProj);
	const Matrix4x4 matWorldViewProjBottomMatrix = MathUtils::GetMatrixWorldViewProjT(Matrix4x4::RotationY(90 * (cos(time.x))) * matWorld, matView, matProj);


	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderVector4("time", time);
		SetVertexShaderMatrix4x4("matrixWorldViewProjTopMatrix", matWorldViewProjTopMatrix);
		SetVertexShaderMatrix4x4("matrixWorldViewProjBottomMatrix", matWorldViewProjBottomMatrix);
		SetVertexShaderVector4("constColor", Vector4(1, 1, 1, 1));
		SetVertexShaderEnd();

		SetPixelShaderBegin();
		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}
