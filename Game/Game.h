#pragma once

#include <iostream>
#include "GameBase.h"
#include "Window.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "MeshRenderer.h"
#include "ModelLoader.h"
#include "EngineConstants.h"
#include "GameConstants.h"

class Game : public gn::GameBase
{
private:
	gn::GameObject* _model1;
	gn::GameObject* _model2;

protected:
	bool onStart() override;
	bool onStop() override;
	bool onUpdate(float deltaTime) override;
	bool onDraw() override;

public:
	Game();
	~Game();
};