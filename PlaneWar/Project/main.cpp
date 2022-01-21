#include <easyx.h>
#include <tchar.h>
#include <stdio.h>

#define WIDTH 500
#define HEIGHT 750

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Game.h"


int main(void) {
	Game* game = new Game(WIDTH, HEIGHT);//创建游戏对象
	game->init();//游戏初始化
	return 0;
}