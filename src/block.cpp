#include "DxLib.h"
#include "GV.h"
#include "Block.h"
#include "Field.h"
#include "Score.h"
#include <math.h>


extern CField MainField;
extern CScoreManagement PlayerScore;
extern unsigned int maincounter;


int CBlock::Rotation(){														//回転制御関数

	int px,py,cand=0;
	int dummycell[BLOCK_MAX_X][BLOCK_MAX_Y];								//作業用ダミーセル
	
	if(OldKey[KEY_INPUT_X]==1 && type != BLOCK_TYPE_O){						//右回転処理
		if(state == 3)
			state = 0;
		else
			state++;
NextRoteR:
		for(py=0 ; py<BLOCK_MAX_Y ; py++){
			for(px=0 ; px<BLOCK_MAX_X ; px++){
				switch(type){
					case BLOCK_TYPE_I:
						dummycell[py][px] = IRight[state*BLOCK_MAX_Y*ROTATION_CANDIDATE+BLOCK_MAX_Y*cand+py][px];
						break;

					case BLOCK_TYPE_J:
						dummycell[py][px] = JRight[state*BLOCK_MAX_Y*ROTATION_CANDIDATE+BLOCK_MAX_Y*cand+py][px];
						break;

					case BLOCK_TYPE_L:
						dummycell[py][px] = LRight[state*BLOCK_MAX_Y*ROTATION_CANDIDATE+BLOCK_MAX_Y*cand+py][px];
						break;

					case BLOCK_TYPE_S:
						dummycell[py][px] = SRight[state*BLOCK_MAX_Y*ROTATION_CANDIDATE+BLOCK_MAX_Y*cand+py][px];
						break;

					case BLOCK_TYPE_Z:
						dummycell[py][px] = ZRight[state*BLOCK_MAX_Y*ROTATION_CANDIDATE+BLOCK_MAX_Y*cand+py][px];
						break;

					case BLOCK_TYPE_T:
						dummycell[py][px] = TRight[state*BLOCK_MAX_Y*ROTATION_CANDIDATE+BLOCK_MAX_Y*cand+py][px];
						break;
				}

				if( dummycell[py][px]==1 && MainField.CheckField(x/20+px,y/20+py+1)==1 && cand==4 ){
					if(state == 0)
						state = 3;
					else
						state--;
					return 0;				//すべての候補で回転できなかった場合
				}
				else if( dummycell[py][px]==1 && MainField.CheckField(x/20+px,y/20+py+1)==1 ){
					cand++;					//回転できなかった場合次の候補へ
					goto NextRoteR;
				}
			}
		}
		PlaySoundMem( Snd.se[0] , DX_PLAYTYPE_BACK ) ;
		if(actions<10){
			landcnt=0;
			actions++;
		}
	}

	else if(OldKey[KEY_INPUT_Z]==1 && type != BLOCK_TYPE_O){				//左回転処理
		if(state == 0)
			state = 3;
		else
			state--;
NextRoteL:
		for(py=0 ; py<BLOCK_MAX_Y ; py++){
			for(px=0 ; px<BLOCK_MAX_X ; px++){
				switch(type){
					case BLOCK_TYPE_I:
						dummycell[py][px] = ILeft[ (state*BLOCK_MAX_Y*ROTATION_CANDIDATE) + (BLOCK_MAX_Y*cand) + py][px];
						break;

					case BLOCK_TYPE_J:
						dummycell[py][px] = JLeft[state*BLOCK_MAX_Y*ROTATION_CANDIDATE+BLOCK_MAX_Y*cand+py][px];
						break;

					case BLOCK_TYPE_L:
						dummycell[py][px] = LLeft[state*BLOCK_MAX_Y*ROTATION_CANDIDATE+BLOCK_MAX_Y*cand+py][px];
						break;

					case BLOCK_TYPE_S:
						dummycell[py][px] = SLeft[state*BLOCK_MAX_Y*ROTATION_CANDIDATE+BLOCK_MAX_Y*cand+py][px];
						break;

					case BLOCK_TYPE_Z:
						dummycell[py][px] = ZLeft[state*BLOCK_MAX_Y*ROTATION_CANDIDATE+BLOCK_MAX_Y*cand+py][px];
						break;

					case BLOCK_TYPE_T:
						dummycell[py][px] = TLeft[state*BLOCK_MAX_Y*ROTATION_CANDIDATE+BLOCK_MAX_Y*cand+py][px];
						break;
				}
				if( dummycell[py][px]==1 && MainField.CheckField(x/20+px,y/20+py+1)==1 && cand==4){		//すべての候補で回転できなかった場合
					if(state == 0)
						state = 3;
					else
						state--;
					return 0;								
				}
				else if( dummycell[py][px]==1 && MainField.CheckField(x/20+px,y/20+py+1)==1 ){
					cand++;								//回転できなかった場合次の候補へ
					goto NextRoteL;
				}
			}
		}
		PlaySoundMem( Snd.se[1] , DX_PLAYTYPE_BACK ) ;
		if(actions<10){
			landcnt=0;
			actions++;
		}
	}

	else{
		return 0;
	}

	for(px=0 ; px<BLOCK_MAX_X ; px++){						//回転に成功した場合、本物のセルにコピー
		for(py=0 ; py<BLOCK_MAX_Y ; py++){
			cell[0][px][py] = dummycell[py][px];
		}
	}
	
	return 1;
}

