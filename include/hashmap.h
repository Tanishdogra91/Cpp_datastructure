#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>

// Manual declaration of malloc and free to avoid including <cstdlib>
extern "C" {
    void* malloc(decltype(sizeof(0)) size);
    void free(void* ptr);
}

// Default Key Equal functor using operator==
template <typename T>
struct DefaultKeyEqual {
    bool operator()(const T& a, const T& b) const {
        return a == b;
    }
};

// Default Hash functor for arithmetic types
template <typename Key>
struct DefaultHash {
    decltype(sizeof(0)) operator()(const Key& key) const {
        return static_cast<decltype(sizeof(0))>(key);
    }
};

template <typename Key, typename Value>
class HashNode {
public:
    Key key;
    Value value;
    HashNode<Key, Value>* next;

    HashNode(const Key& k, const Value& v);
    ~HashNode() = default;
};

template <typename Key, typename Value, typename Hash = DefaultHash<Key>, typename KeyEqual = DefaultKeyEqual<Key>>
class HashMap {
private:
    HashNode<Key, Value>** buckets;
    int bucketCount;
    int elementCount;
    float maxLoadFactor;
    Hash hashFn;
    KeyEqual equalFn;

    int getBucketIndex(const Key& key) const;
    void clear();

public:
    // Constructors & Destructor
    HashMap(int initialCapacity = 16);
    ~HashMap();

    // Rule of Three
    HashMap(const HashMap& other);
    HashMap& operator=(const HashMap& other);
};

#include "../src/hashmap.tpp"

#endif // HASHMAP_H
