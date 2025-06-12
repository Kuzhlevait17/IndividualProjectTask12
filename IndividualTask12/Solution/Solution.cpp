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

    // Можно использовать этот вариант для проверки :)
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

    // Посимвольно проверяем, что вводимое число корректно.
    for (char C : StringToCheck)
    {
        // Используем unsigned char для правильной проверки русского языка
        if (!isdigit(static_cast<unsigned char>(C)))
        {
            return false;
        }
    }

    return true;
}

int Balloons::StringToInt(const string& StringNumber)
{
    // Используем конструкцию try-catch для выловки ошибок
    // вообще не особо нужно по сути но ладно...
    try
    {
        return stoi(StringNumber);
    }
    catch (const invalid_argument&)
    {
        cerr << "Ошибка! Строка не содержит допустимое число." << endl;
    }
    catch (const out_of_range&)
    {
        cerr << "Ошибка! Число выходит за пределы int. " << endl;
    }

    // если не удалось перевести число - возвращаем -1.
    return -1;
}

void Balloons::AddLast(PNode& Head, PNode& Tail, int AdditionalData)
{
    // Создаем новый элемент и добавляем его значения
    PNode NewNode = new Node;
    NewNode->Data = AdditionalData;
    NewNode->Prev = Tail;
    NewNode->Next = nullptr;

    // Меняем адресацию последнего шарика
    if (Tail != nullptr)
    {
        Tail->Next = NewNode;
    }

    Tail = NewNode;

    // Вводимое число - первое
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
        // Заполняем каждый шарик "вручную"
        for (int i = 0; i < AmountOfBalloons;)
        {
            cout << "Введите цвет " << i + 1 << " шарика: ";

            string CheckBalloon;
            int Balloon;

            // Используем конструкцию try-catch для "ловки" ошибок 
            try
            {
                getline(cin, CheckBalloon);
                if (!ColourfulBalloons.isValidNumber(CheckBalloon))
                {
                    throw invalid_argument("Введено неверное значение шарика или вы добавили пробел в конце.");
                }

                try
                {
                    Balloon = ColourfulBalloons.StringToInt(CheckBalloon);
                    // Проверяем,что вводятся только цифры 0-9
                    if (Balloon < 0 || Balloon > 9 )
                    {
                        throw out_of_range("Шарик должен быть целым числом от 0 до 9.");
                    }

                    ColourfulBalloons.AddLast(FirstBalloon, LastBalloon, Balloon);

                    // Увеличиваем счётчик только тогда, когда добавили шарик в список.
                    i++;
                }
                catch (const invalid_argument&e)
                {
                    cerr << "Ошибка: " << e.what() << endl;
                }
                catch (const out_of_range& e)
                {
                    cerr << "Ошибка: " << e.what() << endl;
                }

                
            }
            catch (const invalid_argument& e)
            {
                cerr << "Ошибка ввода: " << e.what() << endl;
            }
        }

        break;
    }

    case 2:
    {

        for (int i = 0; i < AmountOfBalloons; i++)
        {
            // используем рандомайзер
            int Balloon = rand() % 10;
            ColourfulBalloons.AddLast(FirstBalloon, LastBalloon, Balloon);
        }

        break;

    }

    case 3:
    {
        // Сначала создаём файл с данными и заполняем его рандомными числами.
        ofstream OutFile("ThirdChoice.txt");
        for (int i = 0; i < AmountOfBalloons; i++)
        {
            int Balloon = rand() % 10;
            OutFile << Balloon << " ";
        }
        OutFile.close();

        // Затем читаем из файла
        ifstream InFile("ThirdChoice.txt");
        int Balloon;
        while (InFile >> Balloon)
        {
            if (Balloon < 0 || Balloon > 9) // Проверка на случай ручного редактирования файла
            {
                cerr << "Обнаружен некорректный цвет шарика: " << Balloon << endl;
                continue;
            }
            AddLast(FirstBalloon, LastBalloon, Balloon);
        }
        InFile.close();
        break;
    }

    default:
    {
        cerr << "Введено некорректное значение. " << endl;
        break;
    }
    }
}

int Balloons::HasMultipleChains()
{
    int CurrentCount = 1;
    int ChainCount = 0;
    PNode Current = FirstBalloon;

    // Проверяем соседнием элементы.
    while (Current != nullptr && Current->Next != nullptr)
    {
        // Если значение соседних элементов совпадает, то увеличиваем счётчик одинаковых элементов
        if (Current->Data == Current->Next->Data)
        {
            CurrentCount++;
        }
        else
        { 
            // Если значение счётчика больше 3 - нашли цепочку с 3+ одинаковыми шариками.
            if (CurrentCount >= 3)
            {
                ChainCount++;
            }

            // Сбрасываем значение счётчика.
            CurrentCount = 1;
           
        }
        // Переходим на новый элемент
        Current = Current->Next;
    }

    // Проверяем последнюю цепочку
    if (CurrentCount >= 3)
    {
        ChainCount++;
    }

    // Возвращаем число цепочек
    return ChainCount;
}

