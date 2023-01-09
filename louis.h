/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "tiling.h"
#include "objects.h"

//Walking animation
const int WALKING_ANIMATION_FRAMES = 16;
const int BATTLE_ANIM_FRAMES = 1;
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
SDL_Rect gBattleClips[BATTLE_ANIM_FRAMES];
SDL_Rect* currentClip;

bool louisMove = 0;
bool louisHasMoved = 0;

class Enemy;
class LTexture;

class Chara {
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 27;
		static const int DOT_HEIGHT = 50;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 2;

		//Initializes the variables
		Chara();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move( Tile *tiles[], Bed* bed, Table* table );
		void moveNP( Tile *tiles[], Bed* bed, Table* table );
	
		//Centers the camera over the dot
		void setCamera( SDL_Rect& camera );

		SDL_Rect getBox();

		//Shows the dot on the screen
		void render(SDL_Rect& camera, LTexture* gSpriteSheetTexture);
		void renderNP(SDL_Rect& camera, LTexture* gSpriteSheetTexture);

		int checkState(int x);
		int moveState = 1;
		int turnState = 1;
		int frame = 0;
		int count = 0;
		int cutsceneTurnState = 1;
		void setState(int x);
		void setPos(int x, int y);
		void moveToXY(int x, int y, int speed);
		void moveRandomly();

		void warp(int warpLevelID);
    private:
		//Collision box of the dot
		SDL_Rect mBox;

		//The velocity of the dot
		int mVelX, mVelY; int mVelXNP, mVelYNP;
};

class BattleChara {
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 130;
		static const int DOT_HEIGHT = 200;
		
		//Initializes the variables
		BattleChara();

		SDL_Rect getBox();

		SDL_Rect* currentClip;

		//Shows the dot on the screen
		void render(SDL_Rect& camera, Enemy* enemy, SDL_Rect& textbox);
		int attack(SDL_Rect& camera, Enemy* enemy);
		int getAction();
		int getDef();
		int getDex();
		void takeDamage(int dmg);
		void strChange(int chng);
		void defChange(int chng);
		void dexChange(int chng);
		void niceChange(int chng);
		void resetMods();
		void sklWetstone();
		int getSklLv(int skillID);
		int getSklExpenditure(int skillID);
		int eqpSwordID, eqpGunID;
		int eqpSwordAtt, eqpGunAtt;
		SDL_Rect friendBar; SDL_Rect friendBarOutline;
    private:
		//Collision box of the dot
		SDL_Rect mBox;
		int mCurrentHitPoints;
		int mMaxHitPoints;
		int mStrength;
		int mDefense;
		int mDexterity;
		int mNiceness;
		int mCurrentMannerPoints;
		int mMaxMannerPoints;
		int mWetstoneLv;
};