void CBlock::GetImage(){
	blockimg[BLOCK_TYPE_I] = LoadGraph( "dat/img/block/block_sky.png" );
	blockimg[BLOCK_TYPE_J] = LoadGraph( "dat/img/block/block_blue.png" );
	blockimg[BLOCK_TYPE_L] = LoadGraph( "dat/img/block/block_orange.png" );
	blockimg[BLOCK_TYPE_S] = LoadGraph( "dat/img/block/block_green.png" );
	blockimg[BLOCK_TYPE_Z] = LoadGraph( "dat/img/block/block_red.png" );
	blockimg[BLOCK_TYPE_T] = LoadGraph( "dat/img/block/block_purple.png" );
	blockimg[BLOCK_TYPE_O] = LoadGraph( "dat/img/block/block_yellow.png" );
}
CBlock::CBlock(){

	nx[0] = NEXT_DRAW_X_1;
	nx[1] = NEXT_DRAW_X_2;
	nx[2] = NEXT_DRAW_X_3;
	nx[3] = NEXT_DRAW_X_4;
	nx[4] = NEXT_DRAW_X_5;

	ny[0] = NEXT_DRAW_Y_1;
	ny[1] = NEXT_DRAW_Y_2;
	ny[2] = NEXT_DRAW_Y_3;
	ny[3] = NEXT_DRAW_Y_4;
	ny[4] = NEXT_DRAW_Y_5;

	int FHandle[2][6];			//[0が右回転　1が左回転][ブロックタイプ]

	int h,i,j,k;
	char cache;

	FHandle[0][BLOCK_TYPE_I] = FileRead_open( "dat/calc/IRight.csv" );
	FHandle[0][BLOCK_TYPE_J] = FileRead_open( "dat/calc/JRight.csv" );
	FHandle[0][BLOCK_TYPE_L] = FileRead_open( "dat/calc/LRight.csv" );
	FHandle[0][BLOCK_TYPE_S] = FileRead_open( "dat/calc/SRight.csv" );
	FHandle[0][BLOCK_TYPE_Z] = FileRead_open( "dat/calc/ZRight.csv" );
	FHandle[0][BLOCK_TYPE_T] = FileRead_open( "dat/calc/TRight.csv" );

	FHandle[1][BLOCK_TYPE_I] = FileRead_open( "dat/calc/ILeft.csv" );
	FHandle[1][BLOCK_TYPE_J] = FileRead_open( "dat/calc/JLeft.csv" );
	FHandle[1][BLOCK_TYPE_L] = FileRead_open( "dat/calc/LLeft.csv" );
	FHandle[1][BLOCK_TYPE_S] = FileRead_open( "dat/calc/SLeft.csv" );
	FHandle[1][BLOCK_TYPE_Z] = FileRead_open( "dat/calc/ZLeft.csv" );
	FHandle[1][BLOCK_TYPE_T] = FileRead_open( "dat/calc/TLeft.csv" );

	for(k=0 ; k<5 ; k++){
		nexttype[k] = 0;
	}
	x=y=0;
	landcnt=0;
	flag=0;
	state=0;


	for( h=0 ; h<2 ; h++ ){
		for( i=0 ; i<BLOCK_MAX_Y*5*4 ; i++){
			for( j=0 ; j<BLOCK_MAX_X ; ){
				cache = FileRead_getc(FHandle[h][BLOCK_TYPE_I]);
				if( cache == ',' ){
					continue;
				}
				else if( cache == '0' || cache == '1' ){
					if(h==0)
						IRight[i][j] = atoi(&cache);
					else
						ILeft[i][j] = atoi(&cache);
					j++;
				}
			}
		}
	}

	for( h=0 ; h<2 ; h++ ){
		for( i=0 ; i<BLOCK_MAX_Y*5*4 ; i++){
			for( j=0 ; j<BLOCK_MAX_X ; ){
				cache = FileRead_getc(FHandle[h][BLOCK_TYPE_J]);
				if( cache == ',' ){
					continue;
				}
				else if( cache == '0' || cache == '1' ){
					if(h==0)
						JRight[i][j] = atoi(&cache);
					else
						JLeft[i][j] = atoi(&cache);
					j++;
				}
			}
		}
	}

	for( h=0 ; h<2 ; h++ ){
		for( i=0 ; i<BLOCK_MAX_Y*5*4 ; i++){
			for( j=0 ; j<BLOCK_MAX_X ; ){
				cache = FileRead_getc(FHandle[h][BLOCK_TYPE_L]);
				if( cache == ',' ){
					continue;
				}
				else if( cache == '0' || cache == '1' ){
					if(h==0)
						LRight[i][j] = atoi(&cache);
					else
						LLeft[i][j] = atoi(&cache);
					j++;
				}
			}
		}
	}

	for( h=0 ; h<2 ; h++ ){
		for( i=0 ; i<BLOCK_MAX_Y*5*4 ; i++){
			for( j=0 ; j<BLOCK_MAX_X ; ){
				cache = FileRead_getc(FHandle[h][BLOCK_TYPE_S]);
				if( cache == ',' ){
					continue;
				}
				else if( cache == '0' || cache == '1' ){
					if(h==0)
						SRight[i][j] = atoi(&cache);
					else
						SLeft[i][j] = atoi(&cache);
					j++;
				}
			}
		}
	}

	for( h=0 ; h<2 ; h++ ){
		for( i=0 ; i<BLOCK_MAX_Y*5*4 ; i++){
			for( j=0 ; j<BLOCK_MAX_X ; ){
				cache = FileRead_getc(FHandle[h][BLOCK_TYPE_Z]);
				if( cache == ',' ){
					continue;
				}
				else if( cache == '0' || cache == '1' ){
					if(h==0)
						ZRight[i][j] = atoi(&cache);
					else
						ZLeft[i][j] = atoi(&cache);
					j++;
				}
			}
		}
	}

	for( h=0 ; h<2 ; h++ ){
		for( i=0 ; i<BLOCK_MAX_Y*5*4 ; i++){
			for( j=0 ; j<BLOCK_MAX_X ; ){
				cache = FileRead_getc(FHandle[h][BLOCK_TYPE_T]);
				if( cache == ',' ){
					continue;
				}
				else if( cache == '0' || cache == '1' ){
					if(h==0)
						TRight[i][j] = atoi(&cache);
					else
						TLeft[i][j] = atoi(&cache);
					j++;
				}
			}
		}
	}

	FileRead_close( FHandle[0][BLOCK_TYPE_I] );
	FileRead_close( FHandle[0][BLOCK_TYPE_J] );
	FileRead_close( FHandle[0][BLOCK_TYPE_L] );
	FileRead_close( FHandle[0][BLOCK_TYPE_S] );
	FileRead_close( FHandle[0][BLOCK_TYPE_Z] );
	FileRead_close( FHandle[0][BLOCK_TYPE_T] );

	FileRead_close( FHandle[1][BLOCK_TYPE_I] );
	FileRead_close( FHandle[1][BLOCK_TYPE_J] );
	FileRead_close( FHandle[1][BLOCK_TYPE_L] );
	FileRead_close( FHandle[1][BLOCK_TYPE_S] );
	FileRead_close( FHandle[1][BLOCK_TYPE_Z] );
	FileRead_close( FHandle[1][BLOCK_TYPE_T] );

}


