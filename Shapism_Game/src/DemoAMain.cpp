#include "header.h"
#include "templates.h"

#include "DemoAMain.h"
#include "DemoBObject.h"


DemoAMain::DemoAMain()
	: BaseEngine(6)
{
}


DemoAMain::~DemoAMain()
{
}

void DemoAMain::SetupBackgroundBuffer()
{
	FillBackground(0x000000);
	for (int iX = 0; iX < GetScreenWidth(); iX++)
		for (int iY = 0; iY < this->GetScreenHeight(); iY++)
			switch (rand() % 100)
		{
			case 0: SetBackgroundPixel(iX, iY, 0xFF0000); break;
			case 1: SetBackgroundPixel(iX, iY, 0x00FF00); break;
			case 2: SetBackgroundPixel(iX, iY, 0x0000FF); break;
			case 3: SetBackgroundPixel(iX, iY, 0xFFFF00); break;
			case 4: SetBackgroundPixel(iX, iY, 0x00FFFF); break;
			case 5: SetBackgroundPixel(iX, iY, 0xFF00FF); break;
		}
}


void DemoAMain::MouseDown(int iButton, int iX, int iY)
{
	printf("%d %d\n", iX, iY);
	if (iButton == SDL_BUTTON_LEFT)
	{
		//DrawRectangle(iX - 10, iY - 10, iX + 10, iY + 10, 0xffff00);
		DrawBackgroundRectangle(iX - 10, iY - 10, iX + 10, iY + 10, 0xffff00);
		Redraw(true);
	}
	else if (iButton == SDL_BUTTON_RIGHT)
	{
		//DrawOval(iX - 10, iY - 10, iX + 10, iY + 10, 0xff0000);
		DrawBackgroundOval(iX - 10, iY - 10, iX + 10, iY + 10, 0xff0000);
		//Redraw(false);
		Redraw(true);
	}
}


void DemoAMain::KeyDown(int iKeyCode)
{
	switch (iKeyCode)
	{
	case ' ':
		SetupBackgroundBuffer();
		Redraw(true);
		break;
	}
}

int DemoAMain::InitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get
	//used elsewhere without reloading it
	DrawableObjectsChanged();
	// Destroy any existing objects
	DestroyOldObjects();
	// Creates an array to store the objects
	// Needs to have room for the NULL at the end
	CreateObjectArray(2);
	// You MUST set the array entry after the last one that you create to NULL, so
	//that the system knows when to stop.
	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in
	//order to work out where the end of the array is.
	StoreObjectInArray(0, new DemoBObject(this));
	StoreObjectInArray(1, NULL);

	return 0;
}


void DemoAMain::DrawStringsUnderneath()
{
	// Build the string to print
	char buf[128];
	sprintf(buf, "Changing random %6d", rand());
	DrawScreenString(50, 10, buf, 0x00ffff, NULL);
	DrawScreenString(450, 10, "Underneath the objects", 0xff0000, NULL);
}



void DemoAMain::UnDrawStrings()
{
	// Clear the top of the screen, since we about to draw text on it.
	CopyBackgroundPixels(0, 0, GetScreenWidth(), 70);
}
