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
            if (tree1->getSize() >= tree2->getSize()) {
                tree2->setParent(tree1);
                tree1->setSize(tree1->getSize() + tree2->getSize());
                tree2->setGamesPlayedRank(tree2->getGamesPlayedRank() - tree1->getGamesPlayedRank());
                tree2->setSpiritRank(tree2->getSpiritRank() * tree1->getSpiritRank().inv());
            }
            else {
                tree1->setParent(tree1);
                tree2->setSize(tree1->getSize() + tree2->getSize());
                tree1->setGamesPlayedRank(tree1->getGamesPlayedRank() - tree2->getGamesPlayedRank());
                tree1->setSpiritRank(tree1->getSpiritRank() * tree2->getSpiritRank().inv());
                tree2->setGamesPlayedRank(tree1->getGamesPlayedRank() + tree2->getGamesPlayedRank());
                tree2->setSpiritRank(tree2->getSpiritRank() * tree1->getSpiritRank());
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
};

#endif