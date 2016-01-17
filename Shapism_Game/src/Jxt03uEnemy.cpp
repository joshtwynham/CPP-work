#include "header.h"
#include "templates.h"

#include "Jxt03uEnemy.h"

Jxt03uEnemy::Jxt03uEnemy(BaseEngine *pEngine, Jxt03uPlayer* player, int speed, int colour)
	: DisplayableObject(pEngine)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = rand()%770;

	// If position is too close to player position, set it to a default position
	if (m_iCurrentScreenX < player->GetXCentre() + 80 && m_iCurrentScreenX > player->GetXCentre() - 80)
	{
		m_iCurrentScreenX = 0;
	}

	m_iCurrentScreenY = m_iPreviousScreenY = 300;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 30;
	m_iDrawHeight = 30;
	// And make it visible
	SetVisible(true);

	this->player = player;
	this->speed = speed;
	this->colour = colour;
}


Jxt03uEnemy::~Jxt03uEnemy()
{
}

void Jxt03uEnemy::Draw()
{
	m_iCurrentScreenY += YVelocity;

	if (m_iCurrentScreenY >= GetEngine()->GetScreenHeight() - m_iDrawHeight)
		m_iCurrentScreenY = GetEngine()->GetScreenHeight() - m_iDrawHeight;

	switch (colour)
	{
	case 0:
		GetEngine()->DrawScreenRectangle(
			m_iCurrentScreenX, m_iCurrentScreenY,
			m_iCurrentScreenX + m_iDrawWidth - 1,
			m_iCurrentScreenY + m_iDrawHeight - 1,
			0xffff00);
		break;
	case 1:
		GetEngine()->DrawScreenRectangle(
			m_iCurrentScreenX, m_iCurrentScreenY,
			m_iCurrentScreenX + m_iDrawWidth - 1,
			m_iCurrentScreenY + m_iDrawHeight - 1,
			0x00ffff);
		break;
	case 2:
		GetEngine()->DrawScreenRectangle(
			m_iCurrentScreenX, m_iCurrentScreenY,
			m_iCurrentScreenX + m_iDrawWidth - 1,
			m_iCurrentScreenY + m_iDrawHeight - 1,
			0xff00ff);
		break;
	case 3:
		GetEngine()->DrawScreenRectangle(
			m_iCurrentScreenX, m_iCurrentScreenY,
			m_iCurrentScreenX + m_iDrawWidth - 1,
			m_iCurrentScreenY + m_iDrawHeight - 1,
			0xf00fff);
		break;
	case 4:
		GetEngine()->DrawScreenRectangle(
			m_iCurrentScreenX, m_iCurrentScreenY,
			m_iCurrentScreenX + m_iDrawWidth - 1,
			m_iCurrentScreenY + m_iDrawHeight - 1,
			0xfff00f);
		break;
	case 5:
		GetEngine()->DrawScreenRectangle(
			m_iCurrentScreenX, m_iCurrentScreenY,
			m_iCurrentScreenX + m_iDrawWidth - 1,
			m_iCurrentScreenY + m_iDrawHeight - 1,
			0xff0ff0);
		break;
	case 6:
		GetEngine()->DrawScreenRectangle(
			m_iCurrentScreenX, m_iCurrentScreenY,
			m_iCurrentScreenX + m_iDrawWidth - 1,
			m_iCurrentScreenY + m_iDrawHeight - 1,
			0x0fff0f);
	}
	
	StoreLastScreenPositionForUndraw();
}

void Jxt03uEnemy::DoUpdate(int iCurrentTime)
{
	YVelocity += gravity;

	ChasePlayer();

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

void Jxt03uEnemy::ChasePlayer()
{
	direction = player->GetXCentre() - m_iCurrentScreenX;

	if (direction < 0)
	{
		m_iCurrentScreenX -= speed;
	}
	else
	{
		m_iCurrentScreenX += speed;
	}
}

