#pragma once
#include "GameObject.h"
#include "BaseProc.h"

class Object3D : public GameObject, public CBaseProc
{
public:
	Object3D();
	virtual ~Object3D();
	virtual void Update() override;
	virtual void Draw() override;
private:
};