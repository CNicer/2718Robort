//2718人机大战游戏
//游戏分为三关，每一关玩家打字可用的时间逐渐缩短 


#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<Mmsystem.h>
#include<string.h>


int game(int level); 	//游戏玩法处理 
void startshow();//游戏开始界面 
void start(); //startshow的辅助函数 
void gamerootletter(char *str,int gc);//游戏核心 1随机生成字母
void gamerootarithmetic(int *arith);//游戏核心2随机生成算术 
void gotoxy(int x, int y);	//坐标处理 
void gameplay(int counts);	//游戏界面输出 
void story();		//向玩家介绍游戏背景
void rules() ;		//输出游戏规则 
void refresh();		//fflush(stdin)	for kbhit() 
void inshow();		//输出框架 
void winshow();		//玩家胜利界面的输出 
void faileshow();		//玩家失败界面的输出 


char lowc[27]={"abcdefghijklmnopqrstuvwxyz"}; //lowercase 小写字母 
char upc[27]={"ABCDEFGHIJKLMNOPQRSTUVWXYZ"}; //uppercase 大写字母 
char choice; //玩家是否打开音乐 

main()				//主函数 
{
	char loop,im[7000],ps[7000];
	do{
		system("color 3F");
		system("cls");
		printf("是否希望打开音乐？(打开请按y,推荐打开音乐以获得更好的体验)");
		choice=getch();
		int ifwin;
		system("mode con cols=153 lines=46");
		startshow();
		PlaySound(NULL,NULL,SND_FILENAME);
		system("cls");
		for(int level=1;level<=3;level++)
		{
			FILE *fp;
			char filename[20]={"file//round0.txt"};
			filename[11]+=level;
			fp=fopen(filename,"r");
			for(int i=0;i<6900;i++)
				im[i]=fgetc(fp);
			fclose(fp);
			if(choice=='y'||choice=='Y')
				PlaySound("file//startgame.wav",NULL,SND_FILENAME|SND_ASYNC);
			puts(im);
			gotoxy(60,0);
			system("pause");
			ifwin=game(level);
			if(ifwin==0)
				break;
			if(ifwin==1&&(level==1||level==2))
			{
				FILE *fp;
				fp=fopen("file//pass.txt","r");
				for(int i=0;i<6900;i++)
					ps[i]=fgetc(fp);
				fclose(fp);
				if(choice=='y'||choice=='Y')
					PlaySound("file//pass.wav",NULL,SND_FILENAME|SND_ASYNC);
				puts(ps);
				gotoxy(60,0);
				system("pause");
			}
			if(ifwin==1&&level==3)
			{
				FILE *fp;
				fp=fopen("file//allpass.txt","r");
				for(int i=0;i<6900;i++)
					ps[i]=fgetc(fp);
				if(choice=='y'||choice=='Y')
					PlaySound("file//allpass.wav",NULL,SND_FILENAME|SND_ASYNC);
				puts(ps);
				gotoxy(60,0);
				system("pause");
			}
		}
		if(ifwin==1)
			winshow();
		else 
			faileshow();
		system("cls");
		printf("\n\n\n\n\t\t\t\t\t\t\t\t是否继续游戏？");
		printf("\n\t\t\t\t\t\t\t\t  (按y继续)"); 
		loop=getch();
	}while(loop=='y'||loop=='Y');
	
}

void startshow()
{
	FILE *fp;
	char im[7000],ch=0;
	fp=fopen("start//start.txt","r"); 
	for(int i=0;i<5500;i++)
		im[i]=fgetc(fp);
	im[5499]=NULL;
	if(choice=='y'||choice=='Y')
		PlaySound("file//The End of Heros.wav",NULL,SND_FILENAME |SND_ASYNC|SND_LOOP);
	start();
	system("cls");
	puts(im); 
	gotoxy(60,0);
	system("pause");
	while(ch!='1')
	{
		int i=0;
		system("cls");
		fp=fopen("file//menu.txt","r");
		for(int i=0;i<1716;i++)
			im[i]=fgetc(fp); 
		puts(im);
		ch=getch(); 
		switch(ch){
			case '1':break;
			case '2':story();break;
			case '3':rules();break;
			default:printf("请输入1、2或3！");break; 
		}
	}
	fclose(fp);
}

