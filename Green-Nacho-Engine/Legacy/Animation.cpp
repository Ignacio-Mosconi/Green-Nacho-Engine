#include "Legacy/Animation.h"
#include "Legacy/Sprite.h"

namespace gn
{
	namespace legacy
	{
		Animation::Animation(const std::string& name, unsigned int frames[], float speed, bool looped) :
			_frames(new std::queue<unsigned int>), _name(name),
			_currentFrame(0), _lastFrame(0), _speed(speed), _frameTime(1.0f / speed),
			_looped(looped), _stopped(true), _finished(false), _timer(0.0f)
		{
			int arraySize = sizeof(frames) / sizeof(unsigned int);

			for (int i = 0; i < arraySize; i++)
				_frames->push(frames[i]);
			_currentFrame = _frames->front();
			_lastFrame = _frames->back();
		}

		Animation::~Animation()
		{
			delete _frames;
		}

		void Animation::update(float deltaTime)
		{
			if (!_stopped && _sprite)
			{
				_timer += deltaTime;
				if (_timer >= _frameTime)
				{
					_timer = 0.0f;
					if (!_finished)
					{
						_currentFrame = _frames->front();
						_frames->pop();
						_frames->push(_currentFrame);
						_sprite->setAnimationFrame(_currentFrame);

						if (_currentFrame == _lastFrame && !_looped)
							_finished = false;
					}
					else
						_stopped = true;
				}
			}
		}

		void Animation::play(bool resume)
		{
			if (!resume)
				_timer = 0.0f;
			_finished = false;
			_stopped = false;
		}

		void Animation::stop()
		{
			_stopped = true;
		}
	}
}