#pragma once
#include <easyx.h>

struct EnemyType {
	int HP;//�л�����ֵ
	int width;//�л����
	int height;//�л�����
	int attack;//�л�������
	int speed;//�л��ƶ��ٶ�
	int point;//�л�����
};
//�������С�л�������
EnemyType SMALL = {2, 50, 60, 1, 3, 1};
EnemyType MIDDLE = {5, 80, 100, 2, 2, 2};
EnemyType BIG = {10, 120, 150, 5, 1, 5};

class Enemy
{
public:
	Enemy* next = NULL;
	Enemy* previous = NULL;
	//���췽��
	Enemy(int difficulty) {
		int type = rand() % 100;
		//������ɵл�������
		if (type > 0 && type < 100 - difficulty * 10) {
			this->value = SMALL;
		}
		else if (type > 100 - difficulty * 10 && type < 100 - difficulty * 2) {
			this->value = MIDDLE;
		}
		else {
			this->value = BIG;
		}
		//������ɵл�����λ��
		int x = rand() % (WIDTH - this->value.width);
		this->x = x;
		loadimage(&this->img, _T("./img/enemy_small.jpg"), this->value.width, this->value.height);
		loadimage(&this->img_cover, _T("./img/enemy_small_cover.jpg"), this->value.width, this->value.height);
	}
	//�л���Ⱦͼ�񷽷�
	void render() {
		putimage(this->x, this->y, &this->img_cover, NOTSRCERASE);
		putimage(this->x, this->y, &this->img, SRCINVERT);
	}
	//�л��ƶ�����
	void move(Enemy** lastOne) {
		//�ƶ��л�
		if (this->y + this->value.speed < HEIGHT) {
			this->y += this->value.speed;
		}
		//���л��ƶ�����ͼ��Χ����ݻٶ���
		else {
			this->destroy(lastOne);
		}
	}
	//�л��ݻٶ��󷽷�
	void destroy(Enemy** lastOne) {
		//���ö���ĺ�һ������Ϊ�գ������ö���Ŀǰ�����������һ�����������lastָ��ö������һ��
		if (this->next == NULL) {
			*lastOne = this->previous;
		}
		//ɾ���ö�����Ϊ��ǰ�����ָ��˳��һλ
		if (this->next != NULL) {
			this->next->previous = this->previous;
			//outtextxy(100, 200, _T("next notNUll"));
		}
		if (this->previous != NULL) {
			this->previous->next = this->next;
			//outtextxy(100, 400, _T("previous notNUll"));
		}//��previousΪNULLʱ��bug
		//if (this->previous == NULL && this->next == NULL) {
		//	*lastOne = NULL;
		//}
		//delete this;
	}
	//�л���̬���ɷ���
	static Enemy* create(Enemy* previous, int difficulty) {
		Enemy* enemy = new Enemy(difficulty);
		enemy->previous = previous;
		//�����������ǰһ������Ϊ�գ��򽫸ö���previousָ��ָ��ǰ��
		if (previous != NULL) {
			previous->next = enemy;
		}
		return enemy;
	}
	//�л���ײ����
	int crash(Player* player,Bullet** lastBullet,Enemy** lastOne,Bullet** BulletRub) {
		//�ȼ���Ƿ��������ײ������ײ��ݻٵл����󣬲��۳��������ֵ�����ط���
		if (player != NULL && player->checkPosition(this->x, this->y, this->value.width, this->value.height)) {
			this->destroy(lastOne);//�ݻ��������
			player->deHP(this->value.attack);//��ҿ۳�����ֵ
			return this->value.point;//���ط�ֵ
		}
		//����Ƿ����ӵ���ײ
		Bullet* tmp = *lastBullet;//����һ����ʱָ�봢��ָ����Ϸ�����ԱlastBulletָ���ָ��
		for (;tmp && tmp->previous; tmp = tmp->previous) {
			if (tmp->checkPosition(this->x, this->y, this->value.width, this->value.height)) {
				this->value.HP--;//�л��۳�����ֵ
				tmp->destroy(lastBullet, BulletRub);//�ݻ��ӵ�����
				//���л�����ֵΪ0ʱ���ݻ��������
				if (this->value.HP <= 0) {
					this->destroy(lastOne);
					return this->value.point;//���ط�ֵ
				}
				break;
			}
		}
		return 0;
	}
private:
	int x;//�л�x����
	int y = -100;//�л�y����
	EnemyType value;//�л�����
	IMAGE img;
	IMAGE img_cover;
};

