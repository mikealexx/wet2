#ifndef Team_h
#define Team_h

#include "Player.h"
#include "AVLTree.h"
#include "wet2util.h"
#include "UpTreeNode.h"
#include "TeamStats.h"

class Player;
class UpTreeNode;

class Team {
    private:
        int id;
        int points;
        int gamesPlayed;
        int ability;
        int size;
        int goalKeepers;
        permutation_t teamSpirit;
        UpTreeNode* rootPlayer;
        permutation_t lastPerm;
        int lastGamesPlayed;
        TeamStats stats;



    public:
        Team() = delete;
        Team(int id);
        ~Team() = default;

        int getID() const;
        int getPoints() const;
        int getGamesPlayed() const;
        int getAbility() const;
        int getSize() const;
        int getGoalKeepers() const;
        permutation_t getTeamSpirit() const;
        UpTreeNode* getRootPlayer() const;
        permutation_t getlastPerm() const;
        int getLastGamesPlayed() const;

        void addPoints(int points);
        void addGamesPlayed(int games);
        void addAbility(int ability);
        void addToSize(int size);
        void addGoalKeepers(int keepers);
        void setTeamSpirit(permutation_t teamSpirit);
        void setLastPerm(permutation_t perm);
        void setLastGamesPlayed(int games);

};

#endif