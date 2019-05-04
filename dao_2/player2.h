// player1.h: player 2 agent.
// Author:    Joseph Kotva
// Date:	  4/9/2018
// MS Visual C++
// Description: Agent uses the min/max algorithm with a cutoff depth of 6 ply. The utility function looks at
//				all possible winning configurations and assigns points for how close the agent is--and negative
//				points for how close the opponent is--to a winning position. Points are assigned such that 
//				a position 1 stone away from winning is worth more points that n positions that are 2 stones
//				away from winning.
#ifndef PLAYER2_H
#define PLAYER2_H 2

using namespace std;

class Player2 : public Player
{
public:

#pragma region min/max functions
	// functions to minimize/maximize the utility function "happiness"
	int max(int happiness[])
	{
		int choice = 0;
		for (int i = 0; i < numberOfPossibleMoves1; i++)
		{
			if (happiness[i + 1] != NULL)
			{
				if (happiness[choice] < happiness[i + 1])
					choice = i + 1;
			}
		}
		return choice;
	}

	int min(int happiness[])
	{
		int choice = 0;
		for (int i = 0; i < numberOfPossibleMoves1; i++)
		{
			if (happiness[i + 1] != NULL)
			{
				if (happiness[choice] > happiness[i + 1])
					choice = i + 1;
			}
		}
		return choice;
	}

#pragma endregion
	// calculates board positions given a starting board position and a list of possible moves
	void calculateFutureBoards(board game_board, board game_boards[], Move possibleMoves[], int numberOfPossibleMoves)
	{
		for (int i = 0; i < numberOfPossibleMoves; i++)
		{
			game_boards[i] = game_board;
			game_boards[i].layout[possibleMoves[i].src_y][possibleMoves[i].src_x] = EMPTY;
			game_boards[i].layout[possibleMoves[i].dst_y][possibleMoves[i].dst_x] = possibleMoves[i].player;
		}
	}

	// finds the available legal moves for a given player
	int findMoves(unsigned short p, board game_board, Move possibleMoves[], int numberOfPossibleMoves)
	{
		Move move;

		move.player = p;
		for (int src_x = 0; src_x < XYDIM; src_x++)
		{
			for (int src_y = 0; src_y < XYDIM; src_y++)
			{
				if (game_board.layout[src_y][src_x] == p)
				{
					move.src_x = src_x;
					move.src_y = src_y;
					for (int dst_x = 0; dst_x < XYDIM; dst_x++)
					{
						for (int dst_y = 0; dst_y < XYDIM; dst_y++)
						{
							move.dst_x = dst_x;
							move.dst_y = dst_y;
							if (isMoveValid(game_board, move))
							{
								possibleMoves[numberOfPossibleMoves] = move;
								numberOfPossibleMoves++;
							}
						}
					}
				}
			}
		}
		return numberOfPossibleMoves;
	}
#pragma region happiness

