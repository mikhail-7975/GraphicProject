#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Meshes/MeshQuad.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Materials/MaterialUnlit.h"
#include "GraphicsEngine/Light.h"

#include "Tasks/Task.h"
#include "Tasks/CameraController.h"


/**
* @brief Shows how to process user's input (keyboard and mouse).
* Key code is situated in the classes CameraController, Input, IternalInput, WinInput, GL20Input.
*/
class Task08: public Task
{
public:
	virtual ~Task08() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();
	
		//camera
		/*{
			auto head_controller = new CameraControllerHead;

			Object* Body = new Object();
			Body->m_pTransform = new Transform(Vector3(0.0f, 0.1f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
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
		}*/
		/*
		// Object #1 - Road with 3 textures
		{
			Object * pObject1 = new Object();

			pObject1->m_pTransform	= new Transform( 0,0,0, 0,0,0, 2,2,2 );
			pObject1->m_pMesh		= new MeshQuad();			
			//pObject1->m_pMaterial	= new MaterialUnlit(Vector3(0.5, 0.5, 0.5));
			pObject1->m_pMaterial = new MaterialHighway();
						
			scene.AddObject( pObject1 );
		}

		{
			Object* pObject1 = new Object();
			//pObject1->m_pMesh		= new MeshObjFile("MeshCube.obj");
			//pObject1->m_pMesh		= new MeshObjFile("MeshSphere.obj");
			//pObject1->m_pMesh		= new MeshObjFile("PLANE.obj");
			pObject1->m_pMesh = new MeshObjFile("Cartoon_Turtle.obj");
			pObject1->m_pTransform = new Transform(1.5, -5, -2, 0, 0, 0, 0.1, 0.1, 0.1);
			pObject1->m_pMaterial = new MaterialDiffuse();
			pObject1->AddComponent(new ObjectRotator(0, 0, 0));

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
		}*/
		// Object # 1 - Cube (is morphed to sphere)
		{
			Object* pObject = new Object();
			pObject->m_pTransform = new Transform(Vector3(0, 0, 0), Vector3(0, 30, 0));
			pObject->m_pMesh = new MeshCube(1);
			pObject->m_pMaterial = new MaterialUnlitCube();

			scene.AddObject( pObject );
		}

		// Object #2 - Cylinder (is twisted)
		/*{
			Object* pObject = new Object();
			pObject->m_pTransform = new Transform(Vector3(0, 0, 0), Vector3(0, 30, 0));
			pObject->m_pMesh = new MeshCylinder(4);
			//pObject->m_pMaterial    = new MaterialUnlitSimple();
			pObject->m_pMaterial = new MaterialUnlitCylinder();

			scene.AddObject(pObject);
		}*/
	}

	virtual void Update()
	{
		
	}
};
