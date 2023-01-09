#include "button.h"

SDL_Rect gArrowClip[1];

LTexture gText;
LTexture gArrow;
LTexture gYes;
LTexture gNo;

Button button;

int selectedDirection = 0;
int xSelect = 0;
int ySelect = 0;
bool whatToDoPrompt = 1;
bool selectWeapon = 0;
bool selectAssist = 0;
bool attackPrompt = 0;
bool friendsPrompt = 0;
bool coverPrompt = 0;
bool runPrompt = 0;
bool enemyDie = 0;
bool louisDie = 0;
bool endTurn = 0;
int battleTicks = 0;
bool runSuccess = 0;
bool loadedFont = 0;
bool louisHasActed = 0;
bool enemyHasActed = 0;
bool hasActed = 0;
bool enemyAct = 0;
bool activeResponse = 0;
bool activeDialogue = 0;
bool doNotAdvance = 0;
bool enemyMove = 0;
bool enemyHasMoved = 0;
bool isCutscene = 0;
bool success = 0;
int ticks = 0;
int rejectSpan = 0;
bool changeLevelAnimation = 0;

int charCount = 0;
std::string textWritten = "";
std::string battleTextWritten = "";
bool doNotType = 0;
void drawDialogueText(std::string s, LTexture* gText, Textbox* textbox) {
	int wrpBnd = textbox->getWidth() - 150;
	if(!doNotType) {
		if(charCount < s.size()) {
			textWritten += s[charCount]; charCount++;
		}
			gText->loadFromRenderedText(textWritten, White, wrpBnd, gFont); 
			gText->render(textbox->getX() + 150, textbox->getY() + 50); 
	} else {
		gText->loadFromRenderedText(s, White, wrpBnd, gFont);
		gText->render(textbox->getX() + 150, textbox->getY() + 50);
	}
}

void drawBattleText(std::string s, LTexture* gText, SDL_Rect& textbox, int x, int y) {
	int wrpBnd = textbox.w - 150;
	if(!doNotType) {
		if(charCount < s.size()) {
			battleTextWritten += s[charCount];
		}
			gText->loadFromRenderedText(battleTextWritten, White, wrpBnd, gBattleFont); charCount++;
			gText->render(x, y); 
	} else {
		gText->loadFromRenderedText(s, White, wrpBnd, gBattleFont);
		gText->render(x, y);
	}
}
void loadFont(int size) {
		gBattleFont= TTF_OpenFont("resources/fonts/battlefont.ttf", size);
		gFont= TTF_OpenFont("resources/fonts/font1.ttf", size);
}

void freeText(LTexture* gText) {
	charCount = 0;
	gText->free();
	textWritten = "";
	battleTextWritten = "";
}

void resetChars() {
	textWritten = "";	
}

void resetBattleState() {
	whatToDoPrompt = 1; selectWeapon = 0; attackPrompt = 0;
	friendsPrompt = 0; coverPrompt = 0; runPrompt = 0;
	enemyDie = 0; louisDie = 0; battleTicks = 0;
	selectAssist = 0; endTurn = 0; runSuccess = 0; 
	loadedFont = 0; enemyAct = 0; activeResponse = 0;
	freeText(&gText);
}

void resetXYSelect() {
	xSelect = 0;
	ySelect = 0;
}

Button::Button() {
	mBox.x = 50;
	mBox.y = 50;
	mBox.w = 30;
	mBox.h = 30;
}

SDL_Rect Button::getBox() {
	return mBox;
}

void Button::handleEvent( SDL_Event& e )
{
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    	{
        switch( e.key.keysym.sym )
        {
	    case SDLK_UP: selectedDirection = 0; break;
	    case SDLK_DOWN: selectedDirection = 1; break;
            case SDLK_LEFT: selectedDirection = 2; break;
	    case SDLK_RIGHT: selectedDirection = 3; break;
	    default: selectedDirection = 2; break;

        }
    }
}

void Button::render(std::string text1, std::string text2, SDL_Rect& camera, Textbox* textbox, int selectedDirection) {
	gYes.loadFromRenderedText(text1, White, 0, gFont);
	gYes.render(textbox->getWidth() / 3, 
			textbox->getY() / 2 + textbox->getHeight() + 125);

	gNo.loadFromRenderedText(text2, White, 0, gFont);
	gNo.render(textbox->getWidth() - textbox->getWidth() / 3, 
			textbox->getY() / 2 + textbox->getHeight() + 125);

	switch(selectedDirection) {
		case 0: break;
		case 1: break;
		case 2: gArrow.render(textbox->getWidth() / 3 - 25,
			textbox->getY() / 2 + textbox->getHeight() + 125, 
			&gArrowClip[0]);
			break;
		case 3: gArrow.render(textbox->getWidth() - textbox->getWidth() / 3 - 25,
			textbox->getY() / 2 + textbox->getHeight() + 125, 
			&gArrowClip[0]);
			break;
}
}

