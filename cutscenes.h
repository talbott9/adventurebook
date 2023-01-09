class Cutscene {
	public:
		void talkToBed1(Textbox* textbox, SDL_Event& e, SDL_Rect& camera);
		void talkToTable1(Textbox* textbox, SDL_Event& e, SDL_Rect& camera);
		void firstCutscene(Textbox* textbox, SDL_Event& e, SDL_Rect& camera, Chara* louis);
		void interruptBed(Textbox* textbox, SDL_Rect& camera);
		void render( SDL_Rect& camera );
		void handleEvent(SDL_Event& e);
		void tutorialCutscene(Textbox* textbox, SDL_Rect& camera, Enemy* enemy);
		void sirohebiCutscene1(Chara* louis, Chara* blanche);
		void hallCutscene1(Chara* louis, Chara* blanche, Bed* bed, Table* table, Tile** tileSet);
	private:
};
