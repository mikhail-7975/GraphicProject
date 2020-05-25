#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Meshes/MeshObjFile.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/SceneUtils.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Materials/MaterialDiffuse.h"
#include "GraphicsEngine/Light.h"


#include "Tasks/Task.h"
#include "Tasks/ObjectRotator.h"

class ObjectController : public Component
{
	bool moved = false;
	bool a = false;
public:
	ObjectController()
	{
	}

	virtual ~ObjectController() {}

	virtual void Update()
	{
		Vector3 cameraPos = SceneUtils::GetEyePosition();
		//std::cout << cameraPos.x << " " << cameraPos.y << " " << cameraPos.z << std::endl;
		double dt = Time::GetDeltaTime();


		if (a) {
			Transform* pTransform = m_pObject->m_pTransform;
			pTransform->Translate(dt * Vector3(1., .0, .0));
			pTransform->Rotate(dt * Vector3(0., 10., 0.));
			if (pTransform->GetPosition().x > 3)
				a = false;
		}
		else {
			Transform* pTransform = m_pObject->m_pTransform;
			pTransform->Translate(dt * Vector3(-1., .0, .0));
			pTransform->Rotate(dt * Vector3(0., 10., 0.));
			if (pTransform->GetPosition().x < 0)
				a = true;
		}
		moved = false;
	}
};