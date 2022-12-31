#include "Player.h"

Player::Player(int id, int teamId, permutation_t spirit, int gamesPlayed, int ability, int cards, bool goalKeeper):
    id(id),
    teamId(teamId),
    spirit(spirit),
    gamesPlayed(gamesPlayed),
    ability(ability),
    cards(cards),
    goalKeeper(goalKeeper)
{}

int Player::getId() const {
    return this->id;
}

int Player::getTeamId() const {
    return this->teamId;
}

permutation_t Player::getSpirit() const {
    return this->spirit;
}

int Player::getAbility() const {
    return this->ability;
}

int Player::getCards() const {
    return this->cards;
}

bool Player::isGoalKeeper() const {
    return this->goalKeeper;
}

void Player::addAbility(int ability) {
    this->ability += ability;
}

void Player::addCards(int cards) {
    this->cards += cards;
}