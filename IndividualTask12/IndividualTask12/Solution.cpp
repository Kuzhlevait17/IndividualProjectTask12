# include <iostream>
# include <fstream>
# include <string>

# include "Classes.h"

using namespace std;

bool Balloons::isValidNumber(const string& StringToCheck)
{

    if (StringToCheck.empty())
    {
        return false;
    }

    // ����� ������������ ���� ������� ��� �������� :)
    /* if (StringToCheck.find(' ') != string::npos) 
    {
        return false;
    }

    for (char C : StringToCheck)
    {
        if (C < '0' || C > '9')
        {
            return false;
        }
    }*/

    // ����������� ���������, ��� �������� ����� ���������.
    for (char C : StringToCheck)
    {
        // ���������� unsigned char ��� ���������� �������� �������� �����
        if (!isdigit(static_cast<unsigned char>(C)))
        {
            return false;
        }
    }

    return true;
}

int Balloons::StringToInt(const string& StringNumber)
{
    // ���������� ����������� try-catch ��� ������� ������
    // ������ �� ����� ����� �� ���� �� �����...
    try
    {
        return stoi(StringNumber);
    }
    catch (const invalid_argument&)
    {
        cerr << "������! ������ �� �������� ���������� �����." << endl;
    }
    catch (const out_of_range&)
    {
        cerr << "������! ����� ������� �� ������� int. " << endl;
    }

    // ���� �� ������� ��������� ����� - ���������� -1.
    return -1;
}

void Balloons::AddLast(PNode& Head, PNode& Tail, int AdditionalData)
{
    // ������� ����� ������� � ��������� ��� ��������
    PNode NewNode = new Node;
    NewNode->Data = AdditionalData;
    NewNode->Prev = Tail;
    NewNode->Next = nullptr;

    // ������ ��������� ���������� ������
    if (Tail != nullptr)
    {
        Tail->Next = NewNode;
    }

    Tail = NewNode;

    // �������� ����� - ������
    if (Head == nullptr)
    {
        Head = Tail;
    }
}

void Balloons::FillBalloons(int UserChoice, int AmountOfBalloons, Balloons& ColourfulBalloons)
{
    switch (UserChoice)
    {
    case 1:
    {
        // ��������� ������ ����� "�������"
        for (int i = 0; i < AmountOfBalloons;)
        {
            cout << "������� ���� " << i + 1 << " ������: ";

            string CheckBalloon;
            int Balloon;

            // ���������� ����������� try-catch ��� "�����" ������ 
            try
            {
                getline(cin, CheckBalloon);
                if (!ColourfulBalloons.isValidNumber(CheckBalloon))
                {
                    throw invalid_argument("������� �������� �������� ������ ��� �� �������� ������ � �����.");
                }

                try
                {
                    Balloon = ColourfulBalloons.StringToInt(CheckBalloon);
                    // ���������,��� �������� ������ ����� 0-9
                    if (Balloon < 0 || Balloon > 9 )
                    {
                        throw out_of_range("����� ������ ���� ����� ������ �� 0 �� 9.");
                    }

                    ColourfulBalloons.AddLast(FirstBalloon, LastBalloon, Balloon);

                    // ����������� ������� ������ �����, ����� �������� ����� � ������.
                    i++;
                }
                catch (const invalid_argument&e)
                {
                    cerr << "������: " << e.what() << endl;
                }
                catch (const out_of_range& e)
                {
                    cerr << "������: " << e.what() << endl;
                }

                
            }
            catch (const invalid_argument& e)
            {
                cerr << "������ �����: " << e.what() << endl;
            }
        }

        break;
    }

    case 2:
    {

        for (int i = 0; i < AmountOfBalloons; i++)
        {
            // ���������� �����������
            int Balloon = rand() % 10;
            ColourfulBalloons.AddLast(FirstBalloon, LastBalloon, Balloon);
        }

        break;

    }

    case 3:
    {
        // ������� ������ ���� � ������� � ��������� ��� ���������� �������.
        ofstream OutFile("ThirdChoice.txt");
        for (int i = 0; i < AmountOfBalloons; i++)
        {
            int Balloon = rand() % 10;
            OutFile << Balloon << " ";
        }
        OutFile.close();

        // ����� ������ �� �����
        ifstream InFile("ThirdChoice.txt");
        int Balloon;
        while (InFile >> Balloon)
        {
            if (Balloon < 0 || Balloon > 9) // �������� �� ������ ������� �������������� �����
            {
                cerr << "��������� ������������ ���� ������: " << Balloon << endl;
                continue;
            }
            AddLast(FirstBalloon, LastBalloon, Balloon);
        }
        InFile.close();
        break;
    }

    default:
    {
        cerr << "������� ������������ ��������. " << endl;
        break;
    }
    }
}

