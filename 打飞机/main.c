#include "acllib.h"
#include <stdlib.h>
#define cpx centralPosX
#define cpy centralPoxY
#define topX cpx+angle[PosNow][1]
#define topY cpy-angle[PosNow][0]
//��̨�ڵ�x, y 

int angle[10][2] = {
	50, -86, 
	70, -70, 
	86, -50, 
	96, -25, 
	100, 0, 
	96, 25, 
	86, 50, 
	70, 70, 
	50, 86
};//0�����ӵĸ߶ȣ�1������ƫ����

/*
�е�λ����400�� 510 
�ɻ���λ����������ɵ�
�߶���0 - 300��Χ
�ɻ��Ĺ����80 * 40
��¼�ɻ����ĵ��λ�ü���
�ڵ��İ뾶��10
�ڵ����ƶ��ٶ�Ҫ��ܶ�ܶ� 
ɡ���Ĺ����16 * 32
��ը֮����50 * 50 
*/

//ctrl + m   dev c++ ����ͼ 
 
//��̨������λ�ã��������ڹܵĻ��㣬�ڹܵĳ�����100 
int centralPosX = 400;
int centralPoxY = 510;
int PosNow = 4; 
int flag = 0;
//int deathCounter = 0; �ĳɺ�������mod = 3��ʿ������
int endGame = 0;

typedef struct Node {
	int x, y;
	int turn; //����������ݽṹ��ʱ��ֻ�����ɻ���0����߳�����1���ұ߳���
	int speed; //�������ٶȣ�3, 4, 5��dx�ֱ����5, 4, 3 
	int beginX, beginY; // ��ʼ���� 
	int mod; //ɡ����̬ 1 ������̬ 2 ��ը��̬ 3 || Ҳ�Ǳ�ը�ĳ���ʱ���ʱ�� 
	struct Node *next;
}	Link;

void move(Link *object) { //������һ����λ��
	int speed = object->speed;
	switch(speed) {
		case 1:
			object->x = object->x + (double)object->beginX / 5;
			object->y = object->y - (double)object->beginY / 5;
			break;
		case 2:
			if(object->y + 16 < 540)
				object->y = object->y + 1;
			else {
				if(object->x > 320 && object->x < 480) 
					object->mod = 3;
				else 
					object->x = object->x + 1*object->turn;
			}
			break;
		case 3:
			object->x = object->x+object->turn*8;
			break;
		case 4:
			object->x = object->x+object->turn*5;
			break;
		case 5:
			object->x = object->x+object->turn*3;
			break;
		default:
			break;
	}
}

Link *AirHead = NULL;
int planeNum = 0;

Link *BulletHead = NULL;
int bulletNum = 0;

Link *FirstMan = NULL;
int manNum = 0;

Link *ExplosionHead = NULL;
int explosionNum = 0;

Link *boom(int x, int y) {
	printf("���٣�\n");
	Link *newBoom = (Link *)malloc(sizeof(Link));
	newBoom->x = x;
	newBoom->y = y;
	newBoom->mod = 50; 
	if(ExplosionHead == NULL) {
		ExplosionHead = newBoom;
	} else {
		Link *i;
		for(i = ExplosionHead; i->next != NULL; i = i->next); 
		i->next = newBoom;
	}
	newBoom->next = NULL;
}

//�ӷɻ������µ�ɡ�����併��
Link *land() {
	printf("���棡�������� ɡ������\n");
	Link *newMan = (Link *)malloc(sizeof(Link));
	//����һ��0��4���������Ȼ����Ǹ���+1�ɻ���λ��������ɡ��
	int target = rand()%5;
	Link *i = AirHead;
	while(target--) {
		i = i->next;
	} 
	newMan->x = i->x;
	newMan->y = i->y + 20;
	newMan->speed = 2;
	newMan->turn = (newMan->x > 400 ? -1 : 1);
	newMan->mod = 1;
	if(FirstMan == NULL) {
		FirstMan = newMan;
	} else {
		for(i = FirstMan; i->next != NULL; i = i->next);
		i->next = newMan;
	} 
	newMan->next = NULL;
	manNum++;
}

//����һ��bullet
Link *shoot() {
	Link *newBullet = (Link *)malloc(sizeof(Link));
	
	newBullet->x = topX;
	newBullet->y = topY;
	newBullet->beginX = angle[PosNow][1];
	newBullet->beginY = angle[PosNow][0];
	newBullet->speed = 1;
	
	
	if(BulletHead == NULL) {
		BulletHead = newBullet;
	} else {
		Link *i;
		for(i = BulletHead; i->next != NULL; i = i->next)
			;
			
			
		i->next = newBullet;
	}
	
	
	newBullet->next = NULL;
	bulletNum++;
} 


