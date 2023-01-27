#pragma once

#include "Vector3.h"
#include <Dxlib.h>

//Matrix4 �\����
struct Matrix4
{
	float m[4][4];
};

//�P�ʍs������߂�
Matrix4 identity();

//�g��k���s��̐ݒ�
Matrix4 scale(const Vector3& s);

//��]�s��̐ݒ�
Matrix4 rotateX(float angle);
Matrix4 rotateY(float angle);
Matrix4 rotateZ(float angle);

//���s�ړ��s��̍쐬
Matrix4 translate(const Vector3& t);

//���W�ϊ�(�x�N�g���ƍs��̊|���Z������)
Vector3 transform(const Vector3& v, const Matrix4& m);

//���W�Ԃ̋��������߂�
double CalculateDistance(Vector3& vec1, Vector3& vec2);

//������Z�q�I�[�o�[���[�h
Matrix4& operator*=(Matrix4& m1, Matrix4& m2);

//2�����Z�q�I�[�o�[���[�h
Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
Vector3 operator*(const Vector3& v, const  Matrix4& m);

