#include "GL20Input.h"
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20.h"
#include "GraphicsEngine/Internal/InternalInput.h"

#ifdef CAN_USE_OPEN_GL


void GL20Input::Init()
{
	// TODO : Task08
}

void GL20Input::Clear()
{
	InternalInput::Clear();
}

void GL20Input::SetLetterKeyDown(unsigned char key)
{
	// TODO : Task08
	InternalInput::SetKeyDown(key);
	// Call InternalInput
}

void GL20Input::SetLetterKeyUp(unsigned char key)
{
	// TODO : Task08
	InternalInput::SetKeyUp(key);
	// Call InternalInput
}

void GL20Input::SetSpecialKeyDown(unsigned char key)
{
	// TODO : Task08
	unsigned int true_key = key;

	if (true_key == GLUT_KEY_UP)
	{
		true_key = (KEY_CODE_UP_ARROW);
	}
	if (true_key == GLUT_KEY_DOWN)
	{
		true_key = (KEY_CODE_DOWN_ARROW);
	}
	if (true_key == GLUT_KEY_LEFT)
	{
		true_key = (KEY_CODE_LEFT_ARROW);
	}
	if (true_key == GLUT_KEY_RIGHT)
	{
		true_key = (KEY_CODE_RIGHT_ARROW);
	}
	InternalInput::SetKeyDown(true_key);
	// Call InternalInput
}

void GL20Input::SetSpecialKeyUp(unsigned char key)
{
	// TODO : Task08
		unsigned int true_key = key;

		if (true_key == GLUT_KEY_UP)
		{
			true_key = (KEY_CODE_UP_ARROW);
		}
		if (true_key == GLUT_KEY_DOWN)
		{
			true_key = (KEY_CODE_DOWN_ARROW);
		}
		if (true_key == GLUT_KEY_LEFT)
		{
			true_key = (KEY_CODE_LEFT_ARROW);
		}
		if (true_key == GLUT_KEY_RIGHT)
		{
			true_key = (KEY_CODE_RIGHT_ARROW);
		}

		InternalInput::SetKeyUp(true_key);
	
	// Call InternalInput
}


void GL20Input::SetMouseButtonsEvent(int button, int state, int x, int y)
{
	// TODO : Task08
	InternalInput::SetMouseButton(button, !state);
	InternalInput::SetMousePosition(x, y);
	// Call InternalInput
}

void GL20Input::SetMouseMotionEvent(int x, int y)
{
	// TODO : Task08
	InternalInput::SetMousePosition(x, y);
	// Call InternalInput
}

#endif
