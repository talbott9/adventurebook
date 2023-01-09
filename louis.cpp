#include "louis.h"

bool withSword = 1;
bool useWetstone = 0;
bool useMaglass = 0;

bool wetstoneInEffect = 0;
int wetstoneTurns = 0;
int wetstoneBuff = 0;
bool takingCover = 0;


Chara::Chara() {
	mBox.x = 500 + DOT_WIDTH;
    	mBox.y = 450 + DOT_HEIGHT;
	mBox.w = DOT_WIDTH;
	mBox.h = DOT_HEIGHT / 2;
	
	mVelX = 0; mVelXNP = 0;
	mVelY = 0; mVelYNP = 0;
}

BattleChara::BattleChara() {
	mBox.x = 500;
	mBox.y = 200;
	mBox.w = DOT_WIDTH;
	mBox.h = DOT_HEIGHT;
	
	mCurrentHitPoints = 20;
	mMaxHitPoints= 20;
	mStrength = 10;
	mDefense = 10;
	mDexterity = 10;
	mNiceness = 10;
	mCurrentMannerPoints = 10;
	mMaxMannerPoints = 10;

	eqpSwordID = 1; eqpGunID = 1;

	mWetstoneLv = 1;

	friendBar.x = 0; friendBar.y = 0; 
	friendBar.w = 100; friendBar.h = 15;

	friendBarOutline.x = 0; friendBarOutline.y = 0; 
	friendBarOutline.w = 100; friendBarOutline.h = 15;
}

void Chara::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
	    case SDLK_UP: mVelY -= DOT_VEL; break;
	    case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
	    case SDLK_RIGHT: mVelX += DOT_VEL; break;

        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
}


SDL_Rect Chara::getBox() {
	return mBox;
}

SDL_Rect BattleChara::getBox() {
	return mBox;
}

void Chara::setState(int x) {
	cutsceneTurnState = x;
	turnState = x;
	moveState = x;
}

void Chara::setPos(int x, int y) {
	mBox.x = x; 
	mBox.y = y;
}

void Chara::moveToXY(int x, int y, int speed) {
	if(mBox.x != x && mBox.x < x) {
		mVelXNP = speed;
		if(mBox.x > x)
			mBox.x -= mBox.x - x;
	} else if(mBox.x != x && mBox.x > x) {
		mVelXNP = -speed;
		if(mBox.x < x)
			mBox.x += mBox.x - x;
	} else if(mBox.y != y && mBox.y < y) {
		mVelYNP = speed;
		if(mBox.y > y)
			mBox.y -= mBox.y - y;
	} else if(mBox.y != y && mBox.y > y) {
		mVelYNP = -speed;
		if(mBox.y < y)
			mBox.y += mBox.y - y;
	}
	if(mBox.x == x && mBox.y == y) {
		louisMove = 0;
		mVelXNP = 0; mVelYNP = 0;
	}
}

int BattleChara::getDef() {
	return mDefense;
}

int BattleChara::getDex() {
	return mDexterity;
} 

void BattleChara::strChange(int chng) {
	mStrength += chng;
}

void BattleChara::defChange(int chng) {
	mDefense += chng;
}

void BattleChara::dexChange(int chng) {
	mDexterity += chng;
}

void BattleChara::niceChange(int chng) {
	mNiceness += chng;
}

int BattleChara::getAction() {
	if(useMaglass) {
		return 1;
	} else if(useWetstone) {
		return 2;
	}
}

void BattleChara::takeDamage(int dmg) {
	mCurrentHitPoints -= dmg;
}

//Skill IDs: 1 magGlass (unused), 2 Wetstone

int BattleChara::getSklLv(int skillID) {
	switch(skillID) {
		case 2: return mWetstoneLv; break;
	}
}

int BattleChara::getSklExpenditure(int skillID) {
	switch(skillID) {
		case 2: return mCurrentMannerPoints - mWetstoneLv; break;
	}
}

void BattleChara::sklWetstone() {
	if(wetstoneInEffect) {
		wetstoneTurns = 0;
		strChange(-wetstoneBuff);
	}
	wetstoneBuff = rand() % 3 + mWetstoneLv * 2;
	strChange(wetstoneBuff);
	mCurrentMannerPoints -= mWetstoneLv;
	wetstoneInEffect = 1;
}

void BattleChara::resetMods() {
	if(wetstoneInEffect) {
		wetstoneTurns++;
		if(wetstoneTurns == 5 + 1) {
			wetstoneInEffect = 0; wetstoneTurns = 0;
			strChange(-wetstoneBuff);
		}
	}
	takingCover = 0;
}
