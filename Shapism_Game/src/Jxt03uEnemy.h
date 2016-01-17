#pragma once
#include "DisplayableObject.h"
#include "Jxt03uPlayer.h"

class Jxt03uEnemy :
	public DisplayableObject
{
public:
	Jxt03uEnemy(BaseEngine* pEngine, Jxt03uPlayer* player, int speed, int colour);
	~Jxt03uEnemy();

	void Draw();
	void DoUpdate(int iCurrentTime);

	int GetWidth() const { return m_iDrawWidth; }
	int GetHeight() const { return m_iDrawHeight; }

private:
	Jxt03uPlayer* player;

	int direction;
	int speed;
	int colour;
	float YVelocity = 0;
	bool isOnSolidGround = false;
	const float gravity = 0.4;

	void ChasePlayer();
};

