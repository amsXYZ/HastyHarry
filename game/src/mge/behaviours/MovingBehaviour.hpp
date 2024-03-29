#ifndef MOVINGBEHAVIOUR_H
#define MOVINGBEHAVIOUR_H

#include <glm.hpp>
#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * Moves the Game Object between two positions.
 */
class MovingBehaviour : public AbstractBehaviour
{
	public:
		MovingBehaviour(glm::vec3 pOrigin, glm::vec3 pEnd, float pSpeed, bool pLoop = false);
		MovingBehaviour(glm::vec3 pStart, std::string params);
		virtual ~MovingBehaviour();

		void updateValues(glm::vec3 pOrigin, glm::vec3 pEnd, float pSpeed, bool pLoop = false);
		virtual void update(float step);

		void setDestroyFlag();
	private:
		glm::vec3 _originPosition;
		glm::vec3 _endPosition;
		float _speed;
		bool _loop;
		bool _dead;

		bool _destroyAtEnd;
};

#endif // MOVINGBEHAVIOUR_H
