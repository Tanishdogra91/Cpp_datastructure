#ifndef HASHMAP_TPP
#define HASHMAP_TPP

#ifndef HASHMAP_H
#include "../include/hashmap.h"
#endif

//Hash node Implementation

template <typename Key, typename Value>
HashNode<Key, Value>::HashNode(const Key& k, const Value& v)
    : key(k), value(v), next(nullptr) {}


// HashMap Implementation
template <typename Key, typename Value, typename Hash, typename KeyEqual>
HashMap<Key, Value, Hash, KeyEqual>::HashMap(int initialCapacity) {
    if (initialCapacity <= 0) {
        initialCapacity = 16;
    }
    bucketCount = initialCapacity;
    elementCount = 0;
    maxLoadFactor = 0.75f;
    
    buckets = allocateBuckets(bucketCount);
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
HashMap<Key, Value, Hash, KeyEqual>::~HashMap() {
    destroyBuckets(buckets, bucketCount);
    buckets = nullptr;
}

// Copy Constructor (Rule of Three)
template <typename Key, typename Value, typename Hash, typename KeyEqual>
HashMap<Key, Value, Hash, KeyEqual>::HashMap(const HashMap<Key, Value, Hash, KeyEqual>& other) {
    bucketCount = other.bucketCount;
    elementCount = 0;
    maxLoadFactor = other.maxLoadFactor;
    hashFn = other.hashFn;
    equalFn = other.equalFn;

    buckets = allocateBuckets(bucketCount);

    try {
        for (int i = 0; i < other.bucketCount; ++i) {
            HashNode<Key, Value>* current = other.buckets[i];
            HashNode<Key, Value>* prev = nullptr;
            while (current != nullptr) {
                HashNode<Key, Value>* newNode = createNode(current->key, current->value);
                
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
        destroyBuckets(buckets, bucketCount);
        throw;
    }
}

// Copy Assignment Operator (Rule of Three)
template <typename Key, typename Value, typename Hash, typename KeyEqual>
HashMap<Key, Value, Hash, KeyEqual>& HashMap<Key, Value, Hash, KeyEqual>::operator=(const HashMap<Key, Value, Hash, KeyEqual>& other) {
    if (this == &other) {
        return *this;
    }

    HashNode<Key, Value>** newBuckets = allocateBuckets(other.bucketCount);
    int newElementCount = 0;

    try {
        for (int i = 0; i < other.bucketCount; ++i) {
            HashNode<Key, Value>* current = other.buckets[i];
            HashNode<Key, Value>* prev = nullptr;
            while (current != nullptr) {
                HashNode<Key, Value>* newNode = createNode(current->key, current->value);
                
                if (prev == nullptr) {
                    newBuckets[i] = newNode;
                } else {
                    prev->next = newNode;
                }
                prev = newNode;
                current = current->next;
                newElementCount++;
            }
        }
    } catch (...) {
        destroyBuckets(newBuckets, other.bucketCount);
        throw;
    }

    destroyBuckets(buckets, bucketCount);

    buckets = newBuckets;
    bucketCount = other.bucketCount;
    elementCount = newElementCount;
    maxLoadFactor = other.maxLoadFactor;
    hashFn = other.hashFn;
    equalFn = other.equalFn;

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
      destroyNode(temp);
    }
    buckets[i] = nullptr;
  }
  elementCount = 0;
}

// Helper function to allocate dynamic memory and construct a HashNode using placement new
template <typename Key, typename Value, typename Hash, typename KeyEqual>
HashNode<Key, Value>* HashMap<Key, Value, Hash, KeyEqual>::createNode(const Key& k, const Value& v) {
    HashNode<Key, Value>* newNode = static_cast<HashNode<Key, Value>*>(std::malloc(sizeof(HashNode<Key, Value>)));
    if (newNode == nullptr) {
        throw std::bad_alloc();
    }
    new (newNode) HashNode<Key, Value>(k, v);
    return newNode;
}

// Helper function to call destructor and free memory of a HashNode
template <typename Key, typename Value, typename Hash, typename KeyEqual>
void HashMap<Key, Value, Hash, KeyEqual>::destroyNode(HashNode<Key, Value>* node) {
    if (node != nullptr) {
        node->~HashNode();
        std::free(node);
    }
}

// Helper function to allocate memory for buckets and initialize them to nullptr
template <typename Key, typename Value, typename Hash, typename KeyEqual>
HashNode<Key, Value>** HashMap<Key, Value, Hash, KeyEqual>::allocateBuckets(int capacity) {
    HashNode<Key, Value>** bucketsArray = static_cast<HashNode<Key, Value>**>(std::malloc(capacity * sizeof(HashNode<Key, Value>*)));
    if (bucketsArray == nullptr) {
        throw std::bad_alloc();
    }
    for (int i = 0; i < capacity; ++i) {
        bucketsArray[i] = nullptr;
    }
    return bucketsArray;
}

// Helper function to clear and free buckets array
template <typename Key, typename Value, typename Hash, typename KeyEqual>
void HashMap<Key, Value, Hash, KeyEqual>::destroyBuckets(HashNode<Key, Value>** bucketsArray, int capacity) {
    if (bucketsArray == nullptr) {
        return;
    }
    for (int i = 0; i < capacity; ++i) {
        HashNode<Key, Value>* current = bucketsArray[i];
        while (current != nullptr) {
            HashNode<Key, Value>* temp = current;
            current = current->next;
            destroyNode(temp);
        }
    }
    std::free(bucketsArray);
}

#endif // HASHMAP_TPP
