#pragma once
class Vector3
{
public:
	float x;//x����
	float y;//y����
	float z;//z����
public:
	Vector3();					//��x�N�g���Ƃ��Đ���
	Vector3(float x, float y, float z);	//x����,y����,z�������w�肵�Đ���

	//�����o�[�֐�
	float length() const;				//�m����(����)�����߂�
	Vector3& normalize();				//���K������
	float dot(const Vector3& v)const;	//���ς����߂�
	float cross(const Vector3& v)const;	//�O�ς����߂�

	//�P�����Z���I�[�o�[���[�h
	Vector3 operator+() const;
	Vector3 operator-() const;

	//������Z�q�I�[�o�[���[�h
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);
};

//2�����Z�q�I�[�o�[���[�h
//*�����Ȉ���(�����̌^�Ə���)�̃p�^�[���ɑΉ����邽�߁A�ȉ��ɏ�������
const Vector3 operator+(const Vector3& v1, const Vector3& v2);
const Vector3 operator-(const Vector3& v1, const Vector3& v2);
const Vector3 operator*(const Vector3& v, float s);
const Vector3 operator*(float s, const Vector3& v);
const Vector3 operator/(const Vector3& v, float s);
/// <summary>
/// ���`���
/// </summary>
/// <param name="start"></�X�^�[�g�ʒu>
/// <param name="end"></�I���ʒu>
/// <param name="time"></�|���鎞��>
/// <returns></returns>
const Vector3 lerp(const Vector3& start, const Vector3& end, const float t);