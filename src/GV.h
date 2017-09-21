#include "DxLib.h"
#include "Define.h"


typedef struct{
	char *title;
	char *bgm[19];						//サウンドファイルへのパスを格納
	int se[10];
	int ending;
}SOUND;

typedef struct{
	int Arrow;
	int black;
	int title;
	int CRClogo;
	int TETLIS;
	int stage[20];
}IMAGE;

typedef struct{
	int score[10];
	int level[10];
	int lines[10];
	int h[10];
	int m[10];
	int s[10];
	int ds[10];
	char name[10][11];
}RANKING;

#ifdef _GLOBAL_INSTANCE_
#define GLOBAL
#else
#define GLOBAL extern 
#endif

GLOBAL char Key[256];
GLOBAL int  OldKey[256];
GLOBAL int Font1;
GLOBAL int Font2;
GLOBAL int Font3;
GLOBAL int fadeoutflg;
GLOBAL int fadeinflg;
GLOBAL int fadeoutcnt;
GLOBAL int fadeincnt;
GLOBAL SOUND Snd;
GLOBAL IMAGE Img;
GLOBAL RANKING NORMAL;
GLOBAL RANKING ENDLESS;
