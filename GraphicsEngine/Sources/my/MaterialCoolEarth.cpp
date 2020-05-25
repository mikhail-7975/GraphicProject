#include "MaterialCoolEarth.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"
#include "GraphicsEngine/Light.h"

MaterialCoolEarth::MaterialCoolEarth()
{
	m_vsFileName = "ShaderCoolEarth";
	m_psFileName = "ShaderCoolEarth";
	texture = NULL;
	textureNormal = NULL;
}

// TODO: Реализовать переключение Graphics API при нажатии на кнопки (1 - DirectX 11, 2 - OpenGL 2.0, 9 - DirectX 9)
// и отладить на этом механизм использования функций Init() и Deinit()
void MaterialCoolEarth::Init()
{
	Material::Init();

	texture = new Texture2D("Earth_Albedo.jpg");
	textureNormal = new Texture2D("Earth_NormalMap.jpg");
	//texture = new Texture2D("kek.jpg");
	// TODO: Нужно при компиляции скопировать папку с шейдерами
	// Google it: "visual studio during build copy files into application folder"
	texture->SetWrapMode(TEXTURE_WRAP_MODE_CLAMP_TO_EDGE);
	texture->SetFilterMode(TEXTURE_FILTER_MODE_ANISOTROPIC);
	textureNormal->SetWrapMode(TEXTURE_WRAP_MODE_CLAMP_TO_EDGE);
	textureNormal->SetFilterMode(TEXTURE_FILTER_MODE_ANISOTROPIC);
}

void MaterialCoolEarth::Deinit()
{
	Material::Deinit();
}

void MaterialCoolEarth::SetMaterial(const Object* pObject)
{
	// Заполняем матрицы World, View, Proj
	const Matrix4x4& matWorld = SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4& matView = SceneUtils::GetMatrixView();
	const Matrix4x4& matProj = SceneUtils::GetMatrixProj();

	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);
	const Matrix4x4 matWorldT = matWorld.Transpose();
	const Matrix4x4 matWorldNormal = matWorld.Inverse();

	// Получили список всех источников света в сцене
	std::list<const Light*> lights = SceneUtils::GetLights();
	const size_t count = lights.size() < 3 ? lights.size() : 3;

	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderEnd();

		SetPixelShaderBegin();
		SetPixelShaderTexture2d("texture", texture);
		SetPixelShaderTexture2d("textureNormal", textureNormal);
		SetPixelShaderMatrix4x4("matWorldNormal", matWorldNormal);
		SetPixelShaderMatrix4x4("matWorldT", matWorldT);
		SetPixelShaderVector4("materialColor", Vector4(1, 1, 1, 1));
		SetPixelShaderVector4("lightsCount", Vector4(count, 1, 1, 1));

		//передаём в шейдер информацию о камере   
		SetPixelShaderVector4("camPosition", Vector4(SceneUtils::GetEyePosition(), 0.0f));

		// Передаём параметры каждого источника света
		int i = 0;
		std::list<const Light*>::iterator iter;
		for (iter = lights.begin(); iter != lights.end(); ++iter, ++i)
		{
			const Light* pLight = *iter;
			const Vector4 lightType = pLight->GetType();
			const Vector4 lightPosition = Vector4(pLight->GetPosition(), 1);
			const Vector4 lightDirection = Vector4(pLight->GetDirection(), 0);
			const Vector4 lightColor = pLight->GetColor();



			// "lights[i]"
			std::string lightStr = "lights[" + std::to_string(static_cast<long long>(i)) + "]";

			// "lights[i].type", "lights[i].position", "lights[i].direction", "lights[i].color"
			SetPixelShaderVector4((lightStr + ".type").c_str(), lightType);
			SetPixelShaderVector4((lightStr + ".position").c_str(), lightPosition);
			SetPixelShaderVector4((lightStr + ".direction").c_str(), lightDirection);
			SetPixelShaderVector4((lightStr + ".color").c_str(), lightColor);


		}

		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}

/*void MaterialCoolEarth::SetMaterial(const Object * pObject)
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
*/