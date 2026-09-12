### Copy List with Random Pointer

Create a copy of every node and store an **`original node → copied node`** mapping in a Hash Map.
Traverse the original list again and use the map to connect each copied node’s `next` and `random` pointers.
Map **node addresses**, not values, because multiple nodes can have the same value.
**Time: O(n), Space: O(n).**
