#include "BspDemo.h"
#include "MovableObject.h"

using namespace gn;

BspDemo::BspDemo() : GameBase()
{

}

BspDemo::~BspDemo()
{

}

bool BspDemo::onStart()
{
	_scene = new GameObject(_renderer);
	
	_character = new GameObject(_renderer, _scene);
	_character->getTransform()->setGlobalPosition(0.0f, 10.0f, 70.0f);
	
	NavigationController* nc = (NavigationController*)_character->addComponent(ComponentID::NAVIGATION_CONTROLLER);
	nc->setSpeeds(12.0f, 180.0f);
	
	_camera = (Camera*)_character->addComponent(ComponentID::CAMERA);

	GameObject* spaceship = ModelLoader::loadModel(_scene, SPACESHIP_PATH, SPACESHIP_TEXTURES);
	spaceship->getTransform()->setGlobalPosition(0.0f, 2.0f, 20.0f);
	_spaceship = new MovableObject(spaceship->getTransform());
	
	_nanosuit = ModelLoader::loadModel(_scene, NANOSUIT_PATH, NANOSUIT_TEXTURES);
	_nanosuit->getTransform()->setGlobalPosition(0.0f, 2.0f, 5.0f);

	_assaultRifle1 = ModelLoader::loadModel(_scene, AK_47_PATH, AK_47_TEXTURES);
	_assaultRifle1->getTransform()->setGlobalPosition(64.0f, 5.0f, 10.0f);
	
	_assaultRifle2 = ModelLoader::loadModel(_scene, AK_47_PATH, AK_47_TEXTURES);
	_assaultRifle2->getTransform()->setGlobalPosition(-64.0f, 5.0f, 10.0f);

	_terrain = ModelLoader::loadRandomTerrain(_scene, 128, 128, glm::vec3(2.0f, 1.0f, 2.0f), TERRAIN_TEXTURE);
	Terrain* terrain = (Terrain*)_terrain->getComponent(ComponentID::TERRAIN);
	terrain->flattenArea(-32.0f, 32.0f, -32.0f, 32.0f, 1.0f);
	_terrain->getTransform()->setGlobalPosition(-64.0f * terrain->getScale().x, 0.0f, -64.0f * terrain->getScale().z);

	std::vector<Component*> bbs = (std::vector<Component*>)_nanosuit->getComponentsInChildren(ComponentID::BOUNDING_BOX);

	GameObject* wall1 = ModelLoader::loadModel(_scene, WALL_PATH, WALL_TEXTURES);
	GameObject* wall2 = ModelLoader::loadModel(_scene, WALL_PATH, WALL_TEXTURES);
	GameObject* wall3 = ModelLoader::loadModel(_scene, WALL_PATH, WALL_TEXTURES);

	wall1->getTransform()->setGlobalPosition(0.0f, 0.0f, 0.0f);
	wall2->getTransform()->setGlobalPosition(-22.5f, 0.0f, 22.5f);
	wall3->getTransform()->setGlobalPosition(22.5f, 0.0f, 22.5f);
	
	wall1->getTransform()->setScale(1.5f, 1.0f, 1.0f);
	wall2->getTransform()->setScale(1.5f, 1.0f, 1.0f);
	wall3->getTransform()->setScale(1.5f, 1.0f, 1.0f);
	
	wall2->getTransform()->rotate(0.0f, 90.0f, 0.0f);
	wall3->getTransform()->setGlobalRotation(0.0f, -90.0f, 0.0f);

	BspPlane* bspPlane1 = (BspPlane*)wall1->addComponent(ComponentID::BSP_PLANE);
	BspPlane* bspPlane2 = (BspPlane*)wall2->addComponent(ComponentID::BSP_PLANE);
	BspPlane* bspPlane3 = (BspPlane*)wall3->addComponent(ComponentID::BSP_PLANE);
	
	bspPlane1->createPlane(wall1->getTransform()->getForward(), wall1->getTransform()->getGlobalPosition());
	bspPlane2->createPlane(wall2->getTransform()->getForward(), wall2->getTransform()->getGlobalPosition());
	bspPlane3->createPlane(wall3->getTransform()->getForward(), wall3->getTransform()->getGlobalPosition());

	_bspPlanes.push_back(bspPlane1);
	_bspPlanes.push_back(bspPlane2);
	_bspPlanes.push_back(bspPlane3);

	_scene->start();

	return true;
}

bool BspDemo::onStop()
{
	_scene->stop();

	delete _scene;
	delete _spaceship;

	return true;
}

bool BspDemo::onUpdate(float deltaTime)
{
	_scene->update(deltaTime);

	_nanosuit->getTransform()->translate(2.0f * deltaTime, 0.0f, 0.0f);
	_nanosuit->getTransform()->rotate(2.0f * deltaTime, 0.0f, 0.0f);
	std::vector<Component*> bbs = _nanosuit->getComponentsInChildren(ComponentID::BOUNDING_BOX);
	BoundingBox* bb = (BoundingBox*)bbs[3];
	bb->getGameObject()->getTransform()->rotate(0.0f, 25.0f * deltaTime, 0.0f);

	_spaceship->update(deltaTime);

	return true;
}

bool BspDemo::onDraw()
{
	int objectsDrawn = 0;

	_scene->draw(_camera, _bspPlanes, objectsDrawn);

	std::cout << "Objects Drawn: " << objectsDrawn << std::endl;

	return true;
}