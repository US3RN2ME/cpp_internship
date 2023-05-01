#ifndef LAB4_RANDOM_HPP
#define LAB4_RANDOM_HPP

#include <random>

namespace Lab4 {

    class Random {
    public:
        static int nextInt(int min, int max) {
            std::uniform_int_distribution<> dist(min, max);
            return dist(m_mt);
        }

    private:
        inline static std::mt19937 m_mt{ std::random_device()() };
    };

}

#endif // !LAB4_RANDOM_HPP
