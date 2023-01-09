#include "battle.h"
#include "enemy.cpp"

Battle battle;
BattleChara battleLouis;
Cutscene cutscene;

bool endBattle = 0;

void resetCamera(SDL_Rect* camera) {
	camera->x = 0;
	camera->y = 0;
}

Battle::Battle() {
	battleIntroSquare.x = camera.w/2; battleIntroSquare.y = camera.h/2;
	battleIntroSquare.w = 1; battleIntroSquare.h = 1;

        battleActionBox.w = 500; battleActionBox.h = 150;
	battleActionBox.x = camera.w/2 - battleActionBox.w/2; battleActionBox.y = camera.y + 20;

	battleEndSquare.x = camera.x; battleEndSquare.y = camera.y;
	battleEndSquare.w = camera.w; battleEndSquare.h = camera.h;

	int alphaValueProgr = 0; setAlpha = 0;
}

int getXthButton() {
	//Gets button from 1st to 16th, column by column
	switch(xSelect) {
		case 0: switch(ySelect) {
				case 0: return 1; break;
				case 1: return 2; break;
				case 2: return 3; break;
				case 3: return 4; break;
			} break;
		case 1: switch(ySelect) {
				case 0: return 5; break;
				case 1: return 6; break;
				case 2: return 7; break;
				case 3: return 8; break;
			} break;
		case 2: switch(ySelect) {
				case 0: return 9; break;
				case 1: return 10; break;
				case 2: return 11; break;
				case 3: return 12; break;
			} break;
		case 3: switch(ySelect) {
				case 0: return 13; break;
				case 1: return 14; break;
				case 2: return 15; break;
				case 3: return 16; break;
			} break;
	}
}

void Battle::handleEvent(SDL_Event& e) {
	if(!endTurn && !selectWeapon && !endBattle && !selectAssist) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch(e.key.keysym.sym) {
			case SDLK_UP: ySelect--; break;
			case SDLK_DOWN: ySelect++; break;
			case SDLK_LEFT: xSelect--; break;
			case SDLK_RIGHT: xSelect++; break;
			case SDLK_z: switch(getXthButton()) {
					     case 1: selectWeapon = 1; break;
					     case 2: selectAssist = 1; break;
					     case 5: coverPrompt = 1; whatToDoPrompt = 0; break;
					     case 6: runPrompt = 1; whatToDoPrompt = 0; break;
				     } 
					 resetXYSelect();
					 break;
		}
	}
} else if(selectWeapon || selectAssist) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch(e.key.keysym.sym) {
			case SDLK_UP: ySelect--; break;
			case SDLK_DOWN: ySelect++; break;
			case SDLK_LEFT: xSelect--; break;
			case SDLK_RIGHT: xSelect++; break;
			case SDLK_x: selectWeapon = 0; selectAssist = 0; resetXYSelect(); break;
			case SDLK_z: if(selectWeapon) {
				     switch(getXthButton()) {
					     	case 1: withSword = 1; break;
					     	case 2: withSword = 0; break;
				     } 
					 attackPrompt = 1; whatToDoPrompt = 0; selectWeapon = 0; resetXYSelect();
				     } else if(selectAssist) {
				     	switch(getXthButton()) {
						case 1: useMaglass = 1; break;
					     	case 2: useWetstone = 1; break;
				     } 
					 friendsPrompt = 1; whatToDoPrompt = 0; selectAssist = 0; resetXYSelect(); break;
				     }
		}
	}
}
	if(xSelect < 0)
		xSelect = 0;
	else if(xSelect > numberOfButtonColumns - 1)
		xSelect = numberOfButtonColumns - 1;
	if(ySelect < 0)
		ySelect = 0;
	else if(ySelect > numberOfButtonRows - 1)
		ySelect = numberOfButtonRows - 1;
}

void Battle::actionBox() {
	SDL_SetRenderDrawColor(gRenderer, 70,130,180, 255);
	SDL_RenderFillRect(gRenderer, &battleActionBox);
	button.battleRender(battleActionBox, &battleLouis);
}

