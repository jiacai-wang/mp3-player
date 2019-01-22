#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include "PlayInterface.h"
#include "fileHandler.h"

#define MAX_SONG_NUM 200

char dir[20] = {0};

//		0��ֹͣ
//	 ���������ڲ���
//	 ������������ͣ
int playing = 0;
int songNum = 0;
boolean isRndPlay = 0;
// �����ļ�������
char songs[MAX_SONG_NUM][50] = {""};

void showstatus()
{
	if(isRndPlay)
		printf("�������ģʽ��");
	else
		printf("˳�򲥷�ģʽ��");
	if (playing == 0)
		printf("��ǰΪֹͣ״̬\n");
	else if (playing > 0)
		printf("���ڲ��ŵ�%d��:%s\n",playing,songs[playing]);
	else
		printf("������ͣ��%d��:%s\n",-playing,songs[-playing]);
}

void playctrl(void){
	while(1){
		system("cls");
		showstatus();
		printf("1. ����/��ͣ\
			   \n2. ֹͣ\
			   \n3. ��һ��\
			   \n4. ��һ��\
			   \n5. ���/˳�򲥷�\
			   \n0. �˳�\
			   \n�������������:\n");
		switch (getch())
		{
		case '0':
			return;
			break;
		case '1':
			if(playing == 0)				//ֹͣ״̬ʱ��1���ŵ�1��
			{
				playing = (1 + isRndPlay * rand())%songNum;
				if(playing == 0) playing = songNum;
				play(songs[playing]);
			}
			else if(playing > 0)			//����״̬ʱ��ͣ����
			{
				playing = -playing;
				pause(songs[-playing]);
			}
			else							//��ͣ״̬ʱ���Ÿ���
			{
				playing = -playing;
				play(songs[playing]);
			}
			break;
		case '2':
			stop(songs[playing]);
			playing = 0;
			break;
		case '3':
			if(playing > 1 && playing <= songNum)
			{
				stop(songs[playing]);
				//playing--;
				playing = (playing - 1 + isRndPlay * rand()) % songNum;
				if(playing == 0) playing = songNum;
				play(songs[playing]);
			}
			else if(playing < -1 && playing >= -songNum)
			{
				stop(songs[-playing]);
				//playing = -playing - 1;
				playing = (-playing-1 +isRndPlay*rand())%songNum;
				if(playing == 0) playing = songNum;
				play(songs[playing]);
			}
			else if(abs(playing) == 1)			//��1����һ��Ϊ���һ��
			{
				stop(songs[1]);
				playing = (songNum + isRndPlay * rand())%songNum;
				if(playing == 0) playing = songNum;
				play((songs[playing]));
			}
			else
				printf("������Ų���ȷ����һ���Ǹ���������Ա:)\n");
				Sleep(1000);
				while(kbhit()) getch();			//���sleep�ڼ������
			break;
		case '4':
			if(playing >= 0 && playing < songNum)
			{
				stop(songs[playing]);
				//playing++;
				playing = (playing + 1 + isRndPlay * rand()) % songNum;
				if(playing == 0) playing = songNum;
				play(songs[playing]);
			}
			else if(playing < 0 && playing >= -songNum)
			{
				stop(songs[-playing]);
				//playing = -playing + 1;
				playing = (-playing + 1 +isRndPlay*rand())%songNum;
				if(playing == 0) playing = songNum;
				play(songs[playing]);
			}
			else if(abs(playing) == songNum)			//���һ����һ��Ϊ��1��
			{
				stop(songs[abs(songNum)]);
				//playing = 1;
				playing = (1 + isRndPlay * rand())%songNum;
				if(playing == 0) playing = songNum;
				play((songs[playing]));
			}
			else
				printf("������Ų���ȷ����һ���Ǹ���������Ա:)\n");
				Sleep(1000);
				while(kbhit()) getch();			//���sleep�ڼ������
				break;
		case '5':
			isRndPlay = !isRndPlay;
			break;
		default:
			printf("�Ƿ�����!\n");
			Sleep(1000);
			while(kbhit()) getch();			//���sleep�ڼ������
			break;
		}
	}
}
void volctrl(void){
	while(1){
		system("cls");
		showstatus();
		printf("1. ��������\
			   \n2. ������С\
			   \n0. �˳�\
			   \n������������ͣ�\n");
		switch(getch())
		{
		case '0':
			return;
			break;
		case '1':
			printf("vol_up called\n");
			Sleep(1000);
			break;
		case '2':
			printf("vol_down called\n");
			Sleep(1000);
			break;
		default:
			printf("�Ƿ�����!\n");
			Sleep(1000);
			while(kbhit()) getch();			//���sleep�ڼ������
			break;
		}
	}
}
void killme(void){
	exit(0);
}

int main(int argc, char **argv){
	srand((unsigned)time(NULL));		//������ų�ʼ��
	
	while(songNum == 0)
	{
		printf("������MP3ý��·��:\n");
		scanf("%s",&dir);
		songNum = getPlaylist(&dir);
		printf("path = %s,��%d�׸�\n",&dir,songNum);
	}
	printf("�밴���������...\n");
	getch();
	while(1){
		system("cls");
		showstatus();
		printf("1. ���ſ���\
				\n2. ��������\
				\n0. �˳�\
				\n������������ͣ�\n");
		switch (getch())
		{
		case '0':
			killme();
		case '1':
			playctrl();
			break;
		case '2':
			volctrl();
			break;
		default:
			printf("�Ƿ�����!\n"); 
			Sleep(1000);
			while(kbhit()) getch();			//���sleep�ڼ������
			break;
		}
	}
	return 0;
}