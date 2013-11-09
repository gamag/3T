/**
 * This file is part of 3T
 * Copyright (C) 2011-2013 Gabriel Margiani
 *
 * 3T is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * 3T is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with 3T.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include <iostream>
#include "3K_KI.h"

void test();

int main(int argc, char **argv)
{
	std::cout << "1. Vertical, 2. Horizontal" << std::endl;

	test();
	return 0;
}

void printField(KI_3K::KI_Player);
void test()
{
	std::cout << "Pleas select AI Level (0,1,2,3)\nenter 4 to see two AI playing together\n>>" << std::flush;
	int level;
	std::cin >> level;
	if(level == 4)
	{
		int kl1,kl2;
		std::cout << "pleas select the level of AI x (0,1,2,3)\n>>" << std::flush;
		std::cin >> kl1;
		std::cout << "pleas select the level of AI o (0,1,2)\n>>" << std::flush;
		std::cin >> kl2;
		KI_3K::KI_Player pl1(kl1), pl2(kl2, true);
		pl1.start();
		while((!pl1.has_won())&&pl2.next())
		{
			pl1.next();
			printField(pl1);
			char a = std::cin.get();
		}
		return;
	}

	KI_3K::KI_Player ki(level);
	if(level != 3)
	{
		std::cout << "Do you want to begin ? y/n\n>>" << std::flush;
		char beg;
		std::cin >> beg;
		if(beg == 'n' || beg == 'N')
		{
			ki.start();
		}
	}
	else
	{
		ki.start();
	}

	printField(ki);
	int x, y;
	std::cout << "Enter the line number followed by the col. number to set a filed\neg. 1 1 sets the middle\n>>" << std::flush;
	std::cin >> x >> y;
	while (ki.set(x, y))
	{
		printField(ki);
		std::cout << ">>" << std::flush;
		std::cin >> x >> y;
	}
	int v = ki.has_won();
	std::cout << "game finished "<<
	((v < 0) ? "o has won" : (v == 0) ? "" : "x has won") << std::endl; 
	printField(ki);
}

void printField(KI_3K::KI_Player ki)
{
	std::cout << "   0   1   2" << std::endl;
	std::cout << " \342\225\224" <<
	          "\342\225\220" << "\342\225\220" << "\342\225\220" << "\342\225\244" <<
	          "\342\225\220" << "\342\225\220" << "\342\225\220" << "\342\225\244" <<
	          "\342\225\220" << "\342\225\220" << "\342\225\220" << "\342\225\227" << std::endl;
	for (int i = 0; i < 3; i++)
	{
		if (i > 0)
		{
			std::cout << " \342\225\237" <<
			          "\342\224\200" << "\342\224\200" << "\342\224\200" << "\342\224\274" <<
			          "\342\224\200" << "\342\224\200" << "\342\224\200" << "\342\224\274" <<
			          "\342\224\200" << "\342\224\200" << "\342\224\200" << "\342\225\242" << "\n";
		}
		std::cout << i << "\342\225\221";
		for (int x = 0; x < 3; x++)
		{
			int v = ki.getFieldAt(i, x);
			std::cout << " " <<
			          ((v < 0) ? "o" : (v == 0) ? " " : "x") <<
			          " " << ((x < 2) ? "\342\224\202" : "\342\225\221");
		}
		std::cout << std::endl;
	}
	std::cout << " \342\225\232" <<
	          "\342\225\220" << "\342\225\220" << "\342\225\220" << "\342\225\247" <<
	          "\342\225\220" << "\342\225\220" << "\342\225\220" << "\342\225\247" <<
	          "\342\225\220" << "\342\225\220" << "\342\225\220" << "\342\225\235" << std::endl;
}