int CBlock::NextBlock(){
	int px,py,i;
	type = nexttype[0];

	for(i=0 ; i<NEXT_ALL ; i++){
		//動かしてるブロックをとりあえず削除
		for(px=0 ; px<BLOCK_MAX_X ; px++){
			for(py=0 ; py<BLOCK_MAX_X ; py++){
				cell[i][px][py] = 0;
			}
		}

		switch(nexttype[i]){
		case BLOCK_TYPE_I:
			cell[i][2][3] = 1;
			cell[i][3][3] = 1;
			cell[i][4][3] = 1;
			cell[i][5][3] = 1;
			break;
		case BLOCK_TYPE_J:
			cell[i][2][2] = 1;
			cell[i][2][3] = 1;
			cell[i][3][3] = 1;
			cell[i][4][3] = 1;
			break;
		case BLOCK_TYPE_L:
			cell[i][2][3] = 1;
			cell[i][3][3] = 1;
			cell[i][4][3] = 1;
			cell[i][4][2] = 1;
			break;
		case BLOCK_TYPE_S:
			cell[i][2][3] = 1;
			cell[i][3][3] = 1;
			cell[i][3][2] = 1;
			cell[i][4][2] = 1;
			break;
		case BLOCK_TYPE_Z:
			cell[i][2][2] = 1;
			cell[i][3][2] = 1;
			cell[i][3][3] = 1;
			cell[i][4][3] = 1;
			break;
		case BLOCK_TYPE_T:
			cell[i][3][2] = 1;
			cell[i][2][3] = 1;
			cell[i][3][3] = 1;
			cell[i][4][3] = 1;
			break;
		case BLOCK_TYPE_O:
			cell[i][3][2] = 1;
			cell[i][4][2] = 1;
			cell[i][3][3] = 1;
			cell[i][4][3] = 1;
			break;
		}
	}

	//次のブロックの配列をスライド
	for(i=0 ; i<NEXT_ALL-1 ; i++)
		nexttype[i] = nexttype[i+1];
	state = 0;
	x = 20*2;
	y = 0;
	CopyTime();
	flag = 1;
	landcnt=0;
	fallperframe = 0;
	harddropflag = 0;
	actions = 0;
	return 0;
}

