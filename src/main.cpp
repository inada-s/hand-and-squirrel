#define _GLOBAL_INSTANCE_
#include "DxLib.h"
#include "GV.h"
#include "Block.h"
#include "Field.h"
#include "Score.h"
#include "Field.h"


CBlock MovingBlock;							//移動中ブロックのインスタンス生成
CField MainField;							//フィールドのインスタンス生成
CScoreManagement PlayerScore;				//スコア管理インスタンス生成



unsigned int maincounter = 0;


int FadeIn(){
	if(fadeinflg){
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , fadeincnt+=64 );
		if(fadeincnt>=255){
			fadeinflg = 0;
			fadeincnt = 0;
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 255 );
			return 1;
		}
	}
	return 0;
}

int FadeOut(){
	if(fadeoutflg){
		fadeoutcnt+=64;
		SetDrawBright( 255-fadeoutcnt ,255-fadeoutcnt ,255-fadeoutcnt);
		if(fadeoutcnt>=255){
			fadeoutflg = 0;
			fadeoutcnt = 0;
			SetDrawBright( 255 ,255 ,255 ) ;
			return 1;
		}
	}
	return 0;
}

int GetHitKeyStateAll_2(int KeyStateBuf[]){
        char GetHitKeyStateAll_Key[256];
        GetHitKeyStateAll( GetHitKeyStateAll_Key );
        for(int i=0;i<256;i++){
                if(GetHitKeyStateAll_Key[i]==1) KeyStateBuf[i]++;
                else                            KeyStateBuf[i]=0;
        }
        return 0;
}

void Wait(int ms){
    int term;
    static int t=0;
    term = GetNowCount()-t;
    if(ms-term>0)
            Sleep(ms-term);
    t=GetNowCount();
    return;
}

