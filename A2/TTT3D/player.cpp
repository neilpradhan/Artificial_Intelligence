#include "player.hpp"
#include <cstdlib>
#include <limits>
#include <iostream>
#include <stdint.h>
#include <map>
#include <vector>
#include <algorithm>
#include<unordered_map>
#include<bits/stdc++.h>
#define DIM 4



#define NEGINF std::numeric_limits<int>::min()
#define POSINF std::numeric_limits<int>::max()



namespace TICTACTOE3D
{

int the_six_lines(int* matrice, const uint8_t & player) {
    int sum = 0;
    int i, j;

    int value = 0;

    //check rows  4 
    for(unsigned i = 0; i < DIM; ++i) {
        int sum = 0;
        for(unsigned j = 0; j < DIM; ++j) {
            if(matrice[i*DIM+j] != player && (matrice[i*DIM+j]== CELL_X || matrice[i*DIM+j] == CELL_O)) {
                sum = 0;
                break;
            }
            if(matrice[i*DIM+j] == player) {
                sum++;
            }
        }
        value += (sum*10);
    }

    // check cols 4
    for(unsigned i = 0; i < DIM; ++i) {
        int sum = 0;
        for(unsigned j = 0; j < DIM; ++j) {
            if(matrice[j*DIM+i] != player && (matrice[j*DIM+i] == CELL_X || matrice[j*DIM+i] == CELL_O)) {
                sum = 0;
                break;
            }
            if(matrice[j*DIM+i] == player) {
                sum++;
            }
        }
        value += (sum*10);
    }
    
    // check diagonals 2
    for(i = 0, j = 0; i < DIM && j < DIM; ++i, ++j) {
        if(matrice[i*DIM+j] != player && (matrice[i*DIM+j] == CELL_X || matrice[i*DIM+j] == CELL_O)) {
            sum = 0;
            break;
        }
        if(matrice[i*DIM+j] == player) {
            sum++;
        }
    }
    value += (sum*10);

    sum = 0;
    for(i = DIM-1, j = DIM-1; i >= 0 && j >= 0; --i, --j) {
        if(matrice[i*DIM+j] != player && (matrice[i*DIM+j] == CELL_X || matrice[i*DIM+j] == CELL_O)) {
            sum = 0;
            break;
        }
        if(matrice[i*DIM+j] == player) {
            sum++;
        }
    }
    value += (sum*10);

    return value;
}

int Player::CHECK_TABLE(const GameState & pState) {
    std::string message = std::string(pState.toMessage());

    if(HASHTABLE.find(message) != HASHTABLE.end())
        return HASHTABLE[message];

    return NEGINF;

}

int Player::gamma(const GameState &pState, const uint8_t & player) {
    int i,j,k;



    int value = 0;
    // bitwise exclusive OR
    uint8_t opponent = player ^ (CELL_X | CELL_O);
    // win-loss

	if (pState.isEOG()){
    if (pState.isDraw()){
        return 0;
    }

    if(pState.isXWin())  {
        return 10000;
    }
    
    if (pState.isOWin()){
        return -10000;
    }
	}

	uint8_t cell_content;
	int p_p =0; int o_p = 0;

	const int p_reward [4][4] = {{0,-10,-100,-1000},{10, 0, 0, 0},{100, 0, 0, 0}, {1000, 0, 0, 0}};
	// i , j -> k ; j, i -> k ; and so on
	for(i=0;i<4;i++){
      for(j=0;j<4;j++){
		//player points and oponent points
        p_p =0;  o_p = 0;
        for (k=0; k<4; k++){
          cell_content = pState.at(i,j,k);
          if(cell_content == CELL_X){
            p_p++;
          }else if(cell_content == CELL_O){
            o_p++;
          }
        }
		value += p_reward[p_p][o_p];
      }
    }

    for(i=0; i<4; i++){
      for(k=0;k<4;k++){
        p_p =0;  o_p = 0;
        for (j=0; j<4; j++){
          cell_content = pState.at(i,j,k);
          if(cell_content == CELL_X){
            p_p++;
          }else if(cell_content == CELL_O){
            o_p++;
          }
        }
		value += p_reward[p_p][o_p];
      }
    }


    for(j=0; j<4; j++){
      for(i=0;i<4;i++){
        p_p =0;  o_p = 0;
        for (k=0; k<4; k++){
          cell_content = pState.at(i,j,k);
          if(cell_content == CELL_X){
            p_p++;
          }else if(cell_content == CELL_O){
            o_p++;
          }
        }
		value += p_reward[p_p][o_p];
      }
    }


    for(j=0; j<4; j++){
      for(k=0;k<4;k++){
        p_p =0;  o_p = 0;
        for (i=0; i<4; i++){
          cell_content = pState.at(i,j,k);
          if(cell_content == CELL_X){
            p_p++;
          }else if(cell_content == CELL_O){
            o_p++;
          }
        }
        value += p_reward[p_p][o_p];
      }
    }


    for(k=0; k<4; k++){
      for(i=0;i<4;i++){
        p_p =0;  o_p = 0;
        for (j=0; j<4; j++){
          cell_content = pState.at(i,j,k);
          if(cell_content == CELL_X){
            p_p++;
          }else if(cell_content == CELL_O){
            o_p++;
          }
        }
        value += p_reward[p_p][o_p];
      }
    }





    for(k=0; k<4; k++){
      for(j=0;j<4;j++){
        p_p =0;  o_p = 0;
        for (i=0; i<4; i++){
          cell_content = pState.at(i,j,k);
          if(cell_content == CELL_X){
            p_p++;
          }else if(cell_content == CELL_O){
            o_p++;
          }
        }
        value += p_reward[p_p][o_p];
      }
    }


// diagonals
    for(i=0;i<4;i++){
        p_p =0;  o_p = 0;
      for(j=0;j<4;j++){
        cell_content = pState.at(i,j,j);
        if(cell_content == CELL_X){
          p_p++;
        }else if(cell_content == CELL_O){
          o_p++;
        }
      }
        value += p_reward[p_p][o_p];
    }



    for(i=0;i<4;i++){
        p_p =0;  o_p = 0;
      for(j=0;j<4;j++){
        cell_content = pState.at(i,j,3-j);
        if(cell_content == CELL_X){
          p_p++;
        }else if(cell_content == CELL_O){
          o_p++;
        }
      }
        value += p_reward[p_p][o_p];
    }



    for(j=0;j<4;j++){
        p_p =0;  o_p = 0;
      for(k=0;k<4;k++){
        cell_content = pState.at(k,j,k);
        if(cell_content == CELL_X){
          p_p++;
        }else if(cell_content == CELL_O){
          o_p++;
        }
      }
        value += p_reward[p_p][o_p];
    }


    for(j=0;j<4;j++){
        p_p =0;  o_p = 0;   
      for(k=0;k<4;k++){
        cell_content = pState.at(3-k,j,k);
        if(cell_content == CELL_X){
          p_p++;
        }else if(cell_content == CELL_O){
          o_p++;
        }
      }
        value += p_reward[p_p][o_p];
    }



    for(k=0;k<4;k++){
        p_p =0;  o_p = 0;
      for(int a=0;a<4;a++){
        cell_content = pState.at(a,a,k);
        if(cell_content == CELL_X){
          p_p++;
        }else if(cell_content == CELL_O){
          o_p++;
        }
      }
        value += p_reward[p_p][o_p];
    }


    for(k=0;k<4;k++){
        p_p =0;  o_p = 0;
      for(int a=0;a<4;a++){
        cell_content = pState.at(3-a,a,k);
        if(cell_content == CELL_X){
          p_p++;
        }else if(cell_content == CELL_O){
          o_p++;
        }
      }
        value += p_reward[p_p][o_p];
    }

// 4 diagonals 

    p_p =0;  o_p = 0;
    for(i=0; i<4; i++){
      cell_content = pState.at(3-i,i,i);
      if(cell_content == CELL_X){
        p_p++;
      }else if(cell_content == CELL_O){
        o_p++;
      }
    }
    
	value += p_reward[p_p][o_p];

    p_p =0;  o_p = 0;
    for(i=0; i<4; i++){
      cell_content = pState.at(i,i,i);
      if(cell_content == CELL_X){
        p_p++;
      }else if(cell_content == CELL_O){
        o_p++;
      }
    }
	value += p_reward[p_p][o_p];

    p_p =0;  o_p = 0;
    for(i=0; i<4; i++){
      cell_content = pState.at(i,i,3-i);
      if(cell_content == CELL_X){
        p_p++;
      }else if(cell_content == CELL_O){
        o_p++;
      }
    }
	value += p_reward[p_p][o_p];

    p_p =0;  o_p = 0;
    for(i=0; i<4; i++){
      cell_content = pState.at(i,3-i,i);
      if(cell_content == CELL_X){
        p_p++;
      }else if(cell_content == CELL_O){
        o_p++;
      }
    }
	value += p_reward[p_p][o_p];


    // //check i as height 4 layers
    // for(i = 0; i < DIM; ++i) {
    //     for(j = 0; j < DIM; ++j) {
    //         for(k = 0; k < DIM; ++k) {
    //             matrice[j*DIM+k] = pState.at(j,k,i);
    //         }
    //     }
    //     value += the_six_lines(matrice, CELL_X);
    //     value -= the_six_lines(matrice, CELL_O);
    // }


    // //check j as height  4 layers
    // for(j = 0; j < DIM; ++j) {
    //     for(i = 0; i < DIM; ++i) {
    //         for(k = 0; k < DIM; ++k) {
    //             // should not be changed
    //             matrice[i*DIM+k] = pState.at(j,k,i);
    //         }
    //     }
    //     value += the_six_lines(matrice, CELL_X);
    //     value -= the_six_lines(matrice, CELL_O);
    // }


    // //check k as height 4 layers
    // for(k = 0; k < DIM; ++k) {
    //     for(i = 0; i < DIM; ++i) {
    //         for(j = 0; j < DIM; ++j) {
    //             // this works tweeked and worked
    //             matrice[i*DIM+j] = pState.at(j,k,i);
    //         }
    //     }
    //     value += the_six_lines(matrice, CELL_X);
    //     value -= the_six_lines(matrice, CELL_O);
    // }

    // //4 diagonals 3D 4 only
    // unsigned sum = 0;

    // for(i = 0, j = 0, k = 0; i < DIM && j < DIM && k < DIM; ++i, ++j, ++k) {
    //     if(pState.at(j,k,i) != player && (pState.at(j,k,i) == CELL_X || pState.at(j,k,i) == CELL_O)) {
    //         sum = 0;
    //         break;
    //     }
    //     if(pState.at(j,k,i) == player) {
    //         sum++;
    //     }
    // }
    // value += (sum*10);

    // sum = 0;
    // for(i = 0, j = DIM, k = DIM; i < DIM && j >= 0 && k >= 0; ++i, --j, --k) {
    //     if(pState.at(j,k,i) != player && (pState.at(j,k,i) == CELL_X || pState.at(j,k,i) == CELL_O)) {
    //         sum = 0;
    //         break;
    //     }
    //     if(pState.at(j,k,i) == player) {
    //         sum++;
    //     }
    // }
    // value += (sum*10);


    // sum = 0;
    // for(i = 0, j = DIM, k = 0; i < DIM && j >= 0 && k < DIM; ++i, --j, ++k) {
    //     if(pState.at(j,k,i) != player && (pState.at(j,k,i) == CELL_X || pState.at(j,k,i) == CELL_O)) {
    //         sum = 0;
    //         break;
    //     }
    //     if(pState.at(j,k,i) == player) {
    //         sum++;
    //     }
    // }
    // value += (sum*10);


    // sum = 0;
    // for(i = 0, j = 0, k = DIM; i < DIM && j < DIM && k >= 0; ++i, ++j, --k) {
    //     if(pState.at(j,k,i) != player && (pState.at(j,k,i) == CELL_X || pState.at(j,k,i) == CELL_O)) {
    //         sum = 0;
    //         break;
    //     }
    //     if(pState.at(j,k,i) == player) {
    //         sum++;
    //     }
    // }
    // value += (sum*10);


    // //4 diagonals 3D opponent 
    // sum = 0;
    // for(i = 0, j = 0, k = 0; i < DIM && j < DIM && k < DIM; ++i, ++j, ++k) {
    //     if(pState.at(j,k,i) != opponent && (pState.at(j,k,i) == CELL_X || pState.at(j,k,i) == CELL_O)) {
    //         sum = 0;
    //         break;
    //     }
    //     if(pState.at(j,k,i) == opponent) {
    //         sum++;
    //     }
    // }
    // value -= (sum*10);

    // sum = 0;
    // for(i = 0, j = DIM, k = DIM; i < DIM && j >= 0 && k >= 0; ++i, --j, --k) {
    //     if(pState.at(j,k,i) != opponent && (pState.at(j,k,i) == CELL_X || pState.at(j,k,i) == CELL_O)) {
    //         sum = 0;
    //         break;
    //     }
    //     if(pState.at(j,k,i) == opponent) {
    //         sum++;
    //     }
    // }
    // value -= (sum*10);


    // sum = 0;
    // for(i = 0, j = DIM, k = 0; i < DIM && j >= 0 && k < DIM; ++i, --j, ++k) {
    //     if(pState.at(j,k,i) != opponent && (pState.at(j,k,i) == CELL_X || pState.at(j,k,i) == CELL_O)) {
    //         sum = 0;
    //         break;
    //     }
    //     if(pState.at(j,k,i) == opponent) {
    //         sum++;
    //     }
    // }
    // value -= (sum*10);


    // sum = 0;
    // for(i = 0, j = 0, k = DIM; i < DIM && j < DIM && k >= 0; ++i, ++j, --k) {
    //     if(pState.at(j,k,i) != opponent && (pState.at(j,k,i) == CELL_X || pState.at(j,k,i) == CELL_O)) {
    //         sum = 0;
    //         break;
    //     }
    //     if(pState.at(j,k,i) == opponent) {
    //         sum++;
    //     }
    // }
    // value -= (sum*10);

    return value;
}

// Driver function to sort the vector elements 
// by second element of pairs 
bool Player::sortbysec(const std::pair<int,int> &a,const std::pair<int,int> &b) 
{ 
    return (a.second > b.second); 
} 

int Player::alphaBeta(const GameState &pState, const uint8_t & player, unsigned depth, int alpha, int beta, const Deadline &deadline) {



    std::vector<GameState> NextStates;
    pState.findPossibleMoves(NextStates);


    if (NextStates.size() == 0 || deadline - TICTACTOE3D::Deadline::now() <= 0.2 || (depth == 0) )
        return gamma(pState, player);


	// we find size of children
    unsigned size_next_states = NextStates.size();
	


// 	if (size_next_states > 40){
// 		size_next_states = 4;
// 	}
// 	else {
// 		size_next_states = 12;
// 	} 





// vector pair for location, heuristics
	std::vector<std::pair<int,int>> vect;



    if(player == CELL_O) {

        for(unsigned i = 0; i < NextStates.size(); ++i) {

			vect.push_back(std::make_pair(i,gamma(NextStates[i], player)));
        }

	    sort(vect.begin(), vect.end(), sortbysec); 

        int motha = NEGINF;
        for(unsigned i = 0; i < size_next_states; ++i) {
            motha = std::max(motha,alphaBeta(NextStates[vect[i].first],CELL_X , depth-1, alpha, beta, deadline));
            alpha = std::max(alpha,motha);
            if(beta <= alpha) {
                break;
            }
        }

        return motha;
    }
    //if opponents turn
    else {

        for(unsigned i = 0; i < NextStates.size(); ++i) {
            // h[i] = gamma(NextStates[i], player);
            // h_idx[i] = i;
			vect.push_back(std::make_pair(i,gamma(NextStates[i], player)));

        }

		sort(vect.begin(), vect.end(), sortbysec); 

        int lahan = POSINF;
        for(unsigned i = 0; i < size_next_states; ++i) {
            lahan  = std::min(lahan, alphaBeta(NextStates[vect[i].first],CELL_O , depth-1, alpha, beta, deadline));
            beta = std::min(beta,lahan);
            if(beta <= alpha) {
                break;
            }
        }

        return lahan;
    }
}

GameState Player::play(const GameState &pState,const Deadline &pDue)
{

    
    unsigned depth = 6;
    
    std::vector<GameState> NextStates;
    pState.findPossibleMoves(NextStates);


    if (NextStates.size() == 0) {
        std::cerr << "" << std::endl;
        return GameState(pState, Move());
    }

    int alpha = NEGINF;
    int beta = POSINF;

    int max = NEGINF;
    GameState bestGameState;
    for(unsigned i = 0; i < NextStates.size(); ++i) {
        int tmp = alphaBeta(NextStates[i], pState.getNextPlayer(), depth, alpha, beta, pDue);
        if(tmp > max) {
            max = tmp;
            bestGameState = NextStates[i];
        }
    }


    return bestGameState;
    //return lNextStates[rand() % lNextStates.size()];
}

/*namespace TICTACTOE3D*/ }

