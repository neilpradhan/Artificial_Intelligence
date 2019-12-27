#include "player.hpp"
#include <cstdlib>
#include <limits>
#include <iostream>
#include <stdint.h>
#include<algorithm>

#define ROWS 4
#define COLS 4

#define DEPTH 4

#define NEGINF std::numeric_limits<int>::min()
#define POSINF std::numeric_limits<int>::max()

namespace TICTACTOE
{



int Player::alphaBeta(const GameState &pState, uint8_t player, unsigned depth, int alpha, int beta) {



	//uint8_t nextPlayer = pState.getNextPlayer();

	std::vector<GameState> NextStates;
    pState.findPossibleMoves(NextStates);

    if (NextStates.size() == 0 || depth == 0){ return gamma(pState, player);}



    if( player == CELL_O ) {
    	int motha = NEGINF;
	    for(unsigned i = 0; i < NextStates.size(); ++i) {
	    	motha = std::max(motha,alphaBeta(NextStates[i], CELL_X, depth-1, alpha, beta));
			alpha = std::max(alpha,motha);
	    	if(beta <= alpha)break;
	    }
	    return motha;
    }
    else {
    	int lahan = POSINF;
	    for(unsigned i = 0; i < NextStates.size(); ++i) {
	    	lahan = std::min(lahan,alphaBeta(NextStates[i], CELL_O, depth-1, alpha, beta));
			beta = std::min(beta,lahan);
	    	if(beta <= alpha)break;
	    }
	    return lahan;
    }
}





// code _  version before 

// int Player::alphaBeta(const GameState & pState, uint8_t Player,unsigned Depth , int alpha, int beta)
// {




//     std::vector<GameState> possible_next_states;

//     pState.findPossibleMoves(possible_next_states);

//     if ((Depth ==0) || (possible_next_states.size()==0)) {
//         // terminal state
//         int v = computeHeuristic(pState,Player);
//         return v;
//     }

//     // get next player

//     // if Player =0
//     // next player will be 1
//     //uint8_t nextPlayer = pState.getNextPlayer();
//     // we got next player 


//     if (Player == CELL_X){
//         int v = MINIMUM; // -infinity
//         // iterate over every element in the vector

//         //for each chi ld in ¹(A, state)
//         std::vector<GameState>::iterator itr; 
//         for (auto itr = possible_next_states.begin(); itr < possible_next_states.end() ;itr++)
//         {

//             int v = std::max(v,alphaBeta(*itr,CELL_O,Depth-1,alpha,beta));
//             alpha  = std::max(alpha,v);
//             if (beta<= alpha){
//                 break;
//             }

//         }
//         return v;
    
//     }



//     else
//     {

//         int v = MAXIMUM; // +infinity
//         // iterate over every element in the vector

//         //for each chi ld in ¹(A, state)
//         std::vector<GameState>::iterator itr; 
//         for (auto itr = possible_next_states.begin(); itr < possible_next_states.end() ;itr++)
//         {

//             int v = std::min(v,alphaBeta(*itr,CELL_X,Depth-1,alpha,beta));
//             beta = std::min(beta, v);

//              if (beta<= alpha){
//                 break;
//             }           


//         }
//         return v;


//     }






// }


int Player::gamma(const GameState &pState, uint8_t player) {


	// the more we come closer to winning the more will be the total
	int s = 0;
	int i, j;
	// the award for wins
	int value = 0;

    if (pState.isDraw()){
	    return 0;
	}

	if(pState.isXWin())  {
        return 1000;
	}
	
	if (pState.isOWin()){
	    return -1000;
	}
	
	


	// for every row see if position is valid 
	for(unsigned i = 0; i < COLS; ++i) {
		int s = 0;
		for(unsigned j = 0; j < ROWS; ++j) {
			if(pState.at(i,j) != player && (pState.at(i,j) == CELL_X || pState.at(i,j) == CELL_O)) {
				s = 0;
				break;
			}
			if(pState.at(i,j) == player) {
				s++;
			}
		}
		value +=   s;
	}

	// for every column give points to more players
	for(unsigned i = 0; i < ROWS; ++i) {
		int s = 0;
		for(unsigned j = 0; j < COLS; ++j) {
			if(pState.at(j,i) != player && (pState.at(j,i) == CELL_X || pState.at(j,i) == CELL_O)) {
				s = 0;
				break;
			}
			if(pState.at(j,i) == player) {
				s++;
			}
		}
		value += s;
	}

	// for diagonals give points
	for(i = 0, j = 0; i < COLS && j < ROWS; ++i, ++j) {
		if(pState.at(i,j) != player && (pState.at(i,j) == CELL_X || pState.at(i,j) == CELL_O)) {
			s = 0;
			break;
		}
		if(pState.at(i,j) == player) {
			s++;
		}
	}
	value += s;

	s = 0;
	for(i = COLS-1, j = ROWS-1; i >= 0 && j >= 0; --i, --j) {
		if(pState.at(i,j) != player && (pState.at(i,j) == CELL_X || pState.at(i,j) == CELL_O)) {
			s = 0;
			break;
		}
		if(pState.at(i,j) == player) {
			s++;
		}
	}
	value += s;

	return value;
}

GameState Player::play(const GameState &pState,const Deadline &pDue)
{


    std::vector<GameState> NextStates;
    pState.findPossibleMoves(NextStates);


	if (NextStates.size() == 0) {
		std::cerr << "next_state_empty" << std::endl;
		return GameState(pState, Move());
	}

    int alpha  = NEGINF;
    int beta = POSINF;
    int max = NEGINF;
    GameState bestGameState;
    for(unsigned i = 0; i < NextStates.size(); ++i) {
    	int tmp = alphaBeta(NextStates[i], pState.getNextPlayer(), DEPTH, alpha, beta);
    	if(tmp > max) {
    		max = tmp;
    		bestGameState = NextStates[i];
    	}
    }


    return bestGameState;
    //return lNextStates[rand() % lNextStates.size()];
}

/*namespace TICTACTOE*/ }
