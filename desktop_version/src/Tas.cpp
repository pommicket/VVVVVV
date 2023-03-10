#include "Entity.h"
#include "Map.h"
#include "Graphics.h"
#include "Screen.h"
#include "Music.h"
#include "KeyPoll.h"

typedef struct {
	Graphics graphics;
	musicclass music;
	Game game;
	KeyPoll key;
	mapclass map;
	entityclass obj;
	Screen gameScreen;
} State;

static State save;

static void copy_state_from_game(State *to) {
	to->graphics = graphics;
	to->music = music;
	to->game = game;
	to->key = key;
	to->map = map;
	to->obj = obj;
	to->gameScreen = gameScreen;
}

static void copy_state_to_game(const State *state) {
	graphics = state->graphics;
	music = state->music;
	game = state->game;
	key = state->key;
	map = state->map;
	obj = state->obj;
	gameScreen = state->gameScreen;
	map.gotoroom(game.roomx, game.roomy);
}

void save_state(void) {
	copy_state_from_game(&save);
}

void load_state(void) {
	copy_state_to_game(&save);
}
