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
static const char empty_string[] = "";

// like strdup but returns NULL if s is NULL,
// and does not allocate if s is an empty string
// (as a result yoiu cant modify the resulting string and you shouldnt free it
//  yes this may cause memmory leak over long period of time)
static const char *const_strdup(const char *s) {
	if (!s) return NULL;
	if (!*s) return empty_string;
	return SDL_strdup(s);
}

static void copy_state_from_game(State *to) {
	to->graphics = graphics;
	to->music = music;
	to->game = game;
	to->key = key;
	to->map = map;
	to->obj = obj;
	to->gameScreen = gameScreen;
	
	mapclass *map = &to->map;
	// leaky time!!
	map->roomname = const_strdup(map->roomname);
	map->hiddenname = const_strdup(map->hiddenname);
}

static void copy_state_to_game(const State *state) {
	graphics = state->graphics;
	music = state->music;
	game = state->game;
	key = state->key;
	map = state->map;
	obj = state->obj;
	gameScreen = state->gameScreen;
}

void save_state(void) {
	copy_state_from_game(&save);
}

void load_state(void) {
	copy_state_to_game(&save);
}
