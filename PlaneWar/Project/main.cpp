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
	Game* game = new Game(WIDTH, HEIGHT);//������Ϸ����
	game->init();//��Ϸ��ʼ��
	return 0;
}