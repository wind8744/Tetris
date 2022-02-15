#pragma once

class CTetris
{
private:
	int m_Y; // 시작좌표
	int m_X;

	int m_Score; //점수
	int m_KillLine; //없앤 줄수

	bool m_IsOver;

private:
	void SpinBlock(); //블럭 회전
	bool IsStack(int gx, int gy); //블럭 겹침 확인
	void down();
	void CheckMap();


public:
	void SetBlock();
	void Spin();
	void MoveBlock(int dir);
	void PrintMap();

public:
	CTetris();
};

