#include "DxLib.h"
#include "GV.h"
#include "Score.h"

//得点関係
CScoreManagement::CScoreManagement(){			//初期値
	score = 0;
	level = 1;
	line = 0;
	playtime = 0;
	dline = 0;
}
void CScoreManagement::Initial(){			//同じことかいときまーす。
	score = 0;
	level = 1;
	line = 0;
	playtime = 0;
	dline = 0;
}

void CScoreManagement::DrawScore(){
	DrawFormatStringToHandle( 0+FONT_SHADOW_WIDTH, 150+FONT_SHADOW_WIDTH, GetColor( 000 , 000 , 000 ), Font1, ">>LEVEL");
	DrawFormatStringToHandle( 0+FONT_SHADOW_WIDTH, 180+FONT_SHADOW_WIDTH, GetColor( 000 , 000 , 000 ), Font1, "        %02d", level);
	DrawFormatStringToHandle( 0+FONT_SHADOW_WIDTH, 230+FONT_SHADOW_WIDTH, GetColor( 000 , 000 , 000 ), Font1, ">>SCORE");
	DrawFormatStringToHandle( 0+FONT_SHADOW_WIDTH, 260+FONT_SHADOW_WIDTH, GetColor( 000 , 000 , 000 ), Font1, "    %08d", score);
	DrawFormatStringToHandle( 0+FONT_SHADOW_WIDTH, 310+FONT_SHADOW_WIDTH, GetColor( 000 , 000 , 000 ), Font1, ">>LINES");
	DrawFormatStringToHandle( 0+FONT_SHADOW_WIDTH, 340+FONT_SHADOW_WIDTH, GetColor( 000 , 000 , 000 ), Font1, "       %04d", line);
	DrawFormatStringToHandle( 0+FONT_SHADOW_WIDTH, 390+FONT_SHADOW_WIDTH, GetColor( 000 , 000 , 000 ), Font1, ">>PLAYTIME");
	DrawFormatStringToHandle( 10+FONT_SHADOW_WIDTH, 420+FONT_SHADOW_WIDTH, GetColor( 000 , 000 , 000 ), Font1, "   %02d:%02d:%02d.%1d",h,m,s,ds);

	DrawFormatStringToHandle( 0, 150, GetColor( 250 , 250 , 128 ), Font1, ">>LEVEL");
	DrawFormatStringToHandle( 0, 180, GetColor( 250 , 250 , 180 ), Font1, "        %02d", level);
	DrawFormatStringToHandle( 0, 230, GetColor( 250 , 250 , 128 ), Font1, ">>SCORE");
	DrawFormatStringToHandle( 0, 260, GetColor( 250 , 250 , 180 ), Font1, "    %08d", score);
	DrawFormatStringToHandle( 0, 310, GetColor( 250 , 250 , 128 ), Font1, ">>LINES");
	DrawFormatStringToHandle( 0, 340, GetColor( 250 , 250 , 180 ), Font1, "       %04d", line);
	DrawFormatStringToHandle( 0, 390, GetColor( 250 , 250 , 128 ), Font1, ">>PLAYTIME");
	DrawFormatStringToHandle( 10, 420, GetColor( 250 , 250 , 180 ), Font1, "   %02d:%02d:%02d.%1d",h,m,s,ds);

}

void CScoreManagement::AddScore(){
	score += dline*dline*dline*100;
}

void CScoreManagement::AddDelLine(){
	if((++line %10 )==0)
		LevelUp();
}

void CScoreManagement::GetDelLines1(){
	dlinetmp = line;
}

void CScoreManagement::GetDelLines2(){
	if( line == dlinetmp )
		return;
	else{
		dline = line - dlinetmp;
		AddScore();
	}
}
void CScoreManagement::LevelUp(){
	if(level<20){
		level++;
		PlaySoundMem( Snd.se[8] , DX_PLAYTYPE_BACK );
	}
}
int CScoreManagement::CheckLevel(){
	return level;
}

void CScoreManagement::PlayTimeCalc(int cnt){
	int time;
	ds = (cnt/3)%10;
	time = cnt / 30;
	s = time % 60;
	time /= 60;
	m = time % 60;
	time /= 60;
	h = time % 60;
}


