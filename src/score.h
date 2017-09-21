class CScoreManagement{
private:
	int h,m,s,ds;
	int score;		//スコア
	int level;		//レベル
	int line;		//消したライン数
	int dline;		//最後に同時に消したライン数
	int dlinetmp;
	int playtime;
	char playername[11];

public:
	void ReadRanking();
	void WriteRanking();
	void DrawRanking(int GAMEMODE);
	void UpdateRanking(int GAMEMODE);
	void Initial();
	void PlayTimeCalc(int);
	CScoreManagement();
	void DrawScore();
	void AddScore();
	void LevelUp();
	int CheckLevel();
	int CheckDelLines();	//何ライン消したかを返す
	void AddDelLine();
	void GetDelLines1();
	void GetDelLines2();
	void GetPlayerName();
	int CheckRankIn(int GAMEMODE);

};