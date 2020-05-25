#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Camera.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Meshes/MeshCube.h"
#include "GraphicsEngine/Meshes/MeshCylinder.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/Transform.h"

#include "Tasks/Task.h"
#include "Tasks/ObjectRotator.h"
#include "Tasks/CameraController.h"

#include "my/CubeMaterials.h"
#include "my/CylinderMaterials.h"

/**
* @brief Shows how to morph the objects.
* Key code is situated in the classes MaterialTask02Cube, MaterialTask02Cylinder.
*/
class Task02: 
	
public Task {
public:
	virtual ~Task02() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();
	
		// Camera
		{
			Object * pCameraObj = new Object();
			pCameraObj->m_pTransform = new Transform( Vector3(0, 1.5, -3), Vector3(0.0f, 0.0f, 0.0f));
			Camera * pCamera = new Camera();
			pCamera->SetFovY(90);
			pCamera->SetNearPlane(0.01f);
			pCamera->SetFarPlane(100);
			pCameraObj->AddComponent( pCamera );
			//pCameraObj->AddComponent( new CameraControllerBody() );

			scene.SetCamera( pCamera );
		}

		// Object # 1 - Cube (is morphed to sphere)
		{
			Object * pObject = new Object();
			pObject->m_pTransform	= new Transform( Vector3(0, 0, 0), Vector3(0, 30, 0) );
			pObject->m_pMesh		= new MeshCube(10);			
            pObject->m_pMaterial	= new MaterialUnlitCube();   
			
			//scene.AddObject( pObject );
		}

		// Object #2 - Cylinder (is twisted)
        {
			Object * pObject = new Object();
			pObject->m_pTransform	= new Transform( Vector3(0, 0, 0), Vector3(0, 30, 0) );
			pObject->m_pMesh		= new MeshCylinder(6);			
			//pObject->m_pMaterial    = new MaterialUnlitSimple();
			pObject->m_pMaterial = new MaterialUnlitCylinder();
			
			scene.AddObject( pObject );
        }
	}

	virtual void Update()
	{
		
	}
};
