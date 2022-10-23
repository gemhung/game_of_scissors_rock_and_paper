#ifndef REFEREE_HEADER
#define REFEREE_HEADER

#include <unordered_set> 
#include <optional>

template <class C>
class Referee {
public:
    Referee():
        m_win_pattern({
            {Choice::Paper, Choice::Rock},
            {Choice::Rock, Choice::Scissors},
            {Choice::Scissors, Choice::Paper},
        })
    {
        // empty constructor
    }
    
    auto winner(const C& c1, const C& c2) -> std::optional<C> {
        return c1 == c2 ? std::nullopt : std::make_optional(m_win_pattern.count({c1, c2}) ? c1 : c2);
    }

private:
    struct PairHash {
        template <class T1, class T2>
        std::size_t operator()(const std::pair<T1, T2>& pair) const {
            return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
        }
    };

    std::unordered_set<std::pair<C, C>, Referee::PairHash> m_win_pattern;
};

#endif
