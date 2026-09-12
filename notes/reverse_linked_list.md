# Reverse Linked List

We have a singly linked list and need to reverse the direction of all the links.

For example:

```text
1 → 2 → 3 → 4 → NULL
```

After reversing:

```text
4 → 3 → 2 → 1 → NULL
```

The key idea is to change the `next` pointer of every node so that it points to the previous node.

We can solve this using an **iterative** or **recursive** approach.

The iterative solution is optimal because it takes **O(n) time and O(1) space**.

---

## The Main Idea

Suppose we have:

```text
1 → 2 → 3 → 4 → NULL
```

We want:

```text
NULL ← 1 ← 2 ← 3 ← 4
```

The problem is that if we simply change:

```cpp
current->next = previous;
```

we would lose access to the rest of the list.

For example:

```text
1 → 2 → 3 → 4
↑
current
```

If we change `1.next` to `NULL`, we no longer know where node `2` is.

So **before reversing the link, we need to save the next node**.

That gives us three important pointers:

```text
previous
current
next
```

---

## Iterative Approach

Initially:

```text
previous = NULL
current = head
```

For:

```text
1 → 2 → 3 → 4 → NULL
```

we have:

```text
previous
   ↓
 NULL

current
   ↓
   1 → 2 → 3 → 4 → NULL
```

At every step we do three things:

1. Save `current->next`
2. Reverse `current->next`
3. Move both pointers forward

In code:

```cpp
next = current->next;
current->next = previous;
previous = current;
current = next;
```

---

## Step 1

Initially:

```text
previous = NULL
current = 1
```

Save the next node:

```text
next = 2
```

Reverse the link:

```text
1 → NULL
```

Move the pointers:

```text
previous = 1
current = 2
```

Now:

```text
NULL ← 1    2 → 3 → 4 → NULL
        ↑    ↑
    previous current
```

---

## Step 2

Again save the next node:

```text
next = 3
```

Reverse the link:

```text
2 → 1 → NULL
```

Move the pointers:

```text
previous = 2
current = 3
```

Now:

```text
NULL ← 1 ← 2    3 → 4 → NULL
              ↑    ↑
          previous current
```

---

## Step 3

Save:

```text
next = 4
```

Reverse:

```text
3 → 2 → 1 → NULL
```

Move:

```text
previous = 3
current = 4
```

Now:

```text
NULL ← 1 ← 2 ← 3    4 → NULL
                  ↑    ↑
              previous current
```

---

## Step 4

Save:

```text
next = NULL
```

Reverse:

```text
4 → 3 → 2 → 1 → NULL
```

Move:

```text
previous = 4
current = NULL
```

Now `current` is `NULL`, so we are done.

The new head is:

```text
previous
    ↓
    4 → 3 → 2 → 1 → NULL
```

Therefore:

```cpp
return previous;
```

---

## The Easiest Mental Picture

Think of `previous` as the **already reversed portion** and `current` as the **remaining portion**.

```text
        reversed          remaining
           ↓                 ↓
NULL ← 1 ← 2    3 → 4 → NULL
              ↑
           current
```

Every iteration takes the first node from the remaining portion and adds it to the front of the reversed portion.

```text
Before:

NULL ← 1 ← 2    3 → 4
              ↑
           current


After:

NULL ← 1 ← 2 ← 3    4
                    ↑
                 current
```

So the entire algorithm is basically:

```text
Save next
Reverse current
Move previous
Move current
```

---

## Why Do We Need `next`?

This is the most important part to understand.

Suppose:

```text
1 → 2 → 3 → 4
```

and:

```text
current = 1
previous = NULL
```

If we immediately do:

```cpp
current->next = previous;
```

we get:

```text
1 → NULL
```

But we have lost the pointer to:

```text
2 → 3 → 4
```

Therefore, we must first save:

```cpp
next = current->next;
```

Then reverse:

```cpp
current->next = previous;
```

Then we can safely move:

```cpp
current = next;
```

This is why the order of these operations matters.

---

## Recursive Approach

We can also solve the problem recursively.

Instead of reversing the list from the beginning, we can ask:

> **Can I reverse everything after the current node first?**

Suppose:

```text
1 → 2 → 3 → 4 → NULL
```

We recursively reverse:

```text
2 → 3 → 4
```

Then:

```text
4 → 3 → 2
```

Now we only need to attach `1` correctly.

The important observation is:

```text
1 → 2
```

After the rest of the list has been reversed:

```text
4 → 3 → 2
```

we want:

```text
4 → 3 → 2 → 1
```

So we make node `2` point back to node `1`.

This is done with:

```cpp
head->next->next = head;
```

---

## Recursive Breakdown

Start with:

```text
1 → 2 → 3 → 4 → NULL
```

Call:

```cpp
reverseList(1)
```

which calls:

```cpp
reverseList(2)
```

which calls:

```cpp
reverseList(3)
```

which calls:

```cpp
reverseList(4)
```

