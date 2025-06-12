#pragma once

# include <iostream>
# include <fstream>
# include <string>

using namespace std;

/// Класс Balloons(Шарики), описывающий основную работу программы из PrintWelcomeMessage
class Balloons
{
private:
	/// Структура, которая задает шаблон для двусвязнного списка
	struct Node
	{
		int Data;
		Node* Next;
		Node* Prev;
	};

	typedef Node* PNode;

	/// Сразу же заполняем значения первого и последнего шарика. 
	/// Извне класса обращаться нельзя.
	PNode FirstBalloon = nullptr;
    PNode LastBalloon = nullptr;
	
public:

	/// Функция, которая проверяет, что число является числом, а не какой-то страшной подписью и т.д.
	/// <param name="StringToCheck">Входная строка с символами.</param>
	/// <returns>true, если введеная строка - целое число. Иначе - false.</returns>
	bool isValidNumber(const string& StringToCheck);

	///  Функция, которая переводит строку в целое число.
	/// <param name="StringNumber"> Входная строка с числом.</param>
	/// <returns>Целое число, полученное из строки.</returns>
	int StringToInt(const string& StringNumber);

	/// Функция, которая заполняет двусязный список шариками в зависимости от выбора пользователя.
	/// <param name="UserChoice"> Выбор пользователя для заполнения шариками: 1 - Из консоли;
	/// 2 - Рандомайзер;
	/// 3 - Текстовый файл;</param>
	/// <param name="AmountOfBalloons"> Количество шариков в изначальный момент.</param>
	/// <param name="ColourfulBalloons"> Объект класса Balloons. </param>
	void FillBalloons(int UserChoice, int AmountOfBalloons, Balloons& ColourfulBalloons);

	/// Функция, которая проверяет, что в начальный момент количество цепочек с 3+ шариками только одна
	/// (из условия задачи).
	/// <returns>Возвращает количество цепочек.</returns>
	int HasMultipleChains();

	/// Функция, которая добавляем элементы в конец списка.
	/// <param name="Head"> Первый элемент двусвязного списка.</param>
	/// <param name="Tail"> Последний элемент двусвязного списка.</param>
	/// <param name="AdditionalData"> Значение нового добавляемого элемента. </param>
	void AddLast(PNode& Head, PNode& Tail, int AdditionalData);

	/// Функция, которая очищает список элементов, если в нем изначально
	/// содержится более одной цепочки (из условия более одной не должно быть).
	void ClearList();

	/// Основная функция программы, которая удаляет 3+ шарика идущих подряд.
	/// <returns> Целое число - количество удаленных шариков. </returns>
	int RemoveChains();

	/// Функция, которая выводит на экран все шарики. 
	/// Очень важно, когда пользователь выбирает 2 - рандом или 3 - текстовый файл
	/// то есть, он не знает заранее, какие элементы будут.
	void ShowBalloons();

	/// Функция, которая запрашивает у пользователя закончить игру или продолжить дальше.
	/// <param name="ColourfulBalloons"> Объект класса Balloons. </param>
	/// <returns>true, если игра продолжается. false, если выходим из игры.</returns>
	bool AskToContinue(Balloons& ColourfulBalloons);	


	/// Деструктор, удаляющий все узлы двусвязного списка
	/// когда объект ColourfulBalloons выходит из области видимости
	~Balloons()
	{
		ClearList();
	}
};