int CScoreManagement::CheckDelLines(){
	return line;
}


void CScoreManagement::ReadRanking(){
	int i,n=0,num=0;
	int inputi[64];
	char inputc[64];
	FILE *fp1;
	FILE *fp2;//ファイルハンドル
	fp1 = fopen("RANK/ENDLESS.dat", "r");
	fp2 = fopen("RANK/NORMAL.dat", "r");
	if(fp1 == NULL || fp2 == NULL)
		return;
	while(1){
		for(i=0;i<64;i++){
			inputc[i]=inputi[i]=getc(fp1);//1文字取得する

			if(inputc[i]=='/'){//スラッシュがあるなら以後読み飛ばし
				while(getc(fp1)!='\n');
				i=-1;
				continue;
			}
			if(inputi[i]==',' || inputi[i]=='\n'){
				inputc[i]='\0';
				break;
			}
			if(inputi[i]==EOF){
				 goto EXFILE;//終了
			}
		}
		switch(num){
			case 0:	ENDLESS.score[n]	=	atoi(inputc);	break;
			case 1:	ENDLESS.level[n]	=	atoi(inputc);	break;
			case 2:	ENDLESS.lines[n]	=	atoi(inputc);	break;
			case 3:	ENDLESS.h[n]		=	atoi(inputc);	break;
			case 4:	ENDLESS.m[n]		=	atoi(inputc);	break;
			case 5:	ENDLESS.s[n]		=	atoi(inputc);	break;
			case 6:	ENDLESS.ds[n]		=	atoi(inputc);	break;
			case 7:	strcpy(ENDLESS.name[n],inputc);			break;
		}
		num++;
		if(num==8){
			num=0;
			n++;
		}
	}
EXFILE:
	fclose( fp1 );
	n=num=0;
	while(1){
		for(i=0;i<64;i++){
			inputc[i]=inputi[i]=getc(fp2);//1文字取得する

			if(inputc[i]=='/'){//スラッシュがあるなら以後読み飛ばし
				while(getc(fp2)!='\n');
				i=-1;
				continue;
			}
			if(inputi[i]==',' || inputi[i]=='\n'){
				inputc[i]='\0';
				break;
			}
			if(inputi[i]==EOF){
				 goto EXFILE2;//終了
			}
		}
		switch(num){
			case 0:	NORMAL.score[n]	=	atoi(inputc);	break;
			case 1:	NORMAL.level[n]	=	atoi(inputc);	break;
			case 2:	NORMAL.lines[n]	=	atoi(inputc);	break;
			case 3:	NORMAL.h[n]		=	atoi(inputc);	break;
			case 4:	NORMAL.m[n]		=	atoi(inputc);	break;
			case 5:	NORMAL.s[n]		=	atoi(inputc);	break;
			case 6:	NORMAL.ds[n]	=	atoi(inputc);	break;
			case 7:	strcpy(NORMAL.name[n],inputc);		break;
		}
		num++;
		if(num==8){
			num=0;
			n++;
		}
	}
EXFILE2:
	fclose( fp2 );

}

