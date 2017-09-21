class CScoreManagement{
private:
	int h,m,s,ds;
	int score;		//�X�R�A
	int level;		//���x��
	int line;		//���������C����
	int dline;		//�Ō�ɓ����ɏ��������C����
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
	int CheckDelLines();	//�����C������������Ԃ�
	void AddDelLine();
	void GetDelLines1();
	void GetDelLines2();
	void GetPlayerName();
	int CheckRankIn(int GAMEMODE);

};