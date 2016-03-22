#ifndef REIMU_UNTILS_RANDOMUNTIL
#define REIMU_UNTILS_RANDOMUNTIL
#include <random>


class RandomUntil
{
public:
    static inline float fgRangeRand(float min, float max){
        float rnd = ((float)rand() / (float)RAND_MAX);
        return rnd*(max - min) + min;
    }
};

#endif