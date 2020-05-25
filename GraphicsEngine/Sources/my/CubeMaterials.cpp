#include "CubeMaterials.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"

#include <GraphicsEngine/Time.h>

MaterialUnlitCube::MaterialUnlitCube()
{
	m_vsFileName = "ShaderUnlitCube";//�������� ��������   ��������� ������.vs
	m_psFileName = "ShaderUnlitCube";//						����������.fs . �� �������, ����� � �������
}

// TODO: ����������� ������������ Graphics API ��� ������� �� ������ (1 - DirectX 11, 2 - OpenGL 2.0, 9 - DirectX 9)
// � �������� �� ���� �������� ������������� ������� Init() � Deinit()
void MaterialUnlitCube::Init()
{
	Material::Init(); //�� �������

	// TODO: ����� ��� ���������� ����������� ����� � ���������
	// Google it: "visual studio during build copy files into application folder"
}

void MaterialUnlitCube::Deinit()
{
	Material::Deinit(); //�� �������
}

void MaterialUnlitCube::SetMaterial(const Object* pObject)
{
	// ��������� ������� World, View, Proj
	const Matrix4x4& matWorld = SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4& matView = SceneUtils::GetMatrixView();
	const Matrix4x4& matProj = SceneUtils::GetMatrixProj();

	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);
	double time_ = sin(Time::GetTime()) * sin(Time::GetTime());
	const Vector4 time(time_, 0, 0, 0);//    �������������; 

	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderVector4("time", time);//  �������������  
		SetVertexShaderVector4("constColor", Vector4(1, 1, 1, 1));
		SetVertexShaderEnd();

		SetPixelShaderBegin();
		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}
