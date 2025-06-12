#pragma once

# include <iostream>
# include <fstream>
# include <string>

using namespace std;

/// ����� Balloons(������), ����������� �������� ������ ��������� �� PrintWelcomeMessage
class Balloons
{
private:
	/// ���������, ������� ������ ������ ��� ������������ ������
	struct Node
	{
		int Data;
		Node* Next;
		Node* Prev;
	};

	typedef Node* PNode;

	/// ����� �� ��������� �������� ������� � ���������� ������. 
	/// ����� ������ ���������� ������.
	PNode FirstBalloon = nullptr;
    PNode LastBalloon = nullptr;
	
public:

	/// �������, ������� ���������, ��� ����� �������� ������, � �� �����-�� �������� �������� � �.�.
	/// <param name="StringToCheck">������� ������ � ���������.</param>
	/// <returns>true, ���� �������� ������ - ����� �����. ����� - false.</returns>
	bool isValidNumber(const string& StringToCheck);

	///  �������, ������� ��������� ������ � ����� �����.
	/// <param name="StringNumber"> ������� ������ � ������.</param>
	/// <returns>����� �����, ���������� �� ������.</returns>
	int StringToInt(const string& StringNumber);

	/// �������, ������� ��������� ��������� ������ �������� � ����������� �� ������ ������������.
	/// <param name="UserChoice"> ����� ������������ ��� ���������� ��������: 1 - �� �������;
	/// 2 - �����������;
	/// 3 - ��������� ����;</param>
	/// <param name="AmountOfBalloons"> ���������� ������� � ����������� ������.</param>
	/// <param name="ColourfulBalloons"> ������ ������ Balloons. </param>
	void FillBalloons(int UserChoice, int AmountOfBalloons, Balloons& ColourfulBalloons);

	/// �������, ������� ���������, ��� � ��������� ������ ���������� ������� � 3+ �������� ������ ����
	/// (�� ������� ������).
	/// <returns>���������� ���������� �������.</returns>
	int HasMultipleChains();

	/// �������, ������� ��������� �������� � ����� ������.
	/// <param name="Head"> ������ ������� ����������� ������.</param>
	/// <param name="Tail"> ��������� ������� ����������� ������.</param>
	/// <param name="AdditionalData"> �������� ������ ������������ ��������. </param>
	void AddLast(PNode& Head, PNode& Tail, int AdditionalData);

	/// �������, ������� ������� ������ ���������, ���� � ��� ����������
	/// ���������� ����� ����� ������� (�� ������� ����� ����� �� ������ ����).
	void ClearList();

	/// �������� ������� ���������, ������� ������� 3+ ������ ������ ������.
	/// <returns> ����� ����� - ���������� ��������� �������. </returns>
	int RemoveChains();

	/// �������, ������� ������� �� ����� ��� ������. 
	/// ����� �����, ����� ������������ �������� 2 - ������ ��� 3 - ��������� ����
	/// �� ����, �� �� ����� �������, ����� �������� �����.
	void ShowBalloons();

	/// �������, ������� ����������� � ������������ ��������� ���� ��� ���������� ������.
	/// <param name="ColourfulBalloons"> ������ ������ Balloons. </param>
	/// <returns>true, ���� ���� ������������. false, ���� ������� �� ����.</returns>
	bool AskToContinue(Balloons& ColourfulBalloons);	


	/// ����������, ��������� ��� ���� ����������� ������
	/// ����� ������ ColourfulBalloons ������� �� ������� ���������
	~Balloons()
	{
		ClearList();
	}
};
