//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "level1.cpp"

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close( Tile* tiles[] );

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Placeholder", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				//Initialize SDL_ttf
                		if( TTF_Init() == -1 )
                		{
                			printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    			success = false;
                		}
			}
		}
	}

	return success;
}

void freeAll(Tile* tiles[]) {
	freeTileSet(tileSet);
	//Free loaded images
	gSpriteSheetTexture.free();
	gBed.free();
	gTextbox.free();
	gArrow.free();
	gText.free();
	gTable.free();
	gLouisBattleTexture.free();
	gBedBattleTexture.free();
}

void close()
{
	freeAll(tileSet);
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	srand(time(NULL));
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		loadFont(20);
		if( !loadMedia( tileSet ) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				if(!inBattle) {
					if(interactValue)
						louis.move(tileSet, &bed, &table);
				
				louis.setCamera( camera );

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render level
				for( int i = 0; i < TOTAL_TILES; ++i )
				{
					tileSet[ i ]->render( camera );
				}

				switch(levelID) {
					case 1:
						if(changeLevel) {
							changeLevelAnimation = 1;
							bed.setPos(480, 450);
						}
						changeLevel = 0;
						warp.setWarp(630, 775, 10, 1);
						bed.render(camera);
						table.render(camera);
						louis.render(camera, &gSpriteSheetTexture);
						
						if(inSirohebiCutscene1)
							cutscene.sirohebiCutscene1(&louis, &blanche);

						if(warp.checkWarp(&louis, 1)) {
							if(!hasSeenFirstCutscene)
								cutscene.firstCutscene(&textbox, e, camera, &louis);
						}
						if(warp.checkWarp(&louis, 0))
							louis.warp(2);
		
						if(bedMove) {
							isFirstCutscene = 0;
							if(!bedHasMoved) {
								bed.moveToXY(louis.getBox().x, louis.getBox().y - 100, &louis);
								currentClip = &gSpriteClips[ 0 ];
								resumeCutscene = 1;
							} else {
								bed.moveToXY(480, 450, &louis);
							}
						}
				
						if (resumeCutscene && !bedMove) {
							cutscene.firstCutscene(&textbox, e, camera, &louis);
							resumeCutscene = 0;
						}

						if(interruptBedMove && !hasShownInterruptBed) {
							hasShownInterruptBed = 1;
							cutscene.interruptBed(&textbox, camera);
						}

						if(battleIntro)
							battle.battleIntroAnimation();

						if(endBattle)
							battle.battleEnd2ndPart();

						break;
					case 2: 
						if(changeLevel) {
							changeLevelAnimation = 1;
							changeLevel = 0;
						}
						if(interactValue)
							louis.render(camera, &gSpriteSheetTexture);
						else
							louis.renderNP(camera, &gSpriteSheetTexture);
						warp.setWarp(630, 60, 10, 2);
						warp1.setWarp(420, 140, 2, 70);
						warp2.setWarp(867, 120, 2, 70);
						warp3.setWarp(600, 564, 90, 2);
						warp4.setWarp(450, 140, 2, 70);

						if(warp.checkWarp(&louis, 0))
							louis.warp(1);
						if(warp1.checkWarp(&louis, 0))
							louis.warp(3);
						if(warp4.checkWarp(&louis, 0))
							 battleIntro = 1;

						if(battleIntro)
							battle.battleIntroAnimation();

						if(endBattle)
							battle.battleEnd2ndPart();


						if(warp2.checkWarp(&louis, rejectSpan)) {
							if(sirohebiFlag1) {
								switch(trigger) {
									case 0: activeDialogue = 1;
										interactValue = 0; dialogueText = "It's locked."; 
										rejectSpan = 999; break;
									case 1: activeDialogue = 0; 
										louisMove = 1; louis.moveToXY(warp2.getBox().x - 67, louis.getBox().y, 2);
										louis.moveNP(tileSet, &bed, &table);
										if(!louisMove) {
											trigger = 0; interactValue = 1; rejectSpan = 0; louis.setState(2); freeText(&gText);
										}
										break;
								} 
							} else {
								louis.warp(4);
							}
						}
						if(warp3.checkWarp(&louis, rejectSpan)) {
							if(sirohebiFlag1) {
								switch(trigger) {
									case 0: activeDialogue = 1;
										interactValue = 0; dialogueText = "I oughtn't leave yet."; 
										rejectSpan = 999; break;
									case 1: activeDialogue = 0; 
										louisMove = 1; louis.moveToXY(louis.getBox().x, warp3.getBox().y - 64, 2);
										louis.moveNP(tileSet, &bed, &table);
										if(!louisMove) {
											trigger = 0; interactValue = 1; rejectSpan = 0; louis.setState(0); freeText(&gText);
										}
										break;
								} 
							} else {
								louis.warp(6);
							}
						}

						if(sirohebiFlag1)
							cutscene.hallCutscene1(&louis, &blanche, &bed, &table, tileSet);	
						break;
					case 3:
						if(changeLevel) {
							changeLevelAnimation = 1;
							changeLevel = 0;
						}
						if(interactValue)
							louis.render(camera, &gSpriteSheetTexture);
						else 
							louis.renderNP(camera, &gSpriteSheetTexture);
						warp.setWarp(507, 130, 2, 10);
						if(warp.checkWarp(&louis, 0)) {
							louis.warp(2);
						}
						break;
				}
				
				if(activeDialogue) {
					textbox.render(camera, "placeholder");
					drawDialogueText(dialogueText, &gText, &textbox);
				}

				
				if(promptSelect) {
					if(!isFirstCutscene)
						button.render("Yes", "No", camera, &textbox, selectedDirection);
					else
						button.render("Yes", "OK", camera, &textbox, selectedDirection);
				}

				if(changeLevelAnimation)
					battle.levelChangeAnim();

				//printf("%i/%b\n", trigger, louisMove);

				LTexture gPosition;
			        std::string louisXPos = std::to_string(louis.getBox().x);
				std::string louisYPos = std::to_string(louis.getBox().y);
				gPosition.loadFromRenderedText(louisXPos + ", " + louisYPos, White, 0, gFont);
				gPosition.render(camera.x - camera.x, camera.y - camera.y);

				} else if(inBattle) {
					SDL_RenderClear(gRenderer);
					battle.battling();
					if(endBattle)
						battle.battleEndAnimation();
				}

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
						if(e.key.keysym.sym == SDLK_q)
							quit = true;
						if(e.key.keysym.sym == SDLK_a) {
							/*louis.warp(2);
							sirohebiFlag1 = 1;
							blanche.setPos(420, 140); hasSeenFirstCutscene = 1;*/
						}
					}

					if(!inBattle) {
						if(!battleIntro) {
							//if(interactValue)
								louis.handleEvent( e );
							bed.handleEvent(e, &louis);
							table.handleEvent(e, &louis);
							if(isFirstCutscene)
								warp.handleEvent(e);
						}
						button.handleEvent(e);
						if(!doNotAdvance && activeDialogue)
							cutscene.handleEvent(e);
					} else {
						if(interactValue && !endTurn)
							battle.handleEvent(e);
						if(isCutscene && !doNotAdvance)
							cutscene.handleEvent(e);
					}

				}

								
				SDL_RenderPresent( gRenderer );

			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

