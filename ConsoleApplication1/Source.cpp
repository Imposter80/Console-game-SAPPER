
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>
using  namespace std;


template <typename T>void Start_Game(T **Display, T **Mines, const int size);    /* ���������� ������� �����*/
template <typename T>void Create_Mines(T **arr, const int size, int Mine);       /* ������� ����������� ���*/
template <typename T>void Print_Game(T **arr, const int size);                   /* ����� �������� ����*/
template <typename T>void Print_Mines(T **arr, const int size);                   /* ����� ������� ����*/
template <typename T>void Sum_Mines(T **Mines, T **Display, int size, char x, int y, int &Life);    /* ����� ��� � �������� �����*/
template <typename T>void Cell_Count(T **Display, int size, int &cell_count, int &Mine);    /*���������� ��������� �������� �������� � ���������� ���*/
void Point_Count(int &Points, int &Step);    /*������� �����*/





void main()
{

	setlocale(LC_ALL, "Russian");

	/*--------------- ���������� 1 ------------------*/

	int Mine = 10;               /*���������� ���*/
	int N = 5;                   /*������ ����*/
	int Life = 3;                /*���������� ������*/	
	int Points = 0;              /*���������� �����*/
	char x;                      /*���������� ��� ��� �*/
	int y;                       /*���������� ��� ��� y*/	
	int Step = 0;                /*���������� ��������� ��������� ����� */


	
	


	while (true)
	{
		system("cls");   /*�������� �������*/

		cout << "1) ������ ����.\n";
		cout << "2) �������� ������ ���� � ���������� ���.\n";		
		cout << "0) �����\n";
		cout << "������� ����� ����������.\n";
		char task;
		cin >> task;
		if (task == '0') break;
		switch (task)
		{

			
		case '1':
		{
			/*--------------- ���������� 2 ------------------*/

			int Run = N*N;                /*����� ���������� ����� */
			int cell_count = N*N - Mine;   /*���������� ��������� �������� ��������*/

			int **Display = new int *[N];  /*������ ��� ����������� ���� ����*/
			int **Mines = new int *[N];    /*������ ��� ���*/
	

			Start_Game(Display, Mines, N);   /*�������� � ���������� ������� ��������*/
			Create_Mines(Mines, N, Mine);    /* ���������� ������� ������*/


           
			
			/*----------------- ������� ���� ������ -------------------------------------------------------*/
			system("cls");   /*�������� �������*/

			while (Life > 0 && Run > 0 && cell_count > 0)
			{

				/*---------------- ����� ������� � ������ -----------------*/

			/*	Print_Mines(Mines, N);*/

				/*--------------------------------------------------------------*/

				cout << "   ------- Sapper -------\n";
				cout << "������ ���� - " << N << " x " << N << endl;
				cout << "���������� ��� - " << Mine << endl;
				cout << "����� - " << Life << endl;
				cout << "���� - " << Points << endl;
				cout << "�������� ����� - " << Run << endl;
				cout << "���������� ��������� �������� ����� - " << cell_count << endl;
				cout << "-----------------------" << endl;

				Print_Game(Display, N);




				cout << " * - " << "������� ����" << endl;
				cout << " % - " << "���������� ����" << endl << endl;
			
				do
				{
					cout << "������� ���������� �� A �� " << (char)(N + 64) << " : ";
					cin >> x;
				} while (x < 'A' || x >(char)(N + 64));
				x = x - 65;

				do
				{
					cout << "������� ���������� �� 1 �� " << N << " : ";
					cin >> y;
				} while (y < 1 || y > N);
				y -= 1;

				system("cls");   /*�������� �������*/

				if (Display[x][y] != 9)
				{
					cout << "*************************************************************" << endl;
					cout << "*  ������ ������������, ������ ���������� ��������� ������  *" << endl;
					cout << "*************************************************************" << endl;
					Run += 1;
					if (Display[x][y] == -1)
					{
						Life++;
					}
				}


				if (Display[x][y] == 9 && Mines[x][y] == 0)   /*������� ���������� �����*/
				{
					Point_Count(Points, Step);
					Step++;
				}

				Sum_Mines(Mines, Display, N, x, y, Life);
				Run--;


				Cell_Count(Display, N, cell_count, Mine);    /* ����� �������� ��������*/

				if (Display[x][y] == -1)
				{
					cout << "****************************" << endl;
					cout << "*  �� ����������� �� ����  *" << endl;
					cout << "****************************" << endl;
				}				
			}       /*------  ������� ���� ����� -----------*/


			if (Life == 0 || Run == 0)   /*���� ���������� ������ ��� ����� = 0 */
			{
				cout << "******************" << endl;
				cout << "*  �� ���������  *" << endl;
				cout << "******************" << endl;

				Print_Game(Display, N);
				Print_Mines(Mines, N);
				
			}
			if (cell_count == 0)        /*���� ���������� ��������� ������ = 0 */
			{
				cout << "******************" << endl;
				cout << "*  �����������  *" << endl;
				cout << "*  �� ��������  *" << endl;
				cout << "******************" << endl;
				cout << "������  - " << Points << " �����" << endl;
				Print_Game(Display, N);
				Print_Mines(Mines, N);
			}

			/*��� ����������� ���� ���������� ����������� �������� ��������*/

			Life = 3;                /*���������� ������*/
			Run = N*N;                /*����� ���������� ����� */
			Points = 0;              /*���������� �����*/


			for (int i = 0; i < N; i++)   /*�������� ��������*/
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
			cout << "������� ������ �������� ����:  ";
			cin >> N;
			cout << "������� ���������� ���:  ";
			cin >> Mine;


			
		/* 2 -----------------------------------------------------------------------------*/
			
			break;
		}	
	 system("pause");
	 break;
	 }
	}

}  /*MAIN*/


