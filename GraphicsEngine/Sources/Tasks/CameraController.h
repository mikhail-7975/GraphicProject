#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/Input.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"
#include "GraphicsEngine/Internal/InternalInput.h"

#include <iostream>

class CameraControllerHead : public Component
{
    Vector3 mousePos;
    Vector3 mousePosPrev;

    bool isCameraMove = false;

public:
    CameraControllerHead()
    {
        mousePos = Vector3::Zero();
        mousePosPrev = Vector3::Zero();
    }

    virtual ~CameraControllerHead() {}

    Vector3 calculateMoving() {
        Transform* pTransform = m_pObject->m_pTransform;

        //fing projection caneraVector to X and Z axis
        //nirmalize
        //it is direction.

        //direction = Vector3(sin(PI / 180 * angle.y), 0, cos(PI / 180 * angle.y));
       /* Scene& scene = Application::Instance().GetScene();
        Vector3 eyeAngle = scene.GetCamera()->GetObjectPtr()->m_pTransform->GetEulerAngles();// GetPosition();

        auto cameraDirection = Vector3(sin(PI / 180 * eyeAngle.y), cos(PI / 180 * eyeAngle.x), cos(PI / 180 * eyeAngle.y));
        */
        Vector3 forward = pTransform->GetForward();//возвращают пересчитанное значение
        Vector3 right = pTransform->GetRight();
        Vector3 up = pTransform->GetUp();

        double dt = Time::GetDeltaTime();
        Vector3 direction;

        if (Input::GetKey(KEY_CODE_W)) {
            direction += forward;
        }
        if (Input::GetKey(KEY_CODE_S)) {
            direction -= forward;
        }
        /*if (Input::GetKey(KEY_CODE_D)) {
            direction += right;
        }
        if (Input::GetKey(KEY_CODE_A)) {
            direction -= right;
        }*/
        /*if (Input::GetKey(KEY_CODE_Q)) {
            direction += up;
        }
        if (Input::GetKey(KEY_CODE_E)) {
            direction -= up;
        }*/
        return dt * direction;
    }

    void moveHead(Vector3 _direction) {
        Transform* pTransform = m_pObject->m_pTransform;
        pTransform->Translate(_direction);
    }

    void rotateCamera() {
        Transform* pTransform = m_pObject->m_pTransform;
        if (Input::GetMouseButtonUp(0)) {
            isCameraMove = false;
        }
        if (Input::GetMouseButtonDown(0)) {
            isCameraMove = true;
        }
        
        mousePos = Input::GetMousePosition();
        if (isCameraMove) {
            const double speed = 1.0;
            Vector3 direction;
            direction += (mousePosPrev - mousePos);
            pTransform->Rotate(0.1 * Vector3(direction.y, 0, 0));
        }

        mousePosPrev = mousePos;
        
    }

    virtual void Update() {
        rotateCamera();
        auto vec = calculateMoving();
        //moveHead(vec);
    }
};


class NewCameraController : public Component {
public:
    void calculateCameraDirection() {
        Transform* pTransform = m_pObject->m_pTransform;
        auto angle = pTransform->GetEulerAngles();
        std::cout << sin(angle.x) << " " << 0 << " " << cos(angle.z) << " === ";
        //fing projection caneraVector to X and Z axis
        //nirmalize
        //it is direction.
        
        cameraDirection = Vector3(sin(PI / 180 * angle.y), 0, cos(PI / 180 * angle.y));
    }

    Vector3 calculateMovingDirection() {
        if (Input::GetKey(KEY_CODE_Q))
        {
            return Vector3(0, -1, 0);
        }

        if (Input::GetKey(KEY_CODE_E))
        {
            return Vector3(0, 1, 0);
        }

        if (Input::GetKey(KEY_CODE_W) || Input::GetKey(KEY_CODE_UP_ARROW))
        {
            return cameraDirection;
        }

        if (Input::GetKey(KEY_CODE_S) || Input::GetKey(KEY_CODE_DOWN_ARROW))
        {
            return -1 * cameraDirection;
        }

        if (Input::GetKey(KEY_CODE_D) || Input::GetKey(KEY_CODE_RIGHT_ARROW))
        {
            return Vector3(cameraDirection.z, 0, -cameraDirection.x);
        }

        if (Input::GetKey(KEY_CODE_A) || Input::GetKey(KEY_CODE_LEFT_ARROW))
        {
            return Vector3(cameraDirection.z, 0, -cameraDirection.x);
        }
        return Vector3(0, 0, 0);
    }

    void moveCamera(Vector3 movingDirection) {
        Transform* pTransform = m_pObject->m_pTransform;
        double dt = Time::GetDeltaTime();
        std::cout << movingDirection.x << ' ' << movingDirection.y << ' ' << movingDirection.z << std::endl;
        pTransform->Translate(dt * movingDirection);
    }

