#ifndef FIELD_H
#define FIELD_H

class CField{
private:
	int holdimg;
	int frameimg[2];									//�g�摜
	int backblackimg;
	int backblueimg;
	int field[FIELD_WIDTH][FIELD_HEIGHT];				//�Q�[���t�B�[���h
	int dummyfield[3][FIELD_WIDTH][FIELD_HEIGHT];			//���������̃G�t�F�N�g�ŗ��p
	int gameoverflag;
	int blockimg[BLOCK_TYPE_ALL];

	int ConvertPoint(int);								//���W�ϊ��֐�
	//int nextblockflag;								//���̃u���b�N�𐶐����Ă������ǂ����̃t���O
	//int CheckLine(int py);
	//void DelLine(py);

public:
	int effecnt;
	int deleffectflag;
	int CheckEffectFlag();
	void DummyFieldClac();
	void CopyToDummy();									//�_�~�[�t�B�[���h�փR�s�[
	void CopyToMain(int);								//���C���t�B�[���h�փR�s�[
	void GameOverManagement();							//�Q�[���I�[�o�[�Ǘ�
	int nextblockflag;
	CField();
	int CheckNextFlag();
	void Initial();
	void GetImage();									//�摜�擾�֐�
	int CheckField(int px,int py);						//�w�肵�����W�̃u���b�N�𒲂ׂ�֐�
	int PutField(int px,int py,int blocktype);			//�w�肵�����W�Ƀu���b�N��u���֐�
	void Draw1();
	void Draw2();//�t�B�[���h��`��
	int CheckLine(int py);								//�u���b�N������񂻂���Ă��邩�ǂ�����Ԃ�
	void DelLine(int py);								//�w�肵���s�̃u���b�N���폜����
	void LineSlide(int py);
	void Gameover();									//�Q�[���I�[�o�[�t���O�𗧂Ă�֐�
	int CheckGameOver();								//�Q�[���I�[�o�[�Ȃ�P��Ԃ�
};

#endif