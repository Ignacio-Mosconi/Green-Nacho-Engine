#include "Game.h"

#include <PxPhysicsAPI.h>

using namespace gn;

Game::Game() : GameBase()
{

}

Game::~Game()
{

}

bool Game::onStart()
{
	_scene = new GameObject(_renderer);

	_navCamera = new NavigationCamera(_renderer);

	_model1 = ModelLoader::loadModel(_scene, NANOSUIT_PATH, NANOSUIT_TEXTURES);
	_model2 = ModelLoader::loadModel(_model1, AK_47_PATH, AK_47_TEXTURES);

	_model1->getTransform()->setPosition(-5.0f, -10.0f, -10.0f);
	_model2->getTransform()->setPosition(5.0f, 10.0f, -5.0f);

	RigidBody* rb = (RigidBody*)_model2->addComponent(ComponentID::RigidBody);
	rb->createRigidBody(_model2->getTransform(), _physicsManager->createCapsuleGeometry(5.0f, 10.0f), false);

	_scene->start();

	return true;
}

bool Game::onStop()
{
	_scene->stop();

	delete _navCamera;
	delete _scene;
	
	return true;
}

bool Game::onUpdate(float deltaTime)
{	
	_scene->update();

	_navCamera->update(deltaTime);

	//_model1->getTransform()->rotate(0.0f, 0.5f * deltaTime, 0.0f);

	return true;
}

bool Game::onDraw()
{
	_scene->draw();

	return true;
}