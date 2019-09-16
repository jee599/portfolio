#include "Header.h"
#include "CPlayer.h"

enum Function { MAKEID, RANDID };

// Function

// Process
void Init(vector<CPlayer>& P);			// 시작할 때 Code와 점수를 임의로 채워줌
void Process(vector<CPlayer>& P);		// 게임을 한번 실행한다 10%의 유저
void Menu(vector<CPlayer>& P);			// 메뉴를 고르게 하고, 해당 기능을 실행
void MakeRank(vector <CPlayer>& P);		// 점수를 갱신할 때마다 아레나별 순위를 갱신해준다.
// OutPut
void Output_All(vector<CPlayer>& P);	// 상위 1%의 플레이어를 보여줌
void Output_Code(vector<CPlayer>::iterator iter, vector<CPlayer>& P);	// Code를 입력 받고, 해당 순위 위,아래의 점수,등수까지 보여줌
// FileInOut
void FileOut(vector <CPlayer>& P);		// 파일에 쓴다 (Code , Arena Score 1~5)
void FileIn(vector <CPlayer>& P);		// 파일에 있는 것을 읽어 온다.
// Find, Check
vector<CPlayer>::iterator Find(vector<CPlayer>& P);		// 검색하는 Code 와 일치하는 백터의 iter를 반환 후 해당 vector에 접근을 도와줌
int CheckCode(int n, bool a);			// 중복된 Code인지 확인한다.(Code 생성 시)

int Make[20000];						// 이 배열과 밑의 배열은 중복을 검사하는 배열이다
int Rand[2000];
int Rand_Size = 0;
int Make_Size = 0;

default_random_engine dre;
uniform_int_distribution<> score(0, 25000000);
uniform_int_distribution<> code(10000, 99999);

void main()
{
	dre.seed(time(NULL));
	vector<CPlayer> Player;
	Player.reserve(20000);
	Init(Player);
	Menu(Player);
}

void FileOut(vector<CPlayer>& P)
{
	ofstream fout;
	fout.open("Output.txt", ios::out, ios::trunc);
	for (int i = 0; i < 20000; ++i)
	{
		fout << P.at(i).GetCode() << "\t";
		for (int j = 1; j < 6; ++j)
			fout << P.at(i).GetArena(j) << "\t";
		fout << endl;
	}
	if (fout.is_open() == true)
		fout.close();
}

void FileIn(vector <CPlayer> & P)
{
	int n[6] = { 0 };

	ifstream fin;
	fin.open("Output.txt");
	if (fin.is_open() == false)
		cout << "파일에 내용이 없습니다." << endl;

	else
	{
		for (int i = 0; i < 20000; ++i)
		{
			fin >> n[5];
			P.at(i).SetCode(n[5]);
			fin >> n[0] >> n[1] >> n[2] >> n[3] >> n[4];
			P.at(i).SetSA(n[0], n[1], n[2], n[3], n[4]);
		}
	}
}
void MakeRank(vector<CPlayer> & P)
{
	for (int i = 1; i < 7; ++i)
	{
		sort(P.begin(), P.end(), [i](CPlayer & a, CPlayer & b)
			{
				return a.GetArena(i) > b.GetArena(i);
			});
		for (int j = 0; j < 20000; ++j)
			P.at(j).SetRank(j + 1, i);
	}
}
void Output_Code(vector<CPlayer>::iterator iter, vector<CPlayer> & P)
{
	int m = -1;
	if (iter == P.end())
		return;
	if (iter == P.begin())
		m = 0;
	for (int i = m; i < 2; ++i)
	{
		int n = (iter + i)->GetPrev();
		cout << " CODE : " << (iter + i)->GetCode() << " 의 Total Score : " << (iter + i)->GetTotal() <<
			" RANK : " << (iter + i)->GetRank(6) << " 위( " << ((iter + i)->GetRank(6)) / 200 << " %) ";
		if (n < 0)
		{
			n = n * -1;
			cout << " ( - " << n << " 등) " << endl;
		}
		else if (n > 0) cout << " ( + " << n << " 등) " << endl;
		else cout << "( 동일 ) " << endl;
	}
	cout << " - - - - - - - - - - - - - - " << endl;
	for (int i = 1; i < 6; ++i)
		cout << " CODE : " << iter->GetCode() << "의  ARENA " << i << "의 Score : " <<
		iter->GetArena(i) << "  순위 " << iter->GetRank(i) << "위" << endl;
}

