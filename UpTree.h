#ifndef upTree_h
#define upTree_h

#include "Player.h"
#include "Team.h"
#include "wet2util.h"

class Player;
class Team;

//will be used in the up-tree inside the UF data structure
class UpTree {
    private:
        Player* player;
        UpTree* parent;
        permutation_t spiritRank;
        int gamesPlayedRank;
        int playerId;
        int size;

    public:
        UpTree() = delete;
        UpTree(Player* player, UpTree* parent, permutation_t& spiritRank, int gamesPlayedRank);
        ~UpTree() = default;
        
        int getPlayerId() const;

        static void Union(int playerId1, int playerId2) {
            UpTree* tree1 = Find(playerId1);
            UpTree* tree2 = Find(playerId2);
        }
        
        static UpTree* Find(int playerId) {}
        
};

#endif