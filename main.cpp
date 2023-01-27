#include "DxLib.h"
#include "Vector3.h"
#include <cstring>

// ��(sphere)�̕`��
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum, const unsigned int DifColor, const unsigned int
	SpcColor, const int FillFlag);

// �����̕`��
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color);

// �J�����̈ʒu�Ǝp���̐ݒ�
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition, // �J�����̈ʒu
	const Vector3& cameraTarget,   // �J�����̒����_
	const Vector3& vameraUp        // �J�����̏�̌���
);

void DrawAxis3D(const float lengh); // x,y,z ���̕`��

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LE2C_10_�R�o�V_�n���g";
const int WindowWidth = 1600;
const int WindowHeight = 900;
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {

	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WindowWidth, WindowHeight, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0, 0, 64);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	SetUseZBuffer3D(TRUE); // Z�o�b�t�@��L���ɂ���
	SetWriteZBuffer3D(TRUE); // Z�o�b�t�@�ւ̏������݂�L���ɂ���

	// �N���b�v��   �߁@�@�@��
	SetCameraNearFar(1.0f, 1000.0f); // �J�����̗L���͈͂̐ݒ�
	SetCameraScreenCenter(WindowWidth / 2.0f, WindowHeight / 2.0f); // ��ʂ̒��S���J�����̒��S�ɍ��킹��
	SetCameraPositionAndTargetAndUpVec(
		Vector3(0.0f, 200.0f, 0.0f),
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(0.0f, 0.0f, 1.0f)
	);

	// ���Ԍv���ɕK�v�ȃf�[�^
	long long startCount = 0;
	long long nowCount = 0;
	long long elapsedCount = 0;

	// ��ԂŎg���f�[�^
	// start -> end �� 5 [s] �Ŋ���������
	Vector3 p0(-100.0f, 0.0f, 0.0f);  // �X�^�[�g�n�_
	Vector3 p1(-0.0f, 0.0f, +100.0f);  // ����_
	Vector3 p2(+0.0f, 0.0f, -100.0f);  // ����_
	Vector3 p3(+100.0f, 0.0f, 0.0f);  // �G���h�n�_
	float maxTime = 5.0f; // �S�̎���[s]
	float timeRate;       // ��% ���Ԃ��i�񂾂�(��)

	// ���̈ʒu
	Vector3 position;

	//�v���C���[
	Vector3 player;
	float X = 0;
	float Y = 0;
	float Z = 0;

	int time = 200;
	int coolTime = 50;
	bool timerFlag = false;

	// ���s�O�ɃJ�E���^�l���擾
	startCount = GetNowHiPerformanceCount(); // long long int�^ 64bit int 

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���

	// �Q�[�����[�v�Ŏg���ϐ��̐錾

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		// [R]�L�[�ŁA���X�^�[�g
		if (CheckHitKey(KEY_INPUT_R)) {
			startCount = GetNowHiPerformanceCount();
		}

		if (keys[KEY_INPUT_RIGHT]==1&& oldkeys[KEY_INPUT_RIGHT] == 0)
		{
			timerFlag = true;
			Z = 30;
		}

		if (timerFlag == true)
		{
			coolTime--;
		}
		if (coolTime <= 0 && timerFlag == true)
		{
			timerFlag = false;
			coolTime = 50;
			Z = 0;
		}
		// �o�ߎ���(wlapsedTime[s])�̌v�Z
		nowCount = GetNowHiPerformanceCount();
		elapsedCount = nowCount - startCount;
		float elapsedTime = static_cast<float> (elapsedCount) / 1'000'000.0f;

		// �X�^�[�g�n�_�@�F�@start
		// �G���h�n�_�@�F�@end
		// �o�ߎ��ԁ@�F�@wlapsedTime[s]
		// �ړ������̗�(�o�ߎ���/�S�̎���) : timeRate(%)

		timeRate = min(elapsedTime / maxTime, 1.0f);

		// 2���x�W�F�Ȑ��̍l������K�p����
		Vector3 a = lerp(p0, p1, timeRate);
		Vector3 b = lerp(p1, p2, timeRate);
		Vector3 c = lerp(p2, p3, timeRate);
		Vector3 d = lerp(a, b, timeRate);
		Vector3 e = lerp(b, c, timeRate);

		position = lerp(d, e, timeRate);

		player = { X,Y,Z };

		// position = easeIn(start, end, timeRate);
		// position = easeOut(start,end,timeRate);
		// position = easeInOut(start,end,timeRate);

		// �`�揈��
		ClearDrawScreen(); // ��ʂ�����
		DrawAxis3D(500.0f); // xyz���̕`��

		// ���̕`��
		DrawSphere3D(player, 5.0f, 32, GetColor(0, 0, 0), GetColor(255, 255, 255), TRUE);

		DrawSphere3D(position, 5.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
		DrawSphere3D(p0, 3.0f, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
		DrawSphere3D(p1, 3.0f, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
		DrawSphere3D(p2, 3.0f, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
		DrawSphere3D(p3, 3.0f, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);

		//
		DrawFormatString(0, 0, GetColor(255, 255, 255), "position(%5.1f,%5.1f,%5.1f)", position.x, position.y, position.z);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "%7.3f[s]", elapsedTime);
		DrawFormatString(0, 40, GetColor(255, 255, 255), "[R] : Restart");
		DrawFormatString(0, 60, GetColor(255, 255, 255), "p0 (%6.1f,%6.1f,%6.1f)", p0.x, p0.y, p0.z);
		DrawFormatString(0, 80, GetColor(255, 255, 255), "p1 (%6.1f,%6.1f,%6.1f)", p1.x, p1.y, p1.z);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "p2 (%6.1f,%6.1f,%6.1f)", p2.x, p2.y, p2.z);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "p3 (%6.1f,%6.1f,%6.1f)", p3.x, p3.y, p3.z);

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}

// x���A�����A�����̕`��
void DrawAxis3D(const float length)
{
	DrawLine3D(Vector3(-length, 0, 0), Vector3(+length, 0, 0), GetColor(255, 0, 0)); // ����
	DrawLine3D(Vector3(0, -length, 0), Vector3(0, +length, 0), GetColor(0, 255, 0)); // ����
	DrawLine3D(Vector3(0, 0, -length), Vector3(0, 0, +length), GetColor(0, 0, 255)); // ����
}

// �J�����̈ʒu�Ǝp���̐ݒ�
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,  // �J�����̈ʒu
	const Vector3& cameraTarget,    // �J�����̒����_
	const Vector3& cameraUp         // �J�����̏�̌���
)
{
	VECTOR position = { cameraPosition.x,cameraPosition.y,cameraPosition.z };
	VECTOR target = { cameraTarget.x,cameraTarget.y,cameraTarget.z };
	VECTOR up = { cameraUp.x,cameraUp.y,cameraUp.z };

	return SetCameraPositionAndTargetAndUpVec(position, target, up);
}

// ���̕`��
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag)
{
	VECTOR centerPos = { CenterPos.x,CenterPos.y,CenterPos.z };

	return DrawSphere3D(centerPos, r, DivNum, DifColor, SpcColor, FillFlag);
}

// �����̕`��
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color)
{
	VECTOR p1 = { Pos1.x,Pos1.y,Pos1.z }; // �\���́@�������q���X�g
	VECTOR p2 = { Pos2.x,Pos2.y,Pos2.z }; // �\���́@�������q���X�g

	return DrawLine3D(p1, p2, Color);
}