#ifndef MINI_C_MAP_H
#define MINI_C_MAP_H

#ifndef MINI_C_MAP_CAPACITY
#define MINI_C_MAP_CAPACITY 64
#endif

#define MINI_C_DECLARE_MAP(Key, Val, Name)                                     \
    typedef struct Name##Bucket {                                              \
        Key key;                                                               \
        Val value;                                                             \
        struct Name##Bucket *next;                                                    \
    } Name##Bucket;                                                            \
    typedef void (*Name##IterFn)(Key * key, Val * val, void *user_data);       \
    typedef struct Name {                                                      \
        Name##Bucket **buckets;                                                \
        Mini_Allocator allocator;                                              \
    } Name;                                                                    \
    Name Name##_init(Mini_Allocator allocator);                                \
    bool Name##_contains(Name *map, const Key *key);                           \
    Val *Name##_get(Name *map, const Key *key);                                \
    bool Name##_put(Name *map, Key key, Val val, Val *old_val);                      \
    void Name##_destroy(Name *map);                                            \
    void Name##_foreach(Name *map, Name##IterFn fn, void *ud);

#define MINI_C_DEFINE_MAP(Key, Val, Name, Hash, Eq)                            \
    Name Name##_init(Mini_Allocator allocator) {                               \
        Name map      = {0};                                                   \
        map.allocator = allocator;                                             \
        map.buckets =                                                          \
            MINI_ALLOC_MANY(allocator, Name##Bucket *, MINI_C_MAP_CAPACITY);   \
        memset(map.buckets, 0, sizeof(*map.buckets) * MINI_C_MAP_CAPACITY);\
        return map;                                                            \
    }                                                                          \
    bool Name##_contains(Name *map, const Key *key) {                          \
        usize index          = Hash(key) % MINI_C_MAP_CAPACITY;                \
        Name##Bucket *bucket = map->buckets[index];                            \
        while (bucket != NULL) {                                               \
            if (Eq(&bucket->key, key)) {                                       \
                return true;                                                   \
            }                                                                  \
            bucket = bucket->next;                                             \
        }                                                                      \
        return false;                                                          \
    }                                                                          \
    Val *Name##_get(Name *map, const Key *key) {                              \
        usize index          = Hash(key) % MINI_C_MAP_CAPACITY;                \
        Name##Bucket *bucket = map->buckets[index];                            \
        while (bucket != NULL) {                                               \
            if (Eq(&bucket->key, key)) {                                       \
                return &bucket->value;                                         \
            }                                                                  \
            bucket = bucket->next;                                             \
        }                                                                      \
        return NULL;                                                           \
    }                                                                          \
    bool Name##_put(Name *map, Key key, Val val, Val *old_val) {                     \
        usize index          = Hash(&key) % MINI_C_MAP_CAPACITY;                \
        Name##Bucket *bucket = map->buckets[index];                            \
        Name##Bucket *prev   = NULL;                                           \
        while (bucket != NULL) {                                               \
            if (Eq(&bucket->key, &key)) {                                       \
                if (old_val != NULL)\
                    *old_val = bucket->value;\
                bucket->value = val;\
                return true;\
            }                                                                  \
            prev   = bucket;                                                   \
            bucket = bucket->next;                                             \
        }                                                                      \
        Name##Bucket *new_bucket = MINI_ALLOC(map->allocator, Name##Bucket);   \
        new_bucket->key          = key;                                        \
        new_bucket->value        = val;                                      \
        new_bucket->next         = NULL;                                       \
        if (prev != NULL)                                                      \
            prev->next = new_bucket;                                           \
        else                                                                   \
            map->buckets[index] = new_bucket;                                  \
        return false;                                                   \
    }                                                                          \
    void Name##_destroy(Name *map) {                                           \
        for (usize n = 0; n < MINI_C_MAP_CAPACITY; ++n) {                      \
            Name##Bucket *bucket = map->buckets[n];                            \
            while (bucket != NULL) {                                           \
                Name##Bucket *next = bucket->next;                             \
                MINI_FREE(map->allocator, bucket);                             \
                bucket = next;                                                 \
            }                                                                  \
        }                                                                      \
        MINI_FREE(map->allocator, map->buckets);                               \
        map->buckets = NULL;\
    }                                                                          \
    void Name##_foreach(Name *map, Name##IterFn fn, void *ud) {                \
        for (usize n = 0; n < MINI_C_MAP_CAPACITY; ++n) {                      \
            Name##Bucket *bucket = map->buckets[n];                            \
            while (bucket != NULL) {                                           \
                Name##Bucket *next = bucket->next;                             \
                fn(&bucket->key, &bucket->value, ud);                          \
                bucket = next;                                                 \
            }                                                                  \
        }                                                                      \
    }

#endif // MINI_C_MAP_H
