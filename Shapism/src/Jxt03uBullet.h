#ifndef JXT03UBULLET_H
#define JXT03UBULLET_H

#pragma once
#include "DisplayableObject.h"

class Jxt03uPlayer;

class Jxt03uBullet :
	public DisplayableObject
{
public:
	Jxt03uBullet(BaseEngine* pEngine, Jxt03uPlayer* player);
	~Jxt03uBullet();
	void Draw();
	void DoUpdate(int iCurrentTime);

	

	int GetWidth() const { return m_iDrawWidth; }
	int GetHeight() const { return m_iDrawHeight; }

private:
	int indexInArray;
	const int bulletSpeed = 9;
};

#endif