#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>	// mci库头文件
#pragma comment(lib, "winmm.lib")	// 指定MCI库，mciSendString函数的定义在winmm.lib中


// 播放当前曲，曲号由curno记录
void play(const char *name)          //播放音乐
{
	char cmd[MAX_PATH] = {0};
	char pathname[MAX_PATH] = {0};

	// 加路径
	sprintf(pathname, ".\\music\\%s", name);
	// GetShortPathName用来转换短名，要求被转换的歌名必须能在指定目录下找到文件，否则转换失败。
	// 第一个参数：源文件名，第二个参数：目的文件名，第三个参数：目的数组长度。
	GetShortPathName(pathname, pathname, MAX_PATH);


	// 定义发往MCI的命令，cmd指定命令存储的数组，后面参数跟printf()相同
	sprintf(cmd, "open %s", pathname);
	// 发送命令。
	// 一、存储命令的数组首地址，二、接受MCI返回的信息，三、接受数组的长度，四、没用，NULL
	mciSendString(cmd, "", 0, NULL);
	sprintf(cmd, "play %s", pathname);
	mciSendString(cmd, "", 0, NULL);
}


// 暂停当前曲，曲号由curno记录
void pause(const char *name)        // 暂停播放
{
	char cmd[MAX_PATH] = {0};
	char pathname[MAX_PATH] = {0};
	
	// 加路径
	sprintf(pathname, ".\\music\\%s", name);
	// GetShortPathName用来转换短名，要求被转换的歌名必须能在指定目录下找到文件，否则转换失败。
	// 第一个参数：源文件名，第二个参数：目的文件名，第三个参数：目的数组长度。
	GetShortPathName(pathname, pathname, MAX_PATH);

	sprintf(cmd, "pause %s", pathname);
	mciSendString(cmd,"",0,NULL);
}

// 停止当前曲，曲号由curno记录
void stop(const char *name)         
{
	char cmd[MAX_PATH] = {0};
	char pathname[MAX_PATH] = {0};
	
	// 加路径
	sprintf(pathname, ".\\music\\%s", name);
	// GetShortPathName用来转换短名，要求被转换的歌名必须能在指定目录下找到文件，否则转换失败。
	// 第一个参数：源文件名，第二个参数：目的文件名，第三个参数：目的数组长度。
	GetShortPathName(pathname, pathname, MAX_PATH);

	sprintf(cmd, "stop %s", pathname);
	mciSendString(cmd,"",0,NULL); 
	sprintf(cmd, "close %s", pathname);
	mciSendString(cmd,"",0,NULL); 
}