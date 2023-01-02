#include "worldcup23a2.h"

world_cup_t::world_cup_t():
	teamsById(),
	teamsByRank(),
	playersHash()
{}

//world_cup_t::~world_cup_t() = default;

StatusType world_cup_t::add_team(int teamId) {
	if(teamId <= 0) {
		return StatusType::INVALID_INPUT;
	}
	try {
		shared_ptr<Team> temp = this->teamsById.find(teamId);
		return StatusType::FAILURE; //found an existing team with this id - return FAILURE.
	}
	catch(const AVLTree<Team, int>::KeyAlreadyExists& e) {} //team with this id not found - proceed.
	try {
		shared_ptr<Team> team(new Team(teamId));
		this->teamsById.insert(team, teamId);
		this->teamsByRank.insert(team, team->getStats());
	}
	catch(const std::bad_alloc& e) {
		return StatusType::ALLOCATION_ERROR;
	}
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId) {
	if(teamId <= 0) {
		return StatusType::INVALID_INPUT;
	}

	try {
		shared_ptr<Team> team = this->teamsById->find(teamId);
	}
	catch(const AVLTree<Team, int>::NodeNotFound& e) {
		return StatusType::Failure;
	}

	this->teamsById.remove(teamId);
	this->teamsByStats.remove(team->getStats());
	team->getRoot()->setTeamId(-1);
	
	return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper) {
									   
	if (playerId <= 0 || teamId <= 0 || !spirit.isValid() || gamesPlayed < 0 || cards < 0) {
		return StatusType::INVALID_INPUT;
	}
	
	
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2) {
	if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) {
		return StatusType::INVALID_INPUT;
	}
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId) {
	// TODO: Your code goes here
	return 22;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards) {
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId) {
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_team_points(int teamId) {
	// TODO: Your code goes here
	return 30003;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i) {
	// TODO: Your code goes here
	return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId) {
	// TODO: Your code goes here
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2) {
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
