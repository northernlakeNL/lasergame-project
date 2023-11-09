#pragma once

enum class GunState {IDLE, SHOOT, RELOAD};
enum class GameState{IDLE, SETTINGS, GAME, SEND, FINISH, RECEIVE};
enum class DisplayState {SETTINGS, GAME, FINISH};
enum class MenuState {IDLE, MENU, BULLETS, LIVES, PLAYER_COUNT, PLAY_TIME};
enum class DisplayMenuState {IDLE, MENU, RECEIVE, BULLETS, LIVES, PLAYER_COUNT, PLAY_TIME, DONE, ERROR, GAME, FINISH};
enum class BeeperState{ IDLE, SHOOT, RELOAD, EMPTY_CLIP, HIT };
