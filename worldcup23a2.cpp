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
		shared_ptr<Team> team = this->teamsById.find(teamId);
		this->teamsById.remove(teamId);
		this->teamsByRank.remove(team->getStats());
		team->getRoot()->setTeamId(-1);
	}
	catch(const AVLTree<Team, int>::NodeNotFound& e) {
		return StatusType::FAILURE;
	}

	return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper) {
									   
	if (playerId <= 0 || teamId <= 0 || !spirit.isvalid() || gamesPlayed < 0 || cards < 0) {
		return StatusType::INVALID_INPUT;
	}
	
	try {
		playersHash.find(playerId); //Found an existing player with this id - return FAILURE.
		return StatusType::FAILURE;
	}
	catch(const AVLTree<UpTree, int>::KeyAlreadyExists& e) {} //Player with this id not found - proceed.

	try {
		shared_ptr<Team> team = this->teamsById.find(teamId);
		Player* player = new Player(playerId, spirit, gamesPlayed - team->getGamesPlayed(), ability, cards, goalKeeper);
		shared_ptr<UpTree> tree(new UpTree(player, spirit, 0, teamId));
		if (team->getRoot() == nullptr) {
			tree->setGamesPlayedRank(team->getGamesPlayed());
			team->setRoot(tree);
		}
		else{
			shared_ptr<UpTree> root = team->getRoot();
			tree->setSpiritRank(root->getLastPerm() * spirit);
			root->setLastPerm(root->getLastPerm() * spirit);
		}
		team->setTeamSpirit(team->getTeamSpirit * spirit)
		
	
	}
	catch(const AVLTree<Team, int>::NodeNotFound& e) {
		return StatusType::FAILURE;
	}
	catch(const std::bad_alloc& e) {
		return StatusType::ALLOCATION_ERROR;
	}
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2) {
	if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) {
		return StatusType::INVALID_INPUT;
	}
	try {
		shared_ptr<Team> team1 this->teamById.find(teamId1);
		shared_ptr<Team> team2 this->teamById.find(teamId2);
		if(team1->getGoalKeepers() < 1 || team2->getGoalKeepers() < 1) {
			return StatusType::FAILURE;
		}
		int team1Score = team1->getPoints() + team1->getAbility();
		int team2Score = team2->getPoints() + team2->getAbility();
		if(team1Score < team2Score) { //team1 wins by score
			team1->addPoints(3);
		}
		else if(team1Score > team2Score) { //team2 wins by score
			team2->addPoints(3);
		}
		else { //tie by score, proceed playing by team strength
			int team1Strength = team1->getTeamSpirit().strength();
			int team2Strength = team2->getTeamSpirit().strength();
			if(team1Strength > team2Strength) { //team1 wins by strength
				team1->addPoints(3);
			}
			else if(team1Strength < team2Strength) { //team2 wins by strength
				team2->addPoints(3);
			}
			else { //tie
				team1->addPoints(1);
				team2->addPoints(1);
			}
		}
		team1->addGamesPlayed(1);
		team2->addGamesPlayed(1);
	}
	catch(const std::bad_alloc& e) {
		return StatusType::ALLOCATION_ERROR;
	}
	catch(const AVLTree<Team, int>::NodeNotFound& e) {
		return StatusType::FAILURE;
	}
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId) {
	if(playerId <= 0) {
		return StatusType::INVALID_INPUT;
	}
	try {
		shared_ptr<UpTree> player = this->playersHash.find(playerId);
		return UpTree::getGamesPlayed(player);
	}
	catch(const AVL<UpTree, int>::NodeNotFound& e) {
		return StatusType::FAILURE;
	}
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
