#include "renderer.cpp"
#include "button.cpp"
#include "objects.cpp"
#include <SDL_ttf.h>
#include "cutscenes.h"

bool interactValue = 1;
bool saveGame = 0;
int trigger = 0;
bool promptSelect = 0;
bool inBattle = 0;
bool battleIntro = 0;
std::string dialogueText = "";
int wrpBnd = textbox.getWidth() - 150;

bool inSirohebiCutscene1 = 0;
bool sirohebiFlag1 = 0;

void unshowTextbox(Textbox* textbox) {
	activeDialogue = 0;
	trigger = 0;
	promptSelect = 0;
	selectedDirection = 2;
}

void Cutscene::handleEvent(SDL_Event& e) {
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch(e.key.keysym.sym) {
			case SDLK_z: freeText(&gText);
			     	     trigger++; break;
		}
	}
}

bool talkedToBed = 0;
bool goodAnswer = 0;
void Cutscene::talkToBed1(Textbox* textbox, SDL_Event& e, SDL_Rect& camera) {
	gFont = TTF_OpenFont("resources/fonts/font1.ttf", 20);
	activeDialogue = 1;
	interactValue = 0;
	int wrpBnd = textbox->getWidth() - 150;

	switch(trigger) {
		case 0: if(!sirohebiFlag1) {
			if(talkedToBed) {
				if(!goodAnswer)
					dialogueText = "Beds hardly get any breaks. Everyone's always sleeping on you.";
				else
					dialogueText = "Sometimes it gets boring around here. Cards, anyone?";
				trigger =  3;
			} else { 
			dialogueText = "It's a bed. "; 
			
			}
			} else {
				dialogueText = "Good luck. I'd go with you, but I can't make it through that doorway.";
				trigger = 999;
			}	
			break;
		case 1: dialogueText = "Sleep?"; 	
			break;
		case 2: doNotType = 1; promptSelect = 1;
		       	break;
		case 3: doNotType = 0;
			if(selectedDirection == 2) {
				promptSelect = 0;
				goodAnswer = 0;
				dialogueText = "No.";
			 } else if(selectedDirection == 3) {
				 promptSelect = 0;
				 goodAnswer = 1;
				 dialogueText = "Huh!";
			 }
			
			break;
		case 4: dialogueText = "...?";
			
			break;
		default:
			unshowTextbox(textbox); talkedToBed = 1; interactValue = 1;
			break;
	}
}

void Cutscene::talkToTable1(Textbox* textbox, SDL_Event& e, SDL_Rect& camera) {
	gFont = TTF_OpenFont("resources/fonts/font1.ttf", 20);
	activeDialogue = 1;
	interactValue = 0;
	int wrpBnd = textbox->getWidth() - 150;

	switch(trigger) {
		case 0:	dialogueText = "Save?"; promptSelect = 1; 
			break;
		case 1: if(selectedDirection == 2) {
				promptSelect = 0;
				saveGame = 1;
				dialogueText = "Game saved.";
				
			 } else if(selectedDirection == 3) {
				promptSelect = 0;
				saveGame = 0;
				unshowTextbox(textbox); interactValue = 1;
			 }
			break;
		default:
			unshowTextbox(textbox); interactValue = 1;
 			break;
	}
}

bool isTutorial = 0;
bool isFirstCutscene = 0;
bool resumeCutscene = 0;
bool hasSeenFirstCutscene = 0;
void Cutscene::firstCutscene(Textbox* textbox, SDL_Event& e, SDL_Rect& camera, Chara* louis) {
	isFirstCutscene = 1;
	resumeCutscene = 0;
	hasSeenFirstCutscene = 1;
	gFont = TTF_OpenFont("resources/fonts/font1.ttf", 20);
	activeDialogue = 1;
	interactValue = 0;
	int wrpBnd = textbox->getWidth() - 150;

	switch(trigger) {
		case 0:	louis->setState(1); dialogueText = "Hey."; trigger++;
			break;
		case 1: louis->setState(0); 
			bedMove = 1; activeDialogue = 0; trigger++;
 			break;
		case 2: activeDialogue = 1;
			dialogueText = "You weren't planning on going out there without knowing what's going on, were you?"; trigger++;
			break;
		case 3: dialogueText = "Well, I suppose that's one way to do it, but I think your job would be a lot easier if you at least had a minimum idea of what you're doing."; 
			break;
		case 4: dialogueText = "I'll give you a little explanation. How about it?"; 
		        break;
		case 5: doNotType = 1;
			promptSelect = 1;
			break;
		case 6: doNotType = 0;
			if(selectedDirection == 2 || selectedDirection == 3) {
				dialogueText = "Then, away!"; promptSelect = 0; 
			}			
			 break;
		default: activeDialogue = 0; interactValue = 1; battleIntro = 1; isFirstCutscene = 0; isTutorial = 1;  freeText(&gText); trigger = 0;
			 break;
	}
}

bool hasShownInterruptBed = 0;
void Cutscene::interruptBed(Textbox* textbox, SDL_Rect& camera) {
	gFont = TTF_OpenFont("resources/fonts/font1.ttf", 20);
	activeDialogue = 1;
	interactValue = 0;
	bedMove = 0;
	int wrpBnd = textbox->getWidth() - 150;

	switch(trigger) {
		case 0:	gText.loadFromRenderedText("...", White, wrpBnd, gFont); 
			break;
		default: unshowTextbox(textbox); interactValue = 1;			 break;
	}
}

void Cutscene::hallCutscene1(Chara* louis, Chara* blanche, Bed* bed, Table* table, Tile** tileSet) {
	if(blanche->getBox().x < 830) {
		interactValue = 0;
		if(louis->getBox().x - blanche->getBox().x >= 100)
			louis->setState(2);
		else if(louis->getBox().x - blanche->getBox().x <= 100 && louis->getBox().x - blanche->getBox().x > 0)
			louis->setState(1);
		else 
			louis->setState(3);

		blanche->moveToXY(830, 140, 7);
		blanche->moveNP(tileSet, bed, table);
		blanche->renderNP(camera, &gSirohebiSpriteSheetTexture);
		louisMove = 1;
	} else if(sirohebiFlag1 && !success) {
		louis->moveNP(tileSet, bed, table);
			if(louisMove)
				louis->moveToXY(630, 140, 2);
			else {
				ticks++;
				if(ticks == 1)
					louis->setState(3);
				else if(ticks == 30)
					louis->setState(2);
				else if(ticks == 60) {
					louis->setState(1);
					success = 1;
					interactValue = 1;
				}
			}
	}
}

