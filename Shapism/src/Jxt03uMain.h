#pragma once
#include "BaseEngine.h"
#include "Jxt03uTileManager.h"
#include "windows.h"
#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

class Jxt03uPlayer;

class Jxt03uMain :
	public BaseEngine
{
public:
	Jxt03uMain();
	~Jxt03uMain();
	void SetupBackgroundBuffer();
	void MouseMoved(int iX, int iY);
	void KeyDown(int iKeyCode);

	//get reference to the current tile manager
	Jxt03uTileManager getTileManager() { return tileManager; }

private:
	Jxt03uTileManager tileManager;

public:
	enum State {menu, playing, paused, dead};

private:
	State state = menu;
public:
	void DrawStrings();
	int InitialiseObjects();
	int GameInit();

protected:
	Jxt03uPlayer* player;
	int enemiesKilled = 0;
	DWORD gameEnd;
	DWORD gameStart;
	ofstream scoresFile;
	int highestEnemiesKilled = 0;
	int longestTimeSurvived = 0;
	int timeSurvived = 0;
	int menuLinePosition;
	int menuLineStartTime;
	int menuLineEndTime;
	float currentToHighestScoreRatio;
	int pauseStart;
	int pauseEnd;
public:
	void GameAction();
	bool PlayerIsHit();
	void RemoveShotEnemies();
	void LoadHighScore();
	void UpdateHighScores();
};

