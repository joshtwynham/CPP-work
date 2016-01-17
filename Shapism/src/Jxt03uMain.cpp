#include "header.h"
#include "templates.h"

#include "Jxt03uMain.h"
#include "Jxt03uTileManager.h"
#include "Jxt03uEnemy.h"
#include "Jxt03uBullet.h"
#include <string>

using namespace std;




Jxt03uMain::Jxt03uMain()
	: BaseEngine(7)//7 is max number of moving objects able to draw
{
}


Jxt03uMain::~Jxt03uMain()
{
}


void Jxt03uMain::SetupBackgroundBuffer()
{

	switch (state) 
	{
	case menu:
		// Specify how many tiles wide and high
		tileManager.SetSize(40, 30);
		// Set up the tiles
		for (int x = 0; x < 40; x++)
		{
			for (int y = 0; y < 30; y++)
			{
				tileManager.SetValue(x, y, 0);	
			}
		}
			
				
		// Specify the screen x,y of top left corner
		tileManager.SetBaseTilesPositionOnScreen(0, 0);
		// Tell it to draw tiles from x1,y1 to x2,y2 in tile array,
		// to the background of this screen
		tileManager.DrawAllTiles(this, this->GetBackground(), 0, 0, 39, 29);
		break;
	case playing:

		for (int iX = 0; iX < GetScreenWidth(); iX += 50)
			for (int iY = 0; iY < GetScreenHeight(); iY++)
			{
				

				switch (iX % 4)
				{
				case 0: SetBackgroundPixel(iX, iY, 0xA0A0A0); break;
				case 2: SetBackgroundPixel(iX, iY, 0x909090); break;
				}

				
				//Fills screen with new colour by percentage of the highest score that the player has achieved so far
				if (iY < currentToHighestScoreRatio * GetScreenHeight())
				{
					SetBackgroundPixel(iX, iY, 0xFF0000);
				}

			}
	
		
		
	}
	
	
		
	
}



void Jxt03uMain::MouseMoved(int iX, int iY)
{
	//Changes the colour of 'Tiles' in on the menu screen via the TileManager

	if (state == menu)
	{
		int xTile = tileManager.GetTileXForPositionOnScreen(iX);
		int yTile = tileManager.GetTileYForPositionOnScreen(iY);

		tileManager.SetValue(xTile, yTile, 1);

		// Specify the screen x,y of top left corner
		tileManager.SetBaseTilesPositionOnScreen(0, 0);
		// Tell it to draw tiles from x1,y1 to x2,y2 in tile array,
		// to the background of this screen
		tileManager.DrawAllTiles(this, this->GetBackground(), 0, 0, 39, 29);
		Redraw(true);
		GameRender();
	}
	
}



void Jxt03uMain::KeyDown(int iKeyCode)
{
	
	switch (iKeyCode)
	{
	case '\r':
		switch (state)
		{
		case menu:
			enemiesKilled = 0;
			timeSurvived = 0;
			
			//For recording game play time
			gameStart = GetTickCount() / 1000;

			state = playing;
			SetupBackgroundBuffer();
			InitialiseObjects();
			Redraw(true);
			break;
		case dead:
			//To fill the background with colour as current score approaches high score
			currentToHighestScoreRatio = 0;

			enemiesKilled = 0;
			timeSurvived = 0;
			gameStart = GetTickCount() / 1000;
			state = playing;
			SetupBackgroundBuffer();
			InitialiseObjects();
			Redraw(true);
			break;
		}
		break;
	case SDLK_ESCAPE:
		switch (state)
		{
		case dead:
			state = menu;
			currentToHighestScoreRatio = 0;
			enemiesKilled = 0;
			DestroyOldObjects();
			SetupBackgroundBuffer();
			Redraw(true);
			break;
		}
		break;
	case SDLK_SPACE:
		switch (state)
		{
		case playing:
			state = paused;
			pauseStart = GetTickCount() / 1000;
			Redraw(true);
			break;
		case paused:
			state = playing;
			pauseEnd = GetTickCount() / 1000;

			//To discount any time paused from time survived
			gameStart += pauseEnd - pauseStart;

			Redraw(true);
			break;
		}
	}
	
}


void Jxt03uMain::DrawStrings()
{
	char enemyBuf[128];
	char timeBuf[128];

	switch (state)
	{
	case menu:
		LoadHighScore();
		CopyBackgroundPixels(250/*X*/, 250/*Y*/, GetScreenWidth(), 40/*Height*/);
		
		DrawScreenString(30, 350, "Move left: A", 0x0, NULL);
		DrawScreenString(30, 400, "Move right: D", 0x0, NULL);
		DrawScreenString(30, 450, "Jump: W", 0x0, NULL);
		DrawScreenString(30, 500, "Drop bullet: P", 0x0, NULL);
		DrawScreenString(30, 550, "Pause/Play: Space", 0x0, NULL);
		DrawScreenString(250, 150, "---------SHAPISM---------", 0x0, NULL);
		DrawScreenString(250, 250, "Press Enter to play.", 0x0, NULL);
		sprintf(enemyBuf, "Most enemies killed: %d", highestEnemiesKilled);
		DrawScreenString(500, 500, enemyBuf, 0x0, NULL);
		sprintf(timeBuf, "Longest time survived: %d", longestTimeSurvived);
		DrawScreenString(500, 550, timeBuf, 0x0, NULL);
		break;
	case playing:
		CopyBackgroundPixels(350/*X*/, 50/*Y*/, GetScreenWidth(), 40/*Height*/);
		DrawScreenString(350, 50, "Playing.", 0x0, NULL);
		sprintf(enemyBuf, "Enemies killed: %d", enemiesKilled);
		DrawScreenString(50, 50, enemyBuf, 0x0, NULL);
		gameEnd = GetTickCount() / 1000;
		sprintf(timeBuf, "Time survived: %ds", gameEnd - gameStart);
		DrawScreenString(520, 50, timeBuf, 0x0, NULL);
		break;
	case dead:
		CopyBackgroundPixels(300/*X*/, 250/*Y*/, GetScreenWidth(), 40/*Height*/);
		DrawScreenString(250, 50, "You are dead.", 0x0, NULL);
		DrawScreenString(250, 100, "Press enter to play again.", 0x0, NULL);
		DrawScreenString(250, 150, "Press escape to go to menu.", 0x0, NULL);
		sprintf(enemyBuf, "Enemies killed: %d", enemiesKilled);
		DrawScreenString(250, 250, enemyBuf, 0x0, NULL);
		sprintf(timeBuf, "Time survived: %ds", timeSurvived);
		DrawScreenString(250, 300, timeBuf, 0x0, NULL);
		break;
	case paused:
		sprintf(enemyBuf, "Enemies killed: %d", enemiesKilled);
		DrawScreenString(50, 50, enemyBuf, 0x0, NULL);
		DrawScreenString(350, 300, "Paused", 0x0, NULL);
		sprintf(timeBuf, "Time survived: %ds", gameEnd - gameStart);
		DrawScreenString(520, 50, timeBuf, 0x0, NULL);
		break;
	}
}

