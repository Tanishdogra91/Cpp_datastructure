#ifndef HASHMAP_TPP
#define HASHMAP_TPP

#ifndef HASHMAP_H
#include "../include/hashmap.h"
#endif

namespace details {
// Helper trait to detect pointer types at compile time
template <typename U> struct is_ptr {
  static constexpr bool value = false;
};
template <typename U> struct is_ptr<U *> {
  static constexpr bool value = true;
};
} // namespace details

// Default generic hash function
template <typename T> size_t DefaultHash<T>::operator()(const T &val) const {
  if constexpr (details::is_ptr<T>::value) {
    return reinterpret_cast<size_t>(val);
  } else {
    return reinterpret_cast<size_t>(&val);
  }
}

// Hash specialization for int
inline size_t DefaultHash<int>::operator()(int x) const {
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = (x >> 16) ^ x;
  return static_cast<size_t>(x);
}

// Hash specialization for char
inline size_t DefaultHash<char>::operator()(char c) const {
  return DefaultHash<int>{}(static_cast<int>(c));
}

// Hash specialization for double using union
inline size_t DefaultHash<double>::operator()(double c) const {
  union {
    double d;
    size_t s;
  } u;
  u.s = 0;
  u.d = c;
  return u.s;
}

// Hash specialization for float using union
inline size_t DefaultHash<float>::operator()(float c) const {
  union {
    float f;
    size_t s;
  } u;
  u.s = 0;
  u.f = c;
  return u.s;
}

// FNV-1a hash specialization for std::string
inline size_t DefaultHash<std::string>::operator()(const std::string &s) const {
  size_t hash = 2166136261U;
  for (char c : s) {
    hash ^= static_cast<size_t>(c);
    hash *= 16777619U;
  }
  return hash;
}

// Constructor
template <typename Key, typename Value, typename Hash>
HashMap<Key, Value, Hash>::HashMap(int inibucketcount, double loadfactor) {
  if (inibucketcount <= 0)
    inibucketcount = 16;
  if (loadfactor <= 0.0 || loadfactor >= 1.0)
    loadfactor = 0.75;

  bucketcount = inibucketcount;
  elementcount = 0;
  threshold = loadfactor;

  buckets.clear();
  for (int i = 0; i < bucketcount; ++i) {
    buckets.append(LinkedList<Entry>());
  }
}

// Copy constructor
template <typename Key, typename Value, typename Hash>
HashMap<Key, Value, Hash>::HashMap(const HashMap &map) {
  deepcopy(map);
}

// Copy assignment operator
template <typename Key, typename Value, typename Hash>
HashMap<Key, Value, Hash> &
HashMap<Key, Value, Hash>::operator=(const HashMap &map) {
  if (this != &map) {
    deepcopy(map);
  }
  return *this;
}

// Calculate bucket index for a key
template <typename Key, typename Value, typename Hash>
size_t HashMap<Key, Value, Hash>::BucketIndex(const Key &key) const {
  return hashfun(key) % bucketcount;
}

// Get current load factor
template <typename Key, typename Value, typename Hash>
double HashMap<Key, Value, Hash>::loadfactor() const {
  return static_cast<double>(elementcount) / bucketcount;
}

// Copy internal data from another map
template <typename Key, typename Value, typename Hash>
void HashMap<Key, Value, Hash>::deepcopy(const HashMap &map) {
  bucketcount = map.bucketcount;
  elementcount = map.elementcount;
  threshold = map.threshold;
  hashfun = map.hashfun;
  buckets = map.buckets;
}

// Insert or update key-value pair
template <typename Key, typename Value, typename Hash>
void HashMap<Key, Value, Hash>::insert(const Key &k, const Value &v) {
  size_t index = BucketIndex(k);
  LinkedList<Entry> &bucket = buckets.get(static_cast<int>(index));

  for (int i = 0; i < bucket.size(); ++i) {
    if (bucket.get(i).key == k) {
      bucket.get(i).value = v;
      return;
    }
  }

  bucket.insertFront(Entry(k, v));
  ++elementcount;

  if (loadfactor() > threshold) {
    rehash();
  }
}