void CBlock::Fall(){
	if(flag){
		int i;
		for(i=0 ; i<fallperframe && CheckUnderBlock() == 0 ; i++)
			y+=20;
	}
}

void CBlock::DrawNext(){
	int i,px,py;
	for( i=1 ; i<NEXT_ALL ; i++ ){
		for( px=0 ; px<BLOCK_MAX_X ; px++ ){
			for( py=0 ; py<BLOCK_MAX_Y ; py++ ){
				if(cell[i][px][py]==1){
					(i==1)?
						DrawExtendGraph( nx[i-1] + px*20*4/5 , ny[i-1] + py*20*4/5, nx[i-1] + (px+1)*20*4/5, ny[i-1] + (py+1)*20*4/5, blockimg[nexttype[i-1]], FALSE ):
						DrawGraph( nx[i-1]+px*20 , ny[i-1]+py*20 , blockimg[nexttype[i-1]], FALSE );
				}
			}
		}
	}
}
void CBlock::DrawBlock(){
	int px,py;
	if(flag){
		for( px=0 ; px<BLOCK_MAX_X ; px++ ){
			for( py=0 ; py<BLOCK_MAX_Y ; py++ ){
				if(cell[0][px][py] == 1 && y+py*BLOCK_IMG_SIZE > BLOCK_IMG_SIZE*3 ){
					DrawGraph( x+(10+px)*BLOCK_IMG_SIZE , y+py*BLOCK_IMG_SIZE , blockimg[type], FALSE );
				}
			}
		}
	}
	/*
	DrawFormatString( 450, 190, GetColor( 255 , 255, 255 ) , "出現個数");
	DrawFormatString( 450, 220, GetColor( 255 , 255, 255 ) , "I\t%05d",blockappcnt[0]);
	DrawFormatString( 450, 250, GetColor( 255 , 255, 255 ) , "J\t%05d",blockappcnt[1]);
	DrawFormatString( 450, 280, GetColor( 255 , 255, 255 ) , "L\t%05d",blockappcnt[2]);
	DrawFormatString( 450, 310, GetColor( 255 , 255, 255 ) , "S\t%05d",blockappcnt[3]);
	DrawFormatString( 450, 340, GetColor( 255 , 255, 255 ) , "Z\t%05d",blockappcnt[4]);
	DrawFormatString( 450, 370, GetColor( 255 , 255, 255 ) , "T\t%05d",blockappcnt[5]);
	DrawFormatString( 450, 400, GetColor( 255 , 255, 255 ) , "O\t%05d",blockappcnt[6]);
	*/
}

