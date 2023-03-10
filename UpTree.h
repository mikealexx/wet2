#ifndef upTree_h
#define upTree_h

#include "Player.h"
#include "Team.h"
#include "wet2util.h"

class Player;
class Team;

class UpTree {
    private:

        shared_ptr<Player> player;
        shared_ptr<UpTree> parent;
        permutation_t spiritRank;
        int gamesPlayedRank;
        int playerId;
        int teamId;
        int size;
        permutation_t lastPerm;

    public:

        UpTree() = delete;
        UpTree(shared_ptr<Player> player, const permutation_t& spiritRank, int gamesPlayedRank, int teamId);
        ~UpTree() = default;
        
        int getPlayerId() const;

        // Player1 is the root of the buying team, player2 is the root of the buyee team
        static void Union(shared_ptr<UpTree> player1, shared_ptr<UpTree> player2) {
            shared_ptr<UpTree> tree1 = Find(player1);
            shared_ptr<UpTree> tree2 = Find(player2);
            if (tree1->getSize() >= tree2->getSize()) {
                tree2->setParent(tree1);
                tree1->setParent(nullptr);
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
                tree2->setParent(nullptr);
                tree2->setSize(tree1->getSize() + tree2->getSize());
                int gamesRank1 = tree1->getGamesPlayedRank();
                int gamesRank2 = tree2->getGamesPlayedRank();
                tree1->setGamesPlayedRank(gamesRank1 - gamesRank2);
                permutation_t spirit1 = tree1->getSpiritRank();
                permutation_t spirit2 = tree2->getSpiritRank();
                tree1->setSpiritRank(spirit2.inv() * tree1->getLastPerm().inv());
                tree2->setSpiritRank(spirit1 * tree1->getLastPerm() * spirit2);
                //tree2->setLastPerm(tree2->getLastPerm());
            }
        }
        
        static shared_ptr<UpTree> Find(shared_ptr<UpTree> player) {
            if (player == nullptr) {
                return nullptr;
            }

            int sumGames = 0;
            permutation_t productSpirit = permutation_t::neutral();

            shared_ptr<UpTree> out = player;
            while (out->getParent() != nullptr) {
                sumGames += out->getGamesPlayedRank();
                productSpirit = out->getSpiritRank() * productSpirit;
                out = out->getParent();
            }

            shared_ptr<UpTree> temp = player;
            while(temp->getParent() != nullptr) {
                int tempGames = temp->getGamesPlayedRank();
                temp->setGamesPlayedRank(sumGames);
                sumGames -= tempGames;
                
                permutation_t tempSpirit = temp->getSpiritRank();
                temp->setSpiritRank(productSpirit);
                productSpirit = productSpirit * tempSpirit.inv();

                shared_ptr<UpTree> temp2 = temp;
                temp = temp->getParent();
                temp2->setParent(out);
            }

            return out;
        }

        static int getGamesPlayed(shared_ptr<UpTree> player) {
            if (player == nullptr) {
                return 0;
            }

            int sumGames = player->getPlayer()->getGamesPlayed();

            while (player != nullptr) {
                sumGames += player->getGamesPlayedRank();
                player = player->getParent();
            }

            return sumGames;
        }

        static permutation_t getPartialSpirit(shared_ptr<UpTree> player) {
            if (player == nullptr) {
                return permutation_t::neutral();
            }

            permutation_t productSpirit = permutation_t::neutral();

            while (player != nullptr) {
                productSpirit = player->getSpiritRank() * productSpirit;
                player = player->getParent();
            }

            return productSpirit;
        }

        static bool isActive(shared_ptr<UpTree> player) {
            while(player->getParent() != nullptr) {
                player = player->getParent();
            }
            return player->teamId > 0;
        }
        
        int getSize() const;

        void setSize(int size);

        int getGamesPlayedRank() const;

        void setGamesPlayedRank(int rank);

        permutation_t getSpiritRank() const;

        void setSpiritRank(permutation_t rank);

        shared_ptr<UpTree> getParent() const;

        void setParent(shared_ptr<UpTree> tree);


        permutation_t getLastPerm() const;

        void setLastPerm(permutation_t perm);

        shared_ptr<Player> getPlayer() const;

        int getTeamId() const;

        void setTeamId(const int& id); 
};

#endif //UpTree_h