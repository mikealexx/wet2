#ifndef UpTreeNode_h
#define UpTreeNode_h

#include "Player.h"
#include "Team.h"
#include "wet2util.h"

class Player;
class Team;

//will be used in the up-tree inside the UF data structure
class UpTreeNode {
    private:
        Player* player;
        Team* team;
        UpTreeNode* parent;
        permutation_t spiritRank;
        int gamesPlayedRank;

    public:
        UpTreeNode() = delete;
        UpTreeNode(Player* player, Team* team, UpTreeNode* parent);
};

#endif