int CBlock::GetBlockX(){
	return x;
}

int CBlock::GetBlockY(){
	return y;
}
void CBlock::CopyTime(){
	time = maincounter;
}


int CBlock::CheckUnderBlock(){//ブロックがあれば１
	int px,py;
	for(px=0 ; px<BLOCK_MAX_X ; px++){
		for(py=0 ; py<BLOCK_MAX_Y ; py++){
			if( cell[0][px][py] && MainField.CheckField(x/20+px,y/20+py+2) )
				return 1;
		}
	}
	return 0;
}
int CBlock::CheckLeftBlock(){
	int px,py;
	for(px=0 ; px<BLOCK_MAX_X ; px++){
		for(py=0 ; py<BLOCK_MAX_Y ; py++){
			if( cell[0][px][py] && MainField.CheckField(x/20+px-1,y/20+py+1) )
				return 1;
		}
	}
	return 0;
}

int CBlock::CheckRightBlock(){
	int px,py;
	for(px=0 ; px<BLOCK_MAX_X ; px++){
		for(py=0 ; py<BLOCK_MAX_Y ; py++){
			if( cell[0][px][py] && MainField.CheckField(x/20+px+1,y/20+py+1) )
				return 1;
		}
	}
	return 0;
}

void CBlock::CopyBlock(){
	int px,py;
	for(px=0 ; px<BLOCK_MAX_X ; px++){
		for(py=0 ; py<BLOCK_MAX_Y ; py++){
			if(cell[0][px][py]==1){
				MainField.PutField(x/20+px , y/20+py+1 , type );
			}
		}
	}
}

void CBlock::CalcBlock(){
	if(flag){
		FallSpdManagement();
		if( CheckUnderBlock() == 0 && flag){	//下にブロックがないなら
			Fall();								//落下させる
			landcnt=0;							//カウンタをリセット
		}
		else{									//下にブロックがあるなら
			landcnt++;							//カウンタインクリメント
		}
		if(harddropflag || landcnt>8 && !CheckUnderBlock() == 0){//下にブロックがあり、条件を満たす場合
			PlaySoundMem( Snd.se[2] , DX_PLAYTYPE_BACK ) ;
			CopyBlock();						//現在のブロックをフィールドにコピー
			landcnt=0;							//カウンタをリセット
			holdflag=0;
			flag = 0;
			//NextBlock();						//次のブロックの生成
			//Enqnextblock();
		}
		
		Rotation();								//回転制御関数
	
	
		if(OldKey[KEY_INPUT_A]==1){
			HoldBlock();
		}
		//左右移動制御
		if((OldKey[KEY_INPUT_LEFT]==1 || OldKey[KEY_INPUT_LEFT]>=7) && CheckLeftBlock()!=1 ){
			x-=20;
			if(actions<10){
				landcnt=0;
				actions++;
			}
		}
		if((OldKey[KEY_INPUT_RIGHT]==1 || OldKey[KEY_INPUT_RIGHT]>=7) && CheckRightBlock()!=1){
			x+=20;
			if(actions<10){
				landcnt=0;
				actions++;
			}
		}
	}
}

