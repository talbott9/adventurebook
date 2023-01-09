SDL_Rect gBedClip[1];

class Chara;

class Bed {
    public:
		//Initializes the variables
		Bed();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e, Chara* chara );
		void moveToXY(int x, int y, Chara* chara);
		void setPos(int x, int y);

		SDL_Rect getBox();

		//Shows the dot on the screen
		void render(SDL_Rect& camera);
    private:
		//Collision box of the dot
		SDL_Rect mBox;
};

class Table {
    public:
		//Initializes the variables
		Table();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e, Chara* chara );

		SDL_Rect getBox();

		//Shows the dot on the screen
		void render(SDL_Rect& camera);
    private:
		//Collision box of the dot
		SDL_Rect mBox;
};

class Warp {
	public:
		Warp();

		void handleEvent( SDL_Event& e);
		bool checkWarp(Chara* chara, int addRadius);
		SDL_Rect getBox();
		void setWarp(int x, int y, int w, int h);

		void render(SDL_Rect& camera);

	private:
		SDL_Rect mBox;
};
