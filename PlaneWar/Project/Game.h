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
	int point = 0;//游戏得分
	//构造函数
	Game(int width, int height) {
		this->width = width;
		this->height = height;
		this->mode = 0;
		this->startImg = NULL;
		this->backgroundImg = NULL;
	}
	//初始化绘图
	void init() {
		srand((unsigned)time(NULL));//初始化随机数种子
		initgraph(this->width, this->height);//初始化绘图窗口
		loadimage(&this->startImg, _T("./img/title.jpg"));//加载开始界面图片
		loadimage(&this->backgroundImg, _T("./img/background.jpg"));//加载游戏背景图片
		putimage(0, 0, &this->startImg);//绘制开始界面图片
		//输出标题提示
		TCHAR title[] = _T("按下空格键进入游戏");
		outtextxy(this->width/2 - textwidth(title)/2, this->height/2, title);
		//循环监听 按下空格进入游戏选择界面
		while (1) {
			if (_kbhit()) {
				if (GetAsyncKeyState(VK_SPACE)) {
					break;
				}
			}
		}
		cleardevice();//清空屏幕
		LOGFONT f;//声明字体格式变量
		gettextstyle(&f);//获取当前字体样式
		int theight = 35;//设定一个字体大小
		f.lfHeight = theight;//选择游戏模式时放大字体
		settextstyle(&f);//设置字体样式
		RECT r = { 0, 0, WIDTH - 1, HEIGHT - 1 };//定义文字范围矩形
		TCHAR t[] = _T("\n\n\n选择游戏模式");
		drawtext(t, &r, DT_CENTER);//输出选项文字

		TCHAR t1[] = _T("单人模式");
		RECT r1 = { 0, 300, WIDTH - 1, HEIGHT - 1 };
		drawtext(t1, &r1, DT_CENTER);

		TCHAR t2[] = _T("双人模式");
		RECT r2 = { 0, 350, WIDTH - 1, HEIGHT - 1 };
		drawtext(t2, &r2, DT_CENTER);

		TCHAR t3[] = _T("排行榜");
		RECT r3 = { 0, 400, WIDTH - 1, HEIGHT - 1 };
		drawtext(t3, &r3, DT_CENTER);
		f.lfHeight = 10;//恢复字体大小
		settextstyle(&f);//设置字体样式
		//循环监听 获取游戏选项
		//循环监听选项选择事件
		while (1) {			
			setlinecolor(WHITE);
			ExMessage mouse = getmessage(EM_MOUSE);//获取鼠标事件
			if (mouse.y>=300 && mouse.y<=300+theight && mouse.x>=(WIDTH/2-textwidth(t1)) && mouse.x <=(WIDTH/2+textwidth(t1))) {
				rectangle(WIDTH / 2 - textwidth(t1), 300, WIDTH / 2 + textwidth(t1), 300 + theight);//绘制鼠标放在上面时的边框
				//渲染选中效果
				if (mouse.lbutton) {
					this->mode = 1;
					this->player_num = mode;
					this->WIN = player_num;
					start(1);
					break;
				}
			}
			else if (mouse.y >= 350 && mouse.y <= 350 + textheight(t2) && mouse.x >= (WIDTH / 2 - textwidth(t2)) && mouse.x <= (WIDTH / 2 + textwidth(t2))) {
				rectangle(WIDTH / 2 - textwidth(t2), 350, WIDTH / 2 + textwidth(t2), 350 + theight);//绘制鼠标放在上面时的边框
				//渲染选中效果
				if (mouse.lbutton) {
					this->mode = 2;
					this->player_num = mode;
					this->WIN = player_num;
					start(2);
					break;
				}
			}
			else if (mouse.y >= 400 && mouse.y <= 400 + textheight(t3) && mouse.x >= (WIDTH / 2 - textwidth(t3)) && mouse.x <= (WIDTH / 2 + textwidth(t3))) {
				rectangle(WIDTH / 2 - textwidth(t3), 400, WIDTH / 2 + textwidth(t3), 400 + theight);//绘制鼠标放在上面时的边框
				//渲染选中效果
				if (mouse.lbutton) {
					this->mode = 3;
					showPoint();
				}
			}
			else {
				//用黑色边框覆盖被选中后显示的白色边框
				setlinecolor(BLACK);
				rectangle(WIDTH / 2 - textwidth(t1), 300, WIDTH / 2 + textwidth(t1), 300 + theight);
				rectangle(WIDTH / 2 - textwidth(t2), 350, WIDTH / 2 + textwidth(t2), 350 + theight);
				rectangle(WIDTH / 2 - textwidth(t3), 400, WIDTH / 2 + textwidth(t3), 400 + theight);
			}
		}
	}
	//游戏开始方法
	void start(int player_num) {
		this->drawBackground();//先渲染一次背景图片
		//初始化
		for (int i = 0; i < player_num;i ++) {
			Player* player = new Player(this->width/(3 - i), this->height - 110, i + 1);
			//初始生成玩家飞机
			this->players[i] = player;
			this->players[i]->render();
			//初始生成子弹，这坨代码没啥用
			//Bullet* bull = new Bullet(this->players[i]->x + 25, this->players[i]->y - 20);
			//this->lastBullet[i] = bull;
			//初始生成敌机
			/*Enemy* enemy = new Enemy(this->difficulty);
			this->lastEnemy = enemy;*/
		}
		process(player_num);
	}
	//游戏进行过程方法
	void process(int player_num) {
		BeginBatchDraw();//开始批量绘图，避免闪烁
		int t = 0;//定义一个数字来代表进程循环的周期数
		while (1)
		{
			//按键监听玩家动作
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
			//每一定周期数发射一颗子弹
			if (t % 10 == 0) {
				for (int i = 0; i < player_num; i++) {
					if (this->players[i] != NULL) {
						this->lastBullet[i] = Bullet::create(this->lastBullet[i], this->players[i]->x + 36.5, this->players[i]->y - 20);
					}
				}
			}
			
			drawBackground();//用背景图片覆盖窗口以便重新绘图

			//隔一定周期创造敌机
			if (t % this->interval == 0) {
				this->lastEnemy = Enemy::create(this->lastEnemy, this->difficulty);
				t = 0;
			}

			this->moveEnemy();//移动所有敌人
			this->renderEnemy();//绘制所有敌人
			//循环绘制贴图
			for (int i = 0; i < player_num; i++) {
				if (this->players[i] != NULL && this->players[i]->getHP() > 0) {
					this->players[i]->render();
					this->moveBullet(i);//移动所有子弹
					this->renderBullet(i);//绘制所有子弹
				}
			}
			showInfo(player_num, this->players);//显示游戏信息
			checkDifficulty();
			checkEnd();
			FlushBatchDraw();//将绘制的图像一次性加载到绘制窗口
			t++;
			Sleep(1);
			removeRub();
		}
	}
	//绘制背景图片方法
	void drawBackground() {
		putimage(0, 0, &this->backgroundImg);
		//SetWorkingImage(&this->backgroundImg);
	}
	//批量移动子弹方法
	void moveBullet(int player) {
		Bullet* lastOne = this->lastBullet[player];
		while (lastOne != NULL){
			lastOne->move(&this->lastBullet[player], &this->BulletRub);
			lastOne = lastOne->previous;
		}
	}
	//批量移动敌机方法
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
	//批量绘制子弹方法
	void renderBullet(int player) {
		Bullet* lastOne = this->lastBullet[player];
		while (lastOne != NULL) {
			lastOne->render();
			lastOne = lastOne->previous;
		}
	}
	//批量绘制敌机方法
	void renderEnemy() {
		Enemy* lastOne = this->lastEnemy;
		while (lastOne != NULL) {
			lastOne->render();
			lastOne = lastOne->previous;
		}
	}
	//检查并提升游戏难度
	void checkDifficulty() {
		this->difficulty = this->point / (30/this->player_num) + 1;
		if (this->interval >= 30) {
			this->interval -= this->point / 60 * 5 * this->player_num;
		}
	}
	//显示游戏信息
	void showInfo(int player_num, Player** players) {
		TCHAR hp[10];
		for (int i = 0; i < player_num;i ++) {
			if (players[i] != NULL) {
				_itow_s(players[i]->getHP(), hp, 10);
				if (i == 0) {
					outtextxy(0, 0, _T("Player1 生命值："));
					outtextxy(100, 0, hp);
				}
				else if (i == 1) {
					outtextxy(WIDTH - 120, 0, _T("Player2 生命值："));
					outtextxy(WIDTH - 20, 0, hp);
				}
			}
		}
		TCHAR point[5];
		_itow_s(this->point, point, 10);
		outtextxy(0, 30, _T("得分："));
		outtextxy(50, 30, point);
		TCHAR dif[5];
		_itow_s(this->difficulty, dif, 10);
		outtextxy(0, 100, _T("难度："));
		outtextxy(50, 100, dif);
		TCHAR skill[10];
		_itow_s(this->skill, skill, 10);
		outtextxy(0, 150, _T("技能点："));
		outtextxy(50, 150, skill);
		outtextxy(0, HEIGHT - 20, _T("按下空格释放技能(消耗10技能点)"));
	}
	//检查游戏结束条件
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
	//游戏结束
	void end() {
		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 40;
		settextstyle(&f);
		RECT r = { 0, 0, 499, 749 };//定义文字范围矩形
		drawtext(_T("\n\n\n游戏结束\n按下空格回到开始界面"), &r, DT_CENTER);
		FlushBatchDraw();
		while (1)
		{
			if (GetAsyncKeyState(VK_SPACE)) {
				closegraph();
				break;
			}
		}
		//按下空格重新回到游戏开始界面
		EndBatchDraw();
		//delete this;
		Game* new_game = new Game(500, 750);
		new_game->init();
	}
	//释放技能方法
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
	//储存记录分值方法
	void savePoint() {
		FILE* fp = NULL;//定义文件指针
		errno_t err;//定义一个报错
		err = fopen_s(&fp, "./data/rank.txt", "a+");//打开储存分数的文件
		if (err != 0)
		{
			puts("要写入的文件出错，按任意键退出");
			getchar();
			exit(0);
		}
		else {
			char ax[10];//定义要储存的字符串
			_itoa_s(this->point, ax, 10);//将分数转化为字符串
			strcat_s(ax, "\n\0");//拼接一个换行符和字符串结束符
			fputs(ax, fp);//写入文件
			//char a[10];
			//while (fgets(a, 9, fp) != NULL) {
			//	printf("%s", a);
			//}
		}
		fclose(fp);//关闭打开的文件
	}
	//打开排行榜显示分数
	void showPoint() {
		FILE* fp = NULL;
		errno_t err;
		err = fopen_s(&fp, "./data/rank.txt", "r");
		if (err != 0)
		{
			puts("要写入的文件出错，按任意键退出");
			getchar();
			exit(0);
		}
		else {
			cleardevice();//清空屏幕
			LOGFONT f;//声明字体格式变量
			gettextstyle(&f);//获取当前字体样式
			int theight = 35;//设定一个字体大小
			f.lfHeight = theight;//放大字体
			settextstyle(&f);//设置字体样式
			RECT r = { 0, 0, WIDTH - 1, HEIGHT - 1 };//定义文字范围矩形
			TCHAR t[] = _T("\n\n\n分数排行榜");
			drawtext(t, &r, DT_CENTER);//输出选项文字
			char charPoint[5] = "0";//定义一个字符串储存读取的字符串
			int points[1000];//定义整形数组来储存转换得到的分数
			//读取分数并存进一个数组
			for (int i = 0; fgets(charPoint, 9, fp) != NULL; i++) {
				points[i] = atoi(charPoint);//将字符串转换为数字方便下面排序
			}
			//将分数进行排序,使用插入排序法
			int tmp;//定义一个暂存数
			int j;//内层循环数
			for (int i = 1; i < 1000; i++)
			{
				tmp = points[i];
				for (j = i - 1; j >= 0 && points[j] < tmp; j--)
				{
					points[j + 1] = points[j];
				}
				points[j + 1] = tmp;
			}

			//遍历输出分数排行榜
			for (int i = 0; i < 10;i ++) {
				char text[1000] = "No.";//定义一个字符串标头
				char rank[5];//定义一个字符串来显示排名
				_itoa_s(i + 1, rank, 10);//将当前排名转换为字符串
				strcat_s(text, rank);//拼接标头和字符串
				char space[] = ":  ";//定义一个空格字符串来排版
				strcat_s(text, space);//连接前文和空格
				char point[15];//定义一个字符串以储存转换得到的分数
				_itoa_s(points[i], point, 10);
				strcat_s(text, point);//连接前文和分数
				RECT r0 = { 0, 300 + i * 40, WIDTH - 1, HEIGHT - 1 };//定义一个绘图矩形
				drawtext(charToTchar(text), &r0, DT_CENTER);//输出选项文字
			}
			outtextxy(10, 10, _T("返回"));//生成一个返回按钮
			//此处同init方法类似
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
		fclose(fp);//关闭文件
	}
	//将char*类型变量转换为TCHAR类型变量
	wchar_t* charToTchar(char* str) {
		char* CStr = (char*)str;
		size_t len = strlen(CStr) + 1;
		size_t converted = 0;
		wchar_t* WStr;
		WStr = (wchar_t*)malloc(len * sizeof(wchar_t));
		mbstowcs_s(&converted, WStr, len, CStr, _TRUNCATE);
		return WStr;
	}
	//删除垃圾
	void removeRub() {
		//*this->BulletRub = NULL;
	}

private:
	int skill;//技能点
	int WIN = 0;//检查游戏是否结束的变量
	int width;//游戏界面宽度
	int height;//游戏界面高度
	int mode = 0;//游戏模式
	int interval = 60;//出现敌机时间间隔
	int player_num = 0;//玩家数量
	int difficulty = 1;//游戏难度系数
	Bullet* lastBullet[2];//目前存在的最靠后发射的子弹指针
	Bullet* BulletRub;//子弹对象垃圾
	Enemy* lastEnemy;//目前存在的最靠后出现的敌机
	Player* players[2];//玩家对象，最多两个玩家
	IMAGE startImg;//开始界面图片
	IMAGE backgroundImg;//背景图片
	IMAGE boomimg;
	IMAGE boomimgback;
};
