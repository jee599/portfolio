#pragma once

class CPlayer
{
private:

	int Code;
	int Score[6];		// 0�� Total Score, �������� �Ʒ�����
	int Rank[7];		// 1~5�� �Ʒ��� �� ����, 6�� ������ ����, 7�� ���� ����(�񱳿�)
	int Rank_Prev;

public:
	CPlayer() {};
	CPlayer(int m, int n1, int n2, int n3, int n4, int n5);

public:
	void SetCode(int n);									// Code�� �ް� Ŭ������ Id�� ������
	void SetSA(int n1, int n2, int n3, int n4, int n5);		// Score�� 5�� �ް� Arena���� �־���
	void SetRank(int n, int Arena);							// N = ����� �ش� Arena�� �ް� �� �Ʒ����� �´� ����� �־���
	void SetScore(int n);									// �÷������� �� ������ �ް�, ����

	int GetCode();
	int GetRank(int Arena);
	int GetTotal();
	int GetPrev();
	int GetArena(int Arena);

	bool operator == (int a);
};
#pragma once
