
class CBlock{
private:
	int x,y;
	int nx[NEXT_ALL-1],ny[NEXT_ALL-1];
	int holdblocktype;		//ホールドしたブロックの種類
	int holdstate;			//ホールドしたブロックがどの方向を向いてるか
	int time;				//出現したときのメインカウンタの値
	int landcnt;			//着地してからのカウンタ
	int state;				//現在ブロックがどの方向を向いているのか
	int blockappcnt[BLOCK_TYPE_ALL]; //各ブロックの出現数
	int blockimg[BLOCK_TYPE_ALL];
	int holdflag;			//ホールドできるかどうかのフラグ
	int flag;				//出現中かどうかのフラグ
	int harddropflag;		//ハードドロップのフラグ
	int type;				//現在のブロックタイプ
	int fallperframe;		//そのフレームで何マス落下させるか
	int actions;
	int nexttype[BLOCK_TYPE_ALL];
	int holdcell[BLOCK_MAX_X][BLOCK_MAX_Y];
	int cell[NEXT_ALL][BLOCK_MAX_X][BLOCK_MAX_Y];	//表示中とネクストのセルを格納
	short int IRight[BLOCK_MAX_Y*5*4][BLOCK_MAX_X];
	short int JRight[BLOCK_MAX_Y*5*4][BLOCK_MAX_X];
	short int LRight[BLOCK_MAX_Y*5*4][BLOCK_MAX_X];
	short int SRight[BLOCK_MAX_Y*5*4][BLOCK_MAX_X];
	short int ZRight[BLOCK_MAX_Y*5*4][BLOCK_MAX_X];
	short int TRight[BLOCK_MAX_Y*5*4][BLOCK_MAX_X];
	short int ILeft[BLOCK_MAX_Y*5*4][BLOCK_MAX_X];
	short int JLeft[BLOCK_MAX_Y*5*4][BLOCK_MAX_X];
	short int LLeft[BLOCK_MAX_Y*5*4][BLOCK_MAX_X];
	short int SLeft[BLOCK_MAX_Y*5*4][BLOCK_MAX_X];
	short int ZLeft[BLOCK_MAX_Y*5*4][BLOCK_MAX_X];
	short int TLeft[BLOCK_MAX_Y*5*4][BLOCK_MAX_X];
	short rightturnlist[BLOCK_TYPE_ALL-1][BLOCK_STATE_ALL][ROTATION_CANDIDATE][BLOCK_MAX_X][BLOCK_MAX_Y];
	short leftturnlist[BLOCK_TYPE_ALL-1][BLOCK_STATE_ALL][ROTATION_CANDIDATE][BLOCK_MAX_X][BLOCK_MAX_Y];
	void FallSpdManagement();
	void CopyTime();			//timeにメインカウンタをコピーする関数
	void CopyBlock();			//着地したブロックの情報をメインフィールドへコピーする関数
	void Fall();
	void HoldBlock();			//ホールドへ移動させる関数
	int CheckUnderBlock();
	int CheckLeftBlock();
	int CheckRightBlock();
	int Rotation();


public:
	void DrawHold();
	void DrawGhost();
	void DrawNext();
	void DrawBlock();		//現在操作中のブロックを表示する関数
	void Enqnextblock();
	void Initial();			//初期化関数
	
	CBlock();
	int CheckBlockFlag();
	void GetImage();		//画像ファイル取得
	int NextBlock();		//次のブロックを生成する関数
	int GetBlockX();		//X座標取得関数
	int GetBlockY();		//Y座標取得関数
	void CalcBlock();
};

