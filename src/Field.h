#ifndef FIELD_H
#define FIELD_H

class CField{
private:
	int holdimg;
	int frameimg[2];									//枠画像
	int backblackimg;
	int backblueimg;
	int field[FIELD_WIDTH][FIELD_HEIGHT];				//ゲームフィールド
	int dummyfield[3][FIELD_WIDTH][FIELD_HEIGHT];			//消した時のエフェクトで利用
	int gameoverflag;
	int blockimg[BLOCK_TYPE_ALL];

	int ConvertPoint(int);								//座標変換関数
	//int nextblockflag;								//次のブロックを生成していいかどうかのフラグ
	//int CheckLine(int py);
	//void DelLine(py);

public:
	int effecnt;
	int deleffectflag;
	int CheckEffectFlag();
	void DummyFieldClac();
	void CopyToDummy();									//ダミーフィールドへコピー
	void CopyToMain(int);								//メインフィールドへコピー
	void GameOverManagement();							//ゲームオーバー管理
	int nextblockflag;
	CField();
	int CheckNextFlag();
	void Initial();
	void GetImage();									//画像取得関数
	int CheckField(int px,int py);						//指定した座標のブロックを調べる関数
	int PutField(int px,int py,int blocktype);			//指定した座標にブロックを置く関数
	void Draw1();
	void Draw2();//フィールドを描写
	int CheckLine(int py);								//ブロックが横一列そろっているかどうかを返す
	void DelLine(int py);								//指定した行のブロックを削除する
	void LineSlide(int py);
	void Gameover();									//ゲームオーバーフラグを立てる関数
	int CheckGameOver();								//ゲームオーバーなら１を返す
};

#endif