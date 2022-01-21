#pragma once
#include <stdlib.h>
#include <string.h>

class Player
{
public:
	int x;//���x����
	int y;//���y����
	Player() {}//����Ĭ�Ϲ��캯��
	//���췽��
	Player(int x, int y, int num) {
		this->x = x;
		this->y = y;
		this->num = num;
		loadimage(&this->img, _T("./img/plane_a.jpg"), this->width, this->height);
		loadimage(&this->img_cover, _T("./img/plane_b.jpg"), this->width, this->height);
	}
	//��ȡ�������ֵ����
	int getHP() {
		return this->HP;
	}
	//�۳��������ֵ����
	void deHP(int attack) {
		this->HP -= attack;
	}
	//��Ⱦͼ�񷽷�
	void render() {
		putimage(this->x, this->y, &this->img_cover, NOTSRCERASE);
		putimage(this->x, this->y, &this->img, SRCINVERT);
	}
	//����������
	void control(int mode) {//�����¿ո�ʱ�ͷż���
		if (GetAsyncKeyState(VK_ESCAPE)) {//������ESCʱ����

		}
		else {
			this->move(mode);//��������Ϊ�ո��ESC��Ϊ��������ƶ�
		}
	}
	//����ƶ�����
	void move(int mode) {
		//��ͬģʽ�¿��Ƽ�λ��ͬ
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
	//����Ƿ���ײ
	bool checkPosition(int x, int y, int width, int height) {
		if (this->x + this->width > x && this->x < x + width && this->y + this->height > y && this->y < y + height) {
			return true;
		}
		else {
			return false;
		}
	}
private:
	int HP = 20;//�������ֵ
	int width = 76;//�����ͼ���
	int height = 110;//�����ͼ����
	int num;//��ұ��
	int speed = 5;//�ƶ��ٶ�
	IMAGE img;//��ͼ
	IMAGE img_cover;//��ͼ����
};
