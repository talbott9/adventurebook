adventurebook: adventurebook.cpp tiling.h louis.h louis.cpp enemy.h enemy.cpp renderer.h renderer.cpp level1.cpp convert.cpp cutscenes.cpp cutscenes.h button.h button.cpp objects.h objects.cpp collision.cpp battle.h battle.cpp text.h text.cpp
	g++ adventurebook.cpp -w -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o adventurebook 
	g++ convert.cpp -w -o convert
