### Copy List with Random Pointer

Create a copy of every node and store an **`original node → copied node`** mapping in a Hash Map.
Traverse the original list again and use the map to connect each copied node’s `next` and `random` pointers.
Map **node addresses**, not values, because multiple nodes can have the same value.
**Time: O(n), Space: O(n).**

### Add Two Numbers

Traverse both linked lists together, adding corresponding digits plus a **carry**.
Treat missing nodes as `0`, create a new node with `sum % 10`, and update carry using `sum / 10`.
Continue while either list has nodes **or carry is not 0**, using a dummy node to build the result.
**Time: O(max(n,m)), Space: O(max(n,m))** for the output list.
