//2718�˻���ս��Ϸ
//��Ϸ��Ϊ���أ�ÿһ����Ҵ��ֿ��õ�ʱ�������� 


#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<Mmsystem.h>
#include<string.h>


int game(int level); 	//��Ϸ�淨���� 
void startshow();//��Ϸ��ʼ���� 
void start(); //startshow�ĸ������� 
void gamerootletter(char *str,int gc);//��Ϸ���� 1���������ĸ
void gamerootarithmetic(int *arith);//��Ϸ����2����������� 
void gotoxy(int x, int y);	//���괦�� 
void gameplay(int counts);	//��Ϸ������� 
void story();		//����ҽ�����Ϸ����
void rules() ;		//�����Ϸ���� 
void refresh();		//fflush(stdin)	for kbhit() 
void inshow();		//������ 
void winshow();		//���ʤ���������� 
void faileshow();		//���ʧ�ܽ������� 


char lowc[27]={"abcdefghijklmnopqrstuvwxyz"}; //lowercase Сд��ĸ 
char upc[27]={"ABCDEFGHIJKLMNOPQRSTUVWXYZ"}; //uppercase ��д��ĸ 
char choice; //����Ƿ������ 

main()				//������ 
{
	char loop,im[7000],ps[7000];
	do{
		system("color 3F");
		system("cls");
		printf("�Ƿ�ϣ�������֣�(���밴y,�Ƽ��������Ի�ø��õ�����)");
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
		printf("\n\n\n\n\t\t\t\t\t\t\t\t�Ƿ������Ϸ��");
		printf("\n\t\t\t\t\t\t\t\t  (��y����)"); 
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
			default:printf("������1��2��3��");break; 
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
				printf(">>>>>>>�����������<<<<<<<");
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
	int jlu,rnu;	//jlw �ж�ʹ�ô�д����Сд  	//rnu������� 	 
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


int game(int level)				//��Ϸ���� 
{
	int result,counts=0,timelimit,gc,chance=1;//result��¼��ҽ���Ƿ���ȷ//counts��¼��ҹ�������//timelimit���������ĸ��ʱ������//gc���������ĸ�ĸ��� 
	switch(level){
		case 1:timelimit=2500;gc=6;if(choice=='y'||choice=='Y')PlaySound("file//level1.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);break;
		case 2:timelimit=2100;gc=9;if(choice=='y'||choice=='Y')PlaySound("file//level2.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);break;
		case 3:timelimit=1600;gc=13;if(choice=='y'||choice=='Y')PlaySound("file//level3.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);break;
		default:printf("program error");break; 
	}
	for(int i=0;i<10;i++)
	{
		gameplay(counts);	//�����Ϸ���� 
		inshow();			//������ 
		gotoxy(0,0);
		printf("Round%d",level);
		if(i==0)
		{
			gotoxy(45,10);
			printf("���Ƚ����뷨����Ӣ�ģ�");
			Sleep(2000);
			gotoxy(45,10);
			printf("ÿ����ĸ��������һ����ʱ��");
			gotoxy(45,11) ;
			printf("��ȴ������ڹ涨��ʱ����Ӧ");
			Sleep(3000);
			gotoxy(45,11);
			printf("                          ");
			gotoxy(45,10);
			printf("׼����ʼ��               ");
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
			printf("ʣ����᣺%d ����Ѫ����%2.2f%%",10-i-1,blood*100);
			gotoxy(45,10); 
			printf("     ");
			for(int f=0;f<gc;f++)
				printf("%c",str[f]);
			for(int e=0;e<20-gc;e++)
				printf(" ");
			gotoxy(40,11);
			printf("������:");
			gotoxy(40,12);
			printf("tips:����Ҫ���س�");
			gotoxy(47,11) ;
			for(int i1=0;i1<gc;i1++)
			{
				Sleep(timelimit);
				if(kbhit())
				{
					char temp=getch();  	//��¼������������ 
					result=temp==str[i1]?1:0;
				}
				else result=0;
				if(result==1)
					printf("��");
				else printf("��");
				if(result==0)
					break; 
			}
			if(result==1)
			{
				counts++;
				gotoxy(40,12);
				printf("        >>>>�����ɹ���<<<<"); 
			}
			else {
				gotoxy(40,12);
				printf("        >>>>����ʧ�ܣ�<<<<");
			}
			Sleep(1000);
		}
		if(counts%5==0&&chance==1&&counts!=0) 
		{
			int arith[5],answer;//������ 
			gamerootarithmetic(arith);
			result=arith[0]+arith[1]-arith[2]+arith[3]-arith[4];
			gotoxy(40,9);
			printf("              !����!        ");
			gotoxy(50,10);
			printf("��������ش�");
			gotoxy(40,11);
			printf("                                 ");
			gotoxy(50,11);
			printf("%d+%d-%d+%d-%d=",arith[0],arith[1],arith[2],arith[3],arith[4]);
			gotoxy(50,12);
			printf("������밴�س�!");
			gotoxy(65,11);
			Sleep(18000);
			if(kbhit())
			{
				scanf("%d",&answer);
				if(answer==result)
				{
					printf("��"); 
					counts+=3;
					gotoxy(46,12);
					printf(">>>>�����ͷųɹ�!<<<<");
					Sleep(1000);
				}
				else{
					printf("��");
					gotoxy(46,12);
					printf(">>>>�����ͷ�ʧ��!<<<<");
					Sleep(1000);
				}
			}
			else
				printf("��");
			i--;//���в����ڹ涨������ 
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
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
    SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
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
	printf("�����������࣬�����˾����������ƽ�ദ��");
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
	printf("�����ˣ������˾���������࣡");
	gotoxy(60,21);
	printf("        ����ʹ����");
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