void start()
{
	char mv[7000];
	int i1,i2,i3; 
	for(i1=0;i1<2;i1++)
	{ 
		for(i2=0;i2<10;i2++)
		{
			for(i3=0;i3<10;i3++)
			{
				system("cls");
				char filename[]={"start//start000.txt"};
				FILE *fp;
				filename[12]+=i1;
				filename[13]+=i2;
				filename[14]+=i3;
				fp=fopen(filename,"r");
				for(int u=0;u<6500;u++)
					mv[u]=fgetc(fp);
				fclose(fp);
				puts(mv);
				gotoxy(62,5);
				printf(">>>>>>>按任意键跳过<<<<<<<");
				Sleep(80);
				if(i1*100+i2*10+i3==147||kbhit())
					break;
			}
			if(i1*100+i2*10+i3==147||kbhit())
				break;
		}
		if(i1*100+i2*10+i3==147||kbhit())
			break;
	} 
}


void gamerootletter(char *str,int gc) 
{
	int jlu,rnu;	//jlw 判断使用大写还是小写  	//rnu随机数字 	 
	srand(time(NULL));
	for(int i=0;i<gc;i++)
	{
		jlu=rand()%2;
		if(jlu==0)
		{
			rnu=rand()%26;
			str[i]=lowc[rnu];	
		}
		else
		{
			rnu=rand()%26;
			str[i]=upc[rnu];
		}
	}
}

void gamerootarithmetic(int *arith)
{
	srand(time(NULL)); 
	for(int i=0;i<5;i++)
		arith[i]=rand()%101;
} 