At node `4`, we have reached the end.

```text
4 → NULL
```

So `4` becomes the new head.

Now the recursive calls start returning.

---

## Coming Back From Recursion

We return to node `3`.

We currently have:

```text
3 → 4
```

We want:

```text
4 → 3
```

So:

```cpp
head->next->next = head;
```

becomes:

```cpp
4->next = 3;
```

Then we remove the old link:

```cpp
head->next = NULL;
```

Now:

```text
4 → 3 → NULL
```

---

We return to node `2`.

Current reversed list:

```text
4 → 3
```

Reverse the link between `2` and `3`:

```text
4 → 3 → 2
```

Then:

```text
2 → NULL
```

---

Finally we return to node `1`.

Reverse:

```text
4 → 3 → 2 → 1
```

So the new head remains `4`.

---

## Recursive Base Case

The recursion stops when there is only one node left.

```cpp
if (head == NULL || head->next == NULL)
    return head;
```

Why?

If:

```text
NULL
```

there is nothing to reverse.

If:

```text
4 → NULL
```

the list is already reversed because there is only one node.

So we return:

```text
4
```

as the new head.

---

## The Recursive Leap of Faith

The important thing about recursion is to trust that:

```cpp
reverseList(head->next)
```

will correctly reverse the rest of the list.

For:

```text
1 → 2 → 3 → 4
```

we don't need to worry about how:

```text
2 → 3 → 4
```

gets reversed.

We simply trust that the recursive call returns:

```text
4 → 3 → 2
```

Then our job is only to attach `1`:

```text
4 → 3 → 2 → 1
```

So the recursive leap of faith is:

> **Assume the recursive call correctly reverses everything after the current node. I only need to reverse the connection between the current node and the next node.**

---

## Why `head->next->next = head`?

This line can initially look confusing:

```cpp
head->next->next = head;
```

Suppose:

```text
1 → 2
```

Here:

```text
head = 1
head->next = 2
```

Therefore:

```cpp
head->next->next = head;
```

means:

```cpp
2->next = 1;
```

So:

```text
1 → 2
```

becomes:

```text
2 → 1
```

This is the actual reversal of the link.

---

## Why Set `head->next = NULL`?

After reversing:

```text
1 → 2
```

we get:

```text
2 → 1
```

But `1` still has its old pointer:

```text
1 → 2
```

That would create:

```text
2 → 1 → 2 → 1 → ...
```

which is a cycle.

So we must break the old link:

```cpp
head->next = NULL;
```

giving:

```text
2 → 1 → NULL
```

---

## Iterative vs Recursive

### Iterative

```text
1 → 2 → 3 → 4

↓

4 → 3 → 2 → 1
```

Uses:

```text
previous
current
next
```

Time:

```text
O(n)
```

Space:

```text
O(1)
```

### Recursive

```text
1 → 2 → 3 → 4

↓
reverse the rest

4 → 3 → 2

↓
attach 1

4 → 3 → 2 → 1
```

Time:

```text
O(n)
```

Space:

```text
O(n)
```

because of the recursive call stack.

---

## Complexity

### Iterative

Every node is visited exactly once.

```text
Time Complexity = O(n)
Space Complexity = O(1)
```

### Recursive

Every node is also processed once.

However, each recursive call stays on the call stack until the recursion starts returning.

```text
Time Complexity = O(n)
Space Complexity = O(n)
```

The iterative solution is therefore the optimal solution when considering auxiliary space.

---

## Code

### Iterative

```cpp
ListNode* reverseList(ListNode* head) {

    // Previous node of the current node
    ListNode* prev = nullptr;

    // Start from the head
    ListNode* cur = head;

    while (cur) {

        // Save the next node before changing the link
        ListNode* next = cur->next;

        // Reverse the current node's pointer
        cur->next = prev;

        // Move prev forward
        prev = cur;

        // Move cur forward
        cur = next;
    }

    // prev is the new head of the reversed list
    return prev;
}
```

---

### Recursive

```cpp
ListNode* reverseList(ListNode* head) {

    // Empty list or single node
    // is already reversed
    if (head == nullptr || head->next == nullptr)
        return head;

    // Reverse everything after head
    ListNode* newHead = reverseList(head->next);

    // Reverse the link between head and head->next
    head->next->next = head;

    // Remove the old forward link
    head->next = nullptr;

    // The last node is the new head
    return newHead;
}
```

---

## Final Takeaway

The iterative solution is the one to remember for interviews.

The entire logic can be reduced to:

```cpp
ListNode* prev = nullptr;
ListNode* cur = head;

while (cur) {
    ListNode* next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
}

return prev;
```

The most important thing to remember is:

```text
SAVE → REVERSE → MOVE → MOVE
```

```text
next = cur->next
cur->next = prev
prev = cur
cur = next
```

Once this pattern becomes familiar, many other linked list problems become much easier because they build on the same idea of carefully manipulating node pointers.
