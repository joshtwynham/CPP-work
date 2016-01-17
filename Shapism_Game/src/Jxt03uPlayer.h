#ifndef JXT03UPLAYER_H
#define JXT03UPLAYER_H

#include "DisplayableObject.h"
#include "windows.h"

class Jxt03uPlayer :
	public DisplayableObject
{
public:
	Jxt03uPlayer(BaseEngine* pEngine);
	~Jxt03uPlayer();
	void Draw();
	void DoUpdate(int iCurrentTime);

	int GetWidth() const { return m_iDrawWidth; }
	int GetHeight() const { return m_iDrawHeight; }

private:
	void Shoot();

	float YVelocity = 0;
	bool mayJumpAgain = false;
	bool isOnSolidGround = false;

	int bulletsOnScreen = 0;

	DWORD shootStart;
	DWORD shootEnd;

	const int bottomOfScreen = 550;
	const int jumpVelocity = -16;
	const float gravityAcceleration = 0.6;
	const int movementSpeed = 7;

	const int minTimeBetweenShots = 500;
};

#endif