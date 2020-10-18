//
// Created by student on 23/09/2020.
//

#ifndef DESIGN_DNA_CACHE_H
#define DESIGN_DNA_CACHE_H

#include <cstdio>

class Cache {
public:
    static size_t getCache();
    static void updateCache(size_t);

private:
    static size_t m_cache_id;
};


inline size_t Cache::getCache() {
    return m_cache_id;
}

inline void Cache::updateCache(size_t id) {
    m_cache_id = id;
}

#endif //DESIGN_DNA_CACHE_H
