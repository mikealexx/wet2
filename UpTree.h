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
        permutation_t lastPerm;

    public:
        UpTree() = delete;
        UpTree(Player* player, UpTree* parent, permutation_t& spiritRank, int gamesPlayedRank);
        ~UpTree() = default;
        
        int getPlayerId() const;

        static void Union(int playerId1, int playerId2) {
            UpTree* tree1 = Find(playerId1);
            UpTree* tree2 = Find(playerId2);
            if (tree1->getSize() >= tree2->getSize()) {
                tree2->setParent(tree1);
                tree1->setSize(tree1->getSize() + tree2->getSize());
                int gamesRank1 = tree1->getGamesPlayedRank();
                int gamesRank2 = tree2->getGamesPlayedRank();
                tree2->setGamesPlayedRank(gamesRank2 - gamesRank1);
                permutation_t spirit2 = tree2->getSpiritRank();
                tree2->setSpiritRank(tree1->getLastPerm() * spirit2);
                tree1->setLastPerm(tree1->getLastPerm() * spirit2 * tree2->getLastPerm());
            }
            else {
                tree1->setParent(tree2);
                tree2->setSize(tree1->getSize() + tree2->getSize());
                
            }
        }
        
        static UpTree* Find(int playerId) {}
        
        int getSize() const;

        void setSize(int size);

        int getGamesPlayedRank() const;

        void setGamesPlayedRank(int rank);

        permutation_t getSpiritRank() const;

        void setSpiritRank(permutation_t rank);

        UpTree* getParent() const;

        void setParent(UpTree* tree);

        permutation_t getLastPerm() const;

        void setLastPerm(permutation_t perm);
};

#endif