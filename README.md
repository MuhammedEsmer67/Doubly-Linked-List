# Doubly Linked List (C++ Template)

A generic, header-only doubly linked list written from scratch in C++ with manual memory management (`new` / `delete`). No STL containers are used. The goal of the project is to understand what happens in memory behind a list: how nodes are allocated, how pointers are rewired, and who owns what.

![C++](https://img.shields.io/badge/C%2B%2B-OOP-blue)
![Platform](https://img.shields.io/badge/Platform-Windows-informational)
![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%202022-purple)

## Features

- **Insert:** at the beginning, at the end, after a given node, after a given index
- **Delete:** a given node, the first node, the last node, or the whole list (`Clear`)
- **Access:** `Find`, `GetNode`, `GetItem`, `UpdateItem`
- **Utilities:** `Reverse`, `Size`, `isEmpty`, `PrintList`
- Works with any type `T` through a class template

## How it works

### Memory layout

Every element lives in its own heap-allocated node:

```
        +--------+-------+-------+
nullptr <-- Prev | Value | Next | --> ...
        +--------+-------+-------+
```

The list object itself only stores two things: a `Head` pointer and an `_Size` counter. Nodes are allocated one by one with `new`, so they are **not contiguous** in memory. That means no random access (reaching index *i* means walking *i* links) and worse cache locality than an array, in exchange for cheap insertion and deletion once you hold a pointer to the right place. With `T = int` on a typical 64-bit build, one node is 24 bytes (4 bytes of data, 4 of padding, 2 x 8 bytes of pointers).

### Invariants

Every operation is written to keep these true:

1. Empty list: `Head == nullptr` and `_Size == 0`.
2. `Head->Prev == nullptr`, and the last node's `Next == nullptr`.
3. For any two neighbouring nodes `a -> b`: `a->Next == b` and `b->Prev == a`.
4. `_Size` equals the number of nodes.

### Ownership and memory management

- The list **owns** every node it allocates. Each `new` in an insert method has a matching `delete` in a delete method.
- The destructor calls `Clear()`, which deletes nodes from the head until the list is empty, so nothing leaks when the list goes out of scope.
- Delete methods **unlink the node from both neighbours before** calling `delete`, so the list never holds a dangling pointer.
- **Copying is disabled** (copy constructor and copy assignment are `= delete`). A default copy would copy only the `Head` pointer, so two lists would share the same nodes and both would try to free them (double free).

### Pointer rewiring

- **InsertBeginning:** the new node points `Next` to the old head, the old head's `Prev` points back to the new node, and `Head` moves to the new node.
- **InsertAfter(node):** the new node is linked to `node` and `node->Next`, then both neighbours are updated. The `node->Next != nullptr` case (inserting after the tail) is handled separately.
- **DeleteNode:** the node's neighbours are connected to each other. If the node has no `Prev`, it was the head, so `Head` moves forward. Because each node knows its predecessor, deletion needs no search.
- **Reverse:** walks the list once and swaps `Prev` and `Next` in every node, then sets `Head` to the old last node. No allocation and no copying of values.

## Complexity

| Operation | Time | Note |
|---|---|---|
| `InsertBeginning` | O(1) | |
| `InsertAfter(node)` | O(1) | given the node pointer |
| `InsertEnd` | O(n) | walks to the tail (no tail pointer) |
| `DeleteFirstNode` | O(1) | |
| `DeleteNode(node)` | O(1) | given the node pointer |
| `DeleteLastNode` | O(n) | walks to the tail |
| `Find`, `GetNode`, `GetItem`, `UpdateItem`, `InsertAfter(index)` | O(n) | linear traversal |
| `Reverse` | O(n) | |
| `Clear`, destructor | O(n) | |
| `Size`, `isEmpty` | O(1) | counter is kept up to date |

## Design decisions and trade-offs

- **Doubly linked instead of singly linked:** costs one extra pointer per node, but `DeleteNode` becomes O(1) and lists can be reversed without extra memory.
- **Size counter:** `Size()` and `isEmpty()` are O(1); the price is updating the counter in every insert and delete.
- **No tail pointer:** keeps the list state minimal, but makes `InsertEnd` and `DeleteLastNode` O(n). Adding a tail pointer is the obvious next improvement.
- **`GetNode` clamps the index:** a negative index returns the head and an index past the end returns the last node, so it never returns an out-of-range pointer.
- **Requirements on `T`:** default-constructible (`GetItem` returns `T()` on failure).

## Known limitations

- `Head` and the node fields are public, so outside code can break the invariants.
- Pointers returned by `Find` / `GetNode` become dangling if that node is deleted.
- No iterators, so it does not work with range-based `for` or STL algorithms.
- Not thread-safe.

## Example

```cpp
#include "clsDblLinkedList.h"

int main()
{
    clsDblLinkedList<int> myList;

    myList.InsertEnd(10);
    myList.InsertEnd(20);
    myList.InsertBeginning(5);

    myList.PrintList();                    // 5 10 20
    myList.Reverse();
    myList.PrintList();                    // 20 10 5

    std::cout << myList.Size() << std::endl;    // 3
    std::cout << myList.isEmpty() << std::endl; // 0
}
```

## Build and run

### Visual Studio 2022 Community

1. Install Visual Studio Community with the **Desktop development with C++** workload.
2. Clone the repo: `git clone https://github.com/MuhammedEsmer67/Doubly-Linked-List.git`
3. Open the project and double-click `.sln` file.
4. Press **Ctrl + F5** (Start Without Debugging). A console window shows the output.

### PowerShell (g++)

```
g++ -std=c++17 main.cpp -o dll
.\dll
```
