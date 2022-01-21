#pragma once
#include <easyx.h>

struct EnemyType {
	int HP;//敌机生命值
	int width;//敌机宽度
	int height;//敌机长度
	int attack;//敌机攻击力
	int speed;//敌机移动速度
	int point;//敌机分数
};
//定义大中小敌机的属性
EnemyType SMALL = {2, 50, 60, 1, 3, 1};
EnemyType MIDDLE = {5, 80, 100, 2, 2, 2};
EnemyType BIG = {10, 120, 150, 5, 1, 5};

class Enemy
{
public:
	Enemy* next = NULL;
	Enemy* previous = NULL;
	//构造方法
	Enemy(int difficulty) {
		int type = rand() % 100;
		//随机生成敌机的类型
		if (type > 0 && type < 100 - difficulty * 10) {
			this->value = SMALL;
		}
		else if (type > 100 - difficulty * 10 && type < 100 - difficulty * 2) {
			this->value = MIDDLE;
		}
		else {
			this->value = BIG;
		}
		//随机生成敌机产生位置
		int x = rand() % (WIDTH - this->value.width);
		this->x = x;
		loadimage(&this->img, _T("./img/enemy_small.jpg"), this->value.width, this->value.height);
		loadimage(&this->img_cover, _T("./img/enemy_small_cover.jpg"), this->value.width, this->value.height);
	}
	//敌机渲染图像方法
	void render() {
		putimage(this->x, this->y, &this->img_cover, NOTSRCERASE);
		putimage(this->x, this->y, &this->img, SRCINVERT);
	}
	//敌机移动方法
	void move(Enemy** lastOne) {
		//移动敌机
		if (this->y + this->value.speed < HEIGHT) {
			this->y += this->value.speed;
		}
		//若敌机移动到地图范围外则摧毁对象
		else {
			this->destroy(lastOne);
		}
	}
	//敌机摧毁对象方法
	void destroy(Enemy** lastOne) {
		//若该对象的后一个对象为空，则代表该对象目前是链表的最新一个对象，则需把last指向该对象的下一个
		if (this->next == NULL) {
			*lastOne = this->previous;
		}
		//删除该对象则为将前后对象指针顺移一位
		if (this->next != NULL) {
			this->next->previous = this->previous;
			//outtextxy(100, 200, _T("next notNUll"));
		}
		if (this->previous != NULL) {
			this->previous->next = this->next;
			//outtextxy(100, 400, _T("previous notNUll"));
		}//当previous为NULL时出bug
		//if (this->previous == NULL && this->next == NULL) {
		//	*lastOne = NULL;
		//}
		//delete this;
	}
	//敌机静态生成方法
	static Enemy* create(Enemy* previous, int difficulty) {
		Enemy* enemy = new Enemy(difficulty);
		enemy->previous = previous;
		//若创建对象的前一个对象不为空，则将该对象previous指针指向前者
		if (previous != NULL) {
			previous->next = enemy;
		}
		return enemy;
	}
	//敌机碰撞方法
	int crash(Player* player,Bullet** lastBullet,Enemy** lastOne,Bullet** BulletRub) {
		//先检查是否与玩家碰撞，若碰撞则摧毁敌机对象，并扣除玩家生命值，返回分数
		if (player != NULL && player->checkPosition(this->x, this->y, this->value.width, this->value.height)) {
			this->destroy(lastOne);//摧毁自身对象
			player->deHP(this->value.attack);//玩家扣除生命值
			return this->value.point;//返回分值
		}
		//检查是否与子弹碰撞
		Bullet* tmp = *lastBullet;//定义一个临时指针储存指向游戏对象成员lastBullet指针的指针
		for (;tmp && tmp->previous; tmp = tmp->previous) {
			if (tmp->checkPosition(this->x, this->y, this->value.width, this->value.height)) {
				this->value.HP--;//敌机扣除生命值
				tmp->destroy(lastBullet, BulletRub);//摧毁子弹对象
				//当敌机生命值为0时即摧毁自身对象
				if (this->value.HP <= 0) {
					this->destroy(lastOne);
					return this->value.point;//返回分值
				}
				break;
			}
		}
		return 0;
	}
private:
	int x;//敌机x坐标
	int y = -100;//敌机y坐标
	EnemyType value;//敌机属性
	IMAGE img;
	IMAGE img_cover;
};

