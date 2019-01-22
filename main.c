#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include "PlayInterface.h"
#include "fileHandler.h"

#define MAX_SONG_NUM 200

char dir[20] = {0};

//		0：停止
//	 正数：正在播放
//	 负数：正在暂停
int playing = 0;
int songNum = 0;
boolean isRndPlay = 0;
// 歌曲文件名数组
char songs[MAX_SONG_NUM][50] = {""};

void showstatus()
{
	if(isRndPlay)
		printf("随机播放模式，");
	else
		printf("顺序播放模式，");
	if (playing == 0)
		printf("当前为停止状态\n");
	else if (playing > 0)
		printf("正在播放第%d曲:%s\n",playing,songs[playing]);
	else
		printf("正在暂停第%d曲:%s\n",-playing,songs[-playing]);
}

void playctrl(void){
	while(1){
		system("cls");
		showstatus();
		printf("1. 播放/暂停\
			   \n2. 停止\
			   \n3. 上一曲\
			   \n4. 下一曲\
			   \n5. 随机/顺序播放\
			   \n0. 退出\
			   \n请输入操作类型:\n");
		switch (getch())
		{
		case '0':
			return;
			break;
		case '1':
			if(playing == 0)				//停止状态时按1播放第1曲
			{
				playing = (1 + isRndPlay * rand())%songNum;
				if(playing == 0) playing = songNum;
				play(songs[playing]);
			}
			else if(playing > 0)			//播放状态时暂停该曲
			{
				playing = -playing;
				pause(songs[-playing]);
			}
			else							//暂停状态时播放该曲
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
			else if(abs(playing) == 1)			//第1首上一曲为最后一首
			{
				stop(songs[1]);
				playing = (songNum + isRndPlay * rand())%songNum;
				if(playing == 0) playing = songNum;
				play((songs[playing]));
			}
			else
				printf("歌曲序号不正确，你一定是个垃圾程序员:)\n");
				Sleep(1000);
				while(kbhit()) getch();			//清除sleep期间的输入
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
			else if(abs(playing) == songNum)			//最后一首上一曲为第1首
			{
				stop(songs[abs(songNum)]);
				//playing = 1;
				playing = (1 + isRndPlay * rand())%songNum;
				if(playing == 0) playing = songNum;
				play((songs[playing]));
			}
			else
				printf("歌曲序号不正确，你一定是个垃圾程序员:)\n");
				Sleep(1000);
				while(kbhit()) getch();			//清除sleep期间的输入
				break;
		case '5':
			isRndPlay = !isRndPlay;
			break;
		default:
			printf("非法输入!\n");
			Sleep(1000);
			while(kbhit()) getch();			//清除sleep期间的输入
			break;
		}
	}
}
void volctrl(void){
	while(1){
		system("cls");
		showstatus();
		printf("1. 音量增大\
			   \n2. 音量减小\
			   \n0. 退出\
			   \n请输入操作类型：\n");
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
			printf("非法输入!\n");
			Sleep(1000);
			while(kbhit()) getch();			//清除sleep期间的输入
			break;
		}
	}
}
void killme(void){
	exit(0);
}

int main(int argc, char **argv){
	srand((unsigned)time(NULL));		//随机播放初始化
	
	while(songNum == 0)
	{
		printf("请输入MP3媒体路径:\n");
		scanf("%s",&dir);
		songNum = getPlaylist(&dir);
		printf("path = %s,共%d首歌\n",&dir,songNum);
	}
	printf("请按任意键继续...\n");
	getch();
	while(1){
		system("cls");
		showstatus();
		printf("1. 播放控制\
				\n2. 音量调节\
				\n0. 退出\
				\n请输入操作类型：\n");
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
			printf("非法输入!\n"); 
			Sleep(1000);
			while(kbhit()) getch();			//清除sleep期间的输入
			break;
		}
	}
	return 0;
}