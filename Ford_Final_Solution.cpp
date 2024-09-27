/**
 * Implement a LeastRecentlyUsed Cache (LRU Cache)
 *
 * An LRU cache is a cache with a policy to discard the least recently used
 * resource first, when the cache's internal capacity limit is reached.
 *
 * Any operation on a resource (i.e. inserting, modifying, or getting) counts
 * as a 'use'.  
 */
  
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <map>
#include <unordered_map>

/* Not using this struct anymore, using an unordered map instead*/
// struct data_unit {
//     std::string key;
//     int value;
// };
  
class LRU {
    private:
        int capacity;
        int curr_capacity = 0;
        std::unordered_map<std::string, int> data;
        /* stores the keys in a least_used order. I recognize that using a vector results in O(N) time complexity for put and get*/
        std::vector<std::string> least_used;
        
    public:
        LRU(int capacity) {
            this->capacity = capacity;
        }
        
        int get(const std::string& key) {
            /* Find the key in question, set it to most used if it exists and return the value*/
            if (data.find(key) != data.end()) {
                for (int i = 0; i < least_used.size(); i++) {
                    if (least_used[i] == key) {
                        std::swap(least_used[i], least_used[least_used.size()-1]);
                    }
                }
                return data[key];
            }
            return -1;
        }
    
        // Insert or update the `value` associated with `key`
        void put(const std::string& key, int value) {
            // Check if key is already in the map. If it exists, update it and set to most used, otherwise add it
            if (data.find(key) == data.end()) {
                // If not at capacity, increase capacity, otherwise erase the first (least used) key in the vector and map, then add the new resource
                if (curr_capacity < capacity) {
                    curr_capacity++;
                } else {
                    data.erase(least_used[0]);
                    least_used.erase(least_used.begin());
                }
                least_used.push_back(key);
                data[key] = value;
            } else {
                for (int i = 0; i < least_used.size(); i++) {
                    if (least_used[i] == key) {
                        std::swap(least_used[i], least_used[least_used.size()-1]);
                    }
                }
                data[key] = value;
            }

        }
};
  
int main() {
    
  std::cout << "Hello World" << std::endl;
  LRU lru(3);
    
  lru.put("one", 1); // [1]
  lru.put("two", 2); // [2, 1]
  lru.put("three", 3); // [3, 2, 1]
  std::cout << "one: " << lru.get("one") << std::endl; // [1, 3, 2] 
  lru.put("four", 4); // [4, 1, 3]
  lru.put("five", 5); // [5, 4 ,1]
  std::cout << "two: " << lru.get("two") << std::endl;
  std::cout << "four: " << lru.get("four") << std::endl; // [4, 5, 1]
  
  std::cout << "done";
  return 0;
} 