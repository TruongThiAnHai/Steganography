#include <iostream>
#include <bitset>
#include <sstream>
#include <string>
#include <fstream>
#include <windows.h>


using namespace std;


int main()
{
	fstream fi;
	fi.open("result.txt", ios::in);////открыли

	if (fi.good()) //если файл вообще нашли
	{
		string a;
		string rows[100];
		int k = 0;
		while (getline(fi, a))
		{
			rows[k] = a;
			k++;
		}
		string Text,HiddenText;
		for (int i = 0; i < k; ++i)
		{
			string a = rows[i];
			size_t blankPos = 0;
			int space[100];
			//считать количество пробелов и позиций в строке
			for (int j = 0; j < a.size(); ++j)
			{
				if (a[j] == ' ')
				{
					space[blankPos] = j;
					blankPos++;
				}
				
			}
			int b[100];
			//вектор b, значение каждого элемента которого зависит от 
			//результата вычисления разности между следующим и текущим
			//значениями элементов вектора space
			for (int j = 0; j < blankPos; ++j)
			{
				if (j == blankPos - 1) b[j] = -1;
				b[j] = space[j + 1] - space[j];
				if (b[j] != 1) b[j] = 0;
				
			}
			//подсчитать двоичного кода сообщения
			string massiv;
			int three = blankPos / 3;
			for (int i = 0; i < three; ++i)
			{
				if ((b[i * 3] == 1) && (b[i * 3 + 1] == 0) && (b[i * 3 + 2] == 0))
					massiv += '0';
				else if ((b[i * 3] == 0) && (b[i * 3 + 1] == 1) && (b[i * 3 + 2] == 0))
					massiv += '1';
				else
					break;
			}

			Text += massiv;

		}
		// Преобразование двоичного кода в символы
		stringstream sstream(Text);
		while (sstream.good())
		{
			bitset<8> bits;
			sstream >> bits;
			HiddenText += char(bits.to_ulong());
		}
		std::cout << "\n\n\n\n\n\n\n" << endl;
		std::cout<<"\t\t\t\t\t\t\t\t\t"<< endl;


		std::cout << "\t\t\t\t\t\t\t\t\t===============The hidden message: " << HiddenText << "================"<< endl;
		std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
	}
	else
	{
		std::cout << "file test.txt not found" << endl;
	}
	fi.close();
	system("pause");
	return 0;
}





