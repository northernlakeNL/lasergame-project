#pragma once

enum class GunState {IDLE, SHOOT, RELOAD};
enum class GameState{IDLE,RECEIVE, SETTINGS, PREGAME, GAME, SEND, FINISH};
enum class DisplayState {SETTINGS, PREGAME, GAME, FINISH};
enum class MenuState {IDLE, MENU, BULLETS, LIVES, PLAYER_COUNT, PLAY_TIME};
enum class DisplayMenuState {IDLE, MENU, RECEIVE, BULLETS, LIVES, PLAYER_COUNT, PLAY_TIME, DONE, ERROR, GAME, FINISH};
enum class BeeperState{ IDLE, SHOOT, RELOAD, EMPTY_CLIP, HIT };
