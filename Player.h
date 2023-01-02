#ifndef Player_h
#define Player_h

#include "wet2util.h"

class Player {
    private:
        int id;
        permutation_t spirit;
        int gamesPlayed;
        int ability;
        int cards;
        bool goalKeeper;

    public:
        Player() = delete;
        Player(int id, permutation_t spirit, int gamesPlayed, int ability, int cards, bool goalKeeper);
        ~Player() = default;

        int getId() const;
        int getTeamId() const;
        permutation_t getSpirit() const;
        int getAbility() const;
        int getCards() const;
        bool isGoalKeeper() const;
        int getGamesPlayed() const;

        void addAbility(int ability);
        void addCards(int cards);
};

#endif