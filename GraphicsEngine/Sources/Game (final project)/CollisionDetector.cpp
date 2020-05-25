#include "CollisionDetector.h"
#include <cmath>

double detectCollision(const Object& obj2, const Object& obj1)
{
	auto pos1 = obj1.m_pTransform->GetPosition();
	auto pos2 = obj2.m_pTransform->GetPosition();

	double distance = sqrt(pow((pos1.x - pos2.x), 2) + pow((pos1.y - pos2.y), 2) + pow((pos1.z - pos2.z), 2));
	return distance;
}
