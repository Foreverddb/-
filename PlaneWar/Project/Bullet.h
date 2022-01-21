#pragma once
#include <stdlib.h>
#include <easyx.h>

class Bullet
{
public:
	Bullet* next;//指向后一颗发射的子弹
	Bullet* previous;//指向前一颗发射的子弹
	Bullet(){}//保留默认构造函数
	//构造方法
	Bullet(int x, int y) {
		this->x = x;
		this->y = y;
		this->next = NULL;
		this->previous = NULL;
		loadimage(&this->img, _T("./img/bullet.jpg"), this->width, this->height);
	}
	//子弹移动方法
	void move(Bullet** lastOne, Bullet** rub) {
		//改变子弹位置
		if (this->y - this->speed + this->height >  - this->height) {
			this->y -= this->speed;
		}
		else {
			//若子弹移动出边界就摧毁当前对象
			this->destroy(lastOne, rub);
		}
	}
	//子弹渲染图像方法
	void render() {
		putimage(this->x, this->y, &this->img);
	}
	//子弹摧毁对象方法
	void destroy(Bullet** lastOne, Bullet** rub) {
		//若该对象的后一个对象为空，则代表该对象目前是链表的最新一个对象，则需把last指向该对象的下一个
		if (this->next == NULL) {
			*lastOne = this->previous;
		}
		//删除该对象则为将前后对象指针顺移一位
		if (this->next != NULL) {
			this->next->previous = this->previous;
		}
		if (this->previous != NULL) {
			this->previous->next = this->next;
		}
		//*rub = this;
		/*delete this;*/
	}
	//静态创建子弹对象
	static Bullet* create(Bullet* previous, int x, int y) {
		Bullet* bull = new Bullet(x, y);
		//若创建对象的前一个对象不为空，则将该对象previous指针指向前者
		if (previous != NULL) {
			bull->previous = previous;
			previous->next = bull;
		}
		return bull;
	}
	//检查碰撞方法
	bool checkPosition(int x, int y, int width, int height) {
		if (this->x+this->width > x && this->x < x+width && this->y+this->height > y && this->y < y+height) {
			return true;
		}else {
			return false;
		}
	}
private:
	int x;//子弹x坐标
	int y;//子弹y坐标
	int width = 7;//子弹宽度
	int height = 20;//子弹长度
	int speed = 10;//子弹移动速度
	IMAGE img;
	//static IMAGE img_cover;
};