	// Calculates the "happiness" of a board position. Positions that are closer to a winning position are assigned a 
	// higher value.
	int calculateHappiness(board game_board)
	{
		int happiness = 0;
		if (PLAYER2_H == 1)
		{
			// look at horizontal positions
			for (int i = 0; i < XYDIM; i++)
			{
				int num_p1 = 0;
				int num_p2 = 0;
				if (game_board.layout[0][i] == PLAYER1)
					num_p1++;
				if (game_board.layout[1][i] == PLAYER1)
					num_p1++;
				if (game_board.layout[2][i] == PLAYER1)
					num_p1++;
				if (game_board.layout[3][i] == PLAYER1)
					num_p1++;
				if (game_board.layout[0][i] == PLAYER2)
					num_p2++;
				if (game_board.layout[1][i] == PLAYER2)
					num_p2++;
				if (game_board.layout[2][i] == PLAYER2)
					num_p2++;
				if (game_board.layout[3][i] == PLAYER2)
					num_p2++;

				if (num_p1 == 2 && num_p2 == 0)
					happiness += 1;
				else if (num_p2 == 2 && num_p1 == 0)
					happiness -= 1;
				else if (num_p1 == 3 && num_p2 == 0)
					happiness += 23;
				else if (num_p2 == 3 && num_p1 == 0)
					happiness -= 23;
				else if (num_p1 == 4)
					return 507;
				else if (num_p2 == 4)
					happiness -= 507;
			}

			// look at vertical positions
			for (int i = 0; i < XYDIM; i++)
			{
				int num_p1 = 0;
				int num_p2 = 0;
				if (game_board.layout[i][0] == PLAYER1)
					num_p1++;
				if (game_board.layout[i][1] == PLAYER1)
					num_p1++;
				if (game_board.layout[i][2] == PLAYER1)
					num_p1++;
				if (game_board.layout[i][3] == PLAYER1)
					num_p1++;
				if (game_board.layout[i][0] == PLAYER2)
					num_p2++;
				if (game_board.layout[i][1] == PLAYER2)
					num_p2++;
				if (game_board.layout[i][2] == PLAYER2)
					num_p2++;
				if (game_board.layout[i][3] == PLAYER2)
					num_p2++;

				if (num_p1 == 2 && num_p2 == 0)
					happiness += 1;
				else if (num_p2 == 2 && num_p1 == 0)
					happiness -= 1;
				else if (num_p1 == 3 && num_p2 == 0)
					happiness += 23;
				else if (num_p2 == 3 && num_p1 == 0)
					happiness -= 23;
				else if (num_p1 == 4)
					return 507;
				else if (num_p2 == 4)
					happiness -= 507;
			}

			// look at cluster positions
			for (int i = 0; i < XYDIM - 1; i++)
			{
				for (int j = 0; j < XYDIM - 1; j++)
				{
					int num_p1 = 0;
					int num_p2 = 0;

					if (game_board.layout[j][i] == PLAYER1)
						num_p1++;
					if (game_board.layout[j + 1][i] == PLAYER1)
						num_p1++;
					if (game_board.layout[j][i + 1] == PLAYER1)
						num_p1++;
					if (game_board.layout[j + 1][i + 1] == PLAYER1)
						num_p1++;
					if (game_board.layout[j][i] == PLAYER2)
						num_p2++;
					if (game_board.layout[j + 1][i] == PLAYER2)
						num_p2++;
					if (game_board.layout[j][i + 1] == PLAYER2)
						num_p2++;
					if (game_board.layout[j + 1][i + 1] == PLAYER2)
						num_p2++;

					if (num_p1 == 2 && num_p2 == 0)
						happiness += 1;
					else if (num_p2 == 2 && num_p1 == 0)
						happiness -= 1;
					else if (num_p1 == 3 && num_p2 == 0)
						happiness += 23;
					else if (num_p2 == 3 && num_p1 == 0)
						happiness -= 23;
					else if (num_p1 == 4)
						return 507;
					else if (num_p2 == 4)
						happiness -= 507;
				}
			}

			// look at corner positions
			int num_p1 = 0;
			int num_p2 = 0;
			for (int i = 0; i < XYDIM; i += 3)
			{
				for (int j = 0; j < XYDIM; j += 3)
				{
					if (game_board.layout[j][i] == PLAYER1)
						num_p1++;
					if (game_board.layout[j][i] == PLAYER2)
						num_p2++;
				}
			}

			if (num_p1 == 2 && num_p2 == 0)
				happiness += 1;
			else if (num_p2 == 2 && num_p1 == 0)
				happiness -= 1;
			else if (num_p1 == 3 && num_p2 == 0)
				happiness += 23;
			else if (num_p2 == 3 && num_p1 == 0)
				happiness -= 23;
			else if (num_p1 == 4)
				return 507;
			else if (num_p2 == 4)
				happiness -= 507;

			// look for backdoor victories
			if (game_board.layout[0][0] == PLAYER2 &&
				game_board.layout[1][0] == game_board.layout[0][1] == game_board.layout[1][1] == PLAYER1)
			{
				return -507;
			}
			if (game_board.layout[0][3] == PLAYER2 &&
				game_board.layout[1][3] == game_board.layout[0][2] == game_board.layout[1][2] == PLAYER1)
			{
				return -507;
			}
			if (game_board.layout[3][0] == PLAYER2 &&
				game_board.layout[2][0] == game_board.layout[3][1] == game_board.layout[2][1] == PLAYER1)
			{
				return -507;
			}
			if (game_board.layout[3][3] == PLAYER2 &&
				game_board.layout[2][3] == game_board.layout[3][2] == game_board.layout[2][2] == PLAYER1)
			{
				return -507;
			}
			if (game_board.layout[0][0] == PLAYER1 &&
				game_board.layout[1][0] == game_board.layout[0][1] == game_board.layout[1][1] == PLAYER2)
			{
				happiness += 507;
			}
			if (game_board.layout[0][3] == PLAYER1 &&
				game_board.layout[1][3] == game_board.layout[0][2] == game_board.layout[1][2] == PLAYER2)
			{
				happiness += 507;
			}
			if (game_board.layout[3][0] == PLAYER1 &&
				game_board.layout[2][0] == game_board.layout[3][1] == game_board.layout[2][1] == PLAYER2)
			{
				happiness += 507;
			}
			if (game_board.layout[3][3] == PLAYER1 &&
				game_board.layout[2][3] == game_board.layout[3][2] == game_board.layout[2][2] == PLAYER2)
			{
				happiness += 507;
			}
		}
		else
		{
			// look at horizontal positions
			for (int i = 0; i < XYDIM; i++)
			{
				int num_p1 = 0;
				int num_p2 = 0;
				if (game_board.layout[0][i] == PLAYER1)
					num_p1++;
				if (game_board.layout[1][i] == PLAYER1)
					num_p1++;
				if (game_board.layout[2][i] == PLAYER1)
					num_p1++;
				if (game_board.layout[3][i] == PLAYER1)
					num_p1++;
				if (game_board.layout[0][i] == PLAYER2)
					num_p2++;
				if (game_board.layout[1][i] == PLAYER2)
					num_p2++;
				if (game_board.layout[2][i] == PLAYER2)
					num_p2++;
				if (game_board.layout[3][i] == PLAYER2)
					num_p2++;

				if (num_p1 == 2 && num_p2 == 0)
					happiness -= 1;
				else if (num_p2 == 2 && num_p1 == 0)
					happiness += 1;
				else if (num_p1 == 3 && num_p2 == 0)
					happiness -= 23;
				else if (num_p2 == 3 && num_p1 == 0)
					happiness += 23;
				else if (num_p1 == 4)
					happiness -= 507;
				else if (num_p2 == 4)
					return 507;
			}

			// look at vertical positions
			for (int i = 0; i < XYDIM; i++)
			{
				int num_p1 = 0;
				int num_p2 = 0;
				if (game_board.layout[i][0] == PLAYER1)
					num_p1++;
				if (game_board.layout[i][1] == PLAYER1)
					num_p1++;
				if (game_board.layout[i][2] == PLAYER1)
					num_p1++;
				if (game_board.layout[i][3] == PLAYER1)
					num_p1++;
				if (game_board.layout[i][0] == PLAYER2)
					num_p2++;
				if (game_board.layout[i][1] == PLAYER2)
					num_p2++;
				if (game_board.layout[i][2] == PLAYER2)
					num_p2++;
				if (game_board.layout[i][3] == PLAYER2)
					num_p2++;

				if (num_p1 == 2 && num_p2 == 0)
					happiness -= 1;
				else if (num_p2 == 2 && num_p1 == 0)
					happiness += 1;
				else if (num_p1 == 3 && num_p2 == 0)
					happiness -= 23;
				else if (num_p2 == 3 && num_p1 == 0)
					happiness += 23;
				else if (num_p1 == 4)
					happiness -= 507;
				else if (num_p2 == 4)
					return 507;
			}

			// look at cluster positions
			for (int i = 0; i < XYDIM - 1; i++)
			{
				for (int j = 0; j < XYDIM - 1; j++)
				{
					int num_p1 = 0;
					int num_p2 = 0;

					if (game_board.layout[j][i] == PLAYER1)
						num_p1++;
					if (game_board.layout[j + 1][i] == PLAYER1)
						num_p1++;
					if (game_board.layout[j][i + 1] == PLAYER1)
						num_p1++;
					if (game_board.layout[j + 1][i + 1] == PLAYER1)
						num_p1++;
					if (game_board.layout[j][i] == PLAYER2)
						num_p2++;
					if (game_board.layout[j + 1][i] == PLAYER2)
						num_p2++;
					if (game_board.layout[j][i + 1] == PLAYER2)
						num_p2++;
					if (game_board.layout[j + 1][i + 1] == PLAYER2)
						num_p2++;

					if (num_p1 == 2 && num_p2 == 0)
						happiness -= 1;
					else if (num_p2 == 2 && num_p1 == 0)
						happiness += 1;
					else if (num_p1 == 3 && num_p2 == 0)
						happiness -= 23;
					else if (num_p2 == 3 && num_p1 == 0)
						happiness += 23;
					else if (num_p1 == 4)
						happiness -= 507;
					else if (num_p2 == 4)
						return 507;
				}
			}

			// look at corner positions
			int num_p1 = 0;
			int num_p2 = 0;
			for (int i = 0; i < XYDIM; i += 3)
			{
				for (int j = 0; j < XYDIM; j += 3)
				{
					if (game_board.layout[j][i] == PLAYER1)
						num_p1++;
					if (game_board.layout[j][i] == PLAYER2)
						num_p2++;
				}
			}

			if (num_p1 == 2 && num_p2 == 0)
				happiness -= 1;
			else if (num_p2 == 2 && num_p1 == 0)
				happiness += 1;
			else if (num_p1 == 3 && num_p2 == 0)
				happiness -= 23;
			else if (num_p2 == 3 && num_p1 == 0)
				happiness += 23;
			else if (num_p1 == 4)
				happiness -= 507;
			else if (num_p2 == 4)
				return 507;

			// look for backdoor victories
			if (game_board.layout[0][0] == PLAYER1 &&
				game_board.layout[1][0] == game_board.layout[0][1] == game_board.layout[1][1] == PLAYER2)
			{
				return -507;
			}
			if (game_board.layout[0][3] == PLAYER1 &&
				game_board.layout[1][3] == game_board.layout[0][2] == game_board.layout[1][2] == PLAYER2)
			{
				return -507;
			}
			if (game_board.layout[3][0] == PLAYER1 &&
				game_board.layout[2][0] == game_board.layout[3][1] == game_board.layout[2][1] == PLAYER2)
			{
				return -507;
			}
			if (game_board.layout[3][3] == PLAYER1 &&
				game_board.layout[2][3] == game_board.layout[3][2] == game_board.layout[2][2] == PLAYER2)
			{
				return -507;
			}
			if (game_board.layout[0][0] == PLAYER2 &&
				game_board.layout[1][0] == game_board.layout[0][1] == game_board.layout[1][1] == PLAYER1)
			{
				happiness += 507;
			}
			if (game_board.layout[0][3] == PLAYER2 &&
				game_board.layout[1][3] == game_board.layout[0][2] == game_board.layout[1][2] == PLAYER1)
			{
				happiness += 507;
			}
			if (game_board.layout[3][0] == PLAYER2 &&
				game_board.layout[2][0] == game_board.layout[3][1] == game_board.layout[2][1] == PLAYER1)
			{
				happiness += 507;
			}
			if (game_board.layout[3][3] == PLAYER2 &&
				game_board.layout[2][3] == game_board.layout[3][2] == game_board.layout[2][2] == PLAYER1)
			{
				happiness += 507;
			}
		}

		return happiness;
	}

#pragma endregion

