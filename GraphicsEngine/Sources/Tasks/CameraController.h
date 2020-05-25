#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/Input.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"

#include <iostream>

class CameraControllerHead : public Component
{
public:
    CameraControllerHead()
    {
        mousePos = Vector3::Zero();
        mousePosPrev = Vector3::Zero();
    }
    
    virtual ~CameraControllerHead() {}

    virtual void Update()
    {
        Transform* pTransform = m_pObject->m_pTransform;

        // Camera Rotation
        {
            if (Input::GetMouseButtonUp(0))
            {
                isCameraMove = true;
            }
            if (Input::GetMouseButtonDown(0))
            {
                isCameraMove = false;
            }

            mousePos = Input::GetMousePosition();
            if (isCameraMove)
            {

                const double speed = 1.0;
                Vector3 direction;

                // TODO : Task08
                direction += (mousePosPrev - mousePos);

                pTransform->Rotate(0.1 * Vector3(direction.y, 0, direction.z));
            }
            mousePosPrev = mousePos;
        }
    }

private:
    Vector3 mousePos;
    Vector3 mousePosPrev;

    bool isCameraMove = false;
};

class CameraControllerBody : public Component
{
	Vector3 mousePos;
	Vector3 mousePosPrev;
    bool isCameraMove = false;
    CameraControllerHead* m_head = nullptr;
public:
    CameraControllerBody() = delete;

    CameraControllerBody(CameraControllerHead* head_controller) : m_head{ head_controller }
	{
		mousePos		= Vector3::Zero();
		mousePosPrev	= Vector3::Zero();
	}


	virtual ~CameraControllerBody() {}

	virtual void Update() 
	{
		Transform * pTransform = m_pObject->m_pTransform;
		
		// Camera Translation
		{
			Vector3 forward	= pTransform->GetForward();
			Vector3 right	= pTransform->GetRight();
            Vector3 up = pTransform->GetUp();
			double dt = Time::GetDeltaTime();

			const double speed = 1.0;
			Vector3 direction;

            if (Input::GetKey(KEY_CODE_Q))
            {
                direction += up;
            }

 

            if (Input::GetKey(KEY_CODE_E))
            {
                direction -= up;
            }

            if (Input::GetKey(KEY_CODE_W) || Input::GetKey(KEY_CODE_UP_ARROW))
            {
                direction += forward;
            }

			if (Input::GetKey(KEY_CODE_W) || Input::GetKey(KEY_CODE_UP_ARROW))
			{
				direction += forward;
			}

            
            if (Input::GetKey(KEY_CODE_S) || Input::GetKey(KEY_CODE_DOWN_ARROW))
            {
                direction -= forward;
            }
            
			if (Input::GetKey(KEY_CODE_D) || Input::GetKey(KEY_CODE_RIGHT_ARROW))
            {
                direction += right;
            }
            
			if (Input::GetKey(KEY_CODE_A) || Input::GetKey(KEY_CODE_LEFT_ARROW))
            {
                direction -= right;
            }
			
		
			// TODO : Task08

			pTransform->Translate( speed * dt * direction );
		}

		// Camera Rotation
        {
            if (Input::GetMouseButtonUp(0))
            {
                isCameraMove = true;
                //isCameraMove = false;
            }
            if (Input::GetMouseButtonDown(0))
            {
                isCameraMove = false;
                //isCameraMove = true;
            }

            mousePos = Input::GetMousePosition();
            if (isCameraMove)
            {
                const double speed = 1.0;
                Vector3 direction;

                // TODO : Task08
                direction += (mousePosPrev - mousePos);

                pTransform->Rotate(0.1 * Vector3(direction.y, direction.x, direction.z));
            }
            mousePosPrev = mousePos;
        }
	}
};