void GetImage(){
	Img.Arrow		= LoadGraph( "dat/img/block/block_blue.png" );
	Img.black		= LoadGraph( "dat/img/main/black.png" );
	Img.title		= LoadGraph( "dat/img/title/Title.png" );
	Img.CRClogo		= LoadGraph( "dat/img/title/CRClogo.png" );
	Img.TETLIS		= LoadGraph( "dat/img/title/tetlis.png" );
	Img.stage[0]	= LoadGraph( "dat/img/back/01.jpg" );
	Img.stage[1]	= LoadGraph( "dat/img/back/02.jpg" );
	Img.stage[2]	= LoadGraph( "dat/img/back/03.jpg" );
	Img.stage[3]	= LoadGraph( "dat/img/back/04.jpg" );
	Img.stage[4]	= LoadGraph( "dat/img/back/05.jpg" );
	Img.stage[5]	= LoadGraph( "dat/img/back/06.jpg" );
	Img.stage[6]	= LoadGraph( "dat/img/back/07.jpg" );
	Img.stage[7]	= LoadGraph( "dat/img/back/08.jpg" );
	Img.stage[8]	= LoadGraph( "dat/img/back/09.jpg" );
	Img.stage[9]	= LoadGraph( "dat/img/back/10.jpg" );
	Img.stage[10]	= LoadGraph( "dat/img/back/11.jpg" );
	Img.stage[11]	= LoadGraph( "dat/img/back/12.jpg" );
	Img.stage[12]	= LoadGraph( "dat/img/back/13.jpg" );
	Img.stage[13]	= LoadGraph( "dat/img/back/14.jpg" );
	Img.stage[14]	= LoadGraph( "dat/img/back/15.jpg" );
	Img.stage[15]	= LoadGraph( "dat/img/back/16.jpg" );
	Img.stage[16]	= LoadGraph( "dat/img/back/17.jpg" );
	Img.stage[17]	= LoadGraph( "dat/img/back/18.jpg" );
	Img.stage[18]	= LoadGraph( "dat/img/back/19.jpg" );
	Img.stage[19]	= LoadGraph( "dat/img/back/20.jpg" );
}
void GetSound(){
	Snd.bgm[0]	= "dat/snd/bgm/45.ogg";
	Snd.bgm[1]	= "dat/snd/bgm/bount.ogg";
	Snd.bgm[2]	= "dat/snd/bgm/chance.ogg";
	Snd.bgm[3]	= "dat/snd/bgm/d17yo.ogg";
	Snd.bgm[4]	= "dat/snd/bgm/emotion.ogg";
	Snd.bgm[5]	= "dat/snd/bgm/humanage.ogg";
	Snd.bgm[6]	= "dat/snd/bgm/inthelight.ogg";
	Snd.bgm[7]	= "dat/snd/bgm/jk-rap.ogg";
	Snd.bgm[8]	= "dat/snd/bgm/justice.ogg";
	Snd.bgm[9]	= "dat/snd/bgm/kemikaru.ogg";
	Snd.bgm[10] = "dat/snd/bgm/kimiheno.ogg";
	Snd.bgm[11] = "dat/snd/bgm/punk-e.ogg";
	Snd.bgm[12] = "dat/snd/bgm/s-punk.ogg";
	Snd.bgm[13] = "dat/snd/bgm/tokinokaze.ogg";
	Snd.bgm[14] = "dat/snd/bgm/xmas.ogg";
	Snd.bgm[15] = "dat/snd/bgm/yatuzaki_kai.ogg";
	Snd.bgm[16] = "dat/snd/bgm/zero.ogg";
	Snd.bgm[17] = "dat/snd/bgm/zero2.ogg";
	Snd.bgm[18] = "dat/snd/bgm/korobu.ogg";

	Snd.se[0] = LoadSoundMem("dat/snd/se/swing30_a.wav");	//回転時の音
	Snd.se[1] = LoadSoundMem("dat/snd/se/swing30_b.wav");
	Snd.se[2] = LoadSoundMem("dat/snd/se/kachi43.wav");		//ブロック固定時
	Snd.se[3] = LoadSoundMem("dat/snd/se/pi02.wav");		//選択決定
	Snd.se[4] = LoadSoundMem("dat/snd/se/push48.wav");
	Snd.se[5] = LoadSoundMem("dat/snd/se/close00.wav");		//ランキングからメニューへ
	Snd.se[6] = LoadSoundMem("dat/snd/se/sha00.wav");		//ランキングページ切り替え
	Snd.se[7] = LoadSoundMem("dat/snd/se/puu24.wav");		//ライン消した時
	Snd.se[8] = LoadSoundMem("dat/snd/se/power32.wav");		//レベルアップしたとき
	Snd.se[9] = LoadSoundMem("dat/snd/se/bell15a.wav");
}



