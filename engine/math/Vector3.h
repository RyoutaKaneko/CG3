#pragma once
#include <cmath>

class Vector3 {
public:
	float x;//x����
	float y;//y����
	float z;//z����

public:
	//�R���X�g���N�g
	Vector3();                            //�[���x�N�g���Ƃ��Đ���
	Vector3(float x, float y, float z);   //x����,y�������w�肵�Ă̐���

	//�@�����o�֐�
	float length() const;                 //�m����(����)�����߂�
	Vector3& normalize();                 //���K������
	static float dot(const Vector3& v, const Vector3& v2);   //���ς����߂�
	Vector3 cross(const Vector3& v)const; //�O�ς����߂�

	// ���`���(1���֐����)
	static const Vector3 lerp(const Vector3& start, const Vector3& end, const float t);

	//�b�����Z�q�I�[�o�[���[�h
	Vector3 operator+() const;
	Vector3 operator-() const;

	//������Z�q�I�[�o�[���[�h
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);
};
//2�����Z�q�I�[�o�[���[�h
//�������Ȉ���(�����̌^�Ə���)�̃p�^�[���ɑΉ����邽�߁A�ȉ��̂悤�ɏ������Ă���
const Vector3  operator+(const Vector3& v1, const Vector3& v2);
const Vector3  operator-(const Vector3& v1, const Vector3& v2);
const Vector3  operator*(const Vector3& v, float s);
const Vector3  operator*(float s, const Vector3& v);
const Vector3  operator/(const Vector3& v, float s);

