
class CBlock{
private:
	int x,y;
	int nx[NEXT_ALL-1],ny[NEXT_ALL-1];
	int holdblocktype;		//�z�[���h�����u���b�N�̎��
	int holdstate;			//�z�[���h�����u���b�N���ǂ̕����������Ă邩
	int time;				//�o�������Ƃ��̃��C���J�E���^�̒l
	int landcnt;			//���n���Ă���̃J�E���^
	int state;				//���݃u���b�N���ǂ̕����������Ă���̂�
	int blockappcnt[BLOCK_TYPE_ALL]; //�e�u���b�N�̏o����
	int blockimg[BLOCK_TYPE_ALL];
	int holdflag;			//�z�[���h�ł��邩�ǂ����̃t���O
	int flag;				//�o�������ǂ����̃t���O
	int harddropflag;		//�n�[�h�h���b�v�̃t���O
	int type;				//���݂̃u���b�N�^�C�v
	int fallperframe;		//���̃t���[���ŉ��}�X���������邩
	int actions;
	int nexttype[BLOCK_TYPE_ALL];
	int holdcell[BLOCK_MAX_X][BLOCK_MAX_Y];
	int cell[NEXT_ALL][BLOCK_MAX_X][BLOCK_MAX_Y];	//�\�����ƃl�N�X�g�̃Z�����i�[
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
	void CopyTime();			//time�Ƀ��C���J�E���^���R�s�[����֐�
	void CopyBlock();			//���n�����u���b�N�̏������C���t�B�[���h�փR�s�[����֐�
	void Fall();
	void HoldBlock();			//�z�[���h�ֈړ�������֐�
	int CheckUnderBlock();
	int CheckLeftBlock();
	int CheckRightBlock();
	int Rotation();


public:
	void DrawHold();
	void DrawGhost();
	void DrawNext();
	void DrawBlock();		//���ݑ��쒆�̃u���b�N��\������֐�
	void Enqnextblock();
	void Initial();			//�������֐�
	
	CBlock();
	int CheckBlockFlag();
	void GetImage();		//�摜�t�@�C���擾
	int NextBlock();		//���̃u���b�N�𐶐�����֐�
	int GetBlockX();		//X���W�擾�֐�
	int GetBlockY();		//Y���W�擾�֐�
	void CalcBlock();
};

