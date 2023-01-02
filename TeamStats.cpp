#include "TeamStats.h"

TeamStats::TeamStats(int ability, int id): ability(ability), id(id) {}

int TeamStats::getAbility() const {
    return this->ability;
}

void TeamStats::addAbility(int ability) {
    this-> ability += ability;
}

bool operator<(const TeamStats& l, const TeamStats& r) {
    if(l.ability < r.ability) {
        return true;
    }
    else if(l.ability == r.ability) {
        if(l.id < r.id) {
            return true;
        }
    }
    return false;
}

bool operator>(const TeamStats& l, const TeamStats& r) {
    return (r < l);
}