void message_box(){
        int flag;
        flag=MessageBox(
                NULL ,
                TEXT("フルスクリーンで起動しますか？") ,
                TEXT("---Hand & squirrel---") , 
                MB_YESNO | MB_ICONINFORMATION );
        if(flag==IDNO)
                ChangeWindowMode( TRUE );
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						 LPSTR lpCmdLine, int nCmdShow )
{
	message_box();
	SetMainWindowText( "---Hand & squirrel---" );		//ウインドウ名の変更
	int itm;											//タイトルセレクト制御変数
	int startflg;										//ゲームスタート時かどうかのフラグ
	int startcnt;										//ゲームスタートしてからのカウンタ
	int sndno=0;										//ゲーム中の曲ナンバー
	int	state = STATE_SYSTEMINI;						//処理切り替え用変数
	int rankingstate;
	SetOutApplicationLogValidFlag( FALSE );
	SetGraphMode( 640 , 480 , 32 );			//ウインドウの初期化
	if( DxLib_Init() == -1 )				//ＤＸライブラリ初期化処理
		return -1;							//エラーが起きたら直ちに終了
	SetDrawScreen( DX_SCREEN_BACK );		//描写先を裏画面にセット
	Font1 = CreateFontToHandle("Arial Black",32,7,DX_FONTTYPE_ANTIALIASING, DX_CHARSET_DEFAULT);
	Font2 = CreateFontToHandle("Arial Black",20,4,DX_FONTTYPE_ANTIALIASING, DX_CHARSET_DEFAULT);
	Font3 = CreateFontToHandle("Arial Black",28,4,DX_FONTTYPE_ANTIALIASING, DX_CHARSET_DEFAULT);
	
	//曲とか画像とかをロード
	GetSound();
	GetImage();
	MainField.GetImage();
	MovingBlock.GetImage();
	PlayerScore.ReadRanking();

	//メインループ
	while( ProcessMessage() == 0 && CheckHitKey( KEY_INPUT_ESCAPE ) == 0 )
	{
		GetHitKeyStateAll(Key);				//キー入力情報取得
		GetHitKeyStateAll_2(OldKey);
		ClearDrawScreen();					//画面を消去


		switch(state){
			case STATE_SYSTEMINI:
				PlayerScore.WriteRanking();
				int fadecnt;
				WaitTimer(500);
				for( fadecnt=0 ; fadecnt<255 ; fadecnt+=5 ){
					SetDrawBright( fadecnt , fadecnt , fadecnt );
					DrawGraph( 0 , 0 , Img.CRClogo , FALSE );
					ScreenFlip();
				}
				WaitTimer(1000);
				for( fadecnt=0 ; fadecnt<255 ; fadecnt+=5 ){
					SetDrawBright( 255-fadecnt , 255-fadecnt , 255-fadecnt );
					DrawGraph( 0 , 0 , Img.CRClogo , FALSE );
					ScreenFlip();
				}
				ClearDrawScreen();					//画面を消去

				for( fadecnt=0 ; fadecnt<255 ; fadecnt+=5 ){
					SetDrawBright( fadecnt , fadecnt , fadecnt );
					DrawGraph( 160 , 80 , Img.TETLIS , FALSE );
					ScreenFlip();
				}
				WaitTimer(1000);
				PlayMusic( Snd.bgm[18] , DX_PLAYTYPE_BACK );
				SetVolumeMusic(10);
				for( fadecnt=0 ; fadecnt<255 ; fadecnt+=5 ){
					SetDrawBright( 255-fadecnt , 255-fadecnt , 255-fadecnt );
					DrawGraph( 160 , 80 , Img.TETLIS , FALSE );
					ScreenFlip();
				}
				ClearDrawScreen();					//画面を消去
				SetDrawBright( 255 , 255 , 255 );
				state = STATE_INITIAL;
				WaitTimer(550);
				break;

			case STATE_INITIAL:
				rankingstate = 0;
				itm = 0;
				startflg = 1;				//ブロック落下スタートフラグ
				MovingBlock.Initial();
				MainField.Initial();
				PlayerScore.Initial();
				state = STATE_TITLE;
				fadeinflg = 1;
				fadeoutflg = 0;
				fadeincnt = 0;
				fadeoutcnt = 0;
				break;

			case STATE_TITLE:
				
				//曲が終了したらロゴ画面へ
				if(!CheckMusic()){state = STATE_SYSTEMINI;}

				//計算部分
				if(OldKey[KEY_INPUT_DOWN]==1 || OldKey[KEY_INPUT_DOWN]>=10 && OldKey[KEY_INPUT_DOWN]%5==1){if(itm == 3) itm = 0; else itm ++;PlaySoundMem( Snd.se[3] , DX_PLAYTYPE_BACK ) ;}
				else if(OldKey[KEY_INPUT_UP]==1 || OldKey[KEY_INPUT_UP]>=10 && OldKey[KEY_INPUT_UP]%5==1){if(itm == 0) itm = 3;else itm--;PlaySoundMem( Snd.se[3] , DX_PLAYTYPE_BACK ) ;}
				
				else if(OldKey[KEY_INPUT_Z]==1 || OldKey[KEY_INPUT_RETURN]==1){
					PlaySoundMem( Snd.se[4] , DX_PLAYTYPE_BACK ) ;
					switch(itm){
						case 0://ノーマルモード選択
							StopMusic();
							sndno = 0;
							state = STATE_NORMAL;
							fadeinflg = 1 ;
							WaitTimer(500);
							break;
						case 1://エンドレスモード選択
							StopMusic();
							sndno = 0;
							state = STATE_ENDLESS;
							fadeinflg = 1 ;
							WaitTimer(500);
							break;
						case 2:
							state = STATE_RANKING;
							WaitTimer(200);
							break;
						case 3://ゲーム終了
							WaitTimer(200);
							StopMusic();
							goto ENDLABEL;
						default:
							break;
					}
				}
				
				//描写部分
				DrawGraph( 0 , 0 , Img.title , TRUE );

				DrawFormatStringToHandle( 540, 280, GetColor( 220 , 220 , 220 ), Font2, "Ver 1.1");

				
				DrawFormatStringToHandle( 50+FONT_SHADOW_WIDTH, 320+FONT_SHADOW_WIDTH, GetColor( 0 , 0 , 0 ), Font1, "NORMAL MODE");
				DrawFormatStringToHandle( 50, 320, GetColor( 128 , 128 , 128 ), Font1, "NORMAL MODE");

				DrawFormatStringToHandle( 50+FONT_SHADOW_WIDTH, 350+FONT_SHADOW_WIDTH, GetColor( 0 , 0 , 0 ), Font1, "ENDLESS MODE");
				DrawFormatStringToHandle( 50, 350, GetColor( 128 , 128 , 128 ), Font1, "ENDLESS MODE");
				
				DrawFormatStringToHandle( 50+FONT_SHADOW_WIDTH, 380+FONT_SHADOW_WIDTH, GetColor( 0 , 0 , 0 ), Font1, "RANKING");
				DrawFormatStringToHandle( 50, 380, GetColor( 128 , 128 , 128 ), Font1, "RANKING");
				
				DrawFormatStringToHandle( 50+FONT_SHADOW_WIDTH, 410+FONT_SHADOW_WIDTH, GetColor( 0 , 0 , 0 ), Font1, "QUIT");
				DrawFormatStringToHandle( 50, 410, GetColor( 128 , 128 , 128 ), Font1, "QUIT");

				DrawFormatStringToHandle( 10, 450, GetColor( 240 , 240 , 240 ), Font2, "Copyright 2008, Miyakojima THS Computer Research Club. All Rights Reserved.");
				

				DrawGraph( 15+maincounter%6 , 326+itm*30 , Img.Arrow , FALSE );
				switch(itm){//選択中の奴を明るく表示
					case 0:
						DrawFormatStringToHandle( 50, 320, GetColor( 255 , 255 , 255 ), Font1, "NORMAL MODE");
						break;
					case 1:
						DrawFormatStringToHandle( 50, 350, GetColor( 255 , 255 , 255 ), Font1, "ENDLESS MODE");
						break;
					case 2:
						DrawFormatStringToHandle( 50, 380, GetColor( 255 , 255 , 255 ), Font1, "RANKING");
						break;
					case 3:
						DrawFormatStringToHandle( 50, 410, GetColor( 255 , 255 , 255 ), Font1, "QUIT");
						break;
					default:
						break;
				}
				//PlayerScore.DrawRanking(STATE_ENDLESS);
				break;

			case STATE_ENDLESS://エンドレスモード
				MainField.GameOverManagement();
				if(!CheckMusic()){
					if(sndno == 19) sndno = 0;
					PlayMusic( Snd.bgm[sndno++] , DX_PLAYTYPE_BACK );
					SetVolumeMusic(10);
					}
				if(startflg==1 && OldKey[KEY_INPUT_RETURN]==1){
					MovingBlock.NextBlock();
					startcnt = maincounter;
					startflg = 0;
				}
				if(startflg){
					startcnt = maincounter;
				}
				if(!MainField.CheckGameOver() && !startflg && MainField.CheckNextFlag() && !MovingBlock.CheckBlockFlag()){
					MovingBlock.NextBlock();						//次のブロックの生成
					MovingBlock.Enqnextblock();
				}
				MovingBlock.CalcBlock();
				
				PlayerScore.PlayTimeCalc(maincounter - startcnt);
				PlayerScore.GetDelLines1();

				if(!MovingBlock.CheckBlockFlag() && !MainField.CheckEffectFlag()){
					MainField.CopyToDummy();
					for( int py=2;py<FIELD_HEIGHT-1 ; py++){
						if(MainField.CheckLine(py)){
							MainField.effecnt = maincounter+15;
							MainField.nextblockflag=0;
							MainField.deleffectflag=1;
							MainField.DelLine(py);
							MainField.LineSlide(py);
							PlayerScore.AddDelLine();
						}
					}
				}
				if(MainField.effecnt == maincounter+15)
					PlaySoundMem( Snd.se[7] , DX_PLAYTYPE_BACK ) ;
				if(MainField.effecnt == maincounter){
					MainField.deleffectflag = 0;
					MainField.nextblockflag = 1;
					PlaySoundMem( Snd.se[5] , DX_PLAYTYPE_BACK ) ;
				}
				if(!MainField.CheckEffectFlag()){
					MainField.CopyToMain(2);
				}
				else{
					MainField.CopyToMain(maincounter%2);
				}

	
				PlayerScore.GetDelLines2();
				DrawGraph( 0, 0, Img.stage[PlayerScore.CheckLevel()-1], FALSE);
				MainField.Draw1();
				MovingBlock.DrawGhost();
				MovingBlock.DrawBlock();
				MovingBlock.DrawNext();
				MovingBlock.DrawHold();
				MainField.Draw2();
				PlayerScore.DrawScore();
					
				DrawFormatStringToHandle( 480+FONT_SHADOW_WIDTH, 380+FONT_SHADOW_WIDTH, GetColor( 0 , 0 , 0 ), Font1, "ENDLESS");
				DrawFormatStringToHandle( 480, 380, GetColor( 128 , 128 , 255 ), Font1, "ENDLESS");
				DrawFormatStringToHandle( 480+FONT_SHADOW_WIDTH, 410+FONT_SHADOW_WIDTH, GetColor( 0 , 0 , 0 ), Font1, "       MODE");
				DrawFormatStringToHandle( 480, 410, GetColor( 128 , 128 , 255 ), Font1, "       MODE");


				if(MainField.CheckGameOver()){
					StopMusic();
					DrawGraph( 0 , 0 , Img.black, TRUE );//背景をくらーく
					ScreenFlip();
					if(PlayerScore.CheckRankIn(state)<=9){
						PlayerScore.GetPlayerName();
						PlayerScore.UpdateRanking(state);
					}
					DrawFormatStringToHandle( 190, 230 , GetColor( 200 , 120 , 120 ), Font1, "===GAME OVER===");
					DrawFormatStringToHandle( 400, 450 , GetColor( 200 , 200 , 200 ), Font1, ">PRESS ANY KEY");
					ScreenFlip();
					PlaySoundMem( Snd.se[9] , DX_PLAYTYPE_BACK );
					//ここにゲームオーバー音楽を入れるよてー
					WaitKey();
					ClearDrawScreen();
					state = STATE_SYSTEMINI;
					break;
				}
				break;


			case STATE_NORMAL://ノーマルモード
				MainField.GameOverManagement();
				if(!CheckMusic()){
					if(sndno == 19) sndno = 0;
					PlayMusic( Snd.bgm[sndno++] , DX_PLAYTYPE_BACK );
					SetVolumeMusic(10);
					}
				if(startflg==1 && OldKey[KEY_INPUT_RETURN]==1){
					MovingBlock.NextBlock();
					startcnt = maincounter;
					startflg = 0;
				}
				if(startflg){
					startcnt = maincounter;
				}
				if(!MainField.CheckGameOver() && !startflg && MainField.CheckNextFlag() && !MovingBlock.CheckBlockFlag()){
					MovingBlock.NextBlock();						//次のブロックの生成
					MovingBlock.Enqnextblock();
				}
				MovingBlock.CalcBlock();
				
				PlayerScore.PlayTimeCalc(maincounter - startcnt);
				PlayerScore.GetDelLines1();

				if(!MovingBlock.CheckBlockFlag() && !MainField.CheckEffectFlag()){
					MainField.CopyToDummy();
					for( int py=2;py<FIELD_HEIGHT-1 ; py++){
						if(MainField.CheckLine(py)){
							MainField.effecnt = maincounter+15;
							MainField.nextblockflag=0;
							MainField.deleffectflag=1;
							MainField.DelLine(py);
							MainField.LineSlide(py);
							PlayerScore.AddDelLine();
						}
					}
				}
				if(MainField.effecnt == maincounter+15)
					PlaySoundMem( Snd.se[7] , DX_PLAYTYPE_BACK ) ;
				if(MainField.effecnt == maincounter){
					MainField.deleffectflag = 0;
					MainField.nextblockflag = 1;
					PlaySoundMem( Snd.se[5] , DX_PLAYTYPE_BACK ) ;
				}
				if(!MainField.CheckEffectFlag()){
					MainField.CopyToMain(2);
				}
				else{
					MainField.CopyToMain(maincounter%2);
				}

	
				PlayerScore.GetDelLines2();
				DrawGraph( 0, 0, Img.stage[PlayerScore.CheckLevel()-1], FALSE);
				MainField.Draw1();
				MovingBlock.DrawGhost();
				MovingBlock.DrawBlock();
				MovingBlock.DrawNext();
				MovingBlock.DrawHold();
				MainField.Draw2();
				PlayerScore.DrawScore();
					
				DrawFormatStringToHandle( 480+FONT_SHADOW_WIDTH, 380+FONT_SHADOW_WIDTH, GetColor( 0 , 0 , 0 ), Font1, "NORMAL");
				DrawFormatStringToHandle( 480, 380, GetColor( 128 , 128 , 255 ), Font1, "NORMAL");
				DrawFormatStringToHandle( 480+FONT_SHADOW_WIDTH, 410+FONT_SHADOW_WIDTH, GetColor( 0 , 0 , 0 ), Font1, "       MODE");
				DrawFormatStringToHandle( 480, 410, GetColor( 128 , 128 , 255 ), Font1, "       MODE");

				if(PlayerScore.CheckDelLines() >= 200)
					MainField.Gameover();

				if(MainField.CheckGameOver()){
					StopMusic();
					DrawGraph( 0 , 0 , Img.black, TRUE );//背景をくらーく
					ScreenFlip();
					if(PlayerScore.CheckRankIn(state)<=9){
						PlayerScore.GetPlayerName();
						PlayerScore.UpdateRanking(state);
					}
					DrawFormatStringToHandle( 190, 230 , GetColor( 200 , 120 , 120 ), Font1, "===GAME OVER===");
					DrawFormatStringToHandle( 400, 450 , GetColor( 200 , 200 , 200 ), Font1, ">PRESS ANY KEY");
					ScreenFlip();
					PlaySoundMem( Snd.se[9] , DX_PLAYTYPE_BACK );
					//ここにゲームオーバー音楽を入れるよてー
					WaitKey();
					ClearDrawScreen();
					state = STATE_SYSTEMINI;
					break;
				}
				break;

			case STATE_RANKING://ランキング表示
				DrawGraph( 0 , 0 , Img.title , TRUE );
				DrawGraph( 0 , 0 , Img.black , TRUE );
				PlayerScore.DrawRanking(rankingstate? STATE_ENDLESS : STATE_NORMAL);
				if(OldKey[KEY_INPUT_Z]==1 || OldKey[KEY_INPUT_RETURN]==1){
					PlaySoundMem( Snd.se[6] , DX_PLAYTYPE_BACK ) ;
					if(rankingstate)
						rankingstate = 0;
					else
						rankingstate = 1;
				}
				if(OldKey[KEY_INPUT_X]==1){
					state = STATE_TITLE;
					rankingstate = 0;
					PlaySoundMem( Snd.se[1] , DX_PLAYTYPE_BACK ) ;
					WaitTimer(200);
				}
				break;

			default:
				printfDx("stateエラー\n");
				break;
		}

		ScreenFlip();						//裏画面の内容を表画面に反映させる
		maincounter++;
		Wait(33);
		FadeOut();
		FadeIn();
	}
ENDLABEL:
	DxLib_End();							// ＤＸライブラリ使用の終了処理
	return 0;								// ソフトの終了
}
