#include "Sprite.h"
#include "Sprite.h"
#include "Material.h"
#include "Renderer.h"

Sprite::Sprite(Renderer* renderer, Material* material) : Shape(renderer, material, 4),
_uvBufferData(NULL),
_uvBufferID(-1),
_frameID(0), _rows(0), _columns(0), _frameWidth(0), _frameHeight(0)
{
	cout << "Sprite::Sprite()" << endl;
}

Sprite::~Sprite()
{
	cout << "Sprite::~Sprite()" << endl;
}

bool Sprite::create(unsigned int vertexComponents, float* colorBufferData, float width, float height)
{
	cout << "Sprite::create(vertexComponents, colorBufferData)" << endl;

	int uvBufferSize = sizeof(float) * _vertexCount * 2;

	_uvBufferData = setVerticesUV(0, 0);
	_uvBufferID = _renderer->generateVertexBuffer(_uvBufferData, uvBufferSize);

	return Shape::create(vertexComponents, NULL, width, height);
}

float* Sprite::setVertices(unsigned int vertexComponents, float width, float height) const
{
	cout << "Sprite::setVertices(vertexComponents)" << endl;

	float valueX = (float)width / 2;
	float valueY = (float)height / 2;

	float* vertexBufferData = new float[_vertexCount * vertexComponents]
	{
		-valueX, valueY, 0.0f,
		valueX, valueY, 0.0f,
		-valueX, -valueY, 0.0f,
		valueX, -valueY, 0.0f
	};

	return vertexBufferData;
}

float* Sprite::setVerticesUV(unsigned int x, unsigned int y) const
{
	cout << "Sprite::setVerticesUV()" << endl;

	float minU = (float)x / (float)_material->getTextureWidth();
	float minV = 1.0f - (float)(y + _frameHeight) / (float)_material->getTextureHeight();
	float maxU = (float)(x + _frameWidth) / (float)_material->getTextureWidth();
	float maxV = 1.0f - (float)y / (float)_material->getTextureHeight();

	float* uvBufferData = new float[_vertexCount * 2]
	{
		minU, maxV,
		maxU, maxV,
		minU, minV,
		maxU, minV
	};

	return uvBufferData;
}

void Sprite::setAnimationFrame(unsigned int frameID)
{
	cout << "Sprite::setAnimationFrame(frameID)" << endl;

	_frameID = frameID;
	
	int uvBufferSize = sizeof(float) * _vertexCount * 2;
	unsigned int x = (frameID % _columns) * _frameWidth;
	unsigned int y = (int)(frameID / _rows) * _frameHeight;
	
	_uvBufferData = setVerticesUV(x, y);
	_uvBufferID = _renderer->generateVertexBuffer(_uvBufferData, uvBufferSize);
}

void Sprite::setFramesInfo(unsigned int rows, unsigned int columns, unsigned int frameWidth, unsigned int frameHeight)
{
	cout << "Sprite::setFrameInfo(rows, columns, frameWidth, frameHeight)" << endl;

	_rows = rows;
	_columns = columns;
	_frameWidth = frameWidth;
	_frameHeight = frameHeight;
}

void Sprite::draw() const
{
	cout << "Sprite::draw()" << endl;

	Shape::draw();

	_renderer->enableBlend();

	_renderer->enableAttribute(0);
	_renderer->enableAttribute(1);
	_renderer->bindBuffer(0, 3, _vertexBufferID);
	_renderer->bindBuffer(1, 2, _uvBufferID);
	_renderer->drawBuffer(TRIANGLE_STRIP, _vertexCount);
	_renderer->disableAttribute(0);
	_renderer->disableAttribute(1);

	_renderer->disableBlend();
}