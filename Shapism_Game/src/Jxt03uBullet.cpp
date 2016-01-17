#include "header.h"
#include "templates.h"

#include "Jxt03uBullet.h"
#include "Jxt03uPlayer.h"

Jxt03uBullet::Jxt03uBullet(BaseEngine* pEngine, Jxt03uPlayer* player)
	: DisplayableObject(pEngine)
{
	m_iCurrentScreenX = m_iPreviousScreenX = player->GetXCentre();
	m_iCurrentScreenY = m_iPreviousScreenY = player->GetYCentre();

	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 5;
	m_iDrawHeight = 5;
	// And make it visible
	SetVisible(true);
}


Jxt03uBullet::~Jxt03uBullet()
{
}

void Jxt03uBullet::Draw()
{
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

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

void Jxt03uBullet::DoUpdate(int iCurrentTime)
{

	m_iCurrentScreenY += bulletSpeed;

	if (m_iCurrentScreenY >= GetEngine()->GetScreenHeight() - m_iDrawHeight)
	{
		SetVisible(false);
	}
	
	

	RedrawObjects();
}