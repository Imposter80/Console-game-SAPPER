
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>
using  namespace std;


template <typename T>void Start_Game(T **Display, T **Mines, const int size);    /* подготовка игровых полей*/
template <typename T>void Create_Mines(T **arr, const int size, int Mine);       /* Функция расстановки мин*/
template <typename T>void Print_Game(T **arr, const int size);                   /* вывод игрового поля*/
template <typename T>void Print_Mines(T **arr, const int size);                   /* вывод минного поля*/
template <typename T>void Sum_Mines(T **Mines, T **Display, int size, char x, int y, int &Life);    /* сумма мин в соседних полях*/
template <typename T>void Cell_Count(T **Display, int size, int &cell_count, int &Mine);    /*Количество свободных закрытых клеточек и взорванных мин*/
void Point_Count(int &Points, int &Step);    /*Подсчет очков*/





void main()
{

	setlocale(LC_ALL, "Russian");

	/*--------------- ПЕРЕМЕННЫЕ 1 ------------------*/

	int Mine = 10;               /*количество мин*/
	int N = 5;                   /*размер поля*/
	int Life = 3;                /*количество жизней*/	
	int Points = 0;              /*количество балов*/
	char x;                      /*переменная для оси Х*/
	int y;                       /*переменная для оси y*/	
	int Step = 0;                /*Количество сделанных првильных ходов */


	
	


	while (true)
	{
		system("cls");   /*отчистка консоли*/

		cout << "1) Начать игру.\n";
		cout << "2) Изменить размер поля и количество мин.\n";		
		cout << "0) Выход\n";
		cout << "Введите номер упражнения.\n";
		char task;
		cin >> task;
		if (task == '0') break;
		switch (task)
		{

			
		case '1':
		{
			/*--------------- ПЕРЕМЕННЫЕ 2 ------------------*/

			int Run = N*N;                /*Общее количество ходов */
			int cell_count = N*N - Mine;   /*Количество свободных закрытых клеточек*/

			int **Display = new int *[N];  /*массив для отображения хода игры*/
			int **Mines = new int *[N];    /*массив для мин*/
	

			Start_Game(Display, Mines, N);   /*создание и подготовка игровых массивов*/
			Create_Mines(Mines, N, Mine);    /* заполнение массива минами*/


           
			
			/*----------------- ИГРОВОЙ ЦИКЛ НАЧАЛО -------------------------------------------------------*/
			system("cls");   /*отчистка консоли*/

			while (Life > 0 && Run > 0 && cell_count > 0)
			{

				/*---------------- Вывод массива с минами -----------------*/

			/*	Print_Mines(Mines, N);*/

				/*--------------------------------------------------------------*/

				cout << "   ------- Sapper -------\n";
				cout << "Размер поля - " << N << " x " << N << endl;
				cout << "Количество мин - " << Mine << endl;
				cout << "Жизни - " << Life << endl;
				cout << "Очки - " << Points << endl;
				cout << "Осталось ходов - " << Run << endl;
				cout << "Количество свободных закрытых полей - " << cell_count << endl;
				cout << "-----------------------" << endl;

				Print_Game(Display, N);




				cout << " * - " << "скрытое поле" << endl;
				cout << " % - " << "взорванная мина" << endl << endl;
			
				do
				{
					cout << "Введите координаты от A до " << (char)(N + 64) << " : ";
					cin >> x;
				} while (x < 'A' || x >(char)(N + 64));
				x = x - 65;

				do
				{
					cout << "Введите координаты от 1 до " << N << " : ";
					cin >> y;
				} while (y < 1 || y > N);
				y -= 1;

				system("cls");   /*отчистка консоли*/

				if (Display[x][y] != 9)
				{
					cout << "*************************************************************" << endl;
					cout << "*  Будьте внимательние, данные координаты вносились раннее  *" << endl;
					cout << "*************************************************************" << endl;
					Run += 1;
					if (Display[x][y] == -1)
					{
						Life++;
					}
				}


				if (Display[x][y] == 9 && Mines[x][y] == 0)   /*подсчет привильных ходов*/
				{
					Point_Count(Points, Step);
					Step++;
				}

				Sum_Mines(Mines, Display, N, x, y, Life);
				Run--;


				Cell_Count(Display, N, cell_count, Mine);    /* сумма закрытых клеточек*/

				if (Display[x][y] == -1)
				{
					cout << "****************************" << endl;
					cout << "*  Вы подорвались на мине  *" << endl;
					cout << "****************************" << endl;
				}				
			}       /*------  ИГРОВОЙ ЦИКЛ КОНЕЦ -----------*/


			if (Life == 0 || Run == 0)   /*ЕСЛИ КОЛИЧЕСТВО ЖИЗНЕЙ ИЛИ ХОДОВ = 0 */
			{
				cout << "******************" << endl;
				cout << "*  Вы проиграли  *" << endl;
				cout << "******************" << endl;

				Print_Game(Display, N);
				Print_Mines(Mines, N);
				
			}
			if (cell_count == 0)        /*ЕСЛИ КОЛИЧЕСТВО СВОБОДНЫХ КЛЕТОК = 0 */
			{
				cout << "******************" << endl;
				cout << "*  Поздравляем  *" << endl;
				cout << "*  вы выиграли  *" << endl;
				cout << "******************" << endl;
				cout << "Набрав  - " << Points << " очков" << endl;
				Print_Game(Display, N);
				Print_Mines(Mines, N);
			}

			/*ДЛЯ ПРОДОЛЖЕНИЯ ИГРЫ ВОЗВРАЩАЕМ ПОКАЗАТЕЛЯМ ИСХОДНЫЕ ЗНАЧЕНИЯ*/

			Life = 3;                /*количество жизней*/
			Run = N*N;                /*Общее количество ходов */
			Points = 0;              /*количество балов*/


			for (int i = 0; i < N; i++)   /*удаление массивов*/
			{
				delete[] Display[i];
				delete[] Mines[i];
			}
			delete[] Display;
			delete[] Mines;
			Display = nullptr;
			Mines = nullptr;
			

		/* 1 -----------------------------------------------------------------------------*/
			system("pause");		
			break;
		}

	
		case '2':
		{
			cout << "Введите размер игрового поля:  ";
			cin >> N;
			cout << "Введите количество мин:  ";
			cin >> Mine;


			
		/* 2 -----------------------------------------------------------------------------*/
			
			break;
		}	
	 system("pause");
	 break;
	 }
	}

}  /*MAIN*/


