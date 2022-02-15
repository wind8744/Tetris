#pragma once

class CTetris
{
private:
	int m_Y; // ������ǥ
	int m_X;

	int m_Score; //����
	int m_KillLine; //���� �ټ�

	bool m_IsOver;

private:
	void SpinBlock(); //�� ȸ��
	bool IsStack(int gx, int gy); //�� ��ħ Ȯ��
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

