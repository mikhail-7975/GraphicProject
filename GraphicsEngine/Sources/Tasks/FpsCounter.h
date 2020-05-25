#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/GUI.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"

#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20GUI.h"


class FpsCounter : public Component
{
	double	t1, t2;
	int		f1, f2;
	double	fps_current, fps_last;

public:
	FpsCounter() 
	{
		t1 = Time::GetTime();
		f1 = Time::GetFrameCount();
		fps_current = 0;
		fps_last = 0;
	}

	virtual ~FpsCounter() {}

	virtual void Update() 
	{
		t2 = Time::GetTime();
		f2 = Time::GetFrameCount();

		if ((f2 - f1) && (t2 - t1 > 1)) {
			fps_current = (f2 - f1) / (t2 - t1);
			f1 = f2;
			t1 = t2;
			fps_last = fps_current;
		} else {
			fps_current = fps_last;
		}

		std::string str = std::to_string(fps_current);

		GUI::Label(-670.0, 540.0, 800, 600, ("FPS = " + str).c_str());//    
	}
};
