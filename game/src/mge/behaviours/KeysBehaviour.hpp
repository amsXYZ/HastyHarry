#ifndef KEYSBEHAVIOUR_H
#define KEYSBEHAVIOUR_H

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "SFML/Audio.hpp"

class Sound;

/**
 * KeysBehaviour allows you to move an object using the keyboard in its own local space.
 * Left right turns, forward back moves.
 */
class KeysBehaviour : public AbstractBehaviour
{
	public:
		KeysBehaviour(float moveSpeed = 5, float turnSpeed = 45, std::string pSound = NULL);
		virtual ~KeysBehaviour();
		virtual void update( float step );

    private:
        float _moveSpeed;
        float _turnSpeed;
		bool _jumping = false;
		sf::Sound _jumpingSound;
		sf::SoundBuffer _soundBuffer;
};

#endif // KEYSBEHAVIOUR_H