//����һ���ɻ� 
Link* randomAirplane() {
	printf("����randomAirplane\n");
	
	int dy = rand()%300;
	int turn = (rand()%2)==0?1:-1; //0��1, 0����߳����� 1���ұ߳��� 
	int dx = (turn==1?0:800);
	int speed = rand()%3+3;
	
	printf("����һ���ɻ�dy = %d, ��%s�߷ɳ��� \n", dy, turn==1?"��":"��");
	
	if(planeNum == 0) {
		AirHead = (Link *)malloc(sizeof(Link));
		
		AirHead->x = dx;
		AirHead->y = dy;
		AirHead->speed = speed;
		AirHead->turn = turn;
		
		AirHead->next = NULL;
	} else {
		Link *tail;
		for(tail = AirHead; tail->next != NULL; tail = tail->next);
		
		Link *newPlane = (Link *)malloc(sizeof(Link));
		
		newPlane->x = dx;
		newPlane->y = dy;
		newPlane->turn = turn;
		newPlane->speed = speed;
		
		newPlane->next = NULL;
		tail->next = newPlane;
	}
	planeNum++;
	//printf("�˳�randomAirplane\n");
}


//����ģ�顣mvc
//v -- view
void view() {
	if(!flag) return;
	beginPaint();
		clearDevice();

	setPenWidth(5);
	
	line(0, 540, 800, 540);
	setPenColor(WHITE);
	roundrect(320, 480, 480, 540, 30, 30); //Բ�Ǿ��� ��̨
	setPenColor(BLACK);
	//����ֱ������ʾ�ˣ�͵�� 
	line(cpx, cpy, cpx+angle[PosNow][1], cpy-angle[PosNow][0]);
	
	//���ɻ� �����ɻ����� 
	Link *i = AirHead;
	int cnt = 0;
	while(i != NULL) {
		//printf("����%d���ɻ�\n", ++cnt); 
		int x = i->x;
		int y = i->y;
		if(i->turn == -1) {
			line(x, y-5, x, y-20);
			line(x, y+5, x, y+20);
			line(x, y-5, x+40, y-5);
			line(x, y+5, x+40, y+5);
			line(x, y-20, x-40, y);
			line(x, y+20, x-40, y);
			line(x+40, y-5, x+40, y+5);
		} else {
			line(x, y-5, x, y-20);
			line(x, y+5, x, y+20);
			line(x, y-5, x-40, y-5);
			line(x, y+5, x-40, y+5);
			line(x, y-20, x+40, y);
			line(x, y+20, x+40, y);
			line(x-40, y-5, x-40, y+5);
		}
		i = i->next;
	}
	//
	
	//��bullet
	Link *i2 = BulletHead;
	cnt = 0;
	while(i2 != NULL) {
		ellipse(i2->x-3, i2->y-3, i2->x+3, i2->y+3);
		i2 = i2->next;
	}
	/// 
	
	//ɡ�� 
	Link *i3 = FirstMan;
	while(i3 != NULL) {
		int x = i3->x, y = i3->y;
		switch(i3->mod) {
			case 1:
			case 2:
				line(x, y-6, x, y+4);
				//ͷ 
				line(x-8, y-6, x-8, y-16);
				line(x+8, y-6, x+8, y-16);
				line(x-8, y-16, x+8, y-16);
				line(x-8, y-6, x+8, y-6);
				//�ֱ� 
				line(x, y-6, x-8, y+2);
				line(x, y-6, x+8, y+2);
				//��
				line(x, y+4, x+8, y+16);
				line(x, y+4, x-8, y+16);
				break;
			case 3:
				setPenColor(YELLOW);
				//ʮ���ǣ���ʱ����м��λ˳�����⻭�� 
				line(x+8, y-8, x, y-24);
				line(x+8, y-8, x+24, y);
				
				line(x-8, y-8, x, y-24);
				line(x-8, y-8, x-24, y);
				
				line(x-8, y+8, x, y+24);
				line(x-8, y+8, x-24, y);
				
				line(x+8, y+8, x+24, y);
				line(x+8, y+8, x, y+24);
				setPenColor(BLACK);
				break;
		}
		i3 = i3->next;
	}
	///
	
	//��ը
	Link *i4 = ExplosionHead;
	while(i4 != NULL) {
		int x = i4->x;
		int y = i4->y;
		setPenColor(YELLOW);
		//ʮ���ǣ���ʱ����м��λ˳�����⻭�� 
		line(x+8, y-8, x, y-24);
		line(x+8, y-8, x+24, y);
		
		line(x-8, y-8, x, y-24);
		line(x-8, y-8, x-24, y);
		
		line(x-8, y+8, x, y+24);
		line(x-8, y+8, x-24, y);
		
		line(x+8, y+8, x+24, y);
		line(x+8, y+8, x, y+24);
		setPenColor(BLACK); 
		
		i4 = i4->next;
	} 
	//printf("endPaint\n");
	endPaint();
} 