// Retrieve value associated with key
template <typename Key, typename Value, typename Hash>
bool HashMap<Key, Value, Hash>::get(const Key &k, Value &v) const {
  size_t index = BucketIndex(k);
  const LinkedList<Entry> &bucket = buckets.get(static_cast<int>(index));

  for (int i = 0; i < bucket.size(); ++i) {
    if (bucket.get(i).key == k) {
      v = bucket.get(i).value;
      return true;
    }
  }
  return false;
}

// Remove key-value pair
template <typename Key, typename Value, typename Hash>
void HashMap<Key, Value, Hash>::remove(const Key &k) {
  size_t index = BucketIndex(k);
  LinkedList<Entry> &bucket = buckets.get(static_cast<int>(index));

  for (int i = 0; i < bucket.size(); ++i) {
    if (bucket.get(i).key == k) {
      bucket.deleteAt(i);
      --elementcount;
      return;
    }
  }
}

// Clear all elements
template <typename Key, typename Value, typename Hash>
void HashMap<Key, Value, Hash>::clear() {
  for (int i = 0; i < bucketcount; ++i) {
    buckets.get(i).clear();
  }
  elementcount = 0;
}

// Double bucket capacity and redistribute elements
template <typename Key, typename Value, typename Hash>
void HashMap<Key, Value, Hash>::rehash() {
  int oldBucketCount = bucketcount;
  DynamicArray<LinkedList<Entry>> oldBuckets = buckets;

  bucketcount *= 2;
  buckets.clear();
  for (int i = 0; i < bucketcount; ++i) {
    buckets.append(LinkedList<Entry>());
  }

  for (int i = 0; i < oldBucketCount; ++i) {
    LinkedList<Entry> &bucket = oldBuckets.get(i);
    for (int j = 0; j < bucket.size(); ++j) {
      Entry entry = bucket.get(j);
      size_t index = BucketIndex(entry.key);
      buckets.get(static_cast<int>(index)).insertFront(entry);
    }
  }
}

// Check if key exists in map
template <typename Key, typename Value, typename Hash>
bool HashMap<Key, Value, Hash>::exists(const Key &k) const {
  size_t index = BucketIndex(k);
  const LinkedList<Entry> &bucket = buckets.get(static_cast<int>(index));

  for (int i = 0; i < bucket.size(); ++i) {
    if (bucket.get(i).key == k) {
      return true;
    }
  }
  return false;
}

// Get number of elements
template <typename Key, typename Value, typename Hash>
int HashMap<Key, Value, Hash>::size() const {
  return elementcount;
}

// Get current bucket capacity
template <typename Key, typename Value, typename Hash>
int HashMap<Key, Value, Hash>::bucketCount() const {
  return bucketcount;
}

// Get current load factor
template <typename Key, typename Value, typename Hash>
double HashMap<Key, Value, Hash>::loadFactor() const {
  return loadfactor();
}

// Check if map is empty
template <typename Key, typename Value, typename Hash>
bool HashMap<Key, Value, Hash>::isEmpty() const {
  return elementcount == 0;
}

// Get count of bucket collisions
template <typename Key, typename Value, typename Hash>
int HashMap<Key, Value, Hash>::collisions() const {
  int c = 0;
  for (int i = 0; i < bucketcount; ++i) {
    int sz = buckets.get(i).size();
    if (sz > 1) {
      c += (sz - 1);
    }
  }
  return c;
}

// Print bucket array allocation stats
template <typename Key, typename Value, typename Hash>
void HashMap<Key, Value, Hash>::debugPrint() const {
  for (int i = 0; i < bucketcount; ++i) {
    std::cout << "Bucket " << i << " : " << buckets.get(i).size() << "\n";
  }
}

// Print all elements
template <typename Key, typename Value, typename Hash>
void HashMap<Key, Value, Hash>::print() const {
  for (int i = 0; i < bucketcount; ++i) {
    const LinkedList<Entry> &bucket = buckets.get(i);
    for (int j = 0; j < bucket.size(); ++j) {
      std::cout << bucket.get(j).key << " : " << bucket.get(j).value << "\n";
    }
  }
}

#endif // HASHMAP_TPP
