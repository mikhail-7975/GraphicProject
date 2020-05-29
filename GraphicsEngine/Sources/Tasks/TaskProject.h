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

#include "Game (final project)/ObjectController.h"
#include "Game (final project)/CollisionDetector.h"

/**
* @brief Shows how to load mesh from obj-file.

* Key code is situated in the class MeshObjFile.
*/
class TaskProject : public Task
{
	MeshObjFile* object1;
	MeshObjFile* object2;
	std::vector<Object*> objects;

	size_t count;

public:	
	TaskProject() {
		count = 0;
		object1 = new MeshObjFile("MeshCube.obj");
		object2 = new MeshObjFile("MeshCube.obj");
	}
	
public:
	virtual ~TaskProject() { }

	virtual void Init()
	{
		Scene& scene = Application::Instance().GetScene();

		// Camera
		{
			auto headController = new CameraControllerHead();

			Object* Body = new Object();
				Body->m_pTransform = new Transform(Vector3(0.0f, 0.1f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
				auto bodyController = new CameraControllerBody(headController);
				Body->AddComponent(bodyController);
			scene.AddObject(Body);

			Object* Head = new Object();
				Head->m_pTransform = new Transform(Vector3(0.0f, 0.1f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
				Camera* pCamera = new Camera();
				Head->AddComponent(pCamera);
				Head->AddComponent(headController);
				Head->m_pTransform->SetParent(Body->m_pTransform);

			scene.SetCamera(pCamera);

		}
		/*{
			Object* pCameraObj = new Object();
			pCameraObj->m_pTransform = new Transform(Vector3(0, 0, -5), Vector3(0.0f, 0.0f, 0.0f));
			Camera* pCamera = new Camera();
			//pCamera->SetFovY(90);
			pCamera->SetNearPlane(0.01f);
			pCamera->SetFarPlane(100);
			pCameraObj->AddComponent(pCamera);
			pCameraObj->AddComponent(new CameraControllerBody);

			scene.SetCamera(pCamera);
		}*/
		
		// Camera
		/*{
			Object* body = new Object();
			body->m_pTransform = new Transform(Vector3(0.0f, 0.5f, -5.0f), Vector3(0.0f, 0.0f, 0.0f));
			Object* pCameraObj = new Object();
			Camera* pCamera = new Camera();
			pCameraObj->m_pTransform = new Transform(Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, 0.0f, 0.0f));
			pCameraObj->AddComponent(pCamera);
			pCameraObj->m_pTransform->SetParent(body->m_pTransform);
			pCameraObj->AddComponent(new NewCameraController);
			body->AddComponent(new CameraController(true, pCameraObj->m_pTransform));
			scene.SetCamera(pCamera);
			scene.AddObject(body);
		}*/

		// Object #1 - Earth
		{
			Object* pObject1 = new Object();
			//pObject1->m_pMesh		= new MeshObjFile("MeshCube.obj");
			//pObject1->m_pMesh		= new MeshObjFile("MeshSphere.obj");
			//pObject1->m_pMesh		= new MeshObjFile("PLANE.obj");
			pObject1->makeMovable();
			pObject1->m_pMesh = new MeshObjFile("MeshCube.obj");
			pObject1->m_pTransform = new Transform(3, 0, 0, 0, 0, 0, 1, 1, 1);
			pObject1->m_pMaterial = new MaterialSand(TEXTURE_FILTER_MODE_ANISOTROPIC);
			pObject1->AddComponent(new ObjectMovingController);
			pObject1->AddComponent("ObjectMovingController", new ObjectMovingController);
			scene.AddObject(pObject1);
			objects.push_back(pObject1);
		}

		{
			Object* pObject1 = new Object();
			//pObject1->m_pMesh		= new MeshObjFile("MeshCube.obj");
			//pObject1->m_pMesh		= new MeshObjFile("MeshSphere.obj");
			//pObject1->m_pMesh		= new MeshObjFile("PLANE.obj");
			pObject1->makeMovable();
			pObject1->m_pMesh = new MeshObjFile("MeshCube.obj");
			pObject1->m_pTransform = new Transform(0, 0, 0, 0, 0, 0, 0.1, 0.1, 0.1);
			pObject1->m_pMaterial = new MaterialSand(TEXTURE_FILTER_MODE_ANISOTROPIC);
			pObject1->AddComponent(new CameraControllerBody);
			pObject1->AddComponent("ObjectMovingController", new ObjectMovingController);
			scene.AddObject(pObject1);
			objects.push_back(pObject1);
		}

		{
			Object* pObject1 = new Object();
			//pObject1->m_pMesh		= new MeshObjFile("MeshCube.obj");
			//pObject1->m_pMesh		= new MeshObjFile("MeshSphere.obj");
			//pObject1->m_pMesh		= new MeshObjFile("PLANE.obj");
			pObject1->makeNonMovable();
			pObject1->m_pMesh = new MeshObjFile("MeshCube.obj");
			pObject1->m_pTransform = new Transform(0, 0, 0, 0, 0, 0, 1, 1, 1);
			pObject1->m_pMaterial = new MaterialHighway();
			scene.AddObject(pObject1);
			objects.push_back(pObject1);
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
		
	}

	virtual void Update()
	{
		Scene& scene = Application::Instance().GetScene();
		auto vecObj1 = scene.GetObjects();
		auto vecObj2 = scene.GetObjects();
		
		for (auto& it : vecObj1) {
			//std::cout << it->m_pTransform->GetPosition().x << std::endl;
		}
		
		//for (size_t i = 0; i < 100000000; i++);
		
		
		if (objects.size() <= 1) return;

		for (size_t i1 = 0; i1 < objects.size(); ++i1) {
			for (size_t i2 = i1 ; i2 < objects.size(); ++i2) {
				if (i1 != i2) {
					auto dist = detectCollision(*objects[i1], *objects[i2]);
					Vector3 currentPos1 = objects[i1]->m_pTransform->GetPosition();
					Vector3 currentPos2 = objects[i2]->m_pTransform->GetPosition();
					Vector3 delta = currentPos1 - currentPos2;
					//std::cout << dist << std::endl;
					if (dist < 1.) {
						if(objects[i1]->movable)
							objects[i1]->m_pTransform->Translate(delta * 0.01);
						if (objects[i2]->movable)
							objects[i2]->m_pTransform->Translate(-delta * 0.01);
					}
				}
			}
		}
	}
};

