#include "header.h"
#include "templates.h"

#include "Jxt03uPlayer.h"
#include "Jxt03uBullet.h"


Jxt03uPlayer::Jxt03uPlayer(BaseEngine* pEngine)
	: DisplayableObject(pEngine)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = 400;
	m_iCurrentScreenY = m_iPreviousScreenY = 550;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 20;
	m_iDrawHeight = 50;
	// And make it visible
	SetVisible(true);
}


Jxt03uPlayer::~Jxt03uPlayer()
{
}

void Jxt03uPlayer::Draw()
{

	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	//So you can't jump in mid air
	if (m_iCurrentScreenY == bottomOfScreen) {
		isOnSolidGround = true;
	} else {
		isOnSolidGround = false;
	}

	//For gravity
	m_iCurrentScreenY += YVelocity;

	//So player doesn't fall through bottom of the screen
	if (m_iCurrentScreenY >= GetEngine()->GetScreenHeight() - m_iDrawHeight)
		m_iCurrentScreenY = GetEngine()->GetScreenHeight() - m_iDrawHeight;

	GetEngine()->DrawScreenRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0xffffff);
	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.
	// This will then remove the object from the screen.
	StoreLastScreenPositionForUndraw();
}


void Jxt03uPlayer::DoUpdate(int iCurrentTime)
{

	if (isOnSolidGround) {
		if (GetEngine()->IsKeyPressed('w')) {
			if (mayJumpAgain) {
				YVelocity = jumpVelocity;//Negative value means player will go up
				mayJumpAgain = false;
			}
		} else {
			mayJumpAgain = true;
		}
	} 
	else 
	{
		YVelocity += gravityAcceleration;
	}
	
	if (GetEngine()->IsKeyPressed('a'))
		m_iCurrentScreenX -= movementSpeed;
	if (GetEngine()->IsKeyPressed('d'))
		m_iCurrentScreenX += movementSpeed;
	if (GetEngine()->IsKeyPressed('p'))
	{
		shootEnd = GetTickCount();
		
		if (shootEnd - shootStart > minTimeBetweenShots)
		{
			Shoot();
			shootStart = GetTickCount();
		}
	}
		
	// Ensure that the object gets redrawn on the display, if something changed

	if (m_iCurrentScreenX < 0)
		m_iCurrentScreenX = 0;
	if (m_iCurrentScreenX >= GetEngine()->GetScreenWidth() - m_iDrawWidth)
		m_iCurrentScreenX = GetEngine()->GetScreenWidth() - m_iDrawWidth;
	if (m_iCurrentScreenY < 0)
		m_iCurrentScreenY = 0;
	if (m_iCurrentScreenY >= GetEngine()->GetScreenHeight() - m_iDrawHeight)
		m_iCurrentScreenY = GetEngine()->GetScreenHeight() - m_iDrawHeight;

	RedrawObjects();


}

void Jxt03uPlayer::Shoot()
{
		GetEngine()->StoreObjectInArray((5), new Jxt03uBullet(GetEngine(), this));
		GetEngine()->Redraw(true);
}