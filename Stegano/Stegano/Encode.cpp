#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <map>
#include <math.h>

using namespace std;


int main()
{
	fstream fi;
	fi.open("text.txt", ios::in);////открыли

	if (fi.good()) //если файл вообще нашли
	{
		//Посчитать количество символов каждой строки и найти строку -max длиннa
		string a;
		string rows[100];
		int k = 0;
		while (getline(fi, a))
		{
			rows[k] = a;
			k++;
		}
		size_t s[100];
		for (int i = 0; i < k; ++i)
		{
			s[i] = rows[i].size();
		}
		size_t max = 0;
		for (int i = 0; i < k; ++i)
		{
			if (s[i] > max) max = s[i];
		}
		//вставляемая строка
		string insertString;
		std::cout << "Enter the insertion string: ";
		cin >> insertString;
		string decTo2;
		//преобразование ascii кода вставляемой строки в двоичный вид
		for (size_t ind = 0; ind < insertString.size(); ++ind) {
			int ascii = (int)insertString[ind];
			string binary;
			do {
				binary = to_string(ascii % 2).c_str() + binary;
				ascii = (int)ascii / 2;
			} while (ascii > 0);
			if (binary.size() < 8) binary = '0' + binary;
			decTo2 += binary;
		}
		std::cout << decTo2 << endl;
		string resultText;
		int index = 0;
		ofstream out("result.txt");
		//Разработать каждую строку
		for (int i = 0; i < k; ++i)
		{
			//если строка имеет max символ -> записать в result
			if (s[i] == max)
			{
				resultText += rows[i] + "\n";
				continue;
			}
			size_t blankPos = 0;
			int vector[100];
			string a = rows[i];
			//считать количество пробелов и позиций в строке
			for (int j = 0; j < s[i]; ++j)
			{
				if (a[j] == ' ')
				{
					vector[blankPos] = j;
					blankPos++;
				}
			}
			size_t t = blankPos / 2;
			size_t space;
			// если (blankPos/2 >=  Lmax - Lr) для встраивания испол. Lmax - Lr пар пробелов
			if ((t >= (max - s[i])) && (index < decTo2.size()))
			{
				space = (max - s[i]);
				size_t x = 0;

				while (x <= space * 2)
				{
					if (decTo2[index] == '0')
					{
						if (x >= blankPos) break;
						a.insert(vector[x], 1, ' ');
						for (int j = x + 1; j < blankPos; ++j)
						{
							vector[j] += 1;
						}
						x += 2;

					}
					if (decTo2[index] == '1')
					{
						x += 1;
						if (x >= blankPos) break;
						a.insert(vector[x], 1, ' ');
						for (int j = x + 1; j < blankPos; ++j)
						{
							vector[j] += 1;
						}
						x += 1;
					}
					index += 1;
					if (index >= decTo2.size()) break;
				}

				resultText += a + "\n";
				continue;
			}
			// если (blankPos/2 <  Lmax - Lr) для встраивания испол. floor(blankPos/2)-1 пар пробелов
			if ((t < (max - s[i])) && (index < decTo2.size()))
			{
				space = floor(blankPos/2)-1;
				size_t x = 0;

				while (x <= space * 2)
				{
					
					if (decTo2[index] == '0')
					{
						if (x >= blankPos) break;
						a.insert(vector[x], 1, ' ');
						for (int j = x + 1; j < blankPos; ++j)
						{
							vector[j] += 1;
						}
						x += 2;

					}
					if (decTo2[index] == '1')
					{
						x += 1;
						if (x >= blankPos) break;
						a.insert(vector[x], 1, ' ');
						for (int j = x + 1; j < blankPos; ++j)
						{
							vector[j] += 1;
						}
						x += 1;
					}
					index += 1;
					if (index >= decTo2.size()) break;
				}
				//Добавить пробелов для выровненного по ширине текста
				size_t bonus = max - a.size();
				while (bonus !=0)
					{
					if (x >= blankPos) break;
						a.insert(vector[x], 1, ' ');
						for (int j = x + 1; j < blankPos; ++j)
						{
							vector[j] += 1;
						}
						x += 1;

						bonus -= 1;
					}
				resultText += a + "\n";
				continue;
			}
			// если все биты встаивили
			if (index == decTo2.size() )
			{
				size_t x = 0;
				size_t bonus = max - a.size();
				while (bonus != 0)
				{
					if (x >= blankPos) break;
					a.insert(vector[x], 1, ' ');
					for (int j = x + 1; j < blankPos; ++j)
					{
						vector[j] += 1;
					}
					x += 1;

					bonus -= 1;
				}
				resultText += a + "\n";
			}
		}
		std::cout << "Results saved to file: result.txt!\n";
		out << resultText;
		out.close();
	}
	else
	{
		std::cout << "file test.txt not found" << endl;
	}
	fi.close();
	system("pause");
	return 0;
}





