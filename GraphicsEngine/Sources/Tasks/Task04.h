#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Light.h"
#include "GraphicsEngine/Materials/MaterialDiffuse.h"
#include "GraphicsEngine/Meshes/MeshSphere.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/Transform.h"

#include "Tasks/Task.h"
#include "Tasks/ObjectRotator.h"


/**
* @brief Shows how to write lightning materials.
* Key code is situated in the classes MaterialDiffuse, Light.
*/
class Task04: public Task
{
public:
	virtual ~Task04() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();
		
		// Camera
		{
			Object * pCameraObj = new Object();
			pCameraObj->m_pTransform = new Transform( Vector3(0.0f, 0.0f,7.0f), Vector3(0.0f, 180.0f, 0.0f));
			Camera * pCamera = new Camera();
			pCameraObj->AddComponent( pCamera );

			scene.SetCamera( pCamera );
		}

		// Object - Sphere
		{
			Object * pObject1 = new Object();

			pObject1->m_pTransform	= new Transform(0,0,0, 0,0,0, 3,3,3);
			pObject1->m_pMesh		= new MeshSphere(60);
            pObject1->m_pMaterial	= new MaterialDiffuse();//    
			pObject1->AddComponent( new ObjectRotator(0,10,0));

			scene.AddObject( pObject1 );
		}

		// Ligth source #1 - Directional
		{
			Light * sunLight = new Light(LIGHT_DIRECTIONAL);
			sunLight->SetColor(1,1,0);
			sunLight->SetIntensity(1);

			Object * pLightObject = new Object();
			pLightObject->m_pTransform	= new Transform(1,0,0, 0,90,0, 1,1,1);
			pLightObject->AddComponent(sunLight);

			scene.AddLight(sunLight);
		}

		// Ligth source #2 - Point
		{
			Light * pointLight = new Light(LIGHT_POINT);
			pointLight->SetColor(1,1,1);
			pointLight->SetIntensity(1);

			Object * pLightObject = new Object();
			pLightObject->m_pTransform	= new Transform(3,0, 0, 0,0,0, 1,1,1);
			pLightObject->AddComponent(pointLight);

			scene.AddLight(pointLight);
		}
		
		{
			Light* pointLight = new Light(LIGHT_SPOT);
			pointLight->SetColor(0, 0, 1);
			pointLight->SetIntensity(1);

			Object* pLightObject = new Object();
			pLightObject->m_pTransform = new Transform(0, 0, 9, 0, 160, 0, 1, 1, 1);
			pLightObject->AddComponent(pointLight);

			scene.AddLight(pointLight);
		}
	}

	virtual void Update()
	{
		
	}
};