int numberOfButtonRows = 0;
int numberOfButtonColumns = 0;
LTexture gAttack;
LTexture gCover;
LTexture gFriends;
LTexture gRun;
LTexture gSword;
LTexture gGun;
SDL_Rect selectWeaponBox; 
SDL_Rect selectAssistBox;
SDL_Rect selectAssistPicture;
SDL_Color Color = {255, 255, 255};

void checkColorOfSkill(BattleChara* battleLouis, int skillID) {
	if(battleLouis->getSklExpenditure(skillID) >= 0) {
		Color = White;
	} else {
		Color = Grey;
	}
}

void Button::battleRender(SDL_Rect& textbox, BattleChara* battleLouis) {
	if(whatToDoPrompt) {
		numberOfButtonRows = 2;
		numberOfButtonColumns = 2;
		gAttack.loadFromRenderedText("Attack", White, 0, gBattleFont);
		gAttack.render(textbox.w / 3, textbox.y + textbox.h/4);

		gFriends.loadFromRenderedText("Assist", White, 0, gBattleFont);
		gFriends.render(textbox.w / 3, textbox.y + textbox.h/2 + 20);

		gCover.loadFromRenderedText("Cover", White, 0, gBattleFont);
		gCover.render(textbox.w - textbox.w / 3 + 70, textbox.y + textbox.h/4);

		gRun.loadFromRenderedText("Run", White, 0, gBattleFont);
		gRun.render(textbox.w - textbox.w / 3 + 70, textbox.y + textbox.h/2 + 20);
		if(!(selectWeapon || selectAssist)) {
		switch(xSelect) {
			case 0: switch(ySelect) {
					case 0: gArrow.render(textbox.w / 3 - 20, textbox.y + textbox.h/4 + 5, &gArrowClip[0]); break;
					case 1: gArrow.render(textbox.w / 3 - 20, textbox.y + textbox.h/2 + 20 + 5, &gArrowClip[0]); break; }
				break;
			case 1: switch(ySelect) {
					case 0: gArrow.render(textbox.w - textbox.w / 3 + 70 - 20, textbox.y + textbox.h/4 + 5, &gArrowClip[0]); break;
					case 1: gArrow.render(textbox.w - textbox.w / 3 + 70 - 20, textbox.y + textbox.h/2 + 20 + 5, &gArrowClip[0]); break; }
				break;
}
} else if(selectWeapon) {
	numberOfButtonColumns = 1;
	numberOfButtonRows = 2;
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
	selectWeaponBox.x = textbox.w / 3 + 10; selectWeaponBox.h = 100;
	selectWeaponBox.w = 150; selectWeaponBox.y = 200;
	SDL_RenderFillRect(gRenderer, &selectWeaponBox);
	gSword.loadFromRenderedText("Sword", White, 0, gBattleFont);
	gGun.loadFromRenderedText("Gun", White, 0, gBattleFont);
	gSword.render(selectWeaponBox.x + 30, selectWeaponBox.y + 10);
	gGun.render(selectWeaponBox.x + 30, selectWeaponBox.y + 50);
	switch(ySelect) {
		case 0: gArrow.render(selectWeaponBox.x + 30 - 20, selectWeaponBox.y + 10 + 5); break;
		case 1: gArrow.render(selectWeaponBox.x + 30 - 20, selectWeaponBox.y + 50 + 5); break; 
	}
} else if(selectAssist) {
	numberOfButtonColumns = 1;
	numberOfButtonRows = 2;
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
	selectAssistBox.x = textbox.w / 2 + 50; selectAssistBox.h = 250;
	selectAssistBox.w = 200; selectAssistBox.y = 200;
	selectAssistPicture.x = textbox.w / 3 + 15; selectAssistPicture.h = 100;
	selectAssistPicture.w = 100; selectAssistPicture.y = 200;
	SDL_RenderFillRect(gRenderer, &selectAssistBox);
	SDL_RenderFillRect(gRenderer, &selectAssistPicture);
	gSword.loadFromRenderedText("Magn.Glass 0", White, 0, gBattleFont);
	checkColorOfSkill(battleLouis, 2);
	gGun.loadFromRenderedText("Wetstone " + std::to_string(battleLouis->getSklLv(2)), Color, 0, gBattleFont);
	gSword.render(selectAssistBox.x + 30, selectAssistBox.y + 10);
	gGun.render(selectAssistBox.x + 30, selectAssistBox.y + 50);
	switch(ySelect) {
		case 0: gArrow.render(selectAssistBox.x + 30 - 20, selectAssistBox.y + 10 + 5); break;
		case 1: gArrow.render(selectAssistBox.x + 30 - 20, selectAssistBox.y + 50 + 5); break;
		case 2: gArrow.render(selectAssistBox.x + 30 - 20, selectAssistBox.y + 90 + 5); break;
		case 3: gArrow.render(selectAssistBox.x + 30 - 20, selectAssistBox.y + 130 + 5); break;
	}
}
}
}
