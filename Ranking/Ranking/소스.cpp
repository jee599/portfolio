#include "Header.h"
#include "CPlayer.h"

enum Function { MAKEID, RANDID };

// Function

// Process
void Init(vector<CPlayer>& P);			// ������ �� Code�� ������ ���Ƿ� ä����
void Process(vector<CPlayer>& P);		// ������ �ѹ� �����Ѵ� 10%�� ����
void Menu(vector<CPlayer>& P);			// �޴��� ���� �ϰ�, �ش� ����� ����
void MakeRank(vector <CPlayer>& P);		// ������ ������ ������ �Ʒ����� ������ �������ش�.
// OutPut
void Output_All(vector<CPlayer>& P);	// ���� 1%�� �÷��̾ ������
void Output_Code(vector<CPlayer>::iterator iter, vector<CPlayer>& P);	// Code�� �Է� �ް�, �ش� ���� ��,�Ʒ��� ����,������� ������
// FileInOut
void FileOut(vector <CPlayer>& P);		// ���Ͽ� ���� (Code , Arena Score 1~5)
void FileIn(vector <CPlayer>& P);		// ���Ͽ� �ִ� ���� �о� �´�.
// Find, Check
vector<CPlayer>::iterator Find(vector<CPlayer>& P);		// �˻��ϴ� Code �� ��ġ�ϴ� ������ iter�� ��ȯ �� �ش� vector�� ������ ������
int CheckCode(int n, bool a);			// �ߺ��� Code���� Ȯ���Ѵ�.(Code ���� ��)

int Make[20000];						// �� �迭�� ���� �迭�� �ߺ��� �˻��ϴ� �迭�̴�
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
		cout << "���Ͽ� ������ �����ϴ�." << endl;

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
		cout << " CODE : " << (iter + i)->GetCode() << " �� Total Score : " << (iter + i)->GetTotal() <<
			" RANK : " << (iter + i)->GetRank(6) << " ��( " << ((iter + i)->GetRank(6)) / 200 << " %) ";
		if (n < 0)
		{
			n = n * -1;
			cout << " ( - " << n << " ��) " << endl;
		}
		else if (n > 0) cout << " ( + " << n << " ��) " << endl;
		else cout << "( ���� ) " << endl;
	}
	cout << " - - - - - - - - - - - - - - " << endl;
	for (int i = 1; i < 6; ++i)
		cout << " CODE : " << iter->GetCode() << "��  ARENA " << i << "�� Score : " <<
		iter->GetArena(i) << "  ���� " << iter->GetRank(i) << "��" << endl;
}

void Menu(vector<CPlayer> & P)
{
	while (true)
	{
		cout << "�� Code : 12345 " << endl;
		cout << "1. ���� �÷��� " << endl;
		cout << "2. ���� 1% �÷��̾� ���� ����" << endl;
		cout << "3. Ư�� �÷��̾� ���� ����" << endl;
		cout << "4. ���Ϸ� ����ϱ�" << endl;
		cout << "5. ���Ͽ��� �޾ƿ���" << endl;
		cout << "6. �����ϱ�" << endl;

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
	cout << "�ڵ带 �Է��ϼ���(10000 ~ 99999)" << endl;
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
int CheckCode(int n, bool a)	//Code�� ���� �� �ߺ��� �ڵ����� Ȯ��
{
	if (a == MAKEID)
	{
		for (int i = 0; i <= Make_Size; ++i)		// �ּ������� for�� ���� ���� ������� ���� ������ŭ�� �˻��Ѵ�.
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