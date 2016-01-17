#include "header.h"
#include "templates.h"
#include "Jxt03uTileManager.h"


Jxt03uTileManager::Jxt03uTileManager() 
	: TileManager(20, 20)
{
}


Jxt03uTileManager::~Jxt03uTileManager()
{
}

void Jxt03uTileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	switch (GetValue(iMapX, iMapY))
	{
	case 0:
		pEngine->DrawRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + GetTileWidth() - 1,
			iStartPositionScreenY + GetTileHeight() - 1,
			pEngine->GetColour(28),
			pSurface);
		break;
	case 1:
		pEngine->DrawRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + GetTileWidth() - 1,
			iStartPositionScreenY + GetTileHeight() - 1,
			pEngine->GetColour(27),
			pSurface);
	}
}