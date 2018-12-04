#pragma once

#include <map>
#include <string>
#include "Material.h"
#include "Exports.h"

namespace gn
{
	class Renderer;
	class Material;
	class Texture;
	class Sprite;
	class BoundingBox;
	class Animation;
	class Tilemap;
/*
	A complex class that is meant to be used as a base for all the characters and/or interactables of a game;
	they contain a "Sprite" (for rendering) and a "BoundingBox" (for collision detection), and they also have
	the possibility to include animations.
*/
	class ENGINE_API GameEntity
	{
	private:
		Sprite* _sprite;
		BoundingBox* _boundingBox;
	
		mutable std::map<std::string, Animation*> _animations;

		Material* _material;
		Texture* _texture;

		Tilemap* _tilemap;

		Sprite* createSprite(Renderer* renderer, const std::string& imagePath, int spriteRows = 1, int spriteColumns = 1, 
			int frameWidth = -1, int frameHeight = -1);
		void createBoundingBox(float width, float height, bool isStatic, float mass, const std::string& collisionLayer);

	public:
		GameEntity(Renderer* renderer, const std::string& imagePath, const std::string& collisionLayer);
		GameEntity(Renderer* renderer, Tilemap* tilemap, const std::string& imagePath, const std::string& collisionLayer,
					float x, float y, int spriteRows, int spriteColumns, int frameWidth, int frameHeight, 
					bool isStatic = false, float mass = 1);
		~GameEntity();

		void setBoundingBoxDimensions(float width, float height);

		void addAnimation(Animation* animation, const std::string& animName);

		void move(float x, float y, float z = 0.0f);

		virtual void update(float deltaTime);
		virtual void draw() const;

		inline Animation* getCurrentAnimation() const;
		inline Sprite* getSprite() const { return _sprite; }
		inline BoundingBox* getBoundingBox() const { return _boundingBox; }
	};
}