	// Get the optimal move.
	Move get_move(unsigned short p, board game_board)
	{
		Move move;

		move.player = p;

		if (gettype()) { // this is only used if the player is human player.
			cout << "Enter move (old_x old_y new_x new_y): ";
			cin >> move.src_x;
			cin >> move.src_y;
			cin >> move.dst_x;
			cin >> move.dst_y;
		}
		else {
			unsigned short p2;
			if (p == 1)
				p2 = 2;
			else
				p2 = 1;

			numberOfPossibleMoves1 = 0;
			// find the possible moves the agent can make (1 ply)
			numberOfPossibleMoves1 = findMoves(p, game_board, possibleMoves1, numberOfPossibleMoves1);
			calculateFutureBoards(game_board, game_boards1, possibleMoves1, numberOfPossibleMoves1);

			for (int i = 0; i < numberOfPossibleMoves1; i++)
			{
				numberOfPossibleMoves2 = 0;

				// find the set of possible moves the opponent can make after any of the agent's given moves (2 ply)
				numberOfPossibleMoves2 = findMoves(p2, game_boards1[i], possibleMoves2, numberOfPossibleMoves2);
				calculateFutureBoards(game_boards1[i], game_boards2, possibleMoves2, numberOfPossibleMoves2);

				for (int i2 = 0; i2 < numberOfPossibleMoves2; i2++)
				{
					numberOfPossibleMoves3 = 0;

					// 3 ply
					numberOfPossibleMoves3 = findMoves(p, game_boards2[i2], possibleMoves3, numberOfPossibleMoves3);
					calculateFutureBoards(game_boards2[i2], game_boards3, possibleMoves3, numberOfPossibleMoves3);

					for (int i3 = 0; i3 < numberOfPossibleMoves3; i3++)
					{
						numberOfPossibleMoves4 = 0;

						// 4 ply
						numberOfPossibleMoves4 = findMoves(p2, game_boards3[i3], possibleMoves4, numberOfPossibleMoves4);
						calculateFutureBoards(game_boards3[i3], game_boards4, possibleMoves4, numberOfPossibleMoves4);

						for (int i4 = 0; i4 < numberOfPossibleMoves4; i4++)
						{
							numberOfPossibleMoves5 = 0;

							// 5 ply
							numberOfPossibleMoves5 = findMoves(p, game_boards4[i4], possibleMoves5, numberOfPossibleMoves5);
							calculateFutureBoards(game_boards4[i4], game_boards5, possibleMoves5, numberOfPossibleMoves5);

							for (int i5 = 0; i5 < numberOfPossibleMoves5; i5++)
							{
								numberOfPossibleMoves6 = 0;

								// 6 ply
								numberOfPossibleMoves6 = findMoves(p2, game_boards5[i5], possibleMoves6, numberOfPossibleMoves6);
								calculateFutureBoards(game_boards5[i5], game_boards6, possibleMoves6, numberOfPossibleMoves6);

								// feed the board position into the utility function ("happiness") and minimize it
								for (int j5 = 0; j5 < numberOfPossibleMoves6; j5++)
								{
									happiness6[j5] = calculateHappiness(game_boards6[j5]);
								}
								happiness5[i5] = min(happiness6);

								for (int z = 0; z < 32; z++)
								{
									happiness6[z] = NULL;
								}
							}
							
							// need to check if any of the board states 2 to 5 ply out lead to a winning/losing position, 
							// because if so the game will end before we reach the board states 6 ply out
							for (int z = 0; z < numberOfPossibleMoves5; z++)
							{
								int happiness = calculateHappiness(game_boards5[z]);
								if (happiness == 507)
									happiness5[z] = 510;
								if (happiness == -507)
									happiness5[z] = -510;
							}
							
							happiness4[i4] = max(happiness5);

							for (int z = 0; z < 32; z++)
							{
								happiness5[z] = NULL;
							}
						}
						
						for (int z = 0; z < numberOfPossibleMoves4; z++)
						{
							int happiness = calculateHappiness(game_boards4[z]);
							if (happiness == 507)
								happiness4[z] = 511;
							if (happiness == -507)
								happiness4[z] = -511;
						}

						happiness3[i3] = min(happiness4);

						for (int z = 0; z < 32; z++)
						{
							happiness4[z] = NULL;
						}
					}
					
					for (int z = 0; z < numberOfPossibleMoves3; z++)
					{
						int happiness = calculateHappiness(game_boards3[z]);
						if (happiness == 507)
							happiness3[z] = 512;
						if (happiness == -507)
							happiness3[z] = -512;
					}

					happiness2[i2] = max(happiness3);

					for (int z = 0; z < 32; z++)
					{
						happiness3[z] = NULL;
					}
				}
				
				for (int z = 0; z < numberOfPossibleMoves2; z++)
				{
					int happiness = calculateHappiness(game_boards2[z]);
					if (happiness == 507)
						happiness2[z] = 513;
					if (happiness == -507)
						happiness2[z] = -513;
				}

				happiness1[i] = min(happiness2);

				for (int z = 0; z < 32; z++)
				{
					happiness2[z] = NULL;
				}
			}

			// Check to see if any possible move lead to an immediate winning/losing position.
			for (int z = 0; z < numberOfPossibleMoves1; z++)
			{
				int happiness = calculateHappiness(game_boards1[z]);
				if (happiness == 507)	// if it leads to a winning position, take that move.
					happiness1[z] = 514;
				if (happiness == -507)	// if it leads to a losing position, we ensure to not take it.
					happiness1[z] = -514;
			}

			// take the move that maximizes the agent's happiness
			int choice = max(happiness1);

			move = possibleMoves1[choice];

			for (int z = 0; z < 32; z++)
			{
				happiness1[z] = NULL;
			}

			return move;
		}
}

#pragma region validcheck

