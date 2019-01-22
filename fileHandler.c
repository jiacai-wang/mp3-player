#include <stdio.h>
#include <io.h>
#define MAX_SONG_NUM 200 

extern char songs[MAX_SONG_NUM][50];

//返回path路径下的.mp3文件数
int getPlaylist(char *path)
{
	long Handle = 0;
	int songNum = 0;
	struct _finddata_t FileInfo;
	//if((Handle=_findfirst(".\\music\\*.mp3",&FileInfo))==-1L)
	if((Handle=_findfirst(strcat(path,"\\*.mp3"),&FileInfo))==-1L)
	{
		printf("没有找到匹配的项目\n");
	}
	else
	{
		strcpy(songs[++songNum],FileInfo.name);

		printf("%d: %s\n",songNum,FileInfo.name);
		while(_findnext(Handle,&FileInfo)==0 && songNum<MAX_SONG_NUM)
		{
			strcpy(songs[++songNum],FileInfo.name);
			printf("%d: %s\n",songNum,FileInfo.name);
		}
		_findclose(Handle);
	}
	return songNum;
}