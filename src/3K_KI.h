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

#ifndef _3K_KI_H_
#define _3K_KI_H_

namespace KI_3K
{
	class KI_Player
	{
		private:

			// the 'playground'
			// fields with value
			//		0	= free fields
			//		1	= set by KI
			//		-1	= set by user
			static char field[3][3];

			// if the user should play 1 and the AI -1
			// this doesn't have to be changed (is done by the constructor)
			int user;
			int ki;

			// true if the KI started the Game
			bool kiStarted;

			// Test if two of the same player and one free field
			// are in one of the rows and sets in the free field
			// if needed.
			bool test1();

			// The position in the Algorithm
			int alg_pos;

			// The AI level
			int level;

			// The last field set by the user
			int last_set[2];


			/// The KI/AI functions
			// all functions return true if they have set on a field.

			// level 0 plays using random
			bool ki_0();

			// level 1 plays using one algorithm
			bool ki_1();

			// level 2 - Standard - plays using randomly two algorithms
			bool usingAlg1;
			bool ki_2();

			// level 3 like above, but doesn't allow the user to
			// start the Game
			bool ki_3();

			/// Algorithms

			// to use if AI starts
			bool alg_s1();
			bool alg_s2();

			// to use if the user starts
			bool alg_su();

			// sets a field relative to alg_bas
			bool alg_set(int x, int y);
			int alg_bas;

			// returns a field relative to alg_bas
			char alg_get(int x, int y);

		public:
			// level = difficulty (1,2,3)
			// changeId = false, set if the AI should play -1
			KI_Player(int level = 2, bool changeId = false);
			~KI_Player();

			// starts the game with the KI
			// return false on error
			bool start();

			// Sets the field at posX,posY as of the user
			// and lets the KI play (if not noKI).
			// return false on error
			// moKI = false
			bool set(int posX, int posY, bool noKI = false);

			// makes the KI set one field
			// called by set if not noKI
			// returns true if the AI has set one field else if not false
			bool next();

			// Tests if a player has won the Game
			// returns the player number (1 or -1) or 0
			int has_won();

			// returns the number in field[x][y]
			char getFieldAt(int x, int y);
	};
}
#endif
