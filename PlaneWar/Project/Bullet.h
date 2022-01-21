#pragma once
#include <stdlib.h>
#include <easyx.h>

class Bullet
{
public:
	Bullet* next;//ָ���һ�ŷ�����ӵ�
	Bullet* previous;//ָ��ǰһ�ŷ�����ӵ�
	Bullet(){}//����Ĭ�Ϲ��캯��
	//���췽��
	Bullet(int x, int y) {
		this->x = x;
		this->y = y;
		this->next = NULL;
		this->previous = NULL;
		loadimage(&this->img, _T("./img/bullet.jpg"), this->width, this->height);
	}
	//�ӵ��ƶ�����
	void move(Bullet** lastOne, Bullet** rub) {
		//�ı��ӵ�λ��
		if (this->y - this->speed + this->height >  - this->height) {
			this->y -= this->speed;
		}
		else {
			//���ӵ��ƶ����߽�ʹݻٵ�ǰ����
			this->destroy(lastOne, rub);
		}
	}
	//�ӵ���Ⱦͼ�񷽷�
	void render() {
		putimage(this->x, this->y, &this->img);
	}
	//�ӵ��ݻٶ��󷽷�
	void destroy(Bullet** lastOne, Bullet** rub) {
		//���ö���ĺ�һ������Ϊ�գ������ö���Ŀǰ�����������һ�����������lastָ��ö������һ��
		if (this->next == NULL) {
			*lastOne = this->previous;
		}
		//ɾ���ö�����Ϊ��ǰ�����ָ��˳��һλ
		if (this->next != NULL) {
			this->next->previous = this->previous;
		}
		if (this->previous != NULL) {
			this->previous->next = this->next;
		}
		//*rub = this;
		/*delete this;*/
	}
	//��̬�����ӵ�����
	static Bullet* create(Bullet* previous, int x, int y) {
		Bullet* bull = new Bullet(x, y);
		//�����������ǰһ������Ϊ�գ��򽫸ö���previousָ��ָ��ǰ��
		if (previous != NULL) {
			bull->previous = previous;
			previous->next = bull;
		}
		return bull;
	}
	//�����ײ����
	bool checkPosition(int x, int y, int width, int height) {
		if (this->x+this->width > x && this->x < x+width && this->y+this->height > y && this->y < y+height) {
			return true;
		}else {
			return false;
		}
	}
private:
	int x;//�ӵ�x����
	int y;//�ӵ�y����
	int width = 7;//�ӵ����
	int height = 20;//�ӵ�����
	int speed = 10;//�ӵ��ƶ��ٶ�
	IMAGE img;
	//static IMAGE img_cover;
};
