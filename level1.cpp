#include "louis.cpp"
#include "collision.cpp"
#include "cutscenes.cpp"
#include "battle.cpp"
#include "menu.cpp"

Bed bed;
Table table;
Warp warp;
Warp warp1;
Warp warp2;
Warp warp3;
Warp warp4;
Warp warp5;
Warp warp6;
Chara louis;
Chara blanche;

const int LEVEL_WIDTH = 1290;
const int LEVEL_HEIGHT = 960;

//Tile constants
const int TOTAL_TILES = 1376;

bool setTiles( Tile* tiles[] );
void readTileMap(Tile* tiles[]);
void freeTileSet(Tile* tiles[]);

bool loadMedia( Tile* tiles[] )
{
	//Loading success flag
	bool success = true;

	//Load tile texture
	if( !gTileTexture.loadFromFile( "resources/floor_tiles/tiles1.png" ) )
	{
		printf( "Failed to load tile set texture!\n" );
		success = false;
	}

	//Load tile map
	if( !setTiles( tiles ) )
	{
		printf( "Failed to load tile set!\n" );
		success = false;
	}
	if(!gTassetSpriteSheetTexture.loadFromFile("resources/NPCs/tasset.png")) {
		success = false;
	}
	if(!gArmourmanSpriteSheetTexture.loadFromFile("resources/NPCs/armourman.png")) {
		success = false;
	}
	//Load sprite sheet texture
	if( !gSpriteSheetTexture.loadFromFile( "resources/louis/louissprites.png" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	if( !gSirohebiSpriteSheetTexture.loadFromFile( "resources/sirohebi/sirohebisprites.png" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	if( !gLouisBattleTexture.loadFromFile( "resources/louis/louisbattlesprites.png" ) )
	{
		printf( "Failed to load louisbattlesprites.png\n" );
		success = false;
	}
	if( !gBedBattleTexture.loadFromFile( "resources/enemies/bedbattlesprites.png" ) )
	{
		printf( "Failed to load bedbattlesprites.png\n" );
		success = false;
	}
	if( !gBed.loadFromFile( "resources/objects/bed.png" ) )
	{
		printf("Failed to load object!\n");
		success = false;
	}
	if( !gTextbox.loadFromFile( "resources/objects/textbox.png" ) )
	{
		printf("Failed to load object!\n");
		success = false;
	}
	if( !gArrow.loadFromFile("resources/objects/arrow.png") ) {
		printf("Failed to load object!\n");
		success = false;
	}
	if(!gTable.loadFromFile("resources/objects/table.png")) {
		printf("Failed to load table!\n");
		success = false;
	}
	TTF_Font* gFont = TTF_OpenFont("resources/fonts/font1.ttf", 20);
	if(gFont == NULL) {
		printf("Failed to load gFont! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	TTF_Font* gBattleFont= TTF_OpenFont("resources/fonts/battlefont.ttf", 20);
	if(gBattleFont == NULL) {
		printf("Failed to load gBattleFont! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

	else
	{
		//(Facing) Up		   //Down		      //Left			 //Right
		gSpriteClips[ 0 ].x =   0; gSpriteClips[ 4 ].x =   0; gSpriteClips[ 11 ].x =   0; gSpriteClips[ 12 ].x =   0;
		gSpriteClips[ 0 ].y =   0; gSpriteClips[ 4 ].y =  50; gSpriteClips[ 11 ].y = 100; gSpriteClips[ 12 ].y = 150;
		gSpriteClips[ 0 ].w =  27; gSpriteClips[ 4 ].w =  27; gSpriteClips[ 11 ].w =  27; gSpriteClips[ 12 ].w =  27;
		gSpriteClips[ 0 ].h =  50; gSpriteClips[ 4 ].h =  50; gSpriteClips[ 11 ].h =  50; gSpriteClips[ 12 ].h =  50;

		gSpriteClips[ 1 ].x =  27; gSpriteClips[ 5 ].x =  27; gSpriteClips[ 10 ].x =  27; gSpriteClips[ 13 ].x =  27;
		gSpriteClips[ 1 ].y =   0; gSpriteClips[ 5 ].y =  50; gSpriteClips[ 10 ].y = 100; gSpriteClips[ 13 ].y = 150;
		gSpriteClips[ 1 ].w =  27; gSpriteClips[ 5 ].w =  27; gSpriteClips[ 10 ].w =  27; gSpriteClips[ 13 ].w =  27;
		gSpriteClips[ 1 ].h =  50; gSpriteClips[ 5 ].h =  50; gSpriteClips[ 10 ].h =  50; gSpriteClips[ 13 ].h =  50;

		gSpriteClips[ 2 ].x =  54; gSpriteClips[ 6 ].x =  54; gSpriteClips[ 9 ].x =  54; gSpriteClips[ 14 ].x =  54; 
		gSpriteClips[ 2 ].y =   0; gSpriteClips[ 6 ].y =  50; gSpriteClips[ 9 ].y = 100; gSpriteClips[ 14 ].y = 150; 
		gSpriteClips[ 2 ].w =  27; gSpriteClips[ 6 ].w =  27; gSpriteClips[ 9 ].w =  27; gSpriteClips[ 14 ].w =  27;
		gSpriteClips[ 2 ].h =  50; gSpriteClips[ 6 ].h =  50; gSpriteClips[ 9 ].h =  50; gSpriteClips[ 14 ].h =  50;

		gSpriteClips[ 3 ].x =  81; gSpriteClips[ 7 ].x =  81; gSpriteClips[ 8 ].x =  81; gSpriteClips[ 15 ].x =  81;
		gSpriteClips[ 3 ].y =   0; gSpriteClips[ 7 ].y =  50; gSpriteClips[ 8 ].y = 100; gSpriteClips[ 15 ].y = 150;
		gSpriteClips[ 3 ].w =  27; gSpriteClips[ 7 ].w =  27; gSpriteClips[ 8 ].w =  27; gSpriteClips[ 15 ].w =  27;
		gSpriteClips[ 3 ].h =  50; gSpriteClips[ 7 ].h =  50; gSpriteClips[ 8 ].h =  50; gSpriteClips[ 15 ].h =  50;

		gBedClip[0].x = 0;
		gBedClip[0].y = 0;
		gBedClip[0].w = 40;
		gBedClip[0].h = 60;

		gArrowClip[0].x = 0;
		gArrowClip[0].y = 0;
		gArrowClip[0].w = 20;
		gArrowClip[0].h = 20;

		gBattleClips[0].x = 0; gBattleClips[0].y = 0; gBattleClips[0].w = 130; gBattleClips[0].h = 200;

		gEnemyBattleClips[0].x = 0; gEnemyBattleClips[0].y = 0; gEnemyBattleClips[0].w = 130; gEnemyBattleClips[0].h = 200;
	}


	return success;
}

Tile* tileSet[ TOTAL_TILES ];

bool setTiles( Tile* tiles[] )
{
    //Success flag
    bool tilesLoaded = true;

    //Open the map
    std::ifstream map1("resources/floor_tiles/level1.map");
    std::ifstream map2("resources/floor_tiles/level2.map");

    //If the map couldn't be loaded
    if( map1.fail() || map2.fail() )
    {
		printf( "Unable to load map file!\n" );
		tilesLoaded = false;
    }
	else
	{
		readTileMap(tileSet);
		
		//Clip the sprite sheet
		if( tilesLoaded )
		{
			gTileClips[ TILE_FLOOR ].x = 0;
			gTileClips[ TILE_FLOOR ].y = 0;
			gTileClips[ TILE_FLOOR ].w = TILE_WIDTH;
			gTileClips[ TILE_FLOOR ].h = TILE_HEIGHT;

			gTileClips[ TILE_WALLUP ].x = 0;
			gTileClips[ TILE_WALLUP ].y = 30;
			gTileClips[ TILE_WALLUP ].w = TILE_WIDTH;
			gTileClips[ TILE_WALLUP ].h = TILE_HEIGHT;

			gTileClips[ TILE_WALLDOWN ].x = 0;
			gTileClips[ TILE_WALLDOWN ].y = 60;
			gTileClips[ TILE_WALLDOWN ].w = TILE_WIDTH;
			gTileClips[ TILE_WALLDOWN ].h = TILE_HEIGHT;

			gTileClips[ TILE_WALLLEFT ].x = 0;
			gTileClips[ TILE_WALLLEFT ].y = 90;
			gTileClips[ TILE_WALLLEFT ].w = TILE_WIDTH;
			gTileClips[ TILE_WALLLEFT ].h = TILE_HEIGHT;

			gTileClips[ TILE_WALLRIGHT ].x = 0;
			gTileClips[ TILE_WALLRIGHT ].y = 120;
			gTileClips[ TILE_WALLRIGHT ].w = TILE_WIDTH;
			gTileClips[ TILE_WALLRIGHT ].h = TILE_HEIGHT;

			gTileClips[ TILE_VOID ].x = 0;
			gTileClips[ TILE_VOID ].y = 150;
			gTileClips[ TILE_VOID ].w = TILE_WIDTH;
			gTileClips[ TILE_VOID ].h = TILE_HEIGHT;

			gTileClips[ TILE_DOOR1 ].x = 30;
			gTileClips[ TILE_DOOR1 ].y = 0;
			gTileClips[ TILE_DOOR1 ].w = TILE_WIDTH;
			gTileClips[ TILE_DOOR1 ].h = TILE_HEIGHT;

			gTileClips[ TILE_DOOR2 ].x = 30;
			gTileClips[ TILE_DOOR2 ].y = 30;
			gTileClips[ TILE_DOOR2 ].w = TILE_WIDTH;
			gTileClips[ TILE_DOOR2 ].h = TILE_HEIGHT;

			gTileClips[ TILE_VOID2 ].x = 30;
			gTileClips[ TILE_VOID2 ].y = 60;
			gTileClips[ TILE_VOID2 ].w = TILE_WIDTH;
			gTileClips[ TILE_VOID2 ].h = TILE_HEIGHT;
		}
	}

    //Close the file
    map1.close(); map2.close();

    //If the map was loaded fine
    return tilesLoaded;
}

void readTileMap(Tile* tiles[]) {
	freeTileSet(tileSet);

	//The tile offsets
	int x = 0, y = 0;

	std::ifstream map1("resources/floor_tiles/level1.map");
    	std::ifstream map2("resources/floor_tiles/level2.map");
    	std::ifstream map3("resources/floor_tiles/level3.map");
    	std::ifstream map4("resources/floor_tiles/level4.map");
    	std::ifstream map5("resources/floor_tiles/level5.map");
    	std::ifstream map6("resources/floor_tiles/level6.map");
   	std::ifstream map7("resources/floor_tiles/level7.map");
    	std::ifstream map8("resources/floor_tiles/level8.map");
	std::ifstream map9("resources/floor_tiles/level9.map");
    	std::ifstream map10("resources/floor_tiles/level10.map");
	std::ifstream map11("resources/floor_tiles/level11.map");
    	std::ifstream map12("resources/floor_tiles/level12.map");
	
	//Initialize the tiles
	for( int i = 0; i < TOTAL_TILES; i++ )
	{
		//Determines what kind of tile will be made
		int tileType = -1;

		switch(levelID) {
			case 1: map1 >> tileType; break;
			case 2: map2 >> tileType; break;
			case 3: map3 >> tileType; break;
			case 4: map4 >> tileType; break;
			case 5: map5 >> tileType; break;
			case 6: map6 >> tileType; break;
			case 7: map7 >> tileType; break;
			case 8: map8 >> tileType; break;
			case 9: map9 >> tileType; break;
			case 10: map10 >> tileType; break;
			case 11: map11 >> tileType; break;
			case 12: map12 >> tileType; break;
		}

		//If the number is a valid tile number
		if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) ) {
			tiles[ i ] = new Tile( x, y, tileType );
		}
		//If we don't recognize the tile type
		else {
			//Stop loading map
			printf( "Error loading map: Invalid tile type at %d!\n", i );
			break;
		}

		//Move to next tile spot
		x += TILE_WIDTH;
			//If we've gone too far
			if( x >= LEVEL_WIDTH ) {
			//Move back
			x = 0;

			//Move to the next row
			y += TILE_HEIGHT;
		}
	}

	map1.close(); map6.close(); map11.close();// map2.close();
	map2.close(); map7.close(); map12.close();// map2.close();
	map3.close(); map8.close(); //map8.close(); map2.close();
	map4.close(); map9.close(); //map9.close(); map2.close();
	map5.close(); map10.close(); //map10.close(); map2.close();
}

void freeTileSet(Tile* tiles[]) {
	for( int i = 0; i < TOTAL_TILES; ++i )
	{
		 if( tiles[ i ] != NULL )
		 {
			delete tiles[ i ];
			tiles[ i ] = NULL;
		 }
	}
}

bool touchesWall(SDL_Rect box, Tile* tiles[])
{
    //Go through the tiles
    for(int i = 0; i < TOTAL_TILES; ++i)
    {
        //If the tile is a wall type tile
        if( (tiles[i]->getType() >= TILE_VOID2 && tiles[i]->getType() <= LAST_TILE) && tiles[i]->getType() != TILE_FLOOR  )
        {
            //If the collision box touches the wall tile
            if( checkCollision(box, tiles[ i ]->getBox()) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

void Tile::render( SDL_Rect& camera )
{
    //If the tile is on screen
    if( checkCollision( camera, mBox ) )
    {
        //Show the tile
        gTileTexture.render( mBox.x - camera.x, mBox.y - camera.y, &gTileClips[ mType ] );
    }
}

int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}

bool changeLevel = 0;
void Chara::warp(int warpLevelID) {
	switch(warpLevelID) {
		case 1: battle.levelChangeAnim();
			levelID = warpLevelID; readTileMap(tileSet);
			mBox.x = 630; mBox.y = 750;
			changeLevel = 1;
			break;
		case 2: battle.levelChangeAnim();
			switch(levelID) {
				case 1: mBox.x = 630; mBox.y = 62; break;
				case 3: mBox.x = 422; mBox.y = 130; break;
			}
			levelID = warpLevelID; readTileMap(tileSet); 
			changeLevel = 1;
			break;
		case 3: battle.levelChangeAnim();
			levelID = warpLevelID; readTileMap(tileSet);
			mBox.x = 480; mBox.y = 130; 
			changeLevel = 1;
			break;
	}
}

void Chara::move( Tile *tiles[], Bed* bed, Table* table )
{
    //Move the dot left or right
    mBox.x += mVelX;
    //If the dot went too far to the left or right
    if( ( mBox.x < 0 ) || ( mBox.x + DOT_WIDTH > LEVEL_WIDTH ) || touchesWall(mBox, tiles) || checkCollision(bed->getBox(), mBox) || checkCollision(table->getBox(), mBox) )
    {
        //Move back
        mBox.x -= mVelX;
    }

    //Move the dot up or down
    mBox.y += mVelY;

    //If the dot went too far up or down
    if( ( mBox.y < 0 ) || ( mBox.y + DOT_HEIGHT > LEVEL_HEIGHT ) || touchesWall(mBox, tiles) || checkCollision(bed->getBox(), mBox) || checkCollision(table->getBox(), mBox) )
    {
        //Move back
        mBox.y -= mVelY;
    }

    if( mVelY == 0 && mVelX == 0 ) {
	    moveState = turnState;
    } 
    else if( mVelY != 0 && mVelX == 0 ) {
	    switch(mVelY) {
		    case DOT_VEL: turnState = 1; moveState = 1; break;
		    case -DOT_VEL: turnState = 0; moveState = 0; break;
	    }
    }
    else if( mVelY == 0 && mVelX != 0 ) {
	    switch(mVelX) {
		    case DOT_VEL: turnState = 3; moveState = 3; break;
		    case -DOT_VEL: turnState  = 2; moveState = 2; break;
	    }
    }
    else if( mVelY != 0 && mVelX != 0 ) {
	    switch(mVelX) {
		    case DOT_VEL: turnState = 3; moveState = 3; break;
		    case -DOT_VEL: turnState = 2; moveState = 2; break;
	    }
    }
}

void Chara::moveNP( Tile *tiles[], Bed* bed, Table* table )
{
    mBox.x += mVelXNP;
    if( ( mBox.x < 0 ) || ( mBox.x + DOT_WIDTH > LEVEL_WIDTH ) || touchesWall(mBox, tiles) || checkCollision(bed->getBox(), mBox) || checkCollision(table->getBox(), mBox) ) {
        mBox.x -= mVelXNP;
    }

    mBox.y += mVelYNP;
    if( ( mBox.y < 0 ) || ( mBox.y + DOT_HEIGHT > LEVEL_HEIGHT ) || touchesWall(mBox, tiles) || checkCollision(bed->getBox(), mBox) || checkCollision(table->getBox(), mBox) ) {
        mBox.y -= mVelYNP;
    }

    if( mVelYNP == 0 && mVelXNP == 0 ) {
	    moveState = turnState;
    } 
    else if( mVelYNP != 0 && mVelXNP == 0 ) {
	    if(mVelYNP > 0)
		    moveState = 1; 
	    else 
		    moveState = 0;
    }
    else if( mVelYNP == 0 && mVelXNP != 0 ) {
	    if(mVelXNP > 0) 
		    moveState = 3;
	    else 
		    moveState = 2;
    }
    else if( mVelYNP != 0 && mVelXNP != 0 ) {
	    if(mVelXNP > 0) 
		    moveState = 3;
	    else 
		    moveState = 2;
    }
}

void Chara::setCamera( SDL_Rect& camera )
{
	//Center the camera over the dot
	camera.x = ( mBox.x + DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
	camera.y = ( mBox.y + DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if( camera.x < 0 )
	{ 
		camera.x = 0;
	}
	if( camera.y < 0 )
	{
		camera.y = 0;
	}
	if( camera.x > LEVEL_WIDTH - camera.w )
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if( camera.y > LEVEL_HEIGHT - camera.h )
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

void Chara::render(SDL_Rect& camera, LTexture* gSpriteSheetTexture) {
	if (interactValue) {
	if ( !(mVelY == 0 && mVelX == 0)) {
		switch(moveState) {
			case 0: 
				//Render current frame SDL_Rect* 
				currentClip = &gSpriteClips[ frame ]; 
				gSpriteSheetTexture->render( mBox.x - camera.x, mBox.y - (DOT_HEIGHT / 2) - camera.y, currentClip ); 
				if (count % 10 == 0 && count != 0) 
					++frame; 

				//Cycle animation 
				if( count >= 40 ) 
				{ 
					frame = 0; 
					count = 0; 
				} 
					count++;
					break;
			case 1: 
				currentClip = &gSpriteClips[ frame + 4 ]; 
				gSpriteSheetTexture->render( mBox.x - camera.x, mBox.y - (DOT_HEIGHT / 2) - camera.y, currentClip ); 
				if (count % 10 == 0 && count != 0) 
					++frame; 

				if( count >= 40 ) 
				{ 
					frame = 0; 
					count = 0; 
				} 
					count++;
					break;
			case 2: 
				currentClip = &gSpriteClips[ frame + 8 ]; 
				gSpriteSheetTexture->render( mBox.x - camera.x, mBox.y - (DOT_HEIGHT / 2) - camera.y, currentClip ); 
				if (count % 10 == 0 && count != 0) 
				++frame; 
				if( count >= 40 ) 
				{ 
					frame = 0; 
					count = 0; 
				} 
					count++;
					break;
			case 3:  
				currentClip = &gSpriteClips[ frame + 12 ]; 
				gSpriteSheetTexture->render( mBox.x - camera.x, mBox.y - (DOT_HEIGHT / 2) - camera.y, currentClip ); 
				if (count % 10 == 0 && count != 0) 
					++frame; 

				if( count >= 40 ) 
				{ 
					frame = 0; 
					count = 0; 
				} 
					count++;
					break;

			}
	} else {
		frame = 0; 
		count = 0; 
		switch(moveState) {
			case 0:
				currentClip = &gSpriteClips[ frame ];
				gSpriteSheetTexture->render( mBox.x - camera.x, mBox.y - (DOT_HEIGHT / 2) - camera.y, currentClip );
				break;
			case 1:
				currentClip = &gSpriteClips[ frame + 4 ];
				gSpriteSheetTexture->render( mBox.x - camera.x, mBox.y - (DOT_HEIGHT / 2) - camera.y, currentClip );
				break;
			case 2:
				currentClip = &gSpriteClips[ frame + 8];
				gSpriteSheetTexture->render( mBox.x - camera.x, mBox.y - (DOT_HEIGHT / 2) - camera.y, currentClip );
				break;
			case 3:
				currentClip = &gSpriteClips[ frame + 12];
				gSpriteSheetTexture->render( mBox.x - camera.x, mBox.y - (DOT_HEIGHT / 2) - camera.y, currentClip );
				break;
		}
}
cutsceneTurnState = turnState;
} else {
	turnState = cutsceneTurnState;
	switch(turnState) {
		case 0: currentClip = &gSpriteClips[0]; break;
		case 1: currentClip = &gSpriteClips[4]; break;
		case 2: currentClip = &gSpriteClips[8]; break;
		case 3: currentClip = &gSpriteClips[12]; break;
	}
	gSpriteSheetTexture->render(mBox.x - camera.x, mBox.y - (DOT_HEIGHT / 2) - camera.y, currentClip);
}
}

void Textbox::render(SDL_Rect& camera, std::string string) {
	gTextbox.render( camera.x - camera.x, camera.y - camera.y + mBox.y );
}

void Bed::handleEvent(SDL_Event& e, Chara* chara) {
	if(checkInteract(chara->getBox(), mBox) && !bedMove) {
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			switch(e.key.keysym.sym) {
				case SDLK_z: freeText(&gText);
					     cutscene.talkToBed1(&textbox, e, camera);
					     break;
		}
	}
}
	if(interruptBedMove && hasShownInterruptBed && !bedMove) {
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			switch(e.key.keysym.sym) {
				case SDLK_z: freeText(&gText);
					     cutscene.interruptBed(&textbox, camera); bedMove = 1;
					     break;
		}
	}

}
}

void Chara::renderNP(SDL_Rect& camera, LTexture* gSpriteSheetTexture) {
	if (!(mVelXNP == 0 && mVelYNP == 0)) {
		switch(moveState) {
			case 0: 
				//Render current frame SDL_Rect* 
				currentClip = &gSpriteClips[ frame ]; 
				gSpriteSheetTexture->render( mBox.x - camera.x, mBox.y - (DOT_HEIGHT / 2) - camera.y, currentClip ); 
				if (count % 10 == 0 && count != 0) 
					++frame; 

				//Cycle animation 
				if( count >= 40 ) 
				{ 
					frame = 0; 
					count = 0; 
				} 
					count++;
					break;
			case 1: 
				currentClip = &gSpriteClips[ frame + 4 ]; 
				gSpriteSheetTexture->render( mBox.x - camera.x, mBox.y - (DOT_HEIGHT / 2) - camera.y, currentClip ); 
				if (count % 10 == 0 && count != 0) 
					++frame; 

				if( count >= 40 ) 
				{ 
					frame = 0; 
					count = 0; 
				} 
					count++;
					break;
			case 2: 
				currentClip = &gSpriteClips[ frame + 8 ]; 
				gSpriteSheetTexture->render( mBox.x - camera.x, mBox.y - (DOT_HEIGHT / 2) - camera.y, currentClip ); 
				if (count % 10 == 0 && count != 0) 
				++frame; 
				if( count >= 40 ) 
				{ 
					frame = 0; 
					count = 0; 
				} 
					count++;
					break;
			case 3:  
				currentClip = &gSpriteClips[ frame + 12 ]; 
				gSpriteSheetTexture->render( mBox.x - camera.x, mBox.y - (DOT_HEIGHT / 2) - camera.y, currentClip ); 
				if (count % 10 == 0 && count != 0) 
					++frame; 

				if( count >= 40 ) 
				{ 
					frame = 0; 
					count = 0; 
				} 
					count++;
					break;

			}
	} else {
		frame = 0; 
		count = 0; 
		switch(moveState) {
			case 0:
				currentClip = &gSpriteClips[ frame ];
				gSpriteSheetTexture->render( mBox.x - camera.x, mBox.y - (DOT_HEIGHT / 2) - camera.y, currentClip );
				break;
			case 1:
				currentClip = &gSpriteClips[ frame + 4 ];
				gSpriteSheetTexture->render( mBox.x - camera.x, mBox.y - (DOT_HEIGHT / 2) - camera.y, currentClip );
				break;
			case 2:
				currentClip = &gSpriteClips[ frame + 8];
				gSpriteSheetTexture->render( mBox.x - camera.x, mBox.y - (DOT_HEIGHT / 2) - camera.y, currentClip );
				break;
			case 3:
				currentClip = &gSpriteClips[ frame + 12];
				gSpriteSheetTexture->render( mBox.x - camera.x, mBox.y - (DOT_HEIGHT / 2) - camera.y, currentClip );
				break;
		}
}
}


void Bed::render( SDL_Rect& camera )
{
    //If the tile is on screen
    if( checkCollision( camera, mBox ) )
    {
        //Show the tile
        gBed.render( mBox.x - camera.x, mBox.y - camera.y, &gBedClip[0] );
    }
}

void Table::handleEvent(SDL_Event& e, Chara* chara) {
	if(checkInteract(chara->getBox(), mBox)) {
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			switch(e.key.keysym.sym) {
				case SDLK_z: freeText(&gText);
					     cutscene.talkToTable1(&textbox, e, camera); break;
		}
	}
}
}

void Table::render( SDL_Rect& camera )
{
    //If the tile is on screen
    if( checkCollision( camera, mBox ) )
    {
        //Show the tile
        gTable.render( mBox.x - camera.x, mBox.y - camera.y );
    }
}

void Warp::render( SDL_Rect& camera )
{
    //If the tile is on screen
    if( checkCollision( camera, mBox ) )
    {
        //Show the tile
        gTable.render( mBox.x - camera.x, mBox.y - camera.y );
    }
}

void Warp::handleEvent(SDL_Event& e) {
	if(isFirstCutscene) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch(e.key.keysym.sym) {
			case SDLK_z: freeText(&gText);
				     cutscene.firstCutscene(&textbox, e, camera, &louis); break;
		}
	}
	} 
}

int BattleChara::attack(SDL_Rect& camera, Enemy* enemy) {
	int rng = rand() % 11;
	switch(eqpSwordID) {
		case 1: eqpSwordAtt = 3; break;
	}
	switch(eqpGunID) {
		case 1: eqpGunAtt = 1; break;
	}
	if(withSword) {
		if(rng <= 8 || mDexterity/3 > enemy->getAttack())
			return mStrength + eqpSwordAtt - enemy->getSwordResistance();
		else
			return 0;

	}
	else if(!withSword) {
		if(rng <= 9 || mDexterity/2 > enemy->getAttack())
			return mDexterity + eqpGunAtt - enemy->getGunResistance();
		else
			return 0;
	}
}

LTexture gResponse;
LTexture gLouisHitPoints;
LTexture gMannerPoints;
LTexture gSeme;
LTexture gUke;
std::string runResponse = "NULL";
int i = 0;
int ranNum = 0;
void BattleChara::render(SDL_Rect& camera, Enemy* enemy, SDL_Rect& textbox) {
	gLouisBattleTexture.render(mBox.x - camera.x, mBox.y - camera.y, currentClip);
	std::string n1 = std::to_string(mCurrentHitPoints);
	std::string n2 = std::to_string(mMaxHitPoints);
	std::string print = n1 + "/" + n2;	
	gLouisHitPoints.loadFromRenderedText(print, White, 0, gBattleFont);
	gLouisHitPoints.render(mBox.x - camera.x + mBox.w/8, mBox.y - camera.y + 220);
	//friendBar.x = mBox.x - camera.x; friendBar.y = mBox.y - camera.y + 250;
	//friendBarOutline.x = mBox.x - camera.x; friendBarOutline.y = mBox.y - camera.y + 250;
	gMannerPoints.loadFromRenderedText(std::to_string(mCurrentMannerPoints) + "/" + std::to_string(mMaxMannerPoints), Blue1, 0, gBattleFont);
	gMannerPoints.render(mBox.x - camera.x + mBox.w/8, mBox.y - camera.y + 250);

	if(!(attackPrompt || friendsPrompt || runPrompt || coverPrompt)) {
		currentClip = &gBattleClips[0];
	} else if(attackPrompt) {
		battleTicks++; endTurn = 1;
		currentClip = &gBattleClips[0];
		int semeDamage = attack(camera, enemy);
		std::string semeDamageStr = std::to_string(semeDamage);
		gSeme.loadFromRenderedText(semeDamageStr, White, 0, gBattleFont);
		gSeme.render(enemy->getBox().x - camera.x, enemy->getBox().y - camera.y);
		if(!enemyDie) {
			if(semeDamage != 0)
				responseTxt = enemy->getName() + " took " + semeDamageStr + " damage!"; 
			else
				responseTxt = "Missed!";
			activeResponse = 1;
			if(battleTicks == 60){
				enemy->takeDamage(semeDamage); battleTicks = 0;
				if(enemy->getCrrPoints() > 0) {
					resetBattleState(); louisHasActed = 1; whatToDoPrompt = 0; enemyAct = 1;
				} else {
					enemyDie = 1; activeResponse = 0; freeText(&gText);
				} 
			}

		} else {
			responseTxt = enemy->getDeathMessage(); activeResponse = 1;
			if(battleTicks == 60)
				endBattle = 1;
		}
	} else if(friendsPrompt) {
		battleTicks++; endTurn = 1;
		switch(getAction()) {
			case 1: currentClip = &gBattleClips[0];
				responseTxt = enemy->getDesc(); activeResponse = 1;
				if(battleTicks == 120) {
					resetBattleState(); louisHasActed = 1; whatToDoPrompt = 0; useMaglass = 0; enemyAct = 1;
				}
				break;
			case 2: if(getSklExpenditure(2) >= 0) {
					currentClip = &gBattleClips[0];
					gResponse.loadFromRenderedText("Wetstone.", White, 0, gBattleFont);
					gResponse.render(textbox.w / 2, textbox.y + textbox.h/2 - 5);
					if(battleTicks == 60) {
						sklWetstone();
						resetBattleState(); louisHasActed = 1; whatToDoPrompt = 0; useWetstone = 0; enemyAct = 1;
					}
				} else {
					resetBattleState();
					selectAssist = 1; ySelect = 1;
				}
				break;
		}
	} else if(runPrompt) {
		battleTicks++; endTurn = 1; whatToDoPrompt = 0;
		i = battleTicks / 60;
		if(battleTicks < 180) {
			switch(i) {
				case 0: runResponse = "You look for an opportunity."; break;
				case 1: runResponse = "You look for an opportunity.."; break;
				case 2: runResponse = "You look for an opportunity..."; break;
			}
			gResponse.loadFromRenderedText(runResponse, White, 0, gBattleFont);
			gResponse.render(textbox.w / 3, textbox.y + textbox.h/4);
		} else if(battleTicks >= 180) {
			if(battleTicks == 180) {
				if(mDexterity/2 > enemy->getAttack())
					ranNum = rand()% 20;
				else
					ranNum = rand() % 11 - (enemy->getAttack() / mDexterity);
				if(ranNum >= 5)
					runSuccess = 1;
			} else {
				if(runSuccess) {
					gResponse.loadFromRenderedText("Success.", White, 0, gBattleFont);
					gResponse.render(textbox.w / 3, textbox.y + textbox.h/2 - 5);
					endBattle = 1;
				} else {
					gResponse.loadFromRenderedText("Failed.", White, 0, gBattleFont);
					gResponse.render(textbox.w / 3, textbox.y + textbox.h/2 - 5);
					if(battleTicks == 240) {
						resetBattleState(); louisHasActed = 1;whatToDoPrompt = 0; enemyAct = 1;
					}
				}

			}
		}
	} else if (coverPrompt) {
		battleTicks++; endTurn = 1; whatToDoPrompt = 0;
		responseTxt = "You take cover."; activeResponse = 1;
		if(battleTicks == 60) {
			resetBattleState(); louisHasActed = 1; takingCover = 1; whatToDoPrompt = 0; enemyAct = 1;
		}
	}
}

int enemySeme = 0;
void Enemy::render(SDL_Rect& camera, BattleChara* battleLouis, SDL_Rect& textbox) {
	gEnemyTexture->render(mBox.x - camera.x, mBox.y - camera.y, currentClip);
	if(!enemyAct) {
		currentClip = &gEnemyBattleClips[0];
	} else {
		battleTicks++; endTurn = 1; whatToDoPrompt = 0;
		switch(enemyIdNumber) {
			case 0: enemySeme = attack(battleLouis);
				std::string enemySemeDamageStr = std::to_string(enemySeme);
				responseTxt = "You took " + enemySemeDamageStr + " damage!"; activeResponse = 1;
				if(battleTicks == 60) {
					battleLouis->takeDamage(enemySeme);
					resetBattleState(); enemyHasActed = 1;
				}
				break;
		}
	}
}

bool movedBedTutorialCutscene = 0;
bool tutorialRejectFlag = 0;
void Cutscene::tutorialCutscene(Textbox* textbox, SDL_Rect& camera, Enemy* enemy) {
	isCutscene = 1;
	if(!movedBedTutorialCutscene) {
		enemy->setBox(camera.x - 200, camera.y + 200);
		movedBedTutorialCutscene = 1;
	}
	if(!enemyHasMoved) {
		interactValue = 0; doNotAdvance = 1;
		enemy->moveToXY(camera.x + 50, camera.y + 200, 2);
	} else {
		switch(trigger) {
			case 0:	activeDialogue = 1; doNotAdvance = 0;
				interactValue = 0;
				dialogueText = "This is the BATTLE interface.";
				break;
			case 1: dialogueText = "See those four buttons up there?";
				if(battleTicks != 120) {
					doNotAdvance = 1;
					battleTicks++;
				}
				switch(battleTicks) {
					case 0: xSelect = 0; ySelect = 0; break;
					case 30: xSelect = 1; ySelect = 0; break;
					case 60: xSelect = 1; ySelect = 1; break;
					case 90: xSelect = 0; ySelect = 1; break;
					case 120: xSelect = 0; ySelect = 0;
						  doNotAdvance = 0; break;
				}
				break;
			case 2: battleTicks = 0;
				dialogueText = "They represent the actions you may take during a fight.";
				break;
			case 3: if(!tutorialRejectFlag)
					dialogueText = "Try selecting the ATTACK action first.";				
		        	break;
			case 4: interactValue = 1; activeDialogue = 0; break;
			case 5: if(selectAssist || coverPrompt || runPrompt) {
					dialogueText = "No, not that one. Select the option that says ATTACK."; 
					resetBattleState(); tutorialRejectFlag = 1; interactValue = 0; activeDialogue = 1; trigger = 3;
				} else if(selectWeapon) {
					trigger++;
				}
				break;
			case 6: interactValue = 0; 
				if(battleTicks != 90) {
					doNotAdvance = 1;
					battleTicks++;
				}
				switch(battleTicks) {
					case 0: ySelect = 0; break;
					case 30: ySelect = 1; break;
					case 60: ySelect = 0; break;
					case 90: doNotAdvance = 0; break;
				}
				if(!doNotAdvance) {
					activeDialogue = 1;
					dialogueText = "Enemies will undoubtedly vary in sort and fierceness, but as long as you've got a SWORD and a GUN you can hope to overcome them. I think.";
				}
				break;
			case 7: battleTicks = 0;
				dialogueText = "The damage and effect of an attack depends on an enemy's resistances, the kind of weapon equipped and your dextrousness.";
				break;
			case 8: if(battleTicks != 91)
					battleTicks++;
				switch(battleTicks) {
					case 1: dialogueText = "...what? "; break;
					case 30: dialogueText += "This is all very obvious? "; break;
					case 90: dialogueText += "You could have figured it all out by yourself?"; break;
				}
				break;
			case 9: battleTicks = 0;
				dialogueText = "Well, I don't suppose you want to know what the ASSIST button does?!"; break;
			case 10: if(battleTicks != 90) {
					doNotAdvance = 1; activeDialogue = 0;
					battleTicks++;
				}
				switch(battleTicks) {
					case 1: whatToDoPrompt = 1; 
						resetXYSelect(); 
						selectWeapon = 0; break;
					case 30: xSelect = 0; ySelect = 1; break;
					case 60: resetXYSelect();
						 selectAssist = 1; break;
					case 90: doNotAdvance = 0; activeDialogue = 1; break;
				}
				if(activeDialogue) {
					dialogueText = "You can call some objects you have with you to aid you in battle.";
				}
				 break;
			case 11: battleTicks = 0;
				 dialogueText = "Each time you summon one of them you will spend a certain amount of \"Manner Points\" (MP) trying to convince it to help you."; break;
			case 12: dialogueText = "...what? Why not just ask your weapons to fight by themselves?"; break;
			case 13: dialogueText = "Boy, you sure ask some dumb questions. Why not also bid your shoe to wear itself?"; break;
			case 14: dialogueText = "Let's move on."; break;
			case 15: if(battleTicks != 90) {
					doNotAdvance = 1; activeDialogue = 0;
					battleTicks++;
				}
				switch(battleTicks) {
					case 1: whatToDoPrompt = 1; 
						xSelect = 0; ySelect = 1; 
						selectAssist = 0; break;
					case 30: xSelect = 0; ySelect = 0; break;
					case 60: xSelect = 1; ySelect = 0; break;
					case 90: doNotAdvance = 0; activeDialogue = 1; break;
				}
				if(activeDialogue)
					dialogueText = "Make sure to stand back and take COVER once in a while."; 
				break;
			case 16: xSelect = 1; ySelect = 1;
				 dialogueText = "You can also always RUN away if it gets too dangerous."; break;
			default: resetBattleState(); resetXYSelect(); interactValue = 1; activeDialogue = 0; endBattle = 1; doNotAdvance = 1; inSirohebiCutscene1 = 1; trigger = 0; isTutorial = 0; isCutscene = 0;
			break;
		}
	}
}

void Cutscene::sirohebiCutscene1(Chara* louis, Chara* blanche) {
	interactValue = 0;
	switch(trigger) {
		case 0: louis->setState(0);
			if(!endBattle) {
				activeDialogue = 1; 
				doNotAdvance = 0; 
				dialogueText = "Let's see... I think that's all for explanations.";
			}
			break;
		case 1: if(!success)
				loadFont(50);
			dialogueText = "Help!"; success = 1; break;
		case 2: if(success)
				loadFont(20);
			louis->setState(2); success = 0;
			dialogueText = "...did you hear that? I think it came from that way."; break;
		case 3: dialogueText = "Go investigate that voice. I'll be waiting here."; 
			louis->setState(0); break;
		default: activeDialogue = 0; trigger = 0; inSirohebiCutscene1 = 0; interactValue = 1; sirohebiFlag1 = 1; louis->setState(1); blanche->setPos(420, 140);
	}
}