int game(int level)				//游戏函数 
{
	int result,counts=0,timelimit,gc,chance=1;//result记录玩家结果是否正确//counts记录玩家攻击次数//timelimit玩家输入字母的时间限制//gc随机出现字母的个数 
	switch(level){
		case 1:timelimit=2500;gc=6;if(choice=='y'||choice=='Y')PlaySound("file//level1.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);break;
		case 2:timelimit=2100;gc=9;if(choice=='y'||choice=='Y')PlaySound("file//level2.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);break;
		case 3:timelimit=1600;gc=13;if(choice=='y'||choice=='Y')PlaySound("file//level3.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);break;
		default:printf("program error");break; 
	}
	for(int i=0;i<10;i++)
	{
		gameplay(counts);	//输出游戏界面 
		inshow();			//输出框架 
		gotoxy(0,0);
		printf("Round%d",level);
		if(i==0)
		{
			gotoxy(45,10);
			printf("请先将输入法调至英文！");
			Sleep(2000);
			gotoxy(45,10);
			printf("每个字母都会留有一定的时间");
			gotoxy(45,11) ;
			printf("请等待程序在规定内时间响应");
			Sleep(3000);
			gotoxy(45,11);
			printf("                          ");
			gotoxy(45,10);
			printf("准备开始！               ");
			Sleep(1500);
			gotoxy(45,10);
			system("pause");
		}
		refresh();
		if(counts%5!=0||counts==0||(counts==5&&chance==0))
		{
			char str[20];
			gamerootletter(str,gc);
			gotoxy(40,9);
			float blood=(float)(8-counts)/8;
			printf("剩余机会：%d 敌人血量：%2.2f%%",10-i-1,blood*100);
			gotoxy(45,10); 
			printf("     ");
			for(int f=0;f<gc;f++)
				printf("%c",str[f]);
			for(int e=0;e<20-gc;e++)
				printf(" ");
			gotoxy(40,11);
			printf("请输入:");
			gotoxy(40,12);
			printf("tips:不需要按回车");
			gotoxy(47,11) ;
			for(int i1=0;i1<gc;i1++)
			{
				Sleep(timelimit);
				if(kbhit())
				{
					char temp=getch();  	//记录玩家输入的内容 
					result=temp==str[i1]?1:0;
				}
				else result=0;
				if(result==1)
					printf("√");
				else printf("×");
				if(result==0)
					break; 
			}
			if(result==1)
			{
				counts++;
				gotoxy(40,12);
				printf("        >>>>攻击成功！<<<<"); 
			}
			else {
				gotoxy(40,12);
				printf("        >>>>攻击失败！<<<<");
			}
			Sleep(1000);
		}
		if(counts%5==0&&chance==1&&counts!=0) 
		{
			int arith[5],answer;//算术题 
			gamerootarithmetic(arith);
			result=arith[0]+arith[1]-arith[2]+arith[3]-arith[4];
			gotoxy(40,9);
			printf("              !大招!        ");
			gotoxy(50,10);
			printf("算术题请回答：");
			gotoxy(40,11);
			printf("                                 ");
			gotoxy(50,11);
			printf("%d+%d-%d+%d-%d=",arith[0],arith[1],arith[2],arith[3],arith[4]);
			gotoxy(50,12);
			printf("输入后请按回车!");
			gotoxy(65,11);
			Sleep(18000);
			if(kbhit())
			{
				scanf("%d",&answer);
				if(answer==result)
				{
					printf("√"); 
					counts+=3;
					gotoxy(46,12);
					printf(">>>>大招释放成功!<<<<");
					Sleep(1000);
				}
				else{
					printf("×");
					gotoxy(46,12);
					printf(">>>>大招释放失败!<<<<");
					Sleep(1000);
				}
			}
			else
				printf("×");
			i--;//大招不算在规定次数内 
			chance=0; 
		}
		if(counts>=8)
			break;
	}
	if(counts>=8)
		return 1;
	else return 0;
}

void gameplay(int counts)
{
	FILE *fp;
	char filename[]={"gameplay//0.txt"},im[7500];
	filename[10]+=counts;
	fp=fopen(filename,"r");
	for(int i=0;i<6500;i++)
		im[i]=fgetc(fp);
	puts(im);
	fclose(fp);
}

void gotoxy(int x, int y) {
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
    SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}

void refresh()
{
	for(int i=0;i<20;i++)
		if(kbhit())
		getch();
}

void story()
{
	system("cls");
	char words[500],back[7000],ground[7000];
	FILE *fp;
	fp=fopen("file//story0.txt","r");
	for(int i=0;i<7000;i++)
		back[i]=fgetc(fp);
	fp=fopen("file//story1.txt","r");
	for(int i=0;i<7000;i++)
		ground[i]=fgetc(fp);
	puts(back);
	fp=fopen("file//story.txt","r");
	gotoxy(0,0);
	fgets(words,330,fp);
	puts(words);
	system("pause");
	system("cls");
	puts(ground);
	gotoxy(0,0);
	for(int i=0;i<6;i++)
	{
		fgets(words,90,fp);
		puts(words);
		Sleep(1500); 
	}
	fgets(words,205,fp);
	puts(words);
	Sleep(1500);
	fgets(words,90,fp);
	puts(words);
	system("pause");
	system("cls");
	gotoxy(35,20);
	fgets(words,90,fp);
	puts(words);
	fclose(fp);
	gotoxy(35,0);
	system("pause");
}


void rules()
{
	system("cls");
	FILE *fp;
	char ru[2000];
	fp=fopen("file//rules.txt","r");
	for(int i=0;i<1716;i++)
		ru[i]=fgetc(fp);
	fclose(fp);
	puts(ru);
	system("pause");
}

void inshow()
{
	gotoxy(36,6);
	printf("|======================================|");
	gotoxy(36,7);
	printf("|**************************************|");
	gotoxy(36,8);
	printf("|*                                    *|");
	gotoxy(36,9);
	printf("|*                                    *|");
	gotoxy(36,10);
	printf("|*                                    *|");
	gotoxy(36,11);
	printf("|*                                    *|");
	gotoxy(36,12);
	printf("|*                                    *|");
	gotoxy(36,13);
	printf("|*                                    *|");
	gotoxy(36,14);
	printf("|**************************************|");
	gotoxy(36,15);
	printf("|======================================|");
}

void winshow()
{
	PlaySound(NULL,NULL,SND_FILENAME);
	system("cls");
	system("color 2E");
	if(choice=='y'||choice=='Y')
		PlaySound("file\\The Avengers.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
	FILE *fp;
	fp=fopen("win//win.txt","r");
	char im[7000],ws[7000];
	for(int i=0;i<6900;i++)
		im[i]=fgetc(fp);
	puts(im);
	fclose(fp);
	gotoxy(55,10) ;
	printf("你拯救了人类，机器人决定和人类和平相处！");
	Sleep(5000);
	int i1,i2,i3;
	for(i1=0;i1<2;i1++)
		{
			for(i2=0;i2<10;i2++)
			{
				for(i3=0;i3<10;i3++)
				{
					char filename[]={"win//champion0000.txt"};
					filename[14]+=i1;
					filename[15]+=i2;
					filename[16]+=i3;
					FILE *fp;
					fp=fopen(filename,"r");
					for(int i=0;i<6300;i++)
						ws[i]=fgetc(fp);
					fclose(fp);
					system("cls");
					puts(ws);
					Sleep(50);
					if(i1*100+i2*10+i3==114)
						break;
				}
				if(i1*100+i2*10+i3==114)
					break;
			}
			if(i1*100+i2*10+i3==114)
				break;
		}
	gotoxy(60,0);
	system("pause");
	PlaySound(NULL,NULL,SND_FILENAME);
} 
 
void  faileshow()
{
	PlaySound(NULL,NULL,SND_FILENAME);
	system("cls");
	system("color 04");
	gotoxy(60,20);
	printf("你输了，机器人决定清除人类！");
	gotoxy(60,21);
	printf("        感受痛楚！");
	Sleep(5000);
	int i1=0,i2=0,i3=0,i4=0;
	char fs[7000];
	if(choice=='y'||choice=='Y')
			PlaySound("faile//boom.wav",NULL,SND_FILENAME|SND_ASYNC);
	for(;i1<2;i1++)
	{
		for(i2=0;i2<10;i2++)
		{
			for(i3=0;i3<10;i3++)
			{
				for(i4=0;i4<10;i4++)
				{
					char filename[]={"faile//boom0000.txt"};
					filename[11]+=i1;
					filename[12]+=i2;
					filename[13]+=i3;
					filename[14]+=i4;
					FILE *fp;
					fp=fopen(filename,"r");
					for(int i=0;i<6630;i++)
						fs[i]=fgetc(fp);
					fclose(fp);
					system("cls");
					puts(fs);
					Sleep(40);
					if(i1*1000+i2*100+i3*10+i4==1200)
						break;
				}
				if(i1*1000+i2*100+i3*10+i4==1200)
					break; 
			}
			if(i1*1000+i2*100+i3*10+i4==1200)
				break; 
		}
		if(i1*1000+i2*100+i3*10+i4==1200)
			break; 
	} 
	if(choice=='y'||choice=='Y')
		PlaySound("faile//faile.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
	FILE *fp;
	fp=fopen("faile//faile.txt","r");
	char im[7000];
	for(int i=0;i<6900;i++)
		im[i]=fgetc(fp);
	system("cls");
	puts(im);
	fclose(fp);
	gotoxy(60,0);
	system("pause");
}









