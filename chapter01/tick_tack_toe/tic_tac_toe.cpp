/*###############################################################################################################
This code was ported to c++ from python.																		#
Original code can be found here:																				#
https://github.com/ShangtongZhang/reinforcement-learning-an-introduction/blob/master/chapter01/tic_tac_toe.py   #
# Copyright (C)                                                                                              	#
# 2016 - 2018 Shangtong Zhang(zhangshangtong.cpp@gmail.com)             										#
# 2016 Jan Hakenberg(jan.hakenberg@gmail.com)                         											#
# 2016 Tian Jun(tianjun.cpp@gmail.com)                                											#
# 2016 Kenta Shimada(hyperkentakun@gmail.com)                         											#
# Permission given to modify the code as long as you keep this       											#
# declaration at the top                                              											#
#################################################################################################################
*/

#include <iostream>
#include "State.h"
#include "HumanPlayer.h"
#include "Player.h"
#include "Judger.cpp"

using namespace std;

void getAllStatesImpl(State current_state, int current_symbol, std::map <int, std::pair<State, int>>& all_states) {
	int k = 0;
	while (k < current_state.BOARD_ROWS) {
		for(int i = 3*k; i<current_state.BOARD_COLS + 3*k; i++) {
			if(current_state.data(i) == 0){
				State newState;
				current_state.getNextState(current_state, newState, i, -1, current_symbol);
				int newHash = newState.hashState();
				if(all_states.find(newHash) == all_states.end()){
					short int isEnd = newState.isEnd();
					std::pair<State, int> val = {newState, isEnd};
					std::pair<int, std::pair<State, int>> key_val = {newHash, val};
					all_states.insert(key_val);
					if(!isEnd){
						getAllStatesImpl(newState, -current_symbol, all_states);
					}
				}
 			}
		}
		k++;
	}
}

std::map <int, std::pair<State, int>> getAllStates() {
	std::map <int, std::pair<State, int>> all_states;
	int current_symbol = 1;
	State current_state;
	std::pair<State, int> val = {current_state, current_state.isEnd()};
	std::pair<int, std::pair<State, int>> key_val = {current_state.hashState(), val};
	all_states.insert(key_val);
	getAllStatesImpl(current_state, current_symbol, all_states);
	return all_states;
}

int main() {
	auto all_states = getAllStates();
	/*HumanPlayer player1;
	HumanPlayer player2;
	Judger<HumanPlayer, HumanPlayer> j(player1, player2);
	int winner = j.play(true, all_states);
	std::cout << "The winner is" << winner << std::endl; */
	Player player(0.1 ,0.1, all_states);
	State state;
	State state2;
	state2.data = {{1, 1, 0},
					{-1, -1, 0},
					{0,0,0}};

	state2.winner = 0;
	state2.end = 0;
	State state3;
	state3.data = {{1, 1, 1},
					{-1, -1, 0},
					{0,0,0}};
	state3.winner = 1;
	state3.end = 1;
	player.states.push_back(state);
	player.greedy.push_back(true);
	player.states.push_back(state2);
	player.greedy.push_back(true);
	player.states.push_back(state3);
	player.greedy.push_back(true);
	//std::cout << (player.states)[0] << std::endl;
	//std::cout << (player.greedy)[0] << std::endl;
	player.setSymbol(1);
	player.updateEstimates();
	//player.reset();
	//std::cout << "---------------------------" << std::endl;
	//std::cout << (player.states)[0] << std::endl;
	//std::cout << (player.greedy)[0] << std::endl;
	return 0;
}
