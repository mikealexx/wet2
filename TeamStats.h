#ifndef TeamStats_h
#define TeamStats_h

//class to help sort teams by order needed in function get_ith_pointless_ability
class TeamStats {
    private:
        int ability;
        int id;

    public:
        TeamStats() = delete;
        TeamStats(int ability, int id);
        ~TeamStats() = default;

        int getAbility() const;
        void addAbility(int ability);

        friend bool operator<(const TeamStats& l, const TeamStats& r);
        friend bool operator>(const TeamStats& l, const TeamStats& r);
};

#endif