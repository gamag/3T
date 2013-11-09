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

#include "3K_KI.h"

#include <ctime>
#include <iostream>

namespace KI_3K
{

	/// PRIVATE

	// the 'playground'
	// fields with value
	//		0	= free fields
	//		1	= set by KI
	//		-1	= set by user
	char KI_Player::field[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

	// Test if two of the same player and one free field
	// are in one of the rows and sets in the free field
	// if needed.
	bool KI_Player::test1()
	{
		int setp[3];
		setp[2] = 0;
		// lines
		for (int i = 0; i < 3; i++)
		{
			if ((field[i][0] == field[i][1]) && (field[i][2] == 0) && (field[i][0] != 0))
			{
				if (setp[2] != ki)
				{
					setp[0] = i; setp[1] = 2; setp[2] = field[i][0];
				}
			}
			else if ((field[i][0] == field[i][2]) && (field[i][1] == 0) && (field[i][0] != 0))
			{
				if (setp[2] != ki)
				{
					setp[0] = i; setp[1] = 1; setp[2] = field[i][0];
				}
			}
			else if ((field[i][1] == field[i][2]) && (field[i][0] == 0) && (field[i][1] != 0))
			{
				if (setp[2] != ki)
				{
					setp[0] = i; setp[1] = 0; setp[2] = field[i][1];
				}
			}
		}

		// rows
		for (int i = 0; i < 3; i++)
		{
			if ((field[0][i] == field[1][i]) && (field[2][i] == 0) && (field[0][i] != 0))
			{
				if (setp[2] != ki)
				{
					setp[0] = 2; setp[1] = i; setp[2] = field[0][i];
				}
			}
			else if ((field[0][i] == field[2][i]) && (field[1][i] == 0) && (field[0][i] != 0))
			{
				if (setp[2] != ki)
				{
					setp[0] = 1; setp[1] = i; setp[2] = field[0][i];
				}
			}
			else if ((field[1][i] == field[2][i]) && (field[0][i] == 0) && (field[1][i] != 0))
			{
				if (setp[2] != ki)
				{
					setp[0] = 0; setp[1] = i; setp[2] = field[1][i];
				}
			}
		}

		// diagonals

		// upper left to lower right
		{
			if ((field[0][0] == field[1][1]) && (field[2][2] == 0) && (field[0][0] != 0))
			{
				if (setp[2] != ki)
				{
					setp[0] = 2; setp[1] = 2; setp[2] = field[0][0];
				}
			}
			else if ((field[0][0] == field[2][2]) && (field[1][1] == 0) && (field[0][0] != 0))
			{
				if (setp[2] != ki)
				{
					setp[0] = 1; setp[1] = 1; setp[2] = field[0][0];
				}
			}
			else if ((field[1][1] == field[2][2]) && (field[0][0] == 0) && (field[1][1] != 0))
			{
				if (setp[2] != ki)
				{
					setp[0] = 0; setp[1] = 0; setp[2] = field[1][1];
				}
			}
		}

		// upper right to lower left
		{
			if ((field[0][2] == field[1][1]) && (field[2][0] == 0) && (field[0][2] != 0))
			{
				if (setp[2] != ki)
				{
					setp[0] = 2; setp[1] = 0; setp[2] = field[0][2];
				}
			}
			else if ((field[0][2] == field[2][0]) && (field[1][1] == 0) && (field[0][2] != 0))
			{
				if (setp[2] != ki)
				{
					setp[0] = 1; setp[1] = 1; setp[2] = field[0][2];
				}
			}
			else if ((field[1][1] == field[2][0]) && (field[0][2] == 0) && (field[1][1] != 0))
			{
				if (setp[2] != ki)
				{
					setp[0] = 0; setp[1] = 2; setp[2] = field[1][1];
				}
			}
		}
		if (setp[2])
		{
			field[setp[0]][setp[1]] = ki;
			return true;
		}

		return false;
	}


	/// The KI/AI functions
	// all functions return true if they have set on a field.

	// level 0 plays using random
	bool KI_Player::ki_0()
	{
		std::time_t x;
		std::time(&x);
		if (!field[(x % 3)][((x % 19) % 3)])
		{
			field[(x % 3)][((x % 19) % 3)] = ki;
			return true;
		}

		for (int i = (x % 3); i < 6; i++)
		{
			for (int y = ((x % 19) % 3); y < 6; y++)
			{
				if (!field[i % 3][y % 3])
				{
					field[i % 3][y % 3] = ki;
					return true;
				}
			}
		}
		return false;
	}

	// level 1 plays using one algorithm
	bool KI_Player::ki_1()
	{
		if (kiStarted)
		{
			return alg_s1();
		}

		return alg_su();
	}

	// level 2 - Standard - plays using randomly two algorithms
	bool KI_Player::ki_2()
	{
		if (kiStarted)
		{
			return (usingAlg1) ? alg_s1() : alg_s2();
		}

		return alg_su();
	}

	// level 3 like above, but doesn't allow the user to
	// start the Game
	bool KI_Player::ki_3()
	{
		if (kiStarted)
		{
			return (usingAlg1) ? alg_s1() : alg_s2();
		}
		return false;
	}


	/// Algorithms

	// to use if ki starts
	bool KI_Player::alg_s1()
	{
		switch (alg_pos)
		{
			case 0:
				return alg_set(0, 0);
			case 1:
				if (alg_get(1, 1))
				{
					return alg_set(2, 2);
				}
				if (alg_get(0, 1) || alg_get(0, 2))
				{
					return alg_set(2, 0);
				}
				return alg_set(0, 2);
			case 2:
				if (alg_get(2, 0) || (alg_get(0, 1) == alg_get(1, 0)))
				{
					return alg_set(2, 2);
				}
				return alg_set(2, 0);
			default:
				return false;
		}
	}

	bool KI_Player::alg_s2()
	{
		switch (alg_pos)
		{
			case 0:
				return alg_set(1, 1);
			case 1:
				if ((last_set[0] != 1) && (last_set[1] != 1))
				{
					field[(last_set[0]) ? 0 : 2][(last_set[1]) ? 0 : 2] = ki;
					return true;
				}
				if ((!alg_get(1, 0)) && (!alg_get(1, 2)))
				{
					return alg_set(1, 0);
				}
				return alg_set(2, 1);
			case 2:
				if ((alg_get(2, 1) == ki) || (alg_get(1, 0) == ki))
				{
					return alg_set(2, 0);
				}
				if (!alg_set(0, 0))
				{
					if (!alg_set(2, 0))
					{
						if (!alg_set(2, 2))
						{
							return alg_set(0, 2);
						}
					}
				}
				return true;
			default:
				return ki_0();
		}
	}

	// to use if the user starts
	bool KI_Player::alg_su()
	{
		switch (alg_pos)
		{
			case 0:
				if (alg_get(1, 1))
				{
					return alg_set(0, 2);
				}
				return alg_set(1, 1);
			case 1:
				if ((alg_get(1, 1) == user) && (alg_get(0, 2) == ki))
				{
					if (alg_get(0, 0))
					{
						return alg_set(2, 2);
					}
					return alg_set(0, 0);
				}
				if (alg_get(0, 0) || alg_get(2, 2))
				{
					if (!alg_get(0, 0))
					{
						return alg_set(0, 0);
					}
					if (!alg_get(2, 2))
					{
						return alg_set(2, 2);
					}
					return alg_set(2, 1);
				}
				if (alg_get(0, 2) || alg_get(2, 0))
				{
					if (!alg_get(0, 2))
					{
						return alg_set(0, 2);
					}
					if (!alg_get(2, 0))
					{
						return alg_set(2, 0);
					}
					return alg_set(2, 1);
				}
				if (alg_get(0, 1) && alg_get(2, 1))
				{
					return alg_set(1, 0);
				}
				if (alg_get(1, 0) && alg_get(1, 2))
				{
					return alg_set(2, 1);
				}
			case 2:
				if (((alg_get(1, 0) == ki) && (alg_get(0, 1) == user) && alg_get(2, 1)) ||
				    ((alg_get(2, 1) == ki) && (alg_get(1, 0) == user) && alg_get(1, 2)))
				{
					return alg_set(2, 0);
				}
			default:
				return ki_0();
		}
	}

	bool KI_Player::alg_set(int x, int y)
	{
		int nx, ny;
		switch (alg_bas)
		{
			case 1:
				nx = (y == 1) ? 1 : (y == 2) ? 0 : 2;
				ny = x;
				break;
			case 2:
				nx = (x == 1) ? 1 : (x == 2) ? 0 : 2;
				ny = (y == 1) ? 1 : (y == 2) ? 0 : 2;
				break;
			case 3:
				nx = (y == 1) ? 1 : (y == 2) ? 0 : 2;
				ny = (x == 1) ? 1 : (x == 2) ? 0 : 2;
				break;
			default:
				nx = x;
				ny = y;
		}
		if (field[nx][ny] == 0)
		{
			field[nx][ny] = ki;
			return true;
		}
		return false;
	}


	char KI_Player::alg_get(int x, int y)
	{
		int nx, ny;
		switch (alg_bas)
		{
			case 1:
				nx = (y == 1) ? 1 : (y == 2) ? 0 : 2;
				ny = x;
				break;
			case 2:
				nx = (x == 1) ? 1 : (x == 2) ? 0 : 2;
				ny = (y == 1) ? 1 : (y == 2) ? 0 : 2;
				break;
			case 3:
				nx = (y == 1) ? 1 : (y == 2) ? 0 : 2;
				ny = (x == 1) ? 1 : (x == 2) ? 0 : 2;
				break;
			default:
				nx = x;
				ny = y;
		}
		return field[nx][ny];
	}

	/// PUBLIC

	// level = difficulty (1,2,3)
	KI_Player::KI_Player(int level, bool changeId):
			kiStarted(false), alg_pos(0), level(level)
	{
		std::time_t ab; std::time(&ab);
		alg_bas = (ab % 4);
		if (changeId)
		{
			ki = -1;
			user = 1;
		}
		else
		{
			ki = 1;
			user = -1;
		}
	}

	KI_Player::~KI_Player()
	{
	}

	// starts the game with the KI
	// return false on error
	bool KI_Player::start()
	{
		std::time_t ag; std::time(&ag);
		alg_bas = (ag % 4);
		for (int i = 0; i < 3; i++)
		{
			for (int x = 0; x < 3; x++)
			{
				field[i][x] = 0;
			}
		}

		kiStarted = true;
		next();
	}


	// Sets the field at posX,posY as of the user
	// and lets the KI play (if not noKI).
	// return false on error (if posX,posY is already set)
	// moKI = false
	bool KI_Player::set(int posX, int posY, bool noKI)
	{
		if (!has_won())
		{
			if (!field[posX][posY])
			{
				field[posX][posY] = user;
				last_set[0] = posX;
				last_set[1] = posY;
				if (!noKI)
				{
					return next();
				}
			}
		}
		return false;
	}

	// makes the KI set one field
	// used by set
	bool KI_Player::next()
	{
		if (!alg_pos)
		{
			std::time_t a; std::time(&a);
			usingAlg1 = ((a % 173) % 5);
		}
		if (!test1())
		{
			bool ret;
			switch (level)
			{
				case 0:
					ret = ki_0();
					break;
				case 1:
					ret = ki_1();
					break;
				case 2:
					ret = ki_2();
					break;
				case 3:
					ret = ki_3();
					break;
				default:
					ret = ki_2();
			}
			if (!ret)
			{
				return false;
			}
		}
		alg_pos ++;
		return true;
	}

	// Tests if a player has won the Game
	// returns the player number (1 or -1) or 0
	int KI_Player::has_won()
	{
		// horizontal
		for (int i = 0; i < 3; i++)
		{
			if ((field[i][0] == field[i][1]) &&
			    (field[i][1] == field[i][2]) && (field[i][0] != 0))
			{
				return (int)field[i][0];
			}
		}

		// vertical
		for (int i = 0; i < 3; i++)
		{
			if ((field[0][i] == field[1][i])
			    && (field[1][i] == field[2][i]) && (field[0][i] != 0))
			{
				return (int)field[0][i];
			}
		}

		// Diagonal
		{
			if (((field[0][0] == field[1][1]) && (field[1][1] == field[2][2])) ||
			    ((field[0][2] == field[1][1]) && (field[1][1] == field[2][0])) &&
			    (field[1][1] != 0))
			{
				return (int)field[1][1];
			}
		}
		return (int)false;
	}

	// returns a read-only pointer to field
	char KI_Player::getFieldAt(int x, int y)
	{
		return field[x][y];
	}
}