template <typename T>void Start_Game(T **Display, T **Mines, const int size)           /* ���������� ������� �����*/
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
			Display[i][j] = 9;     /*��������� 9 ��. ��� ����� ����� ���� �� 0 �� 8*/
			Mines[i][j] = 0;     /*��������� 0*/
		}
	}
}


template <typename T>void Create_Mines(T **arr, const int size, int Mine)            /* ������� ����������� ���*/
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


template <typename T>void Print_Game(T **arr, const int size)            /* ����� �������� ����*/
{
	cout << "   ";
	for (int i = 0; i < size; i++)    /*���������� ��������� � �������*/
	{
		cout << i + 1 << " ";
	}
	cout << "\n  ";
	for (int i = 0; i < size; i++)   /*����� ��� ��������� ��������� � �� �������� ����*/
	{
		cout << "--";
	}
	cout << "\n";

	for (int i = 0; i < size; i++)
	{
		cout << (char)(i + 65) << "| ";    /*���������� ��������� � �������*/
		for (int j = 0; j < size; j++)
		{
			if (arr[i][j] == 9)        /*���� � ���� ������ "9" ������� "*"*/
			{
				cout << "*" << " ";
			}
			if (arr[i][j] == -1)        /*���� ����������� �� ���� "-1" ������� "%*/
			{
				cout << "%" << " ";
			}
			if (arr[i][j] != -1 && arr[i][j] != 9) /*����� ������� ���������� ��� �������*/
			{
				cout << arr[i][j] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}
template <typename T>void Print_Mines(T **arr, const int size)                  /* ����� ������� ����*/
{
	cout << "  ������ ����" << endl;
	cout << "   ";
	for (int i = 0; i < size; i++)    /*���������� ��������� � �������*/
	{
		cout << i + 1 << " ";
	}
	cout << "\n  ";
	for (int i = 0; i < size; i++)   /*����� ��� ��������� ��������� � �� �������� ����*/
	{
		cout << "--";
	}
	cout << "\n";

	for (int i = 0; i < size; i++)
	{
		cout << (char)(i + 65) << "| ";    /*���������� ��������� � �������*/
		for (int j = 0; j < size; j++)
		{
			if (arr[i][j] == 0)        /*���� � ���� ������ "0" ������� "*"*/
			{
				cout << "*" << " ";
			}
			if (arr[i][j] == 1)        /*���� ���� "1" ������� "%*/
			{
				cout << "%" << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
	cout << "-----------------------" << endl;
}

template <typename T>void Sum_Mines(T **Mines, T **Display, int size, char x, int y, int &Life)               /* ����� ��� � �������� �����*/
{
	size -= 1;
	int count = 0;    /*������� �������� ���*/
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

template <typename T>void Cell_Count(T **Display, int size, int &cell_count, int &Mine)    /* ���������� ��������� �������� �������� � ���������� ���*/
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


void Point_Count(int &Points, int &Step)    /*������� ����� - ����� ���������� � �������� ��������� ��������*/
{
	Points += ((Step + 5) / 5) * 5;
}