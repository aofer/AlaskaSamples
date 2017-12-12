#pragma once
#include "Common.h"
#include "Model.h"


class Box :public Model {

public:
	Box(uint length, uint width, uint height);
	Box();
	virtual ~Box();

private:
	Mesh* CreateBoxMesh(uint length, uint width, uint height);

};

