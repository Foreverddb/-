#pragma once
#include <stdlib.h>
#include <string.h>

class Player
{
public:
	int x;//玩家x坐标
	int y;//玩家y坐标
	Player() {}//保留默认构造函数
	//构造方法
	Player(int x, int y, int num) {
		this->x = x;
		this->y = y;
		this->num = num;
		loadimage(&this->img, _T("./img/plane_a.jpg"), this->width, this->height);
		loadimage(&this->img_cover, _T("./img/plane_b.jpg"), this->width, this->height);
	}
	//获取玩家生命值方法
	int getHP() {
		return this->HP;
	}
	//扣除玩家生命值方法
	void deHP(int attack) {
		this->HP -= attack;
	}
	//渲染图像方法
	void render() {
		putimage(this->x, this->y, &this->img_cover, NOTSRCERASE);
		putimage(this->x, this->y, &this->img, SRCINVERT);
	}
	//按键控制器
	void control(int mode) {//当按下空格时释放技能
		if (GetAsyncKeyState(VK_ESCAPE)) {//当按下ESC时返回

		}
		else {
			this->move(mode);//若按键不为空格或ESC则为控制玩家移动
		}
	}
	//玩家移动方法
	void move(int mode) {
		//不同模式下控制键位不同
		if (mode == 1) {
			if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) {
				if (this->y - speed > 0) {
					this->y -= speed;
				}
			}
			if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) {
				if (this->y + speed < HEIGHT - height) {
					this->y += speed;
				}
			}
			if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) {
				if (this->x - speed > -25) {
					this->x -= speed;
				}
			}
			if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) {
				if (this->x + speed < WIDTH - width+24) {
					this->x += speed;
				}
			}
		}
		else if (mode == 2) {
			if (this->num == 1) {
				if (GetAsyncKeyState('W')) {
					if (this->y - speed > 0) {
						this->y -= speed;
					}
				}
				if (GetAsyncKeyState('S')) {
					if (this->y + speed < HEIGHT - height) {
						this->y += speed;
					}
				}
				if (GetAsyncKeyState('A')) {
					if (this->x - speed > -25) {
						this->x -= speed;
					}
				}
				if (GetAsyncKeyState('D')) {
					if (this->x + speed < WIDTH - width+24) {
						this->x += speed;
					}
				}
			}
			else if (this->num == 2) {
				if (GetAsyncKeyState(VK_UP)) {
					if (this->y - speed > 0) {
						this->y -= speed;
					}
				}
				if (GetAsyncKeyState(VK_DOWN)) {
					if (this->y + speed < HEIGHT - height) {
						this->y += speed;
					}
				}
				if (GetAsyncKeyState(VK_LEFT)) {
					if (this->x - speed > -25) {
						this->x -= speed;
					}
				}
				if (GetAsyncKeyState(VK_RIGHT)) {
					if (this->x + speed < WIDTH - width+24) {
						this->x += speed;
					}
				}
			}
		}
	}
	//检查是否碰撞
	bool checkPosition(int x, int y, int width, int height) {
		if (this->x + this->width > x && this->x < x + width && this->y + this->height > y && this->y < y + height) {
			return true;
		}
		else {
			return false;
		}
	}
private:
	int HP = 20;//玩家生命值
	int width = 76;//玩家贴图宽度
	int height = 110;//玩家贴图长度
	int num;//玩家编号
	int speed = 5;//移动速度
	IMAGE img;//贴图
	IMAGE img_cover;//贴图遮罩
};
