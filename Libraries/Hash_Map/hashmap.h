//
// Created by student on 07/09/2020.
//
#ifndef INC_20_HASH_MAP_HASHMAP_H
#define INC_20_HASH_MAP_HASHMAP_H
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <cmath>

typedef size_t(*HashFunc)(const std::string& str, size_t hashSize);

size_t defaultFunc(const std::string& key, size_t hashSize);

template <typename T>
class HashMap{
public:
    explicit HashMap(size_t hashSize = HASH_TABLE_SIZE, HashFunc f = defaultFunc);
    void insert(const std::string& key, const T& value);

    const T& operator[](const std::string& key) const;
    T& operator[](const std::string& key);

    const T& at (const std::string& key) const;
    T& at (const std::string& key);

    void remove(const std::string& key);

    void setHashFunc(HashFunc f);
    void setHashSize(size_t size);

    size_t getNumBucketsInUse() const;
    size_t getNumOfPairs() const;
    size_t getHashSize() const;

    bool empty() const;
    bool contains(const std::string&);
    std::vector<std::string> keys();
    std::vector<T> values();

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const HashMap<U>& map);

private:
    static const size_t HASH_TABLE_SIZE = 79;

    typedef std::list<std::pair<std::string, T> > PairList;
    typedef std::pair<std::string, T> Pair;
    typedef std::vector<std::list<Pair> > HashTable;


    size_t m_hash_size;
    HashTable m_table;
    HashFunc m_hash_func;
    size_t m_num_of_pairs;
    size_t m_num_of_buckets_in_use;

    void rehash(size_t new_size = 0);
    bool isPrime(size_t size);
    size_t makePrime(size_t num);
    size_t getIndex(const std::string& key);
    T getValue(size_t index, const std::string& key);
};


template<typename T>
inline HashMap<T>::HashMap(size_t hashSize, HashFunc f):
    m_hash_size(makePrime(hashSize)),
    m_table(m_hash_size),
    m_hash_func(f),
    m_num_of_pairs(0),
    m_num_of_buckets_in_use(0) {}

template<class T>
inline size_t HashMap<T>::getIndex(const std::string& key) {
    return m_hash_func(key, m_hash_size);
}

template<typename T>
void HashMap<T>::insert(const std::string &key, const T &value) {
    size_t index = getIndex(key);
    typename std::list<Pair>::iterator it = m_table[index].begin();
    for (it; it != m_table[index].end(); it++) {
        if (it->first == key) {
            it->second = value;
            return;
        }
    }
    Pair new_pair(key, value);
    if (m_table[index].size() == 0)
        m_num_of_buckets_in_use++;
    m_table[index].push_back(new_pair);
    m_num_of_pairs++;
}

template<typename T>
const T &HashMap<T>::operator[](const std::string &key) const {
    size_t index = getIndex(key);
    typename std::list<Pair>::iterator it = m_table[index].begin();
    for (it; it != m_table[index].end(); it++) {
        if (it->first == key) {
            return it->second;
        }
    }
    throw std::invalid_argument("Error! Key doesn't exist...");
}

template<typename T>
T &HashMap<T>::operator[](const std::string &key) {
    size_t index = getIndex(key);
    typename std::list<Pair>::iterator it = m_table[index].begin();
    for (it; it != m_table[index].end(); it++) {
        if (it->first == key) {
            return it->second;
        }
    }
    Pair new_pair(key, T());
    if (m_table[index].size() == 0)
        m_num_of_buckets_in_use++;
    m_table[index].push_back(new_pair);
    m_num_of_pairs++;
    return m_table[index].back().second;
    //throw std::invalid_argument("Error! Key doesn't exist...");
}

template<typename T>
const T &HashMap<T>::at(const std::string &key) const {
    size_t index = getIndex(key);
    typename std::list<Pair>::iterator it = m_table[index].begin();
    for (it; it != m_table[index].end(); it++) {
        if (it->first == key) {
            return  it->second;
        }
    }
    throw std::invalid_argument("Error! Key doesn't exist...");
}

template<typename T>
T &HashMap<T>::at(const std::string &key) {
    size_t index = getIndex(key);
    typename std::list<Pair>::iterator it = m_table[index].begin();
    for (it; it != m_table[index].end(); it++) {
        if (it->first == key) {
            return it->second;
        }
    }
    Pair new_pair(key, T());
    if (m_table[index].size() == 0)
        m_num_of_buckets_in_use++;
    m_table[index].push_back(new_pair);
    m_num_of_pairs++;
    return m_table[index].back().second;
}

