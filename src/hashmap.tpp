#ifndef HASHMAP_TPP
#define HASHMAP_TPP

#ifndef HASHMAP_H
#include "../include/hashmap.h"
#endif

// ==========================================
// HashNode Implementation
// ==========================================

template <typename Key, typename Value>
HashNode<Key, Value>::HashNode(const Key& k, const Value& v)
    : key(k), value(v), next(nullptr) {}


// ==========================================
// HashMap Implementation
// 

template <typename Key, typename Value, typename Hash, typename KeyEqual>
HashMap<Key, Value, Hash, KeyEqual>::HashMap(int initialCapacity) {
    if (initialCapacity <= 0) {
        initialCapacity = 16;
    }
    bucketCount = initialCapacity;
    elementCount = 0;
    maxLoadFactor = 0.75f;
    
    buckets = static_cast<HashNode<Key, Value>**>(std::malloc(bucketCount * sizeof(HashNode<Key, Value>*)));
    if (buckets == nullptr) {
        throw std::bad_alloc();
    }
    for (int i = 0; i < bucketCount; ++i) {
        buckets[i] = nullptr;
    }
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
HashMap<Key, Value, Hash, KeyEqual>::~HashMap() {
    clear();
    std::free(buckets);
}

// Copy Constructor (Rule of Three)
template <typename Key, typename Value, typename Hash, typename KeyEqual>
HashMap<Key, Value, Hash, KeyEqual>::HashMap(const HashMap<Key, Value, Hash, KeyEqual>& other) {
    bucketCount = other.bucketCount;
    elementCount = 0;
    maxLoadFactor = other.maxLoadFactor;
    hashFn = other.hashFn;
    equalFn = other.equalFn;

    buckets = static_cast<HashNode<Key, Value>**>(std::malloc(bucketCount * sizeof(HashNode<Key, Value>*)));
    if (buckets == nullptr) {
        throw std::bad_alloc();
    }
    for (int i = 0; i < bucketCount; ++i) {
        buckets[i] = nullptr;
    }

    try {
        for (int i = 0; i < other.bucketCount; ++i) {
            HashNode<Key, Value>* current = other.buckets[i];
            HashNode<Key, Value>* prev = nullptr;
            while (current != nullptr) {
                HashNode<Key, Value>* newNode = static_cast<HashNode<Key, Value>*>(std::malloc(sizeof(HashNode<Key, Value>)));
                if (newNode == nullptr) {
                    throw std::bad_alloc();
                }
                new (newNode) HashNode<Key, Value>(current->key, current->value);
                
                if (prev == nullptr) {
                    buckets[i] = newNode;
                } else {
                    prev->next = newNode;
                }
                prev = newNode;
                current = current->next;
                elementCount++;
            }
        }
    } catch (...) {
        clear();
        std::free(buckets);
        throw;
    }
}

// Copy Assignment Operator (Rule of Three)
template <typename Key, typename Value, typename Hash, typename KeyEqual>
HashMap<Key, Value, Hash, KeyEqual>& HashMap<Key, Value, Hash, KeyEqual>::operator=(const HashMap<Key, Value, Hash, KeyEqual>& other) {
    if (this == &other) {
        return *this;
    }

    clear();
    std::free(buckets);

    bucketCount = other.bucketCount;
    elementCount = 0;
    maxLoadFactor = other.maxLoadFactor;
    hashFn = other.hashFn;
    equalFn = other.equalFn;

    buckets = static_cast<HashNode<Key, Value>**>(std::malloc(bucketCount * sizeof(HashNode<Key, Value>*)));
    if (buckets == nullptr) {
        throw std::bad_alloc();
    }
    for (int i = 0; i < bucketCount; ++i) {
        buckets[i] = nullptr;
    }

    try {
        for (int i = 0; i < other.bucketCount; ++i) {
            HashNode<Key, Value>* current = other.buckets[i];
            HashNode<Key, Value>* prev = nullptr;
            while (current != nullptr) {
                HashNode<Key, Value>* newNode = static_cast<HashNode<Key, Value>*>(std::malloc(sizeof(HashNode<Key, Value>)));
                if (newNode == nullptr) {
                    throw std::bad_alloc();
                }
                new (newNode) HashNode<Key, Value>(current->key, current->value);
                
                if (prev == nullptr) {
                    buckets[i] = newNode;
                } else {
                    prev->next = newNode;
                }
                prev = newNode;
                current = current->next;
                elementCount++;
            }
        }
    } catch (...) {
        clear();
        std::free(buckets);
        throw;
    }

    return *this;
}

// Private helper to compute bucket index
template <typename Key, typename Value, typename Hash, typename KeyEqual>
int HashMap<Key, Value, Hash, KeyEqual>::getBucketIndex(const Key& key) const {
    return static_cast<int>(hashFn(key) % static_cast<size_t>(bucketCount));
}

// Private helper to clear all elements from HashMap
template <typename Key, typename Value, typename Hash, typename KeyEqual>
void HashMap<Key, Value, Hash, KeyEqual>::clear() {
  if (buckets == nullptr)
    return;
  for (int i = 0; i < bucketCount; ++i) {
    HashNode<Key, Value> *current = buckets[i];
    while (current != nullptr) {
      HashNode<Key, Value> *temp = current;
      current = current->next;
      temp->~HashNode();
      std::free(temp);
    }
    buckets[i] = nullptr;
  }
  elementCount = 0;
}

#endif // HASHMAP_TPP