void CScoreManagement::DrawRanking(int GAMEMODE){
	int i;
	DrawBox( 20 , 40 , 620 , 460 , GetColor( 210 , 210 , 210 ) , TRUE ) ;
	DrawBox( 27 , 47 , 613 , 453 , GetColor( 0 , 0 , 0 ) , FALSE ) ;
	DrawFormatStringToHandle( 21, 61, GetColor( 0 , 0 , 0 ), Font3, "  RANK     NAME        SCORE     LV LINES PLAY TIME");
	DrawFormatStringToHandle( 20, 60, GetColor( 128 , 92 , 92 ), Font3, "  RANK     NAME        SCORE     LV LINES PLAY TIME");
	if(GAMEMODE==STATE_NORMAL){
		DrawFormatStringToHandle( 20+FONT_SHADOW_WIDTH, 20+FONT_SHADOW_WIDTH, GetColor( 0 , 0 , 0 ), Font1, "NORMAL MODE");
		DrawFormatStringToHandle( 20, 20, GetColor( 240 , 240 , 240 ), Font1, "NORMAL MODE");
		for(i=0;i<10;i++){
			DrawFormatStringToHandle( 51, 100+DRAW_RANK_WIDTH*i+1, GetColor( 0 , 0 , 0 ), Font3, "%02d",i+1);
			DrawFormatStringToHandle( 50, 100+DRAW_RANK_WIDTH*i, GetColor( 128 , 128 , 92 ), Font3, "%02d",i+1);
			DrawFormatStringToHandle( DRAW_RANK_NAME_X+1, DRAW_RANK_NAME_Y+DRAW_RANK_WIDTH*i+1, GetColor( 0 , 0 , 0 ), Font3, "%-10s",NORMAL.name[i]);
			DrawFormatStringToHandle( DRAW_RANK_NAME_X, DRAW_RANK_NAME_Y+DRAW_RANK_WIDTH*i, GetColor( 92, 92, 169  ), Font3, "%-10s",NORMAL.name[i]);

			DrawFormatStringToHandle( DRAW_RANK_SCORE_X+1, DRAW_RANK_SCORE_Y+DRAW_RANK_WIDTH*i+1, GetColor( 0 , 0 , 0 ), Font3, "%08d   %02d  %04d   %02d:%02d:%02d.%1d",
				NORMAL.score[i],NORMAL.level[i],NORMAL.lines[i],NORMAL.h[i],NORMAL.m[i],NORMAL.s[i],NORMAL.ds[i]);
			DrawFormatStringToHandle( DRAW_RANK_SCORE_X, DRAW_RANK_SCORE_Y+DRAW_RANK_WIDTH*i, GetColor(  128 , 128, 128  ), Font3, "%08d   %02d  %04d   %02d:%02d:%02d.%1d",
				NORMAL.score[i],NORMAL.level[i],NORMAL.lines[i],NORMAL.h[i],NORMAL.m[i],NORMAL.s[i],NORMAL.ds[i]);
		}
	}

	else if(GAMEMODE==STATE_ENDLESS){
		DrawFormatStringToHandle( 20+FONT_SHADOW_WIDTH, 20+FONT_SHADOW_WIDTH, GetColor( 0 , 0 , 0 ), Font1, "ENDLESS MODE");
		DrawFormatStringToHandle( 20, 20, GetColor( 240 , 240 , 240 ), Font1, "ENDLESS MODE");
		for(i=0;i<10;i++){
			DrawFormatStringToHandle( 51, 100+DRAW_RANK_WIDTH*i+1, GetColor( 0 , 0 , 0 ), Font3, "%02d",i+1);
			DrawFormatStringToHandle( 50, 100+DRAW_RANK_WIDTH*i, GetColor( 128 , 128 , 92 ), Font3, "%02d",i+1);

			DrawFormatStringToHandle( DRAW_RANK_NAME_X+1, DRAW_RANK_NAME_Y+DRAW_RANK_WIDTH*i+1, GetColor( 0 , 0 , 0 ), Font3, "%-10s",ENDLESS.name[i]);
			DrawFormatStringToHandle( DRAW_RANK_NAME_X, DRAW_RANK_NAME_Y+DRAW_RANK_WIDTH*i, GetColor( 92, 92, 169 ), Font3, "%-10s",ENDLESS.name[i]);

			DrawFormatStringToHandle( DRAW_RANK_SCORE_X+1, DRAW_RANK_SCORE_Y+DRAW_RANK_WIDTH*i+1, GetColor( 0 , 0 , 0 ), Font3, "%08d   %02d  %04d   %02d:%02d:%02d.%1d",
				ENDLESS.score[i],ENDLESS.level[i],ENDLESS.lines[i],ENDLESS.h[i],ENDLESS.m[i],ENDLESS.s[i],ENDLESS.ds[i]);
			DrawFormatStringToHandle( DRAW_RANK_SCORE_X, DRAW_RANK_SCORE_Y+DRAW_RANK_WIDTH*i, GetColor( 128 , 128, 128 ), Font3, "%08d   %02d  %04d   %02d:%02d:%02d.%1d",
				ENDLESS.score[i],ENDLESS.level[i],ENDLESS.lines[i],ENDLESS.h[i],ENDLESS.m[i],ENDLESS.s[i],ENDLESS.ds[i]);
		}
	}
}

