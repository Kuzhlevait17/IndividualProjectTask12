# include <iostream>
# include <fstream>
# include <ctime>
# include <string>
# include <sstream>

# include "Classes.h"

using namespace std;

/// Сообщение, которое выводится в начале программы.
void PrintWelcomeMessage()
{
	cout << endl << endl
		<< "  *************************************" << endl
		<< "  *                                   *" << endl
		<< "  *     ИКМ по C++. Вариант 12        *" << endl
		<< "  *                                   *" << endl
		<< "  *************************************" << endl
		<< endl << endl;

	cout << "Шарики. В одной компьютерной игре игрок выставляет в линию шарики разных цветов. " << endl
		<< "Когда образуется непрерывная цепочка из трех и более шариков одного цвета, она удаляется из линии." << endl
		<< "Все шарики при этом сдвигаются друг к другу, и ситуация может повториться." << endl
		<< "Естественно, непрерывных цепочек из трех и более одноцветных шаров в начальный момент может быть не более одной." << endl << endl
		<< "Входные данные : даны количество шариков в цепочке(не более 10^5) и цвета шариков" << endl
		<< "(от 0 до 9, каждому цвету соответствует свое целое число)." << endl
		<< "Выходные данные : требуется вывести количество шариков, которое будет уничтожено." << endl << endl;

	cout << "Примеры :" << endl << endl
		<< "(входные данные)" << endl
		<< "5 - количество шариков" << endl
		<< "1 3 3 3 2" << endl
		<< "(выходные данные)" << endl
		<< "3 - количество удаленных шариков" << endl << endl
		<< "(входные данные)" << endl
		<< "10 - количество шариков" << endl
		<< "3 3 2 1 1 1 2 2 3 3" << endl
		<< "(выходные данные)" << endl
		<< "10 - количество удаленных шариков" << endl;

	cout << endl << "ОЧЕНЬ ОЧЕНЬ ОЧЕНЬ ВАЖНОЕ ЗАМЕЧАНИЕ!!!!" << endl
		<< "Все числа нужно вводить БЕЗ пробела в конце!!!!!" << endl
		<< "чтобы программа успешно работала, вводите число, а потом нажимайте enter!!!!" << endl;
}

int main()
{

	setlocale(LC_ALL, "rus");

					// Для корректного использования рандомайзера.
	srand(time(0));

					// Переменная для повторной работы программы.
	bool ExitProgramm = true;

					// Очищаем текстовый файл для каждого запуска программы.
	ofstream File("ThirdChoice.txt", ios::trunc);
	File.close();

	PrintWelcomeMessage();

					// Создаем объект класса Balloons для работы с ним.
	Balloons ColourfulBalloons;

					// Пока пользователь не решит закончить игру продолжаем
	while (ExitProgramm)
	{

					
					// Количество шариков 
		int AmountOfBalloons = 0;

					// Зацикливаем ровно до тех пор, пока пользователь не введет корректное значение
		while (true)
		{
			
			cout << endl << "Введите число - количество  создаваемых элементов: ";

					// Используем строки, для того, чтобы посимвольно после
					// проверять корректность вводимого пользователем значения.

			string NumberOfBalloons;
			getline(cin,NumberOfBalloons);
			cout << endl;

					// Используем конструкции  try-catch для обработки исключений
			try
			{
					// Некорректный ввод - запрашиваем заново значение у пользователя.
				if (!ColourfulBalloons.isValidNumber(NumberOfBalloons))
				{
					throw invalid_argument("Неккоретный ввод количества шариков. Возможен пробел в конце.");
				}

					// Перевод строки в целое число.
				AmountOfBalloons = ColourfulBalloons.StringToInt(NumberOfBalloons);

					// Проверяем число на корректность.
				if (AmountOfBalloons > 100000)
				{
					throw out_of_range("Количество шариков не должно превосходить 100.000.");
				}
				if (AmountOfBalloons <= 0)
				{
					throw out_of_range("Количество шариков не должно быть меньше 0.");
				}
					// Выходим из цикла
				break;
			}
				    // Выводим ошибки - неверное значение или слишком большое число.
			catch (const invalid_argument& e)
			{
				cerr << "ОШИБКА: " << e.what() << endl;
				cin.clear();
				/*cin.ignore();*/
			}
			catch (const out_of_range& e)
			{
				cerr << "ОШИБКА: " << e.what() << endl;
				cin.clear();
			}
		}

		cout << endl << "Есть несколько способов добавления шариков: " << endl
			<< "1. Вручную через консоль " << endl
			<< "2. Генерация рандомных чисел " << endl
			<< "3. Текстовый файл с сгенирированными рандомными числами" << endl << endl;

					// Используем строки, для того, чтобы посимвольно после
					// проверять корректность вводимого пользователем значения.
		string UserInput;
		int UserChoice;

		while (true)
		{
					// Очищаем значения двусвязного списка для повторного использования.
			ColourfulBalloons.ClearList();

					// Зацикливание способа ввода до тех пор, пока не будет введено корректное значение.
			while (true)
			{
				try
				{
					cout << "Введите способ добавления шариков (1-3): ";
					getline(cin,UserInput);

					if (!ColourfulBalloons.isValidNumber(UserInput))
					{

						cerr << endl << "Ошибка!" << endl
							<< "Возможно вы добавили пробел в конце или написали неверное число." << endl
							<< endl << "Доступные варианты: 1, 2 или 3." << endl << endl;
						cin.clear();
						/*cin.ignore();*/
						continue;
					}

					UserChoice = ColourfulBalloons.StringToInt(UserInput);

						// Проверяем, что пользователь ввел правильный способ ввода шариков.
					if (UserChoice < 1 || UserChoice > 3)
					{
						cerr << endl << "Ошибка!" << endl
							 << "Возможно вы добавили пробел в конце или написали неверное число." << endl
							 << endl << "Доступные варианты: 1, 2 или 3." << endl << endl;
						continue;
					}

					break;
				}
				catch (const exception& e)
				{
					cerr << e.what() << endl << endl;
					cin.clear();
					/*cin.ignore();*/
				}

				break;
			}

					// Заполнение двусвязного списка шариками.
			ColourfulBalloons.FillBalloons(UserChoice, AmountOfBalloons, ColourfulBalloons);
					// Проверка количества цепочек одинаковых шариков
			int ChainAmount = ColourfulBalloons.HasMultipleChains();			
					// Если такая цепочка одна или её вообще нет - работа программы.
			if (ChainAmount <= 1)
			{
				cout << endl;
					// Вывод шариков на экран
				ColourfulBalloons.ShowBalloons();

					// Результат работы - количество удаленных шариков
				int RemovedCount = ColourfulBalloons.RemoveChains();
				cout << endl << "Количество удаленных шариков: " << RemovedCount << endl;

					// Запрашиваем у пользователя, хочет ли он продолжить игру или закончить её.
				ExitProgramm = ColourfulBalloons.AskToContinue(ColourfulBalloons);
				cout << endl;

				if (!ExitProgramm)
				{
						break;
				}
			}
			else
			{		
					// Выводим на экран шарики, показываем, что цепочек шариков было больше, чем нужно.
				ColourfulBalloons.ShowBalloons();
				cout << endl << "Ошибка: нужно, чтобы была хотя бы одна цепочка из 3+ одинаковых шаров подряд!" << endl;
				cout << "Повторите генерацию..." << endl;
			}
		}
	}

	cout << "Программа завершена." << endl;
	return 0;
}

