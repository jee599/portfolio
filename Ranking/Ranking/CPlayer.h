#pragma once

class CPlayer
{
private:

	int Code;
	int Score[6];		// 0은 Total Score, 나머지는 아레나별
	int Rank[7];		// 1~5는 아레나 별 순위, 6은 총점의 순위, 7은 이전 순위(비교용)
	int Rank_Prev;

public:
	CPlayer() {};
	CPlayer(int m, int n1, int n2, int n3, int n4, int n5);

public:
	void SetCode(int n);									// Code를 받고 클래스의 Id를 정해줌
	void SetSA(int n1, int n2, int n3, int n4, int n5);		// Score를 5개 받고 Arena별로 넣어줌
	void SetRank(int n, int Arena);							// N = 등수와 해당 Arena를 받고 각 아레나에 맞는 등수를 넣어줌
	void SetScore(int n);									// 플레이했을 때 점수를 받고, 저장

	int GetCode();
	int GetRank(int Arena);
	int GetTotal();
	int GetPrev();
	int GetArena(int Arena);

	bool operator == (int a);
};
#pragma once
