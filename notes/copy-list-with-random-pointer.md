# Copy List with Random Pointer

## Problem

You are given a linked list where every node has:

```text
val
next
random
```

`random` can point to **any node** in the list or `nullptr`.

Create a **deep copy** of the entire list.

The copied list must contain completely new nodes, and its `next` and `random` pointers must point only to copied nodes. ([NeetCode][1])

---

## Core Idea

The difficult part is the `random` pointer.

```text
Original:

A → B → C

A.random → C
B.random → A
C.random → B
```

We need:

```text
Copy:

A' → B' → C'

A'.random → C'
B'.random → A'
C'.random → B'
```

So we need a way to know:

```text
Original node → Copy node
```

Use a **Hash Map**.

```text
oldToCopy[A] = A'
oldToCopy[B] = B'
oldToCopy[C] = C'
```

---

## Mental Model

Think of the Hash Map as a **translator**:

```text
Original node
     ↓
  Hash Map
     ↓
Copied node
```

Whenever the original node points somewhere with `random`, use the map to find the corresponding copied node.

---

## Algorithm

### 1. Create a copy of every node

Traverse the original list.

```text
A → B → C

Create:

A'  B'  C'
```

Store:

```text
A → A'
B → B'
C → C'
```

in the Hash Map.

At this point, we only care about the `val` and `next` pointers.

### 2. Connect `next` and `random`

Traverse the original list again.

For every original node:

```cpp
copy->next = oldToCopy[cur->next];
copy->random = oldToCopy[cur->random];
```

Because the map tells us exactly which copied node corresponds to each original node.

---

## Example

```text
Original:

1 → 2 → 3

1.random → 3
2.random → 1
3.random → 2
```

After first pass:

```text
oldToCopy

1 → 1'
2 → 2'
3 → 3'
```

Second pass:

```text
1'.random = oldToCopy[3] = 3'

2'.random = oldToCopy[1] = 1'

3'.random = oldToCopy[2] = 2'
```

Result:

```text
1' → 2' → 3'
↓     ↓     ↓
3'    1'    2'
```

---

## C++ Code

```cpp
class Solution {
public:
    Node* copyRandomList(Node* head) {

        if (head == nullptr) {
            return nullptr;
        }

        unordered_map<Node*, Node*> oldToCopy;

        // First pass: create copies
        Node* cur = head;

        while (cur != nullptr) {
            oldToCopy[cur] = new Node(cur->val);
            cur = cur->next;
        }

        // Second pass: connect next and random
        cur = head;

        while (cur != nullptr) {

            Node* copy = oldToCopy[cur];

            copy->next = oldToCopy[cur->next];
            copy->random = oldToCopy[cur->random];

            cur = cur->next;
        }

        return oldToCopy[head];
    }
};
```

### Why does `oldToCopy[cur->next]` work when `cur->next` is `nullptr`?

`unordered_map` will return a default value for a missing pointer key, which is `nullptr` for this pointer type in this usage.

A cleaner explicit version is:

```cpp
if (cur->next != nullptr) {
    copy->next = oldToCopy[cur->next];
}

if (cur->random != nullptr) {
    copy->random = oldToCopy[cur->random];
}
```

---

## Important Tricky Point

**Do not map node values. Map node addresses.**

Wrong:

```text
value → copy
```

because values can be duplicated.

Correct:

```text
original node address → copied node
```

For example:

```text
3 → 3 → 3

```

All three nodes have the same value but are **different nodes**.

---

## Complexity

**Time: O(n)**

We traverse the list twice. Each Hash Map insertion and lookup takes **O(1) on average**.

**Space: O(n)**

The Hash Map stores one mapping for every original node, and we also create `n` copied nodes. ([NeetCode][1])

---

## Single Most Important Point

> **Create every copy first and store `original → copy` in a Hash Map, then use that map to correctly connect every `next` and `random` pointer.**

[1]: https://neetcode.io/solutions/copy-list-with-random-pointer?utm_source=chatgpt.com "LeetCode 138 Copy List With Random Pointer Solution & Explanation | NeetCode"
