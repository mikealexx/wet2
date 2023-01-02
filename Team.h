#ifndef Team_h
#define Team_h

#include "Player.h"
#include "AVLTree.h"
#include "wet2util.h"
#include "UpTree.h"
#include "TeamStats.h"

class Player;
class UpTree;

class Team {
    private:
        int id;
        int points;
        int gamesPlayed;
        int ability;
        int size;
        int goalKeepers;
        permutation_t teamSpirit;
        shared_ptr<UpTree> rootPlayer;
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
        shared_ptr<UpTree> getRoot() const;
        permutation_t getlastPerm() const;
        int getLastGamesPlayed() const;
        TeamStats getStats() const;
        void updateStats();

        void addPoints(int points);
        void addGamesPlayed(int games);
        void addAbility(int ability);
        void addToSize(int size);
        void addGoalKeepers(int keepers);
        void setTeamSpirit(permutation_t teamSpirit);
        void setLastPerm(permutation_t perm);
        void setLastGamesPlayed(int games);
        void setRoot(shared_ptr<UpTree> root);

};

#endif