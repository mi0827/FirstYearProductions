#pragma once

class MovePlayer : public Base {
public:
	MovePlayer();
	~MovePlayer();

	void Init();   // �����ݒ�
	void Update(); // �X�V����
	void Draw();   // �`�揈��
	void Exit();//	�I������
	
private:

	// �v���C���[�̕���摜�p�̕ϐ�
	int m_image;

};
