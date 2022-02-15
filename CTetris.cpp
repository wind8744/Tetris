#include <iostream>
#include "CTetris.h"
using namespace std;
int Nowblock[4][4] = { 0, };
int Map[15][12] =
{
	2,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,2,
	2,2,2,2,2,2,2,2,2,2,2,2
};
int Blocks[7][4][4] = {
	{
		1, 1, 1, 0,
		1, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	},
	{
		1, 1, 1, 1,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	},
	{
		1, 1, 1, 0,
		0, 0, 1, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	},
	{
		0, 1, 1, 0,
		1, 1, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	},
	{
		1, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	},
	{
		1, 1, 0, 0,
		1, 1, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	},
	{
		1, 1, 1, 0,
		0, 1, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	}
};

CTetris::CTetris()
	:m_X(0)
	, m_Y(4)
	, m_Score(0)
	, m_KillLine(0)
	, m_IsOver(false)
{
}

void CTetris::SetBlock()
{
	//block 7개 중 랜덤하게 1개 선택
	srand(time(NULL));
	int select = rand() % 7;

	m_Y = 0;
	m_X = 5;

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			Nowblock[y][x] = Blocks[select][y][x];
		}
	}
}


void CTetris::PrintMap()
{
	CheckMap();

	system("cls");

	if (m_IsOver) // 게임오버
	{
		for (int y = 0; y < 15; y++)
		{
			if (y >= 5 && y <= 9)
			{
				if (y == 6) printf("      Game Over !!");
				else if (y == 7) printf("      Score : %d", m_Score);
				else if (y == 8) printf("      Line  : %d", m_KillLine);
				else
				{
					for (int x = 13; x < 18; x++) cout << " ";// printf(" ");
					for (int x = 18; x < 32; x++) cout << " "; //printf("=");
				}
			}
			else
			{
				for (int x = 0; x < 12; x++)
				{
					cout << "▨";
				}
			}
			cout << endl;
		}

		return;
	}

	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			if (m_X <= x && x < m_X + 4 && m_Y <= y && y < m_Y + 4
				&& Nowblock[y - m_Y][x - m_X] == 1) // 블럭의 1인부분만 맵에 출력
			{
				//printf("□");
				cout << "□";
			}
			else {

				if (Map[y][x] == 0) cout << "  ";
				else if (Map[y][x] == 2) cout << "▧";
				else cout << "■";
			}
		}

		if (y >= 4 && y <= 7)
		{
			if (y == 5) printf("      Score : %d", m_Score);
			else if (y == 6) printf("      Line : %d", m_KillLine);
			else
			{
				for (int x = 13; x < 18; x++) cout << " ";// printf(" ");
				for (int x = 18; x < 32; x++) cout << "="; //printf("=");
			}
		}
		cout << endl;
	}
}

void CTetris::Spin()
{
	SpinBlock();

	//돌렸는데 겹치면 다시 원래대로
	if (IsStack(m_X, m_Y))
	{
		SpinBlock();
		SpinBlock();
		SpinBlock();
	}
}

void CTetris::SpinBlock()
{
	// 블럭 90도 회전
	int temp[4][4];

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			temp[x][3 - y] = Nowblock[y][x];
		}
	}
	memcpy(Nowblock, temp, 4 * 16);

	// 블럭 당겨주기
	int min_y = 99;
	int min_x = 99;
	int max_y = -99;
	int max_x = -99;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (Nowblock[y][x] == 1) //블럭이 있는 테두리 좌표 구하기
			{
				if (min_y > y) min_y = y;
				if (min_x > x) min_x = x;
				if (max_y < y) max_y = y;
				if (max_x < x) max_x = x;
			}
		}
	}
	memset(temp, 0, sizeof(temp));
	for (int y = min_y; y <= max_y; y++)
	{
		for (int x = min_x; x <= max_x; x++)
		{
			temp[y - min_y][x - min_x] = Nowblock[y][x];
		}
	}
	memcpy(Nowblock, temp, 4 * 16);

	// test
	//for (int y = 0; y < 4; y++)
	//{
	//	for (int x = 0; x < 4; x++)
	//	{
	//		cout << Nowblock[y][x];
	//	}
	//	cout << endl;
	//}
	//cout << endl;
}

void CTetris::MoveBlock(int dir)
{
	// 0 x/ 1 down /2 left / 3 right
	int dx[4] = { 0,0,-1,1 };
	int dy[4] = { 0,0,0,0 };

	if (dir == 1)
	{
		down();
		return;
	}

	if (IsStack(m_X + dx[dir], m_Y + dy[dir])) return;

	m_X += dx[dir];
	m_Y += dy[dir];
}

bool CTetris::IsStack(int gx, int gy)
{
	//gx,gy에 블럭을 두었을때 겹치면 true
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (Nowblock[y][x] == 1 && Map[gy + y][gx + x] == 2)
				return true;

			if (Nowblock[y][x] == 1 && Map[gy + y][gx + x] == 1)
				return true;
		}
	}
	return false;
}

void CTetris::down()
{
	if (!IsStack(m_X, m_Y + 1)) m_Y++;
	else //밑이 막혔을때
	{
		//블록을 맵과 굳도록
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				if (Nowblock[y][x] == 1) {
					Map[m_Y + y][m_X + x] = 1;
				}
			}
		}
		//블록 교체
		SetBlock();
	}
}

void CTetris::CheckMap()
{
	for (int x = 1; x < 11; x++)
	{
		if (Map[0][x] == 1) {
			m_IsOver = true;
			return;
		}
	}

	int Line = 0;
	for (int y = 13; y >= 0; y--)
	{
		int cnt = 0;
		for (int x = 1; x < 11; x++)
		{
			cnt += Map[y][x];
		}

		if (cnt >= 10)
		{
			Line++;
			//삭제
			for (int z = 1; z < 11; z++) {
				Map[y][z] = 0;
			}

			//내력오기
			for (int i = y; i > 0; i--) {
				for (int j = 1; j < 11; j++) {
					Map[i][j] = Map[i - 1][j];
				}
			}
		}
	}
	m_KillLine += Line;
	if (Line >= 2) Line = Line*2;
	m_Score += Line * 100;

}