    void rotateCamera() {
        Transform* pTransform = m_pObject->m_pTransform;
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

            pTransform->Rotate(0.1 * Vector3(direction.y, direction.x, 0));
        }
        
        mousePosPrev = mousePos;
        //InternalInput::SetMousePosition(mousePos.x, mousePos.y);
    }

    virtual void Update()
    {
        rotateCamera();
        calculateCameraDirection();
        Vector3 moveDir = calculateMovingDirection();
        moveCamera(moveDir);
      }

private:
    Vector3 cameraDirection;
    Vector3 mousePosPrev;
    Vector3 mousePos;
    bool isCameraMove;
};

class CameraControllerBody : public Component
{
    Vector3 mousePos;
    Vector3 mousePosPrev;
    const double speed = 1.0;
    bool canCameraMove = false;

    CameraControllerHead* m_head = nullptr;

public:
    CameraControllerBody()
    {
        mousePos = Vector3::Zero();
        mousePosPrev = Vector3::Zero();
    }
    CameraControllerBody(CameraControllerHead* head_controller) : m_head{ head_controller }
    {
        mousePos = Vector3::Zero();
        mousePosPrev = Vector3::Zero();
    }

    virtual ~CameraControllerBody() {}

    Vector3 calculateMoving() {
        Transform* pTransform = m_pObject->m_pTransform;
        
        //fing projection caneraVector to X and Z axis
        //nirmalize
        //it is direction.

        //direction = Vector3(sin(PI / 180 * angle.y), 0, cos(PI / 180 * angle.y));
        Scene& scene = Application::Instance().GetScene();
        Vector3 eyeAngle = scene.GetCamera()->GetObjectPtr()->m_pTransform->GetEulerAngles();// GetPosition();

        auto cameraDirection = Vector3(sin(PI / 180 * eyeAngle.y), cos(PI / 180 * eyeAngle.x), cos(PI / 180 * eyeAngle.y));
        auto pCameraTransform = scene.GetCamera()->GetObjectPtr()->m_pTransform;

        Vector3 forward = pCameraTransform->GetForward();//возвращают пересчитанное значение
        Vector3 right = pCameraTransform->GetRight();
        Vector3 up = pCameraTransform->GetUp();

        /*Vector3 forward = pTransform->GetForward();//возвращают пересчитанное значение
        Vector3 right = pTransform->GetRight();
        Vector3 up = pTransform->GetUp();
        */

        double dt = Time::GetDeltaTime();
        Vector3 direction;

        if (Input::GetKey(KEY_CODE_W)) {
            direction += forward;
        }
        if (Input::GetKey(KEY_CODE_S)) {
             direction -= forward;
        }
        if (Input::GetKey(KEY_CODE_D)) {
            direction += right;
        }
        if (Input::GetKey(KEY_CODE_A)) {
            direction -= right;
        }
        if (Input::GetKey(KEY_CODE_Q)) {
            direction += up;
        }
        if (Input::GetKey(KEY_CODE_E)) {
            direction -= up;
        }
        return dt * direction;
    }

    void moveBody(Vector3 _direction) {
        Transform* pTransform = m_pObject->m_pTransform;
        pTransform->Translate(_direction);
    }

    Vector3 calculateRotation() {
        Transform* pTransform = m_pObject->m_pTransform;
        if (Input::GetMouseButtonUp(0)){
            canCameraMove = false;
        }
        if (Input::GetMouseButtonDown(0)) {
            canCameraMove = true;
        }

        mousePos = Input::GetMousePosition();
        Vector3 mouseMoving = Vector3(0, 0, 0);
        if (canCameraMove) {
            mouseMoving += (mousePosPrev - mousePos);
            pTransform->Rotate(0.1 * Vector3(0, mouseMoving.x, mouseMoving.z));
        }
        mousePosPrev = mousePos;
        return 0.1 * Vector3(0, mouseMoving.x, mouseMoving.z);
    }

    void rotateCamera(Vector3 rotationVector) {

        Transform* pTransform = m_pObject->m_pTransform;
        pTransform->Rotate(rotationVector);
    }

    virtual void Update()
    {
        Scene& scene = Application::Instance().GetScene();
        Vector3 eyeAngle = scene.GetCamera()->GetObjectPtr()->m_pTransform->GetEulerAngles();
        Transform* pTransform = m_pObject->m_pTransform;
        auto moveVector = calculateMoving();
        if ((moveVector.x || moveVector.y || moveVector.z))
            std::cout << eyeAngle.x << " " << cos(PI / 180 * eyeAngle.x) << std::endl;
            moveBody(Vector3(moveVector.x * cos(PI / 180 * eyeAngle.x), moveVector.y, moveVector.z * cos(PI / 180 * eyeAngle.x)));
            //moveBody(Vector3(, moveVector.y, 0));
            

        auto rotVector = calculateRotation();
        if ((rotVector.x || rotVector.y || rotVector.z))
            rotateCamera(rotVector);
    }
};