void CBlock::Initial(){
	int i;
	holdflag = 0;
	actions = 0;
	holdblocktype = -1;
	for(i=0 ; i<BLOCK_TYPE_ALL ; i++)
		blockappcnt[i] = 0;
	for(i=0 ; i<NEXT_ALL ; i++)
		blockappcnt[nexttype[i] = GetRand(6144)%7]++;
	NextBlock();
	flag = 0;
}

void CBlock::Enqnextblock(){
	int dummy[BLOCK_TYPE_ALL];
	int prob[BLOCK_TYPE_ALL];
	int i,j;
	int tmp;
	int rand;

	for(i=0 ; i<BLOCK_TYPE_ALL ; i++){			//とりあえず作業用変数にコピー
		dummy[i] = blockappcnt[i];
	}

	for(i=0 ; i<BLOCK_TYPE_ALL-1 ; i++){		//作業用変数で出現率が低い順にソート
		for(j=i+1 ; j<BLOCK_TYPE_ALL ; j++){
			if(dummy[i]>dummy[j]){
				tmp = dummy[i];
				dummy[i] = dummy[j];
				dummy[j] = tmp;
			}
		}
	}

	for(i=0 ; i<BLOCK_TYPE_ALL ; i++){			//出現率が低い順に要素番号を取り出し
		for(j=0 ; j<BLOCK_TYPE_ALL ; j++){
			if(dummy[i] == blockappcnt[j])
				prob[i] = j;
		}
	}

	rand = GetRand(9999);

	if(rand < NEXT_PRO_1)
		blockappcnt[nexttype[NEXT_ALL-1] = prob[0]]++;
	else if(rand < NEXT_PRO_1+NEXT_PRO_2)
		blockappcnt[nexttype[NEXT_ALL-1] = prob[1]]++;
	else if(rand < NEXT_PRO_1+NEXT_PRO_2+NEXT_PRO_3)
		blockappcnt[nexttype[NEXT_ALL-1] = prob[2]]++;
	else if(rand < NEXT_PRO_1+NEXT_PRO_2+NEXT_PRO_3+NEXT_PRO_4)
		blockappcnt[nexttype[NEXT_ALL-1] = prob[3]]++;
	else if(rand < NEXT_PRO_1+NEXT_PRO_2+NEXT_PRO_3+NEXT_PRO_4+NEXT_PRO_5)
		blockappcnt[nexttype[NEXT_ALL-1] = prob[4]]++;
	else if(rand < NEXT_PRO_1+NEXT_PRO_2+NEXT_PRO_3+NEXT_PRO_4+NEXT_PRO_5+NEXT_PRO_6)
		blockappcnt[nexttype[NEXT_ALL-1] = prob[5]]++;
	else
		blockappcnt[nexttype[NEXT_ALL-1] = prob[6]]++;

}

