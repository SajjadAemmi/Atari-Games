//Sajjad Aemmi

#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<iomanip>
#include<fstream>
#include<time.h>

using namespace std;

#define body1 (char)2
#define body2 (char)4
#define aim (char)15

void gotoxy(int x, int y)
{
	COORD pos;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (INVALID_HANDLE_VALUE != hConsole)
	{
		pos.X = x;
		pos.Y = y;

		SetConsoleCursorPosition(hConsole, pos);
	}
}

///////////////////////////////////////
void color(int number)
{
	HANDLE color;
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, number);
}

///////////////////////////////////////
class snake
{
private:
	struct snake_post
	{
		int x;
		int y;
	};
	snake_post post[100];
	snake_post pre_post[100];
	snake_post aim_post;
	int lenght;

public:
	snake();
	void play();
	void print_wall();
	void print_aim();
	void print();
	void gameover();
};

///////////////////////////////////////
snake::snake()
{
	lenght = 5;

	for (int i = 0; i < lenght; i++)
	{
		post[i].x = i + 40;
		post[i].y = 12;
	}
}

///////////////////////////////////////
void snake::print_wall()
{
	for (int i = 0; i < 79; i++)
	{
		gotoxy(i, 0);
		cout << (char)219;
		gotoxy(i, 24);
		cout << (char)219;
	}
	for (int i = 24; i >= 0; i--)
	{
		gotoxy(0, i);
		cout << (char)219;
		gotoxy(79, i);
		cout << (char)219;
	}
}

///////////////////////////////////////
void snake::print_aim()
{
	srand(time(0));
	aim_post.x = rand() % 70 + 5;
	aim_post.y = rand() % 20 + 3;
	color(10);
	gotoxy(aim_post.x, aim_post.y);
	cout << aim;
	color(11);
}

///////////////////////////////////////
void snake::print()
{
	color(11);
	gotoxy(post[0].x, post[0].y);
	cout << body1;

	for (int i = 0; i < lenght; i++)
	{
		if (i % 2 == 0)
			color(13);
		else
			color(11);
		gotoxy(pre_post[i].x, pre_post[i].y);
		cout << body2;
	}
	gotoxy(pre_post[lenght - 1].x, pre_post[lenght - 1].y);
	cout << " ";
}

///////////////////////////////////////
void snake::play()
{
	char ch = 75, ch1 = 75;
	bool sw;

	print_wall();
	print_aim();

	while (1)
	{
		color(13);
		gotoxy(37, 24);
		cout << "Score: " << lenght - 5;

		if (post[0].x == aim_post.x && post[0].y == aim_post.y)
		{
			lenght++;
			print_aim();
		}

		for (int i = 0; i < lenght; i++)
		{
			pre_post[i].x = post[i].x;
			pre_post[i].y = post[i].y;
		}

		if (_kbhit())
		{
			ch1 = ch;
			_getch();
			ch = _getch();
			if ((ch == 77 && ch1 == 75) || (ch == 75 && ch1 == 77) || (ch == 72 && ch1 == 80) || (ch == 80 && ch1 == 72))
			{
				ch = ch1;
			}
		}
		if (ch == 77) //right
		{
			post[0].x++;
		}
		if (ch == 72) //up
		{
			post[0].y--;
		}
		if (ch == 75) //left
		{
			post[0].x--;
		}
		if (ch == 80) //down
		{
			post[0].y++;
		}
		if (post[0].x == 80 || post[0].x == 0 || post[0].y == 25 || post[0].y == 0)
		{
			gameover();
			return;
		}

		sw = true;
		for (int i = 1; i < lenght; i++)
		{
			if (post[0].x == post[i].x && post[0].y == post[i].y)
			{
				sw = false;
			}
		}
		if (sw == false)
		{
			gameover();
			return;
		}

		if (lenght == 32)
		{
			color(10);
			gotoxy(36, 12);
			cout << "You Win!";
			_getch();
			return;
		}

		for (int i = 0; i < lenght; i++)
		{
			post[i + 1].x = pre_post[i].x;
			post[i + 1].y = pre_post[i].y;
		}

		print();
		Sleep(100);
	}
}

///////////////////////////////////////
void snake::gameover()
{
	color(12);
	gotoxy(36, 12);
	cout << "Game Over!";
	_getch();
}

///////////////////////////////////////
void main()
{
	system("color 0b");
	snake mar;
	mar.play();
	_getch();
}
//Sajjad Aemmi