void Menu(vector<CPlayer> & P)
{
	while (true)
	{
		cout << "내 Code : 12345 " << endl;
		cout << "1. 게임 플레이 " << endl;
		cout << "2. 상위 1% 플레이어 정보 보기" << endl;
		cout << "3. 특정 플레이어 정보 보기" << endl;
		cout << "4. 파일로 출력하기" << endl;
		cout << "5. 파일에서 받아오기" << endl;
		cout << "6. 종료하기" << endl;

		int Input;
		cin >> Input;
		MakeRank(P);
		switch (Input)
		{
		case 1:
			Process(P);
			break;
		case 2:
			Output_All(P);
			break;
		case 3:
			Output_Code(Find(P), P);
			break;
		case 4:
			FileOut(P);
			break;
		case 5:
			FileIn(P);
			break;
		case 6:
			return;
		}
		system("pause");
		system("cls");
		Rand_Size = 0;
	}
}
vector<CPlayer>::iterator Find(vector<CPlayer> & P)
{
	cout << "코드를 입력하세요(10000 ~ 99999)" << endl;
	int Input;
	cin >> Input;

	vector<CPlayer>::iterator iter = P.begin();

	iter = find(P.begin(), P.end(), Input);
	return iter;
}

void Output_All(vector<CPlayer> & P)
{
	for (int i = 0; i < 200; ++i)
	{
		cout << P.at(i).GetRank(6) / 200 << " %";
		cout << P.at(i).GetCode() << " : " << P.at(i).GetTotal() << " \t";
		if (!(i % 5) && i != 0)
			cout << endl;
	}
}

void Process(vector<CPlayer> & P)
{
	uniform_int_distribution<> Random_Player(0, 19999);
	vector<CPlayer>::iterator Iter = P.begin();

	int n = 0;

	n = CheckCode(12345, RANDID);
	Iter = P.begin();
	Iter += n;
	Iter->SetScore(score(dre));

	for (int i = 1; i < 2000; ++i)
	{
		n = CheckCode(Random_Player(dre), RANDID);
		if (n != -1)
		{
			Iter = P.begin();
			Iter += n;
			Iter->SetScore(score(dre));
		}
		else
			--i;
	}
}

void Init(vector<CPlayer> & P)
{
	int n = 0;
	//Initial();
	P.push_back(CPlayer(12345, score(dre), score(dre), score(dre), score(dre), score(dre)));

	for (int i = 1; i < 20000; ++i)
	{
		n = CheckCode(code(dre), MAKEID);
		if (n != -1)
			P.push_back(CPlayer(n, score(dre), score(dre), score(dre), score(dre), score(dre)));
		else
			--i;
	}
	sort(P.begin(), P.end(), [](CPlayer & a, CPlayer & b)
		{
			return a.GetTotal() > b.GetTotal();
		});
}
int CheckCode(int n, bool a)	//Code를 받을 때 중복된 코드인지 확인
{
	if (a == MAKEID)
	{
		for (int i = 0; i <= Make_Size; ++i)		// 최소한으로 for문 돌기 위해 현재까지 받은 갯수만큼만 검사한다.
			if (Make[i] == n)
			{
				n = -1;
				break;
			}
		if (n != -1)
			Make[++Make_Size] = n;
		return n;
	}
	else//RANDID
	{
		for (int i = 0; i <= Rand_Size; ++i)
			if (Rand[i] == n)
			{
				n = -1;
				break;
			}
		if (n != -1)
			Rand[++Rand_Size] = n;
		return n;
	}
}