void CBlock::FallSpdManagement(){
	if( Key[KEY_INPUT_DOWN] && PlayerScore.CheckLevel() < 17 )
		fallperframe = 1;
	else if(OldKey[KEY_INPUT_UP]==1 || OldKey[KEY_INPUT_SPACE]==1){
		fallperframe = 20;
		harddropflag = 1;
	}
	else
		switch(PlayerScore.CheckLevel()){
			case 1:
				if((maincounter-time)%30 == 0)
					fallperframe = 1;
				else
					fallperframe = 0;
				break;

			case 2:
				if((maincounter-time)%27 == 0)
					fallperframe = 1;
				else
					fallperframe = 0;
				break;

			case 3:
				if((maincounter-time)%24 == 0)
					fallperframe = 1;
				else
					fallperframe = 0;
				break;

			case 4:
				if((maincounter-time)%21 == 0)
					fallperframe = 1;
				else
					fallperframe = 0;
				break;

			case 5:
				if((maincounter-time)%19 == 0)
					fallperframe = 1;
				else
					fallperframe = 0;
				break;

			case 6:
				if((maincounter-time)%17 == 0)
					fallperframe = 1;
				else
					fallperframe = 0;
				break;

			case 7:
				if((maincounter-time)%15 == 0)
					fallperframe = 1;
				else
					fallperframe = 0;
				break;

			case 8:
				if((maincounter-time)%13 == 0)
					fallperframe = 1;
				else
					fallperframe = 0;
				break;

			case 9:
				if((maincounter-time)%11 == 0)
					fallperframe = 1;
				else
					fallperframe = 0;
				break;

			case 10:
				if((maincounter-time)%9 == 0)
					fallperframe = 1;
				else
					fallperframe = 0;
				break;

			case 11:
				if((maincounter-time)%7 == 0)
					fallperframe = 1;
				else
					fallperframe = 0;
				break;

			case 12:
				if((maincounter-time)%6 == 0)
					fallperframe = 1;
				else
					fallperframe = 0;
				break;

			case 13:
				if((maincounter-time)%5 == 0)
					fallperframe = 1;
				else
					fallperframe = 0;
				break;

			case 14:
				if((maincounter-time)%4 == 0)
					fallperframe = 1;
				else
					fallperframe = 0;
				break;

			case 15:
				if((maincounter-time)%3 == 0)
					fallperframe = 1;
				else
					fallperframe = 0;
				break;

			case 16:
				if((maincounter-time)%2 == 0)
					fallperframe = 1;
				else
					fallperframe = 0;
				break;

			case 17:
				fallperframe = 1;
				break;

			case 18:
				fallperframe = 2;
				break;

			case 19:
				fallperframe = 5;
				break;

			case 20:
				fallperframe = 20;
				break;

			default:
				break;
	}
}	//落下スピード管理関数

void CBlock::DrawGhost(){
	if(flag){
		int copy,px,py;
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , 64 ) ;
		copy = y;
		while(!CheckUnderBlock()){
			y+=20;
		}
		for( px=0 ; px<BLOCK_MAX_X ; px++ ){
			for( py=0 ; py<BLOCK_MAX_Y ; py++ ){
				if(cell[0][px][py] == 1 && y+py*BLOCK_IMG_SIZE > BLOCK_IMG_SIZE*3 ){
					DrawGraph( x+(10+px)*BLOCK_IMG_SIZE , y+py*BLOCK_IMG_SIZE , blockimg[type], FALSE );
				}
			}
		}
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 );
		y = copy;
	}
}

void CBlock::HoldBlock(){
	if(flag && !holdflag){
		holdflag = 1;
		int px,py,tmp,tmp2;

		int dummy[BLOCK_MAX_X][BLOCK_MAX_Y];
		for( px=0 ; px<BLOCK_MAX_X ; px++ ){
			for( py=0 ; py<BLOCK_MAX_Y ; py++ ){
				dummy[px][py] = cell[0][px][py];
			}
		}
		tmp = holdblocktype;
		holdblocktype = type;
		tmp2 = state;

		if(tmp == -1){
			holdstate = tmp2;
			for( px=0 ; px<BLOCK_MAX_X ; px++ ){
				for( py=0 ; py<BLOCK_MAX_Y ; py++ ){
					holdcell[px][py] = dummy[px][py];
				}
			}
			NextBlock();
		}
		else{
			x = 20*2;
			y = 20;
			type = tmp;
			state = holdstate;
			holdstate = tmp2;
			for( px=0 ; px<BLOCK_MAX_X ; px++ ){
				for( py=0 ; py<BLOCK_MAX_Y ; py++ ){
					cell[0][px][py] = holdcell[px][py];
				}
			}
			for( px=0 ; px<BLOCK_MAX_X ; px++ ){
				for( py=0 ; py<BLOCK_MAX_Y ; py++ ){
					holdcell[px][py] = dummy[px][py];
				}
			}
		}
	}
}

void CBlock::DrawHold(){
	if(!(holdblocktype == -1)){
		int px,py;
		for( px=0 ; px<BLOCK_MAX_X ; px++ ){
			for( py=0 ; py<BLOCK_MAX_Y ; py++ ){
				if(holdcell[px][py] == 1){
					DrawGraph( HOLD_DRAW_X+px*BLOCK_IMG_SIZE , HOLD_DRAW_Y+py*BLOCK_IMG_SIZE , blockimg[holdblocktype], FALSE );
				}
			}
		}
	}
}

int CBlock::CheckBlockFlag(){
	return flag;
}

