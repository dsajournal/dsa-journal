# Remove Nth Node From End of List

## Problem

Given a linked list, remove the **nth node from the end**.

```text
1 → 2 → 3 → 4 → 5
n = 2

↓

1 → 2 → 3 → 5
```

We need to remove `4`.

---

## Core Idea

Use two pointers, `left` and `right`, with an **n node gap**.

```text
left
 ↓
1 → 2 → 3 → 4 → 5
            ↑
          right
```

Move `right` `n` steps ahead, then move both together.

When `right` reaches the end, `left` is just **before the node to remove**.

---

## Why Dummy Node?

Add a dummy node before `head`:

```text
dummy → 1 → 2 → 3
  ↑
 left
```

This also handles removing the head without special logic.

---

## Algorithm

```text
1. Create dummy → head
2. left = right = dummy
3. Move right n steps
4. Move both until right->next is NULL
5. Remove left->next
6. Return dummy->next
```

---

## Code

```cpp
ListNode* removeNthFromEnd(ListNode* head, int n) {

    ListNode dummy(0);
    dummy.next = head;

    ListNode* left = &dummy;
    ListNode* right = &dummy;

    // Create an n-node gap
    for (int i = 0; i < n; i++) {
        right = right->next;
    }

    // Move both pointers
    while (right->next != nullptr) {
        left = left->next;
        right = right->next;
    }

    // Remove the target node
    left->next = left->next->next;

    return dummy.next;
}
```

```cpp
while (right->next != nullptr) {
    right = right->next;
}
```

At the end:

```text
right = address of the LAST NODE
right->next = nullptr
```

So **`right` itself is NOT `nullptr`**.

```text
1 → 2 → 3 → 4 → 5 → nullptr
                ↑
              right
```

Therefore:

```cpp
right == nullptr        // false
right->next == nullptr  // true
```

That's the key distinction.

---

## Important Point

We use:

```cpp
while (right->next != nullptr)
```

because we want `left` to stop **one node before** the node we need to delete.

---

## Complexity

### Time: O(n)

We make at most one pass through the list.

### Space: O(1)

Only a few pointers are used. No extra data structure is required.

---

## Single Most Important Point

> **Keep `left` and `right` n nodes apart. When `right` reaches the end, `left` is just before the node to remove.**