template <typename T>void Start_Game(T **Display, T **Mines, const int size)           /* подготовка игровых полей*/
{
	for (int i = 0; i < size; i++)
	{
		Display[i] = new T[size]{};
		Mines[i] = new T[size]{};
	}
	for (int i = 0; i <size; i++)
	{
		for (int j = 0; j<size; j++)
		{
			Display[i][j] = 9;     /*заполняем 9 тк. мин рядом может быть от 0 до 8*/
			Mines[i][j] = 0;     /*заполняем 0*/
		}
	}
}


template <typename T>void Create_Mines(T **arr, const int size, int Mine)            /* Функция расстановки мин*/
{
	for (int i = 0; i < Mine;)
	{
		int	x = rand() % size;
		int	y = rand() % size;

		/*if (arr[x][y] == 0)*/
		if (!arr[x][y])
		{
			arr[x][y] = 1;
			i++;
		}
	}
}


template <typename T>void Print_Game(T **arr, const int size)            /* вывод игрового поля*/
{
	cout << "   ";
	for (int i = 0; i < size; i++)    /*заполнение координат У цифрами*/
	{
		cout << i + 1 << " ";
	}
	cout << "\n  ";
	for (int i = 0; i < size; i++)   /*линия для отделения координат У от игрового поля*/
	{
		cout << "--";
	}
	cout << "\n";

	for (int i = 0; i < size; i++)
	{
		cout << (char)(i + 65) << "| ";    /*заполнение координат Х буквами*/
		for (int j = 0; j < size; j++)
		{
			if (arr[i][j] == 9)        /*если в поле пустое "9" выводим "*"*/
			{
				cout << "*" << " ";
			}
			if (arr[i][j] == -1)        /*если подорвались на мине "-1" выводим "%*/
			{
				cout << "%" << " ";
			}
			if (arr[i][j] != -1 && arr[i][j] != 9) /*иначе выводим количаство мин соседей*/
			{
				cout << arr[i][j] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}
template <typename T>void Print_Mines(T **arr, const int size)                  /* вывод минного поля*/
{
	cout << "  МИННОЕ ПОЛЕ" << endl;
	cout << "   ";
	for (int i = 0; i < size; i++)    /*заполнение координат У цифрами*/
	{
		cout << i + 1 << " ";
	}
	cout << "\n  ";
	for (int i = 0; i < size; i++)   /*линия для отделения координат У от игрового поля*/
	{
		cout << "--";
	}
	cout << "\n";

	for (int i = 0; i < size; i++)
	{
		cout << (char)(i + 65) << "| ";    /*заполнение координат Х буквами*/
		for (int j = 0; j < size; j++)
		{
			if (arr[i][j] == 0)        /*если в поле пустое "0" выводим "*"*/
			{
				cout << "*" << " ";
			}
			if (arr[i][j] == 1)        /*если мина "1" выводим "%*/
			{
				cout << "%" << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
	cout << "-----------------------" << endl;
}

template <typename T>void Sum_Mines(T **Mines, T **Display, int size, char x, int y, int &Life)               /* сумма мин в соседних полях*/
{
	size -= 1;
	int count = 0;    /*счетчик соседних мин*/
	if (Mines[x][y] == 1)
	{
		count = -1;
		Life--;
	}
	else
	{
		if (x == 0)
		{
			if (Mines[x][y - 1] == 1 && y > 0) { count++; }
			if (Mines[x][y + 1] == 1 && y < size) { count++; }
			if (Mines[x + 1][y] == 1 && x< size) { count++; }
			if (Mines[x + 1][y - 1] == 1 && x < size && y > 0) { count++; }
			if (Mines[x + 1][y + 1] == 1 && x < size && y < size) { count++; }
		}
		if (x == size)
		{
			if (Mines[x][y - 1] == 1 && y > 0) { count++; }
			if (Mines[x][y + 1] == 1 && y < size) { count++; }
			if (Mines[x - 1][y] == 1 && x> 0) { count++; }
			if (Mines[x - 1][y - 1] == 1 && x > 0 && y > 0) { count++; }
			if (Mines[x - 1][y + 1] == 1 && x > 0 && y < size) { count++; }
		}
		if (x != size && x != 0)
		{
			if (Mines[x][y - 1] == 1 && y > 0) { count++; }
			if (Mines[x][y + 1] == 1 && y < size) { count++; }
			if (Mines[x - 1][y] == 1 && x > 0) { count++; }
			if (Mines[x + 1][y] == 1 && x < size) { count++; }
			if (Mines[x - 1][y - 1] == 1 && x > 0 && y > 0) { count++; }
			if (Mines[x - 1][y + 1] == 1 && x > 0 && y < size) { count++; }
			if (Mines[x + 1][y - 1] == 1 && x < size && y > 0) { count++; }
			if (Mines[x + 1][y + 1] == 1 && x < size && y < size) { count++; }
		}
	}
	Display[x][y] = count;
}

template <typename T>void Cell_Count(T **Display, int size, int &cell_count, int &Mine)    /* Количество свободных закрытых клеточек и взорванных мин*/
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j< size; j++)
		{
			if (Display[i][j] == 9 || Display[i][j] == -1)
			{
				count++;
			}
		}
	}
	cell_count = count - Mine;
}


void Point_Count(int &Points, int &Step)    /*Подсчет очков - можно объединить с функцией свободных клеточек*/
{
	Points += ((Step + 5) / 5) * 5;
}