void CScoreManagement::WriteRanking(){
	int i;
	FILE *fp1;
	FILE *fp2;//ファイルハンドル
	fp1 = fopen("RANK/ENDLESS.dat", "w");
	fp2 = fopen("RANK/NORMAL.dat", "w");
	if(fp1 == NULL || fp2 == NULL)
		return;
	for(i=0;i<10;i++){
		fprintf(fp1,"%d,%d,%d,%d,%d,%d,%d,%s\n",
			ENDLESS.score[i], ENDLESS.level[i], ENDLESS.lines[i], ENDLESS.h[i], ENDLESS.m[i], ENDLESS.s[i], ENDLESS.ds[i], ENDLESS.name[i]);
	}
	fclose( fp1 );

	for(i=0;i<10;i++){
		fprintf(fp2,"%d,%d,%d,%d,%d,%d,%d,%s\n",
			NORMAL.score[i], NORMAL.level[i],NORMAL.lines[i], NORMAL.h[i], NORMAL.m[i], NORMAL.s[i],NORMAL.ds[i],NORMAL.name[i]);
	}
	fclose( fp2 );
}

void CScoreManagement::GetPlayerName(){
	DrawFormatStringToHandle( 230 , 210 , GetColor( 255 , 255 , 255 ) ,Font2 ,"Please input your name.");
	DrawBox(270,235,370,260,GetColor(255,255,255),FALSE);
	ScreenFlip();
	KeyInputSingleCharString( 275 , 240 , 10 , playername , FALSE );
}

int CScoreManagement::CheckRankIn(int GAMEMODE){
	int i,rank=0;
	if(GAMEMODE == STATE_NORMAL){
		for(i=0;i<10;i++){
			if(NORMAL.score[i]>=score)
				rank++;
		}
	}
	else if(GAMEMODE == STATE_ENDLESS){
		for(i=0;i<10;i++){
			if(ENDLESS.score[i]>=score)
				rank++;
		}
	}
	return rank;
}

void CScoreManagement::UpdateRanking(int GAMEMODE){
	int i,j;
	i = CheckRankIn(GAMEMODE);
	if(GAMEMODE == STATE_NORMAL){
		for(j=9;j>i;j--){
			strcpy(NORMAL.name[j],NORMAL.name[j-1]);
			NORMAL.score[j]	=	NORMAL.score[j-1];
			NORMAL.level[j]	=	NORMAL.level[j-1];
			NORMAL.lines[j]	=	NORMAL.lines[j-1];
			NORMAL.h[j]		=	NORMAL.h[j-1];
			NORMAL.m[j]		=	NORMAL.m[j-1];
			NORMAL.s[j]		=	NORMAL.s[j-1];
			NORMAL.ds[j]	=	NORMAL.ds[j-1];
		}
		strcpy(NORMAL.name[i],playername);
		NORMAL.score[i]	=	score;
		NORMAL.level[i]	=	level;
		NORMAL.lines[i]	=	line;
		NORMAL.h[i]		=	h;
		NORMAL.m[i]		=	m;
		NORMAL.s[i]		=	s;
		NORMAL.ds[i]	=	ds;
	}
	else if(GAMEMODE == STATE_ENDLESS){
		for(j=9;j>i;j--){
			strcpy(ENDLESS.name[j],ENDLESS.name[j-1]);
			ENDLESS.score[j]	=	ENDLESS.score[j-1];
			ENDLESS.level[j]	=	ENDLESS.level[j-1];
			ENDLESS.lines[j]	=	ENDLESS.lines[j-1];
			ENDLESS.h[j]		=	ENDLESS.h[j-1];
			ENDLESS.m[j]		=	ENDLESS.m[j-1];
			ENDLESS.s[j]		=	ENDLESS.s[j-1];
			ENDLESS.ds[j]		=	ENDLESS.ds[j-1];
		}
		strcpy(ENDLESS.name[i],playername);
		ENDLESS.score[i]=	score;
		ENDLESS.level[i]=	level;
		ENDLESS.lines[i]=	line;
		ENDLESS.h[i]	=	h;
		ENDLESS.m[i]	=	m;
		ENDLESS.s[i]	=	s;
		ENDLESS.ds[i]	=	ds;
	}
}