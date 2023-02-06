#pragma once

#include "Transform.h"

class Cube {
	public:
		Transform* getTransform();
	private:
		Transform transform;
};