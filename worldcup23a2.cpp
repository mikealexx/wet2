#include "worldcup23a2.h"

world_cup_t::world_cup_t():
	teamsById(),
	teamsByRank(),
	playersHash()
{}

world_cup_t::~world_cup_t() = default;

StatusType world_cup_t::add_team(int teamId) {
	if(teamId <= 0) {
		return StatusType::INVALID_INPUT;
	}
	try {
		shared_ptr<Team> temp = this->teamsById.find(teamId);
        if (temp != nullptr){
            return StatusType::FAILURE; //found an existing team with this id - return FAILURE.
        }

	}
	catch(const std::exception& e) {} //team with this id not found (which is good) - proceed.
	try {
		shared_ptr<Team> team(new Team(teamId));
		this->teamsById.insert(team, teamId);
		this->teamsByRank.insert(team, team->getStats());
	}
	catch(const std::bad_alloc& e) {
		return StatusType::ALLOCATION_ERROR;
	}
	catch(const std::exception& e) {
		return StatusType::FAILURE;
	}
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId) {
	if(teamId <= 0) {
		return StatusType::INVALID_INPUT;
	}
    if(this->teamsById.getSize() == 0){
        return StatusType::FAILURE;
    }
	try {
		shared_ptr<Team> team = this->teamsById.find(teamId);
		this->teamsById.remove(teamId);
		this->teamsByRank.remove(team->getStats());
		if(team->getSize() > 0) {
			team->getRoot()->setTeamId(-1);
		}
	}
	catch(const std::exception& e) {
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
		shared_ptr<Team> team = this->teamsById.find(teamId);
		if (team == nullptr){
            return StatusType::FAILURE; //team doesn't exist
        }
		shared_ptr<UpTree> temp = this->playersHash.find(playerId); //Found an existing player with this id - return FAILURE.
		if(temp != nullptr) {
			return StatusType::FAILURE;
		}
	}
	catch(const std::exception& e) {} //Player with this id not found - proceed.

	try {
		shared_ptr<Team> team = this->teamsById.find(teamId);
		shared_ptr<Player> player (new Player(playerId, spirit, gamesPlayed - team->getGamesPlayed(), ability, cards, goalKeeper));
		shared_ptr<UpTree> tree(new UpTree(player, spirit, 0, teamId));
		shared_ptr<UpTree> root = team->getRoot();
		if (root == nullptr) {
			tree->setGamesPlayedRank(team->getGamesPlayed());
			team->setRoot(tree);
			root = team->getRoot();
		}
		else{	
			tree->setSpiritRank(root->getLastPerm() * spirit);
			root->setLastPerm(root->getLastPerm() * spirit);
			tree->setParent(root);
		}
		if (goalKeeper){
			team->addGoalKeepers(1);
		}
		team->setTeamSpirit(team->getTeamSpirit() * spirit);
		team->addAbility(ability);
		team->addToSize(1);
		root->setSize(root->getSize() + 1);
		this->playersHash.add(tree);
		
		this->teamsByRank.remove(team->getStats());
        team->updateStats();
		this->teamsByRank.insert(team, team->getStats());
		
	}
	catch(const std::bad_alloc& e) {
		return StatusType::ALLOCATION_ERROR;
	}
	catch(const std::exception& e) {
		return StatusType::FAILURE;
	}
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2) {
	if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2) {
		return StatusType::INVALID_INPUT;
	}
	int winner = 0; //0 - tie, 1 - team1 won by score, 2 - team1 won by strength, 3 - team2 won by score, 4 - team2 won by strength
	try {
		shared_ptr<Team> team1 = this->teamsById.find(teamId1);
		shared_ptr<Team> team2 = this->teamsById.find(teamId2);
        if(team1 == nullptr || team2 == nullptr) {
            return StatusType::FAILURE;
        }
		if(team1->getGoalKeepers() < 1 || team2->getGoalKeepers() < 1) {
			return StatusType::FAILURE;
		}
		team1->addGamesPlayed(1);
		team2->addGamesPlayed(1);
		int team1Score = team1->getPoints() + team1->getAbility();
		int team2Score = team2->getPoints() + team2->getAbility();
		shared_ptr<UpTree> root1 = team1->getRoot();
		shared_ptr<UpTree> root2 = team2->getRoot();
		root1->setGamesPlayedRank(root1->getGamesPlayedRank() + 1);
		root2->setGamesPlayedRank(root2->getGamesPlayedRank() + 1);
		if(team1Score > team2Score) { //team1 wins by score
			winner = 1;
			team1->addPoints(3);
		}
		else if(team1Score < team2Score) { //team2 wins by score
			winner = 3;
			team2->addPoints(3);
		}
		else { //tie by score, proceed playing by team strength
			int team1Strength = team1->getTeamSpirit().strength();
			int team2Strength = team2->getTeamSpirit().strength();
			if(team1Strength > team2Strength) { //team1 wins by strength
				winner = 2;
				team1->addPoints(3);
			}
			else if(team1Strength < team2Strength) { //team2 wins by strength
				winner = 4;
				team2->addPoints(3);
			}
			else { //tie
				winner = 0;
				team1->addPoints(1);
				team2->addPoints(1);
			} 
		}
		
	}
	catch(const std::bad_alloc& e) {
		return StatusType::ALLOCATION_ERROR;
	}
	catch(const std::exception& e) {
		return StatusType::FAILURE;
	}
	return output_t<int>(winner);
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId) {
	if(playerId <= 0) {
		return StatusType::INVALID_INPUT;
	}
	try {
		shared_ptr<UpTree> player = this->playersHash.find(playerId);
        if (player == nullptr) {
            return StatusType::FAILURE;
        }
		int out = UpTree::getGamesPlayed(player);
		return output_t<int>(out);
	}
	catch(const std::bad_alloc& e) {
		return StatusType::ALLOCATION_ERROR;
	}
	catch(const std::exception& e) {
		return StatusType::FAILURE;
	}
	return 22;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards) {
	if(playerId <= 0 || cards < 0) {
		return StatusType::INVALID_INPUT;
	}
	try {
		shared_ptr<UpTree> player = this->playersHash.find(playerId);
        if (player == nullptr) {
            return StatusType::FAILURE;
        }
		UpTree::Find(player);
		if(!UpTree::isActive(player)) {
			return StatusType::FAILURE;
		}
		player->getPlayer()->addCards(cards);
	}
	catch(const std::bad_alloc& e) {
		return StatusType::ALLOCATION_ERROR;
	}
	catch(const std::exception& e) {
		return StatusType::FAILURE;
	}
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId) {
	if(playerId <= 0) {
		return StatusType::INVALID_INPUT;
	}
	try {
		shared_ptr<UpTree> player = this->playersHash.find(playerId);
        if (player == nullptr) {
            return StatusType::FAILURE;
        }
		UpTree::Find(player);
		return output_t<int>(player->getPlayer()->getCards());
	}
	catch(const std::bad_alloc& e) {
		return StatusType::ALLOCATION_ERROR;
	}
	catch(const std::exception& e) {
		return StatusType::FAILURE;
	}
	return StatusType::SUCCESS; //inaccessible
}

