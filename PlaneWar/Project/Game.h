#pragma once
#include <stdlib.h>
#include <easyx.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#include "Player.h"

class Game
{
public:
	int point = 0;//��Ϸ�÷�
	//���캯��
	Game(int width, int height) {
		this->width = width;
		this->height = height;
		this->mode = 0;
		this->startImg = NULL;
		this->backgroundImg = NULL;
	}
	//��ʼ����ͼ
	void init() {
		srand((unsigned)time(NULL));//��ʼ�����������
		initgraph(this->width, this->height);//��ʼ����ͼ����
		loadimage(&this->startImg, _T("./img/title.jpg"));//���ؿ�ʼ����ͼƬ
		loadimage(&this->backgroundImg, _T("./img/background.jpg"));//������Ϸ����ͼƬ
		putimage(0, 0, &this->startImg);//���ƿ�ʼ����ͼƬ
		//���������ʾ
		TCHAR title[] = _T("���¿ո��������Ϸ");
		outtextxy(this->width/2 - textwidth(title)/2, this->height/2, title);
		//ѭ������ ���¿ո������Ϸѡ�����
		while (1) {
			if (_kbhit()) {
				if (GetAsyncKeyState(VK_SPACE)) {
					break;
				}
			}
		}
		cleardevice();//�����Ļ
		LOGFONT f;//���������ʽ����
		gettextstyle(&f);//��ȡ��ǰ������ʽ
		int theight = 35;//�趨һ�������С
		f.lfHeight = theight;//ѡ����Ϸģʽʱ�Ŵ�����
		settextstyle(&f);//����������ʽ
		RECT r = { 0, 0, WIDTH - 1, HEIGHT - 1 };//�������ַ�Χ����
		TCHAR t[] = _T("\n\n\nѡ����Ϸģʽ");
		drawtext(t, &r, DT_CENTER);//���ѡ������

		TCHAR t1[] = _T("����ģʽ");
		RECT r1 = { 0, 300, WIDTH - 1, HEIGHT - 1 };
		drawtext(t1, &r1, DT_CENTER);

		TCHAR t2[] = _T("˫��ģʽ");
		RECT r2 = { 0, 350, WIDTH - 1, HEIGHT - 1 };
		drawtext(t2, &r2, DT_CENTER);

		TCHAR t3[] = _T("���а�");
		RECT r3 = { 0, 400, WIDTH - 1, HEIGHT - 1 };
		drawtext(t3, &r3, DT_CENTER);
		f.lfHeight = 10;//�ָ������С
		settextstyle(&f);//����������ʽ
		//ѭ������ ��ȡ��Ϸѡ��
		//ѭ������ѡ��ѡ���¼�
		while (1) {			
			setlinecolor(WHITE);
			ExMessage mouse = getmessage(EM_MOUSE);//��ȡ����¼�
			if (mouse.y>=300 && mouse.y<=300+theight && mouse.x>=(WIDTH/2-textwidth(t1)) && mouse.x <=(WIDTH/2+textwidth(t1))) {
				rectangle(WIDTH / 2 - textwidth(t1), 300, WIDTH / 2 + textwidth(t1), 300 + theight);//��������������ʱ�ı߿�
				//��Ⱦѡ��Ч��
				if (mouse.lbutton) {
					this->mode = 1;
					this->player_num = mode;
					this->WIN = player_num;
					start(1);
					break;
				}
			}
			else if (mouse.y >= 350 && mouse.y <= 350 + textheight(t2) && mouse.x >= (WIDTH / 2 - textwidth(t2)) && mouse.x <= (WIDTH / 2 + textwidth(t2))) {
				rectangle(WIDTH / 2 - textwidth(t2), 350, WIDTH / 2 + textwidth(t2), 350 + theight);//��������������ʱ�ı߿�
				//��Ⱦѡ��Ч��
				if (mouse.lbutton) {
					this->mode = 2;
					this->player_num = mode;
					this->WIN = player_num;
					start(2);
					break;
				}
			}
			else if (mouse.y >= 400 && mouse.y <= 400 + textheight(t3) && mouse.x >= (WIDTH / 2 - textwidth(t3)) && mouse.x <= (WIDTH / 2 + textwidth(t3))) {
				rectangle(WIDTH / 2 - textwidth(t3), 400, WIDTH / 2 + textwidth(t3), 400 + theight);//��������������ʱ�ı߿�
				//��Ⱦѡ��Ч��
				if (mouse.lbutton) {
					this->mode = 3;
					showPoint();
				}
			}
			else {
				//�ú�ɫ�߿򸲸Ǳ�ѡ�к���ʾ�İ�ɫ�߿�
				setlinecolor(BLACK);
				rectangle(WIDTH / 2 - textwidth(t1), 300, WIDTH / 2 + textwidth(t1), 300 + theight);
				rectangle(WIDTH / 2 - textwidth(t2), 350, WIDTH / 2 + textwidth(t2), 350 + theight);
				rectangle(WIDTH / 2 - textwidth(t3), 400, WIDTH / 2 + textwidth(t3), 400 + theight);
			}
		}
	}
	//��Ϸ��ʼ����
	void start(int player_num) {
		this->drawBackground();//����Ⱦһ�α���ͼƬ
		//��ʼ��
		for (int i = 0; i < player_num;i ++) {
			Player* player = new Player(this->width/(3 - i), this->height - 110, i + 1);
			//��ʼ������ҷɻ�
			this->players[i] = player;
			this->players[i]->render();
			//��ʼ�����ӵ����������ûɶ��
			//Bullet* bull = new Bullet(this->players[i]->x + 25, this->players[i]->y - 20);
			//this->lastBullet[i] = bull;
			//��ʼ���ɵл�
			/*Enemy* enemy = new Enemy(this->difficulty);
			this->lastEnemy = enemy;*/
		}
		process(player_num);
	}
	//��Ϸ���й��̷���
	void process(int player_num) {
		BeginBatchDraw();//��ʼ������ͼ��������˸
		int t = 0;//����һ���������������ѭ����������
		while (1)
		{
			//����������Ҷ���
			if (_kbhit()) {
				if (GetAsyncKeyState(VK_SPACE)) {
					if (this->skill >= 10) {
						Boom();
					}
				}
				else {
					for (int i = 0; i < player_num; i++) {
						if (this->players[i] != NULL && this->players[i]->getHP() > 0) {
							this->players[i]->control(this->player_num);
						}
					}
				}
			}
			//ÿһ������������һ���ӵ�
			if (t % 10 == 0) {
				for (int i = 0; i < player_num; i++) {
					if (this->players[i] != NULL) {
						this->lastBullet[i] = Bullet::create(this->lastBullet[i], this->players[i]->x + 36.5, this->players[i]->y - 20);
					}
				}
			}
			
			drawBackground();//�ñ���ͼƬ���Ǵ����Ա����»�ͼ

			//��һ�����ڴ���л�
			if (t % this->interval == 0) {
				this->lastEnemy = Enemy::create(this->lastEnemy, this->difficulty);
				t = 0;
			}

			this->moveEnemy();//�ƶ����е���
			this->renderEnemy();//�������е���
			//ѭ��������ͼ
			for (int i = 0; i < player_num; i++) {
				if (this->players[i] != NULL && this->players[i]->getHP() > 0) {
					this->players[i]->render();
					this->moveBullet(i);//�ƶ������ӵ�
					this->renderBullet(i);//���������ӵ�
				}
			}
			showInfo(player_num, this->players);//��ʾ��Ϸ��Ϣ
			checkDifficulty();
			checkEnd();
			FlushBatchDraw();//�����Ƶ�ͼ��һ���Լ��ص����ƴ���
			t++;
			Sleep(1);
			removeRub();
		}
	}
	//���Ʊ���ͼƬ����
	void drawBackground() {
		putimage(0, 0, &this->backgroundImg);
		//SetWorkingImage(&this->backgroundImg);
	}
	//�����ƶ��ӵ�����
	void moveBullet(int player) {
		Bullet* lastOne = this->lastBullet[player];
		while (lastOne != NULL){
			lastOne->move(&this->lastBullet[player], &this->BulletRub);
			lastOne = lastOne->previous;
		}
	}
	//�����ƶ��л�����
	void moveEnemy() {
		Enemy* lastOne = this->lastEnemy;
		while (lastOne != NULL) {
			lastOne->move(&this->lastEnemy);
			for (int i = 0; i < this->player_num;i ++) {
				int p = lastOne->crash(this->players[i], &this->lastBullet[i], &this->lastEnemy, &this->BulletRub);
				this->point += p;
				this->skill += p;
			}
			lastOne = lastOne->previous;
		}
	}
	//���������ӵ�����
	void renderBullet(int player) {
		Bullet* lastOne = this->lastBullet[player];
		while (lastOne != NULL) {
			lastOne->render();
			lastOne = lastOne->previous;
		}
	}
	//�������Ƶл�����
	void renderEnemy() {
		Enemy* lastOne = this->lastEnemy;
		while (lastOne != NULL) {
			lastOne->render();
			lastOne = lastOne->previous;
		}
	}
	//��鲢������Ϸ�Ѷ�
	void checkDifficulty() {
		this->difficulty = this->point / (30/this->player_num) + 1;
		if (this->interval >= 30) {
			this->interval -= this->point / 60 * 5 * this->player_num;
		}
	}
	//��ʾ��Ϸ��Ϣ
	void showInfo(int player_num, Player** players) {
		TCHAR hp[10];
		for (int i = 0; i < player_num;i ++) {
			if (players[i] != NULL) {
				_itow_s(players[i]->getHP(), hp, 10);
				if (i == 0) {
					outtextxy(0, 0, _T("Player1 ����ֵ��"));
					outtextxy(100, 0, hp);
				}
				else if (i == 1) {
					outtextxy(WIDTH - 120, 0, _T("Player2 ����ֵ��"));
					outtextxy(WIDTH - 20, 0, hp);
				}
			}
		}
		TCHAR point[5];
		_itow_s(this->point, point, 10);
		outtextxy(0, 30, _T("�÷֣�"));
		outtextxy(50, 30, point);
		TCHAR dif[5];
		_itow_s(this->difficulty, dif, 10);
		outtextxy(0, 100, _T("�Ѷȣ�"));
		outtextxy(50, 100, dif);
		TCHAR skill[10];
		_itow_s(this->skill, skill, 10);
		outtextxy(0, 150, _T("���ܵ㣺"));
		outtextxy(50, 150, skill);
		outtextxy(0, HEIGHT - 20, _T("���¿ո��ͷż���(����10���ܵ�)"));
	}
	//�����Ϸ��������
	void checkEnd() {
		for (int i = 0; i < this->player_num;i ++) {
			if (this->players[i] != NULL && this->players[i]->getHP() <= 0) {
				this->players[i] = NULL;
				WIN--;
			}
			if (WIN <= 0) {
				savePoint();
				this->end();
			}
		}
	}
	//��Ϸ����
	void end() {
		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 40;
		settextstyle(&f);
		RECT r = { 0, 0, 499, 749 };//�������ַ�Χ����
		drawtext(_T("\n\n\n��Ϸ����\n���¿ո�ص���ʼ����"), &r, DT_CENTER);
		FlushBatchDraw();
		while (1)
		{
			if (GetAsyncKeyState(VK_SPACE)) {
				closegraph();
				break;
			}
		}
		//���¿ո����»ص���Ϸ��ʼ����
		EndBatchDraw();
		//delete this;
		Game* new_game = new Game(500, 750);
		new_game->init();
	}
	//�ͷż��ܷ���
	void Boom() {
		lastEnemy = NULL;
		loadimage(&this->boomimg, _T("./img/boom_a.jpg"), 500, 240);
		loadimage(&this->boomimgback, _T("./img/boom_b.jpg"), 500, 240);
		putimage(0, 180, &this->boomimgback, NOTSRCERASE);
		putimage(0, 180, &this->boomimg, SRCINVERT);
		FlushBatchDraw();
		this->skill -= 10;
		Sleep(1000);
	}
	//�����¼��ֵ����
	void savePoint() {
		FILE* fp = NULL;//�����ļ�ָ��
		errno_t err;//����һ������
		err = fopen_s(&fp, "./data/rank.txt", "a+");//�򿪴���������ļ�
		if (err != 0)
		{
			puts("Ҫд����ļ�������������˳�");
			getchar();
			exit(0);
		}
		else {
			char ax[10];//����Ҫ������ַ���
			_itoa_s(this->point, ax, 10);//������ת��Ϊ�ַ���
			strcat_s(ax, "\n\0");//ƴ��һ�����з����ַ���������
			fputs(ax, fp);//д���ļ�
			//char a[10];
			//while (fgets(a, 9, fp) != NULL) {
			//	printf("%s", a);
			//}
		}
		fclose(fp);//�رմ򿪵��ļ�
	}
	//�����а���ʾ����
	void showPoint() {
		FILE* fp = NULL;
		errno_t err;
		err = fopen_s(&fp, "./data/rank.txt", "r");
		if (err != 0)
		{
			puts("Ҫд����ļ�������������˳�");
			getchar();
			exit(0);
		}
		else {
			cleardevice();//�����Ļ
			LOGFONT f;//���������ʽ����
			gettextstyle(&f);//��ȡ��ǰ������ʽ
			int theight = 35;//�趨һ�������С
			f.lfHeight = theight;//�Ŵ�����
			settextstyle(&f);//����������ʽ
			RECT r = { 0, 0, WIDTH - 1, HEIGHT - 1 };//�������ַ�Χ����
			TCHAR t[] = _T("\n\n\n�������а�");
			drawtext(t, &r, DT_CENTER);//���ѡ������
			char charPoint[5] = "0";//����һ���ַ��������ȡ���ַ���
			int points[1000];//������������������ת���õ��ķ���
			//��ȡ���������һ������
			for (int i = 0; fgets(charPoint, 9, fp) != NULL; i++) {
				points[i] = atoi(charPoint);//���ַ���ת��Ϊ���ַ�����������
			}
			//��������������,ʹ�ò�������
			int tmp;//����һ���ݴ���
			int j;//�ڲ�ѭ����
			for (int i = 1; i < 1000; i++)
			{
				tmp = points[i];
				for (j = i - 1; j >= 0 && points[j] < tmp; j--)
				{
					points[j + 1] = points[j];
				}
				points[j + 1] = tmp;
			}

			//��������������а�
			for (int i = 0; i < 10;i ++) {
				char text[1000] = "No.";//����һ���ַ�����ͷ
				char rank[5];//����һ���ַ�������ʾ����
				_itoa_s(i + 1, rank, 10);//����ǰ����ת��Ϊ�ַ���
				strcat_s(text, rank);//ƴ�ӱ�ͷ���ַ���
				char space[] = ":  ";//����һ���ո��ַ������Ű�
				strcat_s(text, space);//����ǰ�ĺͿո�
				char point[15];//����һ���ַ����Դ���ת���õ��ķ���
				_itoa_s(points[i], point, 10);
				strcat_s(text, point);//����ǰ�ĺͷ���
				RECT r0 = { 0, 300 + i * 40, WIDTH - 1, HEIGHT - 1 };//����һ����ͼ����
				drawtext(charToTchar(text), &r0, DT_CENTER);//���ѡ������
			}
			outtextxy(10, 10, _T("����"));//����һ�����ذ�ť
			//�˴�ͬinit��������
			while (true)
			{
				setlinecolor(WHITE);
				ExMessage mes = getmessage(EM_MOUSE);
				if (mes.y>0 && mes.y<45 && mes.x>0 && mes.x<45) {
					rectangle(5, 5, 80, 45);
					if (mes.lbutton) {
						this->init();
					}
				}
				else {
					setlinecolor(BLACK);
					rectangle(5, 5, 80, 45);
				}
			}
		}
		fclose(fp);//�ر��ļ�
	}
	//��char*���ͱ���ת��ΪTCHAR���ͱ���
	wchar_t* charToTchar(char* str) {
		char* CStr = (char*)str;
		size_t len = strlen(CStr) + 1;
		size_t converted = 0;
		wchar_t* WStr;
		WStr = (wchar_t*)malloc(len * sizeof(wchar_t));
		mbstowcs_s(&converted, WStr, len, CStr, _TRUNCATE);
		return WStr;
	}
	//ɾ������
	void removeRub() {
		//*this->BulletRub = NULL;
	}

private:
	int skill;//���ܵ�
	int WIN = 0;//�����Ϸ�Ƿ�����ı���
	int width;//��Ϸ������
	int height;//��Ϸ����߶�
	int mode = 0;//��Ϸģʽ
	int interval = 60;//���ֵл�ʱ����
	int player_num = 0;//�������
	int difficulty = 1;//��Ϸ�Ѷ�ϵ��
	Bullet* lastBullet[2];//Ŀǰ���ڵ��������ӵ�ָ��
	Bullet* BulletRub;//�ӵ���������
	Enemy* lastEnemy;//Ŀǰ���ڵ������ֵĵл�
	Player* players[2];//��Ҷ�������������
	IMAGE startImg;//��ʼ����ͼƬ
	IMAGE backgroundImg;//����ͼƬ
	IMAGE boomimg;
	IMAGE boomimgback;
};