void Balloons::ClearList()
{
    // Проходимся по двусвязному списку начиная с первого и удаляем все элементы
    PNode Current = FirstBalloon;
    while (Current != nullptr)
    {
        // Используем вспомогательный элемент для корректности удаления.
        PNode Temprorary = Current;
        Current = Current->Next;
        delete Temprorary;
    }

    // Инициализируем первый и последний шарик пустыми.
    FirstBalloon = nullptr;
    LastBalloon = nullptr;
}

int Balloons::RemoveChains() 
{
    // Количество удаленных шариков
    int TotalRemoved = 0;
    // Проверяем, что было что-то удалено
    bool RemovedSomething;

    do 
    {
        RemovedSomething = false;
        // Начинаем проверку с первого шарика
        PNode Current = FirstBalloon;

        // Пока не дойдем до конца
        while (Current != nullptr) 
        {
            // Отдельно запоминаем цвет шарика (число 0-9)
            int Colour = Current->Data;
            // Начинаем цепочку
            PNode Start = Current;
            int Count = 1;

            // Считаем длину цепочки одинаковых шариков
            PNode Runner = Current->Next;
            while (Runner != nullptr && Runner->Data == Colour)
            {
                Count++;
                Runner = Runner->Next;
            }

            // Если нашли цепочку длиной 3+
            if (Count >= 3) 
            {
                // Удаляем цепочку от start до runner->Prev
                PNode End = Runner ? Runner->Prev : LastBalloon;

                // Обновляем связи вокруг удаляемого блока цепочек
                // Before - указатель на узел перед началом цепочки
                // After - указатель на узел после окончания цепочки
                PNode Before = Start->Prev;
                PNode After = Runner;

                // Удаляем узлы (то количество раз, сколько мы нашли)
                PNode Temporary = Start;
                for (int i = 0; i < Count; i++) 
                {
                    PNode ToDelete = Temporary;
                    Temporary = Temporary->Next;
                    delete ToDelete;
                }

                // Связываем before и after
                // Before - указатель на узел перед началом цепочки
                // After - указатель на узел после окончания цепочки
                if (Before)
                {
                    Before->Next = After;
                }
                else
                {
                    FirstBalloon = After; // Если Before нет обновляем указатель на первый узел
                }

                if (After)
                {
                    After->Prev = Before;
                }
                else
                {
                    LastBalloon = Before; // Если After нет обовляем указатель на последний узел
                }

                // Увеличиваем позицию 
                TotalRemoved += Count;
                RemovedSomething = true;

                // Продолжаем проверку с позиции after
                Current = After;
            }
            else
            {
                // Если цепочки нет, двигаемся дальше
                Current = Current->Next;
            }
        }
    } while (RemovedSomething);

    return TotalRemoved;
}

void Balloons::ShowBalloons()
{
    // Если нет ни одного шарика
    if (!FirstBalloon)
    {
        cout << "Пусто!" << endl; 
    }

    // Используя дополнительный элемент
    // проходимся по элементам списка начиная с первого
	PNode Temporary = FirstBalloon;
	while (Temporary != nullptr)
	{
		cout << Temporary->Data << " ";
		Temporary = Temporary->Next;
	}
}

bool Balloons::AskToContinue(Balloons& ColourfulBalloons)
{
    // Зацикливаем, пока не будет введено верное число.
    while (true)
    {
        cout << endl << "Хотите продолжить? ";
        cout << "Напишите 1, если да, иначе - 0";

        // Используем строки, для того, чтобы посимвольно после
        // проверять корректность вводимого пользователем значения.
        string Exiting;
        cout << endl << "Введите ваш выбор: ";
        getline(cin, Exiting);
        int ExitGame;

        try
        {
            // Проверяем на корретность вводимого числа.
            if (!ColourfulBalloons.isValidNumber(Exiting))
            {
                throw invalid_argument("Введено неверное значение или добавлен пробел.");
            }
            ExitGame = ColourfulBalloons.StringToInt(Exiting);

            if (ExitGame != 1 && ExitGame != 0)
            {
                throw out_of_range("Введено невероное значение выхода или добавлен пробел.");
            }

            if (ExitGame == 0)
            {

                cout << "Нажмите Enter для выхода...";
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