output_t<int> world_cup_t::get_team_points(int teamId) {
	if(teamId <= 0) {
		return output_t<int>(StatusType::INVALID_INPUT);
	}
	try {
		shared_ptr<Team> team = this->teamsById.find(teamId);
        if (team == nullptr) {
            return StatusType::FAILURE;
        }
		return output_t<int>(team->getPoints());
	}
	catch(const std::bad_alloc& e) {
		return StatusType::ALLOCATION_ERROR;
	}
	catch(const std::exception& e) {
		return StatusType::FAILURE;
	}
	return 30003; //inaccessible
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i) {
	if (i < 0 || i >= this->teamsByRank.getSize()){
		return output_t<int>(StatusType::FAILURE);
	}
	
	int sum = 0;
	TreeNode<Team, TeamStats>* node = this->teamsByRank.root;
	while (node != nullptr) {
        int leftSize = 0;
        if (node->left != nullptr) {
            leftSize = node->left->getRank();
        }

		int idx = sum + leftSize;

		if (idx == i) {
			return output_t<int>(node->data->getID());
		}
		else if (idx > i) {
			node = node->left;
		}
		else {
			sum = idx + 1;
			node = node->right;
		}
	}
	return output_t<int>(StatusType::FAILURE);
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId) {
	if(playerId <= 0) {
		return StatusType::INVALID_INPUT;
	}
	try {
		shared_ptr<UpTree> player = this->playersHash.find(playerId);
		if(player == nullptr || !UpTree::isActive(player)) {
			return StatusType::FAILURE;
		}
		UpTree::Find(player);
		return output_t<permutation_t>(UpTree::getPartialSpirit(player));
	}
	catch(const std::bad_alloc& e) {
		return StatusType::ALLOCATION_ERROR;
	}
	catch(const std::exception& e) {
		return StatusType::FAILURE;
	}
	return permutation_t(); //inaccessible
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2) {
	if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2){
		return StatusType::INVALID_INPUT;
	}

	try {
		shared_ptr<Team> team1 = this->teamsById.find(teamId1);
		shared_ptr<Team> team2 = this->teamsById.find(teamId2);
        if(team1 == nullptr || team2 == nullptr) {
            return StatusType::FAILURE;
        }

		if (team1->getSize() == 0 && team2->getSize() == 0){
			team1->addPoints(team2->getPoints());
			team1->addAbility(team2->getAbility());
			this->teamsById.remove(teamId2);
			this->teamsByRank.remove(team2->getStats());
			this->teamsByRank.remove(team1->getStats());
        	team1->updateStats();
			this->teamsByRank.insert(team1, team1->getStats());
			team1->addGamesPlayed(team2->getGamesPlayed());
			return StatusType::SUCCESS;
		}
		/*else if (team2->getSize() == 0){
			team1->addPoints(team2->getPoints());
			team1->addAbility(team2->getAbility());
			this->teamsById.remove(teamId2);
			this->teamsByRank.remove(team2->getStats());
			this->teamsByRank.remove(team1->getStats());
        	team1->updateStats();
			this->teamsByRank.insert(team1, team1->getStats());
			return StatusType::SUCCESS;
		}
		else if (team1->getSize() == 0) {
			team1->addPoints(team2->getPoints());
			team1->addAbility(team2->getAbility());
			team1->addToSize(team1->getSize());
			team1->setTeamSpirit(team1->getTeamSpirit() * team2-> getTeamSpirit());
			team1->addGoalKeepers(team2->getGoalKeepers());
			this->teamsById.remove(teamId2);
			this->teamsByRank.remove(team2->getStats());
			team1->setRoot(team2->getRoot());
			this->teamsByRank.remove(team1->getStats());
        	team1->updateStats();
			this->teamsByRank.insert(team1, team1->getStats());
			return StatusType::SUCCESS;
		}*/

		shared_ptr<UpTree> root1 = team1->getRoot();
		shared_ptr<UpTree> root2 = team2->getRoot();

		if (root1 != nullptr && root2 != nullptr){
			UpTree::Union(team1->getRoot(), team2->getRoot());	
		}
		
		int size2 = team2->getSize();
		
		team1->addToSize(size2);
		team1->addAbility(team2->getAbility());
		team1->addPoints(team2->getPoints());
		team1->setTeamSpirit(team1->getTeamSpirit() * team2->getTeamSpirit());
		team1->addGoalKeepers(team2->getGoalKeepers());

        if (team1->getRoot() != nullptr){
            team1->setRoot(UpTree::Find(team1->getRoot()));
        }
		else{
            team1->setRoot(team2->getRoot());
        }
		
		this->teamsById.remove(teamId2);
		this->teamsByRank.remove(team2->getStats());
        this->teamsByRank.remove(team1->getStats());
        team1->updateStats();
		this->teamsByRank.insert(team1, team1->getStats());
		team1->addGamesPlayed(team1->getRoot()->getGamesPlayedRank() - team1->getGamesPlayed());

		if (root2 != nullptr){
			root2->setTeamId(teamId1);
		}

	}
	catch(const std::bad_alloc& e) {
		return StatusType::ALLOCATION_ERROR;
	}
	catch(const std::exception& e) {
		return StatusType::FAILURE;
	}
	
	return StatusType::SUCCESS;
}
