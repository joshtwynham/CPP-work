#pragma once
#include "TileManager.h"
class Jxt03uTileManager :
	public TileManager

{
public:
	Jxt03uTileManager();
	~Jxt03uTileManager();

	virtual void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;


};