int Balloons::HasMultipleChains()
{
    int CurrentCount = 1;
    int ChainCount = 0;
    PNode Current = FirstBalloon;

    // ��������� ��������� ��������.
    while (Current != nullptr && Current->Next != nullptr)
    {
        // ���� �������� �������� ��������� ���������, �� ����������� ������� ���������� ���������
        if (Current->Data == Current->Next->Data)
        {
            CurrentCount++;
        }
        else
        { 
            // ���� �������� �������� ������ 3 - ����� ������� � 3+ ����������� ��������.
            if (CurrentCount >= 3)
            {
                ChainCount++;
            }

            // ���������� �������� ��������.
            CurrentCount = 1;
           
        }
        // ��������� �� ����� �������
        Current = Current->Next;
    }

    // ��������� ��������� �������
    if (CurrentCount >= 3)
    {
        ChainCount++;
    }

    // ���������� ����� �������
    return ChainCount;
}

void Balloons::ClearList()
{
    // ���������� �� ����������� ������ ������� � ������� � ������� ��� ��������
    PNode Current = FirstBalloon;
    while (Current != nullptr)
    {
        // ���������� ��������������� ������� ��� ������������ ��������.
        PNode Temprorary = Current;
        Current = Current->Next;
        delete Temprorary;
    }

    // �������������� ������ � ��������� ����� �������.
    FirstBalloon = nullptr;
    LastBalloon = nullptr;
}

int Balloons::RemoveChains() 
{
    // ���������� ��������� �������
    int TotalRemoved = 0;
    // ���������, ��� ���� ���-�� �������
    bool RemovedSomething;

    do 
    {
        RemovedSomething = false;
        // �������� �������� � ������� ������
        PNode Current = FirstBalloon;

        // ���� �� ������ �� �����
        while (Current != nullptr) 
        {
            // �������� ���������� ���� ������ (����� 0-9)
            int Colour = Current->Data;
            // �������� �������
            PNode Start = Current;
            int Count = 1;

            // ������� ����� ������� ���������� �������
            PNode Runner = Current->Next;
            while (Runner != nullptr && Runner->Data == Colour)
            {
                Count++;
                Runner = Runner->Next;
            }

            // ���� ����� ������� ������ 3+
            if (Count >= 3) 
            {
                // ������� ������� �� start �� runner->Prev
                PNode End = Runner ? Runner->Prev : LastBalloon;

                // ��������� ����� ������ ���������� ����� �������
                // Before - ��������� �� ���� ����� ������� �������
                // After - ��������� �� ���� ����� ��������� �������
                PNode Before = Start->Prev;
                PNode After = Runner;

                // ������� ���� (�� ���������� ���, ������� �� �����)
                PNode Temporary = Start;
                for (int i = 0; i < Count; i++) 
                {
                    PNode ToDelete = Temporary;
                    Temporary = Temporary->Next;
                    delete ToDelete;
                }

                // ��������� before � after
                // Before - ��������� �� ���� ����� ������� �������
                // After - ��������� �� ���� ����� ��������� �������
                if (Before)
                {
                    Before->Next = After;
                }
                else
                {
                    FirstBalloon = After; // ���� Before ��� ��������� ��������� �� ������ ����
                }

                if (After)
                {
                    After->Prev = Before;
                }
                else
                {
                    LastBalloon = Before; // ���� After ��� �������� ��������� �� ��������� ����
                }

                // ����������� ������� 
                TotalRemoved += Count;
                RemovedSomething = true;

                // ���������� �������� � ������� after
                Current = After;
            }
            else
            {
                // ���� ������� ���, ��������� ������
                Current = Current->Next;
            }
        }
    } while (RemovedSomething);

    return TotalRemoved;
}

void Balloons::ShowBalloons()
{
    // ���� ��� �� ������ ������
    if (!FirstBalloon)
    {
        cout << "�����!" << endl; 
    }

    // ��������� �������������� �������
    // ���������� �� ��������� ������ ������� � �������
	PNode Temporary = FirstBalloon;
	while (Temporary != nullptr)
	{
		cout << Temporary->Data << " ";
		Temporary = Temporary->Next;
	}
}

bool Balloons::AskToContinue(Balloons& ColourfulBalloons)
{
    // �����������, ���� �� ����� ������� ������ �����.
    while (true)
    {
        cout << endl << "������ ����������? ";
        cout << "�������� 1, ���� ��, ����� - 0";

        // ���������� ������, ��� ����, ����� ����������� �����
        // ��������� ������������ ��������� ������������� ��������.
        string Exiting;
        cout << endl << "������� ��� �����: ";
        getline(cin, Exiting);
        int ExitGame;

        try
        {
            // ��������� �� ����������� ��������� �����.
            if (!ColourfulBalloons.isValidNumber(Exiting))
            {
                throw invalid_argument("������� �������� �������� ��� �������� ������.");
            }
            ExitGame = ColourfulBalloons.StringToInt(Exiting);

            if (ExitGame != 1 && ExitGame != 0)
            {
                throw out_of_range("������� ��������� �������� ������ ��� �������� ������.");
            }

            if (ExitGame == 0)
            {

                cout << "������� Enter ��� ������...";
                /*cin.ignore();*/
                cin.get();
                return false;
            }
            else
            {
                return true;
            }

            break;
        }
        catch (const exception& e)
        {
            cerr << e.what()<< endl;
            cin.clear();
            /*cin.ignore();*/
        }
    }

}