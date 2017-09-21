#include "DxLib.h"
#include "GV.h"
#include "Block.h"
#include "Field.h"
#include "Score.h"

extern CBlock MovingBlock;							//�ړ����u���b�N�̃C���X�^���X����
extern CScoreManagement PlayerScore;				//�X�R�A�Ǘ��C���X�^���X����


int CField::ConvertPoint(int p){
	return p/20;
}
void CField::GetImage(){
	blockimg[BLOCK_TYPE_I] = LoadGraph( "dat/img/block/block_sky.png" );
	blockimg[BLOCK_TYPE_J] = LoadGraph( "dat/img/block/block_blue.png" );
	blockimg[BLOCK_TYPE_L] = LoadGraph( "dat/img/block/block_orange.png" );
	blockimg[BLOCK_TYPE_S] = LoadGraph( "dat/img/block/block_green.png" );
	blockimg[BLOCK_TYPE_Z] = LoadGraph( "dat/img/block/block_red.png" );
	blockimg[BLOCK_TYPE_T] = LoadGraph( "dat/img/block/block_purple.png" );
	blockimg[BLOCK_TYPE_O] = LoadGraph( "dat/img/block/block_yellow.png" );
	frameimg[0] = LoadGraph( "dat/img/main/Tmain.png" );
	frameimg[1] = LoadGraph( "dat/img/main/Tmain2.png" );
	backblackimg = LoadGraph( "dat/img/main/backblack.png" );
	backblueimg = LoadGraph( "dat/img/main/backblue.png" );
	holdimg = LoadGraph( "dat/img/main/hold.png" );
}
CField::CField(){
	int ini[FIELD_WIDTH][FIELD_HEIGHT]={
		//��
		9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,	//��
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,
		9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9
		//�E
		};
		for(int i = 0 ; i < FIELD_WIDTH ; i++ )
			for(int j = 0 ; j < 
				FIELD_HEIGHT ; j++ )
				field[i][j]=ini[i][j];
		gameoverflag  = 0;
		nextblockflag = 1;
		deleffectflag = 0;
} 

void CField::Draw1(){
	int px,py;
	DrawGraph( 0 , 0 , frameimg[0] , TRUE ) ;//�g�`��1
	DrawGraph( 220 , 60 , backblackimg , TRUE) ;

	for( px=0 ; px<FIELD_WIDTH ; px++ ){
		for( py=3 ; py<FIELD_HEIGHT ; py++ ){
			if(field[px][py] != 8 && FIELD_HEIGHT && field[px][py] != 9 ){
				DrawGraph( (10+px)*20 , (-1+py)*20 , blockimg[field[px][py]], FALSE );
			}
		}
	}
	DrawGraph( 480 , 40 , backblackimg , TRUE) ;
	DrawGraph( 480-20 , 40+20 , backblackimg , TRUE) ;
	DrawGraph( -40 , 40 , backblackimg , TRUE) ;
	DrawGraph( -40+20 , 40+20 , backblackimg , TRUE) ;


}

void CField::Draw2(){
	DrawGraph( 0 , 0 , frameimg[1] , TRUE ) ;//�A�Ȃ��g�`��
	DrawGraph( 0 , 20 , holdimg , TRUE );
}

int CField::CheckField(int px,int py){
	if(field[px][py]==8 && px<FIELD_WIDTH && px>0 && py<FIELD_HEIGHT && py>0)
		return 0;
	else
		return 1;
}
int CField::PutField(int px,int py ,int blocktype){
	if((px < FIELD_WIDTH) && (py < FIELD_HEIGHT) && field[px][py]==8 ){
		field[px][py]=blocktype;
		return 1;
	}
	return 0;
}


void CField::Gameover(){
	gameoverflag = 1;
}
int CField::CheckGameOver(){
	return gameoverflag;
}
void CField::Initial(){
	int ini[FIELD_WIDTH][FIELD_HEIGHT]={
	//��
	9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,	//��
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,
	9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9
	//�E
	};
	for(int i = 0 ; i < FIELD_WIDTH ; i++ )
		for(int j = 0 ; j <	FIELD_HEIGHT ; j++ )
				field[i][j]=ini[i][j];
	gameoverflag = 0;
	deleffectflag = 0;
}

int CField::CheckNextFlag(){
	return nextblockflag;
}
void CField::GameOverManagement(){
	int px,py;
	for(py=0;py<5;py++){
		for(px=3;px<9;px++){
			if(field[px][py] != 8)
				Gameover();
		}
	}
}
void CField::CopyToDummy(){
	int px,py;
	for(py=0;py<FIELD_WIDTH;py++){
		for(px=0;px<FIELD_HEIGHT;px++){
			dummyfield[0][py][px] = dummyfield[1][py][px] = dummyfield[2][py][px] = field[py][px];
		}
	}
}

void CField::CopyToMain(int dummytype){
	int px,py;
	for(py=0;py<FIELD_WIDTH;py++){
		for(px=0;px<FIELD_HEIGHT;px++){
			field[py][px] = dummyfield[dummytype][py][px];
		}
	}
}

int CField::CheckLine(int py){
	int px;
	for(px=1 ; px<FIELD_WIDTH-1 ; px++){
		if((py < FIELD_HEIGHT) && field[px][py]==8)				//������̃}�X�������
			return 0;											//0��Ԃ�
	}
	return 1;													//�P���C��������Ă���ꍇ1��Ԃ�
}

void CField::DelLine(int py){
	int i,px;
	for(i=1;i<3;i++){
		for(px=1 ; px<FIELD_WIDTH-1 ; px++){
			dummyfield[i][px][py]=8;
		}
	}
}
void CField::LineSlide(int py){
	int px;
	for( ; py>0 ; --py ){
		for(px=1 ; px<FIELD_WIDTH-1 ; px++){
		 	dummyfield[2][px][py] = dummyfield[2][px][py-1];
		}
	}
}
void CField::DummyFieldClac(){
	
}

int CField::CheckEffectFlag(){
	return deleffectflag;
}