bool hasDeterminedEnemy = 0;
std::string responseTxt = "NULL";
void Battle::battling() {
	if(!hasDeterminedEnemy) {
		enemy.chooseEnemy(0);
		hasDeterminedEnemy = 1;
	}
	resetCamera(&camera);
	SDL_SetRenderDrawColor(gRenderer, 20, 20, 20, 255);
	SDL_RenderFillRect(gRenderer, &battleIntroSquare);
	if(isTutorial)
		cutscene.tutorialCutscene(&textbox, camera, &enemy);
	battle.actionBox();
	enemy.render(camera, &battleLouis, battleActionBox);
	battleLouis.render(camera, &enemy, battleActionBox);
	if(activeResponse)
		drawBattleText(responseTxt, &gText, battleActionBox, battleActionBox.w / 3, battleActionBox.y + battleActionBox.h/4);
	if(activeDialogue) {
		textbox.render(camera, "placeholder");
		drawDialogueText(dialogueText, &gText, &textbox);
	}
	if(louisHasActed && enemyHasActed) {
		hasActed = 1; louisHasActed = 0; enemyHasActed = 0;
	}
	if(hasActed) {
		battleLouis.resetMods(); hasActed = 0;
	}
}

void Battle::battleIntroAnimation() {
	interactValue = 0;
	SDL_SetRenderDrawColor(gRenderer, 20, 20, 20, 255);
	SDL_RenderFillRect(gRenderer, &battleIntroSquare);
	if(battleIntroSquare.w < SCREEN_WIDTH + 10) {
		battleIntroSquare.h +=8;
		battleIntroSquare.y = camera.h/2 - battleIntroSquare.h/2;
		battleIntroSquare.w +=8;
		battleIntroSquare.x = camera.w/2 - battleIntroSquare.h/2;
	} else {
		inBattle = 1;
		battleIntro = 0; interactValue = 1;
	}
}

void Battle::resetBattleIntroSquare() {
	battleIntroSquare.x = camera.w/2; battleIntroSquare.y = camera.h/2;
	battleIntroSquare.w = 1; battleIntroSquare.h = 1;

	battleEndSquare.x = 1; battleEndSquare.y = 1;
	battleEndSquare.w = SCREEN_WIDTH; battleEndSquare.h = SCREEN_HEIGHT;

	alphaValueProgr = 0;
}

void Battle::battleEndAnimation() {
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);	
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, alphaValueProgr);
	SDL_RenderFillRect(gRenderer, &battleEndSquare);
	if(alphaValueProgr < 255) {
		alphaValueProgr += 15;
	} else {
		leaveAlphaValue = 1; interactValue = 1; hasDeterminedEnemy = 0; inBattle = 0; louisHasActed = 0; enemyHasActed = 0; hasActed = 0;
	}
}

void Battle::battleEnd2ndPart() {
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);	
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, alphaValueProgr);
	SDL_RenderFillRect(gRenderer, &battleEndSquare);
	if(alphaValueProgr > 0) {
		alphaValueProgr -= 15;
	} else {
		endBattle = 0; 
		resetBattleIntroSquare(); resetBattleState();
	}
}

void Battle::levelChangeAnim() {
	if(!setAlpha) {
		alphaValueProgr = 255; leaveAlphaValue = 1;
		setAlpha = 1;
	}
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);	
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, alphaValueProgr);
	SDL_RenderFillRect(gRenderer, &battleEndSquare);
	//if(alphaValueProgr < 255 && !leaveAlphaValue) {
	//	alphaValueProgr += 255;
	/*} else*/ if(alphaValueProgr > 0 && leaveAlphaValue) {
		alphaValueProgr -= 15;
	} else {
		changeLevelAnimation = 0; leaveAlphaValue = 0; resetBattleIntroSquare(); setAlpha = 0;
	}
	//if(alphaValueProgr == 255)
	//	leaveAlphaValue = 1;
}