template<typename T>
inline std::vector<std::string> HashMap<T>::keys() {
    std::vector<std::string> keys;
    typename HashTable::iterator it = m_table.begin();
    for (it; it != m_table.end(); it++) {
        typename std::list<Pair>::iterator it2 = (*it).begin();
        for (it2; it2 != (*it).end(); it2++) {
            keys.push_back(it2->first);
        }
    }
    return keys;
}

template<typename T>
inline std::vector<T> HashMap<T>::values() {
    std::vector<T> values;
    typename HashTable::iterator it = m_table.begin();
    for (it; it != m_table.end(); it++) {
        typename std::list<Pair>::iterator it2 = (*it).begin();
        for (it2; it2 != (*it).end(); it2++) {
            values.push_back(it2->second);
        }
    }
    return values;
}

template<typename T>
void HashMap<T>::remove(const std::string &key) {
    size_t index = getIndex(key);
    T val = getValue(index, key);
    if (val == T())
        return;
    Pair p(key, val);
    m_table[index].remove(p);
    if (m_table[index].size() == 0)
        m_num_of_buckets_in_use--;
    m_num_of_pairs--;
}

template<typename T>
T HashMap<T>::getValue(size_t index, const std::string& key) {
    //size_t index = getIndex(key);
    typename std::list<Pair>::iterator it = m_table[index].begin();
    for (it; it != m_table[index].end(); it++) {
        if (it->first == key) {
            return it->second;
        }
    }
    return T();
}

template<typename T>
inline void HashMap<T>::setHashFunc(HashFunc f) {
    m_hash_func = f;
    rehash(m_hash_size);
}

template<typename T>
void HashMap<T>::rehash(size_t new_size) {
    HashMap<T> new_hash(new_size, m_hash_func);
    for (int i=0; i<m_hash_size; i++) {
        typename std::list<Pair>::iterator it = m_table[i].begin();
        for (it; it != m_table[i].end(); it++) {
            new_hash.insert(it->first, it->second);
        }
    }
    m_num_of_buckets_in_use = new_hash.m_num_of_buckets_in_use;
    m_table = new_hash.m_table;
    m_hash_size = new_size;
}

template<typename T>
inline void HashMap<T>::setHashSize(size_t size) {
    rehash(makePrime(size));
}

template<typename T>
inline size_t HashMap<T>::getNumBucketsInUse() const {
    return m_num_of_buckets_in_use;
}

template<typename T>
inline size_t HashMap<T>::getNumOfPairs() const {
    return m_num_of_pairs;
}

template<typename T>
inline size_t HashMap<T>::getHashSize() const {
    return m_hash_size;
}

template<typename T>
inline bool HashMap<T>::empty() const {
    return m_num_of_pairs == 0;
}

template<typename T>
inline bool HashMap<T>::isPrime(size_t size) {
    for (size_t i = 2; i <= ceil(sqrt(size)); i++) {
        if (size % i == 0)
            return false;
    }
    return true;
}

template<typename T>
inline size_t HashMap<T>::makePrime(size_t num) {
    while (!isPrime(num))
        num++;
    return num;
}

inline size_t defaultFunc(const std::string &key, size_t hashSize) {
    int num = 0;
    for (size_t i=0; i<key.size();i++) {
        num *= 10;
        num += key[i];
    }
    double A = 0.23456;
    return (size_t)(floor(hashSize * ((num * A) - long(num * A)))) % hashSize;
}

template<typename T>
bool HashMap<T>::contains(const std::string& key) {
    if (empty())
        return false;
    size_t index = getIndex(key);
    typename std::list<Pair>::iterator it = m_table[index].begin();
    for (it; it != m_table[index].end(); it++) {
        if (it->first == key) {
            return true;
        }
    }
    return false;
}

template<typename U>
std::ostream &operator<<(std::ostream &os, const HashMap<U> &map) {
    std::cout<<"**************** MY HASH-MAP ****************"<<std::endl;
    std::cout<<"hashmap size: "<<map.m_hash_size<<std::endl;
    std::cout<<"number of pairs: "<<map.m_num_of_pairs<<std::endl;
    std::cout<<"number of buckets in use: "<<map.m_num_of_buckets_in_use<<std::endl;
    std::cout<<std::endl;
    for (size_t i=0; i<map.m_hash_size; i++) {
        if (map.m_table[i].size() > 0) {
            std::cout<<"bucket #"<<i<<": ";
            typename std::list<std::pair<std::string, U> >::const_iterator it = map.m_table[i].begin();
            for (it; it != map.m_table[i].end(); it++) {
                std::cout<<"["<<it->first<<", "<<it->second<<"] -> ";
            }
            std::cout<<std::endl;
        }
    }
    std::cout<<"******************* END *******************"<<std::endl;
    return os;
}



#endif //INC_20_HASH_MAP_HASHMAP_H