void deathView() {
	beginPaint();
	
	const char *bye = "��������ⳡ����Ӯ����Ϸ\n";
	paintText(320, 200, bye);
	
	endPaint();
}


void mouseListener(int x, int y, int button, int event) {
	static int ox = 0;
	static int oy = 0;
	//printf("x=%d, y=%d, button=%d, event=%d\n", x, y, button, event);
	if(event == 2) {
		beginPaint();
		line(ox, oy, x, y);
		endPaint();
		ox = x;
		oy = y;
	}
}

void keyListener(int key, int event) {
	printf("%c %s\n", (char)key, (event==0?"����":"����"));
	/*
	ascii code
	w 87
	s 83
	a 65
	d 68
	space 32
	*/
	if((char)key == 't' || (char)key == 'T')
		flag = 1;
	if(flag)
	if(key == 65 && event == 0) {
		if(PosNow-1 >= 0)
			PosNow--;
	} else if (key == 68 && event == 0) {
		if(PosNow+1 <= 8) 
			PosNow++;
	} else if (key == 32 && event == 0) {
		if(bulletNum < 10) {
			shoot();
		}
	}
	
}

//����(x1, x2)   (x3, x4)�Ƿ񽻴� 
int intersect(int x1, int x2, int x3, int x4) {
	if(x2 < x3) return 0;
	if(x1 > x4) return 0;
	return 1;
}

//ʹ��algorithm������㷨�������Ƿ񽻴� 

int contain(int px, int py, int bx, int by) {
	int plx, prx, pty, pby; //plane left x, plane right x, plane top y, plane bottom y
	int blx, brx, bty, bby;
	
	plx = px-40;
	prx = px+40;
	pty = py-20;
	pby = py+20;
	
	blx = bx-3;
	brx = bx+3;
	bty = by-3;
	bby = by+3;
	
	if(!intersect(plx, prx, blx, brx)) return 0;
	if(!intersect(pty, pby, bty, bby)) return 0;
	return 1;
}

int deathCounter() {
	int cnt = 0;
	Link *i = FirstMan;
	while(i != NULL) {
		if(i->mod == 3)
			cnt++;
		i = i->next; 
	}
	return cnt;
} 

