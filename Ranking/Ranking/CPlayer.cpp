#include "CPlayer.h"

CPlayer::CPlayer(int m, int n1, int n2, int n3, int n4, int n5)
{
	Score[1] = n1;
	Score[2] = n2;
	Score[3] = n3;
	Score[4] = n4;
	Score[5] = n5;
	Score[6] = n1 + n2 + n3 + n4 + n5;
	Code = m;
	Rank_Prev = -1;
	Rank[6] = -1;
}
void CPlayer::SetCode(int n)
{
	Code = n;
}
void CPlayer::SetSA(int n1, int n2, int n3, int n4, int n5) {
	if (Score[1] < n1)
		Score[1] = n1;
	if (Score[2] < n2)
		Score[2] = n2;
	if (Score[3] < n3)
		Score[3] = n3;
	if (Score[4] < n4)
		Score[4] = n4;
	if (Score[5] < n5)
		Score[5] = n5;
	Score[6] = Score[1] + Score[2] + Score[3] + Score[4] + Score[5];
}
int CPlayer::GetArena(int Arena)
{
	if (Arena == 6)
		return GetTotal();
	return Score[Arena];
}
void CPlayer::SetRank(int n, int Arena) {
	if (Arena == 6 && Rank[6] != n)
		Rank[7] = Rank[6];
	Rank[Arena] = n;
}
bool CPlayer::operator ==(int a)
{
	return GetCode() == a;
}
void CPlayer::SetScore(int n) {
	int Arena = n % 5 + 1;
	if (Score[Arena] < n)
		Score[Arena] = n;
	Score[6] = Score[1] + Score[2] + Score[3] + Score[4] + Score[5];
}
int CPlayer::GetCode()
{
	return Code;
}
int CPlayer::GetPrev()
{
	if (Rank[7] == -1)
		return 0;
	return Rank[7] - Rank[6];
}
int CPlayer::GetRank(int Arena)
{
	return Rank[Arena];
}

int CPlayer::GetTotal()
{
	Score[6] = Score[1] + Score[2] + Score[3] + Score[4] + Score[5];
	return Score[6];
}