	// Check if move is valid. (mostly just copied from file Dao.h file)
	bool isMoveValid(board game_board, Move move)
	{
		short x, y;
		bool allclear;
		// First, verify that a player isn't trying to move another's stone.
		if (move.player != game_board.layout[move.src_y][move.src_x])
			return false;

		// Second, verify that a player actually tries to move somewhere...
		if (move.dst_y == move.src_y && move.dst_x == move.src_x)  // Wow - really?
			return false;

		// Check for invalid 'North' move.
		if (move.dst_y < move.src_y && move.dst_x == move.src_x) {

			y = move.src_y - 1;
			allclear = true;

			while (allclear && y >= 0)
				if (game_board.layout[y][move.dst_x] != EMPTY)
					allclear = false;
				else
					y--;

			y++;	// Went past the valid move cell, so back it up.

			if (move.dst_y != y)
				return false;
		}

		// Check for invalid 'South' move.
		if (move.dst_y > move.src_y && move.dst_x == move.src_x) {

			y = move.src_y + 1;
			allclear = true;

			while (allclear && y < XYDIM)
				if (game_board.layout[y][move.dst_x] != EMPTY)
					allclear = false;
				else
					y++;

			y--;	// Went past the valid move cell, so back it up.

			if (move.dst_y != y)
				return false;
		}

		// Check for invalid 'East' move.
		if (move.dst_y == move.src_y && move.dst_x > move.src_x) {

			x = move.src_x + 1;
			allclear = true;

			while (allclear && x < XYDIM)
				if (game_board.layout[move.dst_y][x] != EMPTY)
					allclear = false;
				else
					x++;

			x--;	// Went past the valid move cell, so back it up.

			if (move.dst_x != x)
				return false;
		}

		// Check for invalid 'West' move.
		if (move.dst_y == move.src_y && move.dst_x < move.src_x) {

			x = move.src_x - 1;
			allclear = true;

			while (allclear && x >= 0)
				if (game_board.layout[move.dst_y][x] != EMPTY)
					allclear = false;
				else
					x--;

			x++;	// Went past the valid move cell, so back it up.

			if (move.dst_x != x)
				return false;
		}

		// Check for invalid 'Northeast' move.
		if (move.dst_y < move.src_y && move.dst_x > move.src_x) {

			x = move.src_x + 1;
			y = move.src_y - 1;
			allclear = true;

			while (allclear && y >= 0 && x < XYDIM)
				if (game_board.layout[y][x] != EMPTY)
					allclear = false;
				else {
					x++;
					y--;
				}

				x--;	// Went past the valid move cell, so back it up.
				y++;

				if (move.dst_x != x || move.dst_y != y)
					return false;
		}

		// Check for invalid 'Northwest' move.
		if (move.dst_y < move.src_y && move.dst_x < move.src_x) {

			x = move.src_x - 1;
			y = move.src_y - 1;
			allclear = true;

			while (allclear && y >= 0 && x >= 0)	// Fix due to Kirt Guthrie.
				if (game_board.layout[y][x] != EMPTY)
					allclear = false;
				else {
					x--;
					y--;
				}

				x++;	// Went past the valid move cell, so back it up.
				y++;

				if (move.dst_x != x || move.dst_y != y)
					return false;
		}

		// Check for invalid 'Southeast' move.
		if (move.dst_y > move.src_y && move.dst_x > move.src_x) {

			x = move.src_x + 1;
			y = move.src_y + 1;
			allclear = true;

			while (allclear && y < XYDIM && x < XYDIM)
				if (game_board.layout[y][x] != EMPTY)
					allclear = false;
				else {
					x++;
					y++;
				}

				x--;	// Went past the valid move cell, so back it up.
				y--;

				if (move.dst_x != x || move.dst_y != y)
					return false;
		}

		// Check for invalid 'Southwest' move.
		if (move.dst_y > move.src_y && move.dst_x < move.src_x) {

			x = move.src_x - 1;
			y = move.src_y + 1;
			allclear = true;

			while (allclear && y < XYDIM && x >= 0)
				if (game_board.layout[y][x] != EMPTY)
					allclear = false;
				else {
					x--;
					y++;
				}

				x++;	// Went past the valid move cell, so back it up.
				y--;

				if (move.dst_x != x || move.dst_y != y)
					return false;
		}

		return true;	// If passed all the test, the move is valid.
	}

#pragma endregion
private:
	// variables for cutoff depth of 1 
	Move possibleMoves1[32];
	board game_boards1[32];
	int happiness1[32];
	int numberOfPossibleMoves1;

	// variables for the cutoff depth of 2 (looking at the oponent's immediate moves after the agents' possible moves)
	Move possibleMoves2[32];
	board game_boards2[32];
	int happiness2[32];
	int numberOfPossibleMoves2;

	Move possibleMoves3[32];
	board game_boards3[32];
	int happiness3[32];
	int numberOfPossibleMoves3;

	Move possibleMoves4[32];
	board game_boards4[32];
	int happiness4[32];
	int numberOfPossibleMoves4;

	Move possibleMoves5[32];
	board game_boards5[32];
	int happiness5[32];
	int numberOfPossibleMoves5;

	Move possibleMoves6[32];
	board game_boards6[32];
	int happiness6[32];
	int numberOfPossibleMoves6;
};

#endif