//��ʱ��
//2����һ��ɡ��
int timeCounter = 0; 
void timerListener(int id) {
	/*
	static int cnt = 0;
	printf("id = %d\n", id);
	if(id == 0) {
		cnt++;
		if(cnt == 5) {
			cancelTimer(0);
		}
	}
	*/
	static int cnt = 0;
	if(id == 0) {
		cnt++;
	}
	
	if(endGame) {
		deathView();
		return;
	}
	if(!flag) {
		return;
	}
	///printf("%d-timer wake up for the %dth time\n", id, cnt);
	
	//ը���ĳ���ʱ��
	int counter = 0;
	Link *t = ExplosionHead;
	//for(; t!=NULL; t=t->next) counter++;
	//printf("��%d����ը\n", counter); 
	Link *t2 = NULL;
	while(t != NULL) {
		printf("check\n");
		if(t->mod > 0) {
			t->mod--;
		} else {
			if(t2 == NULL) {
				ExplosionHead = ExplosionHead->next;
			} else {
				t2->next = t->next;
			}
		}
		t2 = t;
		if(ExplosionHead == NULL) break;
		t = t->next;
	}
	///printf("explosion check end\n");
	//�ɻ����˶� 
	if(planeNum < 5) {
		randomAirplane();
	} else {
		//printf("������\n");
	}
	Link *i = AirHead;
	Link *i2 = NULL;
	Link *i3 = BulletHead;
	Link *i4 = NULL;
	Link *i5 = FirstMan; 
	Link *i6 = NULL;
	
	//hit & crash �ɻ���bullet 
	for(; i != NULL; i = i->next) {
		Link *t;
		Link *t2 = NULL;
		int flag = 0; //�Ƿ���У��ǣ�1�� 
		for(t = BulletHead; t != NULL; t = t->next) {
			//if contain, ɾ�����ը����ͬʱ�ѷɻ�Ҳɾ�� 
			if(contain(i->x, i->y, t->x, t->y)) {
				if(t2 == NULL) {
					BulletHead = BulletHead->next;
				} else {
					t2->next = t->next;
				}
				flag = 1;
				bulletNum--;
				
				boom(i->x, i->y);
				break;
			}
			t2 = t;
		}
		
		//�����Ѿ����� 
		if(flag == 1) {
			if(i2 == NULL) {
				AirHead = AirHead->next;
			} else {
				i2->next = i->next;
			}
			planeNum--;
		}
		i2 = i;
	}
	//hit & crash part2 ɡ����bullet
	/*
	Link *i = AirHead;
	Link *i2 = NULL;
	Link *i3 = BulletHead;
	Link *i4 = NULL;
	Link *i5 = FirstMan; 
	Link *i6 = NULL;
	*/
	for(; i5 != NULL; i5 = i5->next) {
		Link *t;
		Link *t2 = NULL;
		int flag = 0;
		for(t = BulletHead; t != NULL; t = t->next) {
			if(contain(t->x, t->y, i5->x, i5->y)) {
				if(t2 == NULL) {
					BulletHead = BulletHead->next;
				} else {
					t2->next = t->next;
				}
				flag = 1;
				bulletNum--;
				
				boom(i5->x, i5->y);
				break;
			}
			t2 = t;
		}
		if(flag) {
			if(i6 == NULL) {
				FirstMan = FirstMan->next;
			} else {
				i6->next = i5->next;
			}
		}
		i6 = i5;
	}
	 
	
	timeCounter++;
	if(timeCounter == 100) {
		timeCounter = 0;
		land();
	}
	
	i = AirHead;
	i2 = NULL;
	i3 = BulletHead;
	i4 = NULL;
	
	//�ɻ����˶� 
	while(i != NULL) {
		if(i->turn == 1 && i->x > 800 || i->turn == -1 && i->x < 0) {
			if(i2 == NULL) {
				//free(AirHead);
				AirHead = AirHead->next;
			} else {
				i2->next = i->next;
			}
			printf("ɾ����y = %d�ķɻ�\n", i->y); 
			planeNum--;
		}
		else {
			move(i);
		}
		i2 = i;
		i = i->next;
	}
	///
	
	//bullet���˶�
	while(i3 != NULL) {
		if(i3->y < 0 || i3->x > 800 || i3->x < 0) {
			if(i4 == NULL) {
				BulletHead = BulletHead->next;
			} else {
				i4->next = i3->next;
			}
			bulletNum--;
		} else {
			move(i3);
		}
		i3 = i3->next;
	} 
	///
	
	
	//ɡ�����˶�
	i5 = FirstMan;
	i6 = NULL; 
	while(i5 != NULL) {
		move(i5);
		i5 = i5->next;
	} 
	
	
	if(deathCounter() == 3) {
		endGame = 1;
		return;
	}
	view();
}

int Setup() {
		srand((unsigned int)(time(NULL)));
	initConsole();
	initWindow("text", 200, 200, 800, 600);
	//��һ����ʼ����
	beginPaint();
	setBrushColor(RED);
	// setBrushStyle(BRUSH_STYLE_DIAGCROSS);
	// roundrect(320, 480, 480, 540, 30, 30);
	//setPenWidth(5);
	// line(100,  200, 100, 300);
	const char* beginText = "AIRPLANE";
	const char* welcome   = "��t��ʼ��Ϸ";
	setTextSize(25);
	paintText(350, 200, beginText);
	paintText(320, 300, welcome); 
	
	 
	endPaint();
	registerKeyboardEvent(keyListener);
	registerTimerEvent(timerListener);
	view();
	startTimer(0, 20);
	
}

/*
	registerMouseEvent(mouseListener);
	registerKeyboardEvent(keyListener);
	registerTimerEvent(timerListener);
	startTimer(0, 500);
	startTimer(1, 1000);
	beginPaint();
	line(0, 540, 800, 540);
	//pie(300, 400, 500, 600, 0, 0, 0, 0); //��Բ 
	//ellipse(200, 300, 210, 310); //Բ 
	roundrect(320, 480, 480, 540, 30, 30); //Բ�Ǿ��� ��̨
	//����ֱ������ʾ�ˣ�͵�� 
	line(20, 20, width-20, width-20);
	endPaint();
	*/