int Jxt03uMain::GameInit()
{
	SetupBackgroundBuffer();

	return 0;
}

int Jxt03uMain::InitialiseObjects()
{
		// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
		DrawableObjectsChanged();
		// Destroy any existing objects
		DestroyOldObjects();
		// Creates an array to store the objects
		// Needs to have room for the NULL at the end
		CreateObjectArray(7);
		// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
		// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.
		player = new Jxt03uPlayer(this);
		StoreObjectInArray(0, player);
		
		//Create enemies
		for (int i = 1; i < 5; i++)
		{
			StoreObjectInArray(i, new Jxt03uEnemy(this, player, (rand()%1)+1, rand()%6));
		}
		
		StoreObjectInArray(7, NULL);

	return 0;
}


void Jxt03uMain::GameAction()
{

	// If too early to act then do nothing
	if (!IsTimeToActWithSleep())
		return;
	
	switch (state)
	{
	case menu:
	case paused:
		break;
	case playing:
		SetTimeToAct(15);
		if (PlayerIsHit())
		{

			gameEnd = GetTickCount() / 1000;
			timeSurvived = gameEnd - gameStart;

			state = dead;

			UpdateHighScores();

			Redraw(true);
		}
		else
		{
			RemoveShotEnemies();
			// Only tell objects to move when not paused etc
			UpdateAllObjects(GetModifiedTime());
		}

		
	}


}

bool Jxt03uMain::PlayerIsHit()
{
	
	for (int i = 1; i < 5; i++)
	{
		Jxt03uEnemy* enemy = dynamic_cast<Jxt03uEnemy*>(GetDisplayableObject(i));

		if (enemy != NULL)
		{
			//Checks if rectangles/squares are overlapping
			if (player->GetXCentre() < enemy->GetXCentre() + enemy->GetWidth() &&
				player->GetXCentre() + player->GetWidth() > enemy->GetXCentre() &&
				player->GetYCentre() < enemy->GetYCentre() + enemy->GetHeight() &&
				player->GetHeight() + player->GetYCentre() > enemy->GetYCentre())
			{	
				return true;
			}
		}

		
	}
	
	return false;
}


void Jxt03uMain::RemoveShotEnemies()
{

	for (int i = 1; i < 5; i++)
	{
		Jxt03uEnemy* enemy = dynamic_cast<Jxt03uEnemy*>(GetDisplayableObject(i));

		for (int j = 5; j < 7; j++)
		{
			Jxt03uBullet* bullet = dynamic_cast<Jxt03uBullet*>(GetDisplayableObject(j));

			if (enemy != NULL && bullet != NULL)
			{
				if (bullet->GetXCentre() < enemy->GetXCentre() + enemy->GetWidth() &&
					bullet->GetXCentre() + bullet->GetWidth() > enemy->GetXCentre() &&
					bullet->GetYCentre() < enemy->GetYCentre() + enemy->GetHeight() &&
					bullet->GetHeight() + bullet->GetYCentre() > enemy->GetYCentre())
				{
					StoreObjectInArray(i, new Jxt03uEnemy(this, player, (rand() % 3) + 1, rand() % 6));
					Redraw(true);
					enemiesKilled += 1;

					//To update background with ratio of current score to highest
					currentToHighestScoreRatio = float(enemiesKilled) / float(highestEnemiesKilled);
					SetupBackgroundBuffer();
				}
			}

		}
	}
}

void Jxt03uMain::LoadHighScore()
{

	ifstream fin("highScores.txt");

	string name;
	int var1;
	int var2;

	while (fin >> name >> var1)
	{
		if (name.compare("Most_enemies_killed:") == 0)
		{
			highestEnemiesKilled = var1;
		}
		else 
		{
			longestTimeSurvived = var1;
		}
	}	
}

void Jxt03uMain::UpdateHighScores()
{

	scoresFile.open("highScores.txt");

	if (enemiesKilled > highestEnemiesKilled)
	{
		highestEnemiesKilled = enemiesKilled;
	}

	if (timeSurvived > longestTimeSurvived)
	{
		longestTimeSurvived = timeSurvived;
	}

	scoresFile << "Most_enemies_killed: " << highestEnemiesKilled << "\n";

	scoresFile << "Longest_time_survived: " << longestTimeSurvived << " seconds";

	scoresFile.close();
}