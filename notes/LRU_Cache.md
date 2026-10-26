# LRU Cache

## Key idea

Use a hash map to find each cache node in average O(1) time and a doubly linked list to maintain usage order.

The dummy head and tail are placeholder nodes. They do not represent real cache entries and their key/value fields are not used. They stay fixed at the boundaries and make insertion and removal easier by avoiding special cases at the ends of the list.

- `lruHead->next` points to the least recently used (LRU) real node.
- `mruTail->prev` points to the most recently used (MRU) real node.
- The LRU node is removed from the front, just after the dummy head.
- New or accessed nodes are inserted at the back, just before the dummy tail.

## C++ implementation

```cpp
#include <unordered_map>
using namespace std;

/*
   Implementation of an LRU (Least Recently Used) Cache using a combination of a hash map and a doubly linked list.
   - Hash map for O(1) average access to cache nodes by key.
   - Doubly linked list to maintain the order of usage (least recently used to most recently used).

   Dummy head and tail nodes are placeholders, not actual cache entries.
   They stay fixed at the boundaries and simplify insertion and removal.
   - lruHead->next points to the least recently used (LRU) node.
   - mruTail->prev points to the most recently used (MRU) node.
   - New or accessed nodes are inserted just before mruTail.

   Time Complexity:
   - O(1) average for both get and put operations.

   Space Complexity:
   - O(capacity) for storing cache nodes.
*/

class Node {
public:
    int k;         // Key of the node
    int val;       // Value of the node
    Node* prev;    // Pointer to the previous node in the list
    Node* next;    // Pointer to the next node in the list

    // Constructor to initialize a node with a key and value
    Node(int key, int value) {
        k = key;
        val = value;
        prev = NULL;
        next = NULL;
    }
};

class LRUCache {
public:
    // Constructor to initialize the LRUCache with a given capacity
    LRUCache(int capacity) {
        cap = capacity;

        // Create dummy nodes for the doubly linked list
        // These nodes are placeholders only; they do not store real cache entries.
        lruHead = new Node(0, 0);  // Dummy head node marking the LRU end
        mruTail = new Node(0, 0);  // Dummy tail node marking the MRU end

        // Connect dummy head to dummy tail
        lruHead->next = mruTail;
        mruTail->prev = lruHead;
    }

    // Destructor to free all dynamically allocated nodes
    ~LRUCache() {
        Node* curr = lruHead;

        while (curr != NULL) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    // Get the value of the key if present in the cache, otherwise return -1
    int get(int key) {
        if (cache.find(key) != cache.end()) {
            // Move the accessed node to the most recently used position
            Node* node = cache[key];
            remove(node);
            insert(node);

            return node->val;
        }

        return -1;
    }

    // Put a key-value pair into the cache
    void put(int key, int value) {

        // Handle zero capacity
        if (cap == 0) return;

        if (cache.find(key) != cache.end()) {
            // Update the existing node if the key is already present
            Node* node = cache[key];
            node->val = value;

            // Move the updated node to the most recently used position
            remove(node);
            insert(node);

            return;
        }

        // Insert the new node into the cache and update its position
        Node* node = new Node(key, value);
        cache[key] = node;
        insert(node);

        if (cache.size() > cap) {
            // Remove the least recently used (LRU) node if the cache exceeds capacity
            Node* lru = lruHead->next;
            remove(lru);
            cache.erase(lru->k);

            // Free the memory of the LRU node
            delete lru;
        }
    }

private:
    int cap;  // Maximum capacity of the cache
    unordered_map<int, Node*> cache;  // Hash map to store key-node pairs
    Node* lruHead;  // Dummy head node marking the LRU boundary
    Node* mruTail;  // Dummy tail node marking the MRU boundary

    // Remove a node from its current position in the doubly linked list
    // This function updates the pointers of the adjacent nodes to exclude the given node.
    // After removal, the given node is no longer part of the list.
    void remove(Node* node) {
        Node* prev = node->prev;  // Pointer to the node before the current node
        Node* next = node->next;  // Pointer to the node after the current node

        // Update the next pointer of the previous node to skip the current node
        prev->next = next;

        // Update the previous pointer of the next node to skip the current node
        next->prev = prev;
    }

    // Insert a node just before the dummy tail (mruTail) node
    // This function adds the given node to the doubly linked list immediately before the dummy tail.
    // After insertion, the given node becomes the new most recently used (MRU) node.
    // Note: The most recently added node is considered the most recently used.
    void insert(Node* node) {
        Node* prev = mruTail->prev;  // Pointer to the node currently at the MRU position
        Node* next = mruTail;        // Pointer to the dummy tail node

        // Update the next pointer of the current MRU node to point to the new node
        prev->next = node;

        // Update the previous pointer of the dummy tail node to point to the new node
        next->prev = node;

        // Set the new node's pointers to properly insert it between the current MRU node and the dummy tail
        node->prev = prev;
        node->next = next;
    }
};

/*
 * Usage:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key, value);
 */
```
