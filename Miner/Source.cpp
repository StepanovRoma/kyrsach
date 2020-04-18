#include <SFML/Graphics.hpp> //SFML
#include <cstdio>
#include <iostream>
#include <ctime>
using namespace sf; // пространство имен SFML
using namespace std;
int open[12][12]; // скрытое поле, которое хранит информацию о клетке, 12x12 из-за попытки реализовать другой функционал и маштабирования по центру
int pole[12][12]; // игровое поле изначально скрытое
void Zapolnenie()  // заполнение цифрами клеткок, рядом с которыми находятся мины
{
	for (int i = 1; i <= 10; i++) // игровое поле состоит из матриц 12x12 в которой используестя только 10х10, остальное не отрисовывается и не учавствует в игре
		for (int j = 1; j <= 10; j++)
		{
			int n = 0;    // обнуляем счетчик мин
			if (open[i][j] == 9) continue; // если хранится мина идем дальше
			if (open[i + 1][j] == 9) n++;   // если мина лежит в одной из 8 клеток в окружении [i][j] клетки
			if (open[i][j + 1] == 9) n++;
			if (open[i - 1][j] == 9) n++;
			if (open[i][j - 1] == 9) n++;
			if (open[i + 1][j + 1] == 9) n++;
			if (open[i - 1][j - 1] == 9) n++;
			if (open[i - 1][j + 1] == 9) n++;
			if (open[i + 1][j - 1] == 9) n++;
			open[i][j] = n; // записываем информацию о минах в клтку
		}
}
void MouseLeft(int x, int y)  // функция ЛКМ, которая вскрывает мины и пустые поля, передаются координаты нажатия
{
	if (pole[x][y] != 11)   // если поле не отмечено флажком
	{
		pole[x][y] = open[x][y]; // то полю присваем значение , которое там хранилосб
		if (pole[x][y] == 0) // если поле вскрыто и вокруг нет мин
		{
			if (x != 0 && y != 0 && x != 11 && y != 11)  // убираем не существующие границы матрци 12x12
			{// проверяем каждое соседние поле(их 8штук) на то , что оно не отмечено флажком, тк если бы флажки тоже вскрывались, информация о их количестве не обнавлялась
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
void MouseRight(int x, int y, int& p, int& z) // функция ПКМ, отмечает флажками и не дает количеству флажков превысить количество мин
{
	if (pole[x][y] != 11 && pole[x][y] > 9) // если поле не флажок и не открыто (тк открытими считаются поля от 0 до 8)
		if (p < z) // сравниваем кол-во мин и поставленных флажков, на первом этапе флажков 0
		{
			pole[x][y] = 11; // присваеваем значение флажка
			p++; // увеличиваем счетчик флажков
		}
		else; // закрываем элс , чтобы перейти к верхнему ифу
	else if (pole[x][y] == 11) // если поле уже флажок 
	{
		pole[x][y] = 10; // То возвращаем ей значение закрытой клетки 
		p--; // и уменьшаем счетчик флажков
	}
}
void Mines(int& z) // заполняем игровое поле минами и закрываем его
{
	for (int i = 1; i <= 10; i++) // опятьже учавсвует только чать 10х10, в остольной части что-то хранится , но это не важно
		for (int j = 1; j <= 10; j++)
		{
			pole[i][j] = 10; // присваиваем значение закрытой клетки
			if (rand() % 11 == 0) // рандомим кол-во мин ( на %10 уже очень сложно выиграть и нужно угадывать где мина)
			{
				open[i][j] = 9; // если рандом удался , то ставим мину в эту клетку
				z++; // счетчик количества мин
			}
			else open[i][j] = 0; // или делаем ее пустой
		}
}
bool CheckWin()  // тупа проверка на победу 
{
	for (int i = 1; i <= 10; i++) // идем по полю 10х10
	{
		for (int j = 1; j <= 10; j++)
		{
			if ((pole[i][j] == 10) || (pole[i][j] == 9) || (open[i][j] == 10)) return false; // если поле еще закрыто или вскрыта мина вы тоно не выиграли и она возвращает 0
		}
	}
	return true; // в случае победы возвращает 1
}
int main() // главаня функция
{
	int z = 0, p = 0; // счетчики мин и флажков
	Font font; // создание шрифта
	if (!font.loadFromFile("Fonts/DroidSansMono.ttf")) // проверка закрузился ли шрифт и сама его загрузка
		throw("COULD NOT LOAD FONT!");
	Text winnertext; // создание текста для победы
	Text losertext; // создание текста для поражения
	winnertext.setFont(font); // выбираем шрифт
	winnertext.setCharacterSize(30); // выбираем размер в пикселях(вроде)
	winnertext.setPosition(144, -5); // располагаю его в центре с верху
	winnertext.setFillColor(Color::Green); // красим в зеленый
	//winnertext.setStyle(Text::Bold);// можно сделать жирным , но не красиво :)
	winnertext.setString("WINNER"); // сам текст 
	losertext.setFont(font);// все тоже самое для лузера
	losertext.setCharacterSize(30);
	losertext.setPosition(144, -5);
	losertext.setFillColor(Color::Red);
	//losertext.setStyle(Text::Bold);
	losertext.setString("LOSER");
	srand(time(0));
	RenderWindow window(VideoMode(400, 400), "miner"); // само окно 400х400
	int w = 32; // размер одной клетки 32х32 пикселя
	Texture texture; // создание текстуры 
	texture.loadFromFile("images/2.jpg"); // её загрузка
	Sprite sprite(texture); // создание спрайта (нужного куска)
	Mines(z); // функция описанная выше
	Zapolnenie(); // функция описанная выше
	while (window.isOpen()) // главный цикл отвечающий за прорисовку окна и его элементов
	{
		Vector2i pos = Mouse::getPosition(window); // определение позиции курсора мыши
		int x = pos.x / w; // делим на 32 тк клетка 32 пикселя
		int y = pos.y / w;
		Event event; // создаем событие
		while (window.pollEvent(event)) // цикл для него // это самый обычный цикл для окна в SFML
		{
			if (event.type == Event::Closed) // закрываем окно , если оно закрыто :D
				window.close();
			if (event.type == Event::MouseButtonPressed) // проверям нажата ли кнопка мыши
			{
				if (event.key.code == Mouse::Left) // ЛКМ
				{
					MouseLeft(x, y); // функция описанная выше
				}
			}
			else if (event.key.code == Mouse::Right) // ПКМ
			{
				MouseRight(x, y, p, z); // функция описанная выше
			}
		}
		window.clear(Color::White); // Рисуем границы поля в белый цвет
		for (int i = 1; i <= 10; i++) // цикл вскрывающий поле , если вы вскрыли мину и выводящий loser
			for (int j = 1; j <= 10; j++)
			{
				if (pole[x][y] == 9)
				{
					pole[i][j] = open[i][j]; // вскрываем циклом все подряд
					window.draw(losertext); // текст loser
				}
				sprite.setTextureRect(IntRect(pole[i][j] * w, 0, w, w)); // берем прямоугольник размера 32х32
				sprite.setPosition(i * w, j * w); // выбираем позицию нужного прямоугольника , чтобы его отрисовать, для большей нагляжности и понятности зайдите в папку images и откройте картинку 2
				window.draw(sprite); // рисуем этот спрайт
			}
		if (event.key.code == Mouse::Middle) if (CheckWin()) // СКМ
		{
			window.draw(winnertext); // отприсовывает винер , если вы выиграли, но для этого нужно нажать СКМ
		}
		window.display(); // отображаем окно
	}
	return 0; // полезная строчка , еще бывает баг , когда открыта игра и с поля переводишь курсор на консоль и поле вскрывается , проконцультировавшись с экспертами в области SFML я пришел к выводу, что это особенность библиотеки
}