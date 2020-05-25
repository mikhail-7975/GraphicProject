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
#include "CameraController.h"

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
		} else {
			Transform* pTransform = m_pObject->m_pTransform;
			pTransform->Translate(dt * Vector3(-1., .0, .0));
			pTransform->Rotate(dt * Vector3(0., 10., 0.));
			if (pTransform->GetPosition().x < 0)
				a = true;
		}
		moved = false;
	}
};



/**
* @brief Shows how to load mesh from obj-file.

* Key code is situated in the class MeshObjFile.
*/
class TaskProject : public Task
{
	MeshObjFile* object1;
	MeshObjFile* object2;

public:	
	TaskProject() {
		object1 = new MeshObjFile("MeshCube.obj");
		object2 = new MeshObjFile("MeshCube.obj");
	}
	
public:
	virtual ~TaskProject() { }

	virtual void Init()
	{
		std::cout << std::endl;
		Scene& scene = Application::Instance().GetScene();

		//camera
		{
			auto head_controller = new CameraControllerHead;

			Object* Body = new Object();
			Body->m_pTransform = new Transform(Vector3(0.0f, 0.1f, -10.0f), Vector3(0.0f, 0.0f, 0.0f));
			auto body_controller = new CameraControllerBody(head_controller);
			Body->AddComponent(body_controller);
			scene.AddObject(Body);

			Object* Head = new Object();
			Camera* pCamera = new Camera();
			Head->m_pTransform = new Transform(Vector3(0.0f, .1f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
			Head->AddComponent(pCamera);
			Head->AddComponent(head_controller);
			scene.SetCamera(pCamera);
			Head->m_pTransform->SetParent(Body->m_pTransform);
		}

		
		// Object #1 - Earth
		{
			Object* pObject1 = new Object();
			//pObject1->m_pMesh		= new MeshObjFile("MeshCube.obj");
			//pObject1->m_pMesh		= new MeshObjFile("MeshSphere.obj");
			//pObject1->m_pMesh		= new MeshObjFile("PLANE.obj");
			pObject1->m_pMesh = object1;
			pObject1->m_pTransform = new Transform(0, 0, 0, 0, 0, 0, 1, 1, 1);
			pObject1->m_pMaterial = new MaterialSand(TEXTURE_FILTER_MODE_ANISOTROPIC);
			pObject1->AddComponent(new ObjectController);
			scene.AddObject(pObject1);
		}

		{
			Object* pObject1 = new Object();
			//pObject1->m_pMesh		= new MeshObjFile("MeshCube.obj");
			//pObject1->m_pMesh		= new MeshObjFile("MeshSphere.obj");
			//pObject1->m_pMesh		= new MeshObjFile("PLANE.obj");
			pObject1->m_pMesh = object2;
			pObject1->m_pTransform = new Transform(0, 0, 0, 0, 0, 0, 1, 1, 1);
			pObject1->m_pMaterial = new MaterialHighway();
			scene.AddObject(pObject1);
		}

		// Lightsource #1 - Directional
		{
			Light* pLight = new Light(LIGHT_DIRECTIONAL);
			pLight->SetColor(1, 1, 1);
			pLight->SetIntensity(1);

			Object* pLightObject = new Object();
			pLightObject->m_pTransform = new Transform(1, 0, 0, 45, 90, 0, 1, 1, 1);
			//pLightObject->AddComponent(new ObjectRotator(0, 4050, 0));
			pLightObject->AddComponent(pLight);

			scene.AddLight(pLight);
		}
	}

	virtual void Denit() {
		object1->Deinit();
	}

	virtual void Update()
	{
		auto vec = object1->getMeshVertices();
		for (auto& it : vec) {
			//std::cout << it.x << " " << it.y << " " << it.z << std::endl;
		}
	}
};

