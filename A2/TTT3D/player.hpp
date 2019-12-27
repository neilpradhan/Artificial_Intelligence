#ifndef _TICTACTOE3D_PLAYER_HPP_
#define _TICTACTOE3D_PLAYER_HPP_

#include "constants.hpp"
#include "deadline.hpp"
#include "move.hpp"
#include "gamestate.hpp"
#include <vector>
#include <map>
#include <unordered_map>
#include<bits/stdc++.h>
#define DIM 4

namespace TICTACTOE3D
{

class Player
{
private:
    // hash map  of string corresponding to integers
	std::unordered_map<std::string, int> HASHTABLE;
public:
	Player() {
		HASHTABLE = std::unordered_map<std::string, int>();
        matrice = new int[DIM*DIM];
	}

    unsigned nbTurn;
    int* matrice;
    ///perform a move
    ///\param pState the current state of the board
    ///\param pDue time before which we must have returned
    ///\return the next state the board is in after our move
    static bool sortbysec(const std::pair<int,int> &a, const std::pair<int,int> &b);
    GameState play(const GameState &pState, const Deadline &pDue);
    int alphaBeta(const GameState &pState, const uint8_t & player, unsigned depth, int alpha, int beta, const Deadline &deadline);
    int gamma(const GameState &pState, const uint8_t & player);
	int CHECK_TABLE(const GameState & pState);


};

/*namespace TICTACTOE3D*/ }

#endif
