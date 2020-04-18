#include <SFML/Graphics.hpp> //SFML
#include <cstdio>
#include <iostream>
#include <ctime>
using namespace sf; // ������������ ���� SFML
using namespace std;
int open[12][12]; // ������� ����, ������� ������ ���������� � ������, 12x12 ��-�� ������� ����������� ������ ���������� � �������������� �� ������
int pole[12][12]; // ������� ���� ���������� �������
void Zapolnenie()  // ���������� ������� �������, ����� � �������� ��������� ����
{
	for (int i = 1; i <= 10; i++) // ������� ���� ������� �� ������ 12x12 � ������� ������������ ������ 10�10, ��������� �� �������������� � �� ���������� � ����
		for (int j = 1; j <= 10; j++)
		{
			int n = 0;    // �������� ������� ���
			if (open[i][j] == 9) continue; // ���� �������� ���� ���� ������
			if (open[i + 1][j] == 9) n++;   // ���� ���� ����� � ����� �� 8 ������ � ��������� [i][j] ������
			if (open[i][j + 1] == 9) n++;
			if (open[i - 1][j] == 9) n++;
			if (open[i][j - 1] == 9) n++;
			if (open[i + 1][j + 1] == 9) n++;
			if (open[i - 1][j - 1] == 9) n++;
			if (open[i - 1][j + 1] == 9) n++;
			if (open[i + 1][j - 1] == 9) n++;
			open[i][j] = n; // ���������� ���������� � ����� � �����
		}
}
void MouseLeft(int x, int y)  // ������� ���, ������� ��������� ���� � ������ ����, ���������� ���������� �������
{
	if (pole[x][y] != 11)   // ���� ���� �� �������� �������
	{
		pole[x][y] = open[x][y]; // �� ���� �������� �������� , ������� ��� ���������
		if (pole[x][y] == 0) // ���� ���� ������� � ������ ��� ���
		{
			if (x != 0 && y != 0 && x != 11 && y != 11)  // ������� �� ������������ ������� ������ 12x12
			{// ��������� ������ �������� ����(�� 8����) �� �� , ��� ��� �� �������� �������, �� ���� �� ������ ���� �����������, ���������� � �� ���������� �� �����������
				if (pole[x - 1][y - 1] != 11) pole[x - 1][y - 1] = open[x - 1][y - 1];
				if (pole[x - 1][y] != 11) pole[x - 1][y] = open[x - 1][y];
				if (pole[x - 1][y + 1] != 11) pole[x - 1][y + 1] = open[x - 1][y + 1];
				if (pole[x][y - 1] != 11) pole[x][y - 1] = open[x][y - 1];
				if (pole[x][y + 1] != 11) pole[x][y + 1] = open[x][y + 1];
				if (pole[x + 1][y - 1] != 11) pole[x + 1][y - 1] = open[x + 1][y - 1];
				if (pole[x + 1][y] != 11) pole[x + 1][y] = open[x + 1][y];
				if (pole[x + 1][y + 1] != 11) pole[x + 1][y + 1] = open[x + 1][y + 1];
			}
		}
	}
}
void MouseRight(int x, int y, int& p, int& z) // ������� ���, �������� �������� � �� ���� ���������� ������� ��������� ���������� ���
{
	if (pole[x][y] != 11 && pole[x][y] > 9) // ���� ���� �� ������ � �� ������� (�� ��������� ��������� ���� �� 0 �� 8)
		if (p < z) // ���������� ���-�� ��� � ������������ �������, �� ������ ����� ������� 0
		{
			pole[x][y] = 11; // ����������� �������� ������
			p++; // ����������� ������� �������
		}
		else; // ��������� ��� , ����� ������� � �������� ���
	else if (pole[x][y] == 11) // ���� ���� ��� ������ 
	{
		pole[x][y] = 10; // �� ���������� �� �������� �������� ������ 
		p--; // � ��������� ������� �������
	}
}
void Mines(int& z) // ��������� ������� ���� ������ � ��������� ���
{
	for (int i = 1; i <= 10; i++) // ������� ��������� ������ ���� 10�10, � ��������� ����� ���-�� �������� , �� ��� �� �����
		for (int j = 1; j <= 10; j++)
		{
			pole[i][j] = 10; // ����������� �������� �������� ������
			if (rand() % 11 == 0) // �������� ���-�� ��� ( �� %10 ��� ����� ������ �������� � ����� ��������� ��� ����)
			{
				open[i][j] = 9; // ���� ������ ������ , �� ������ ���� � ��� ������
				z++; // ������� ���������� ���
			}
			else open[i][j] = 0; // ��� ������ �� ������
		}
}
bool CheckWin()  // ���� �������� �� ������ 
{
	for (int i = 1; i <= 10; i++) // ���� �� ���� 10�10
	{
		for (int j = 1; j <= 10; j++)
		{
			if ((pole[i][j] == 10) || (pole[i][j] == 9) || (open[i][j] == 10)) return false; // ���� ���� ��� ������� ��� ������� ���� �� ���� �� �������� � ��� ���������� 0
		}
	}
	return true; // � ������ ������ ���������� 1
}
int main() // ������� �������
{
	int z = 0, p = 0; // �������� ��� � �������
	Font font; // �������� ������
	if (!font.loadFromFile("Fonts/DroidSansMono.ttf")) // �������� ���������� �� ����� � ���� ��� ��������
		throw("COULD NOT LOAD FONT!");
	Text winnertext; // �������� ������ ��� ������
	Text losertext; // �������� ������ ��� ���������
	winnertext.setFont(font); // �������� �����
	winnertext.setCharacterSize(30); // �������� ������ � ��������(�����)
	winnertext.setPosition(144, -5); // ���������� ��� � ������ � �����
	winnertext.setFillColor(Color::Green); // ������ � �������
	//winnertext.setStyle(Text::Bold);// ����� ������� ������ , �� �� ������� :)
	winnertext.setString("WINNER"); // ��� ����� 
	losertext.setFont(font);// ��� ���� ����� ��� ������
	losertext.setCharacterSize(30);
	losertext.setPosition(144, -5);
	losertext.setFillColor(Color::Red);
	//losertext.setStyle(Text::Bold);
	losertext.setString("LOSER");
	srand(time(0));
	RenderWindow window(VideoMode(400, 400), "miner"); // ���� ���� 400�400
	int w = 32; // ������ ����� ������ 32�32 �������
	Texture texture; // �������� �������� 
	texture.loadFromFile("images/2.jpg"); // � ��������
	Sprite sprite(texture); // �������� ������� (������� �����)
	Mines(z); // ������� ��������� ����
	Zapolnenie(); // ������� ��������� ����
	while (window.isOpen()) // ������� ���� ���������� �� ���������� ���� � ��� ���������
	{
		Vector2i pos = Mouse::getPosition(window); // ����������� ������� ������� ����
		int x = pos.x / w; // ����� �� 32 �� ������ 32 �������
		int y = pos.y / w;
		Event event; // ������� �������
		while (window.pollEvent(event)) // ���� ��� ���� // ��� ����� ������� ���� ��� ���� � SFML
		{
			if (event.type == Event::Closed) // ��������� ���� , ���� ��� ������� :D
				window.close();
			if (event.type == Event::MouseButtonPressed) // �������� ������ �� ������ ����
			{
				if (event.key.code == Mouse::Left) // ���
				{
					MouseLeft(x, y); // ������� ��������� ����
				}
			}
			else if (event.key.code == Mouse::Right) // ���
			{
				MouseRight(x, y, p, z); // ������� ��������� ����
			}
		}
		window.clear(Color::White); // ������ ������� ���� � ����� ����
		for (int i = 1; i <= 10; i++) // ���� ����������� ���� , ���� �� ������� ���� � ��������� loser
			for (int j = 1; j <= 10; j++)
			{
				if (pole[x][y] == 9)
				{
					pole[i][j] = open[i][j]; // ��������� ������ ��� ������
					window.draw(losertext); // ����� loser
				}
				sprite.setTextureRect(IntRect(pole[i][j] * w, 0, w, w)); // ����� ������������� ������� 32�32
				sprite.setPosition(i * w, j * w); // �������� ������� ������� �������������� , ����� ��� ����������, ��� ������� ����������� � ���������� ������� � ����� images � �������� �������� 2
				window.draw(sprite); // ������ ���� ������
			}
		if (event.key.code == Mouse::Middle) if (CheckWin()) // ���
		{
			window.draw(winnertext); // ������������� ����� , ���� �� ��������, �� ��� ����� ����� ������ ���
		}
		window.display(); // ���������� ����
	}
	return 0; // �������� ������� , ��� ������ ��� , ����� ������� ���� � � ���� ���������� ������ �� ������� � ���� ����������� , ��������������������� � ���������� � ������� SFML � ������ � ������, ��� ��� ����������� ����������
}