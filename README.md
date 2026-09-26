A lightweight C++ class that represents a 2D matrix using a single, flat (1D) dynamically-allocated array internally.

---

## 1. What It Is

`Matrix1D` gives you a simple way to create and work with a 2D grid of integers (rows × columns) without using `int**` or `std::vector<std::vector<int>>`. Internally, it stores all elements in **one contiguous 1D array** and converts `(row, column)` coordinates into a single index behind the scenes.

---

## 2. When / Where to Use It

Use `Matrix1D` when:

- You need a **simple, fixed-size 2D grid of integers** (e.g., for a school project, algorithm practice, or small simulation).
- You want to **learn or demonstrate** how 2D data can be stored in 1D memory (a common technique in embedded systems, game boards, image data, and performance-critical code).
- You want **better cache performance** than a jagged 2D array (`int**`), since a single contiguous block of memory is faster to access than scattered rows.
- You're prototyping something like:
  - A grid-based game board (tic-tac-toe, Minesweeper, chess)
  - A small image/pixel map (grayscale values)
  - A simple adjacency/relationship matrix
  - Any tabular integer data before scaling up to a more advanced library (e.g., Eigen)

Avoid it when:

- You need matrices of other types (float, double, custom objects) — this class is hardcoded to `int`.
- You need matrix math (addition, multiplication, transpose, etc.) — not implemented here.
- You need resizing after creation — the size is fixed at construction.

---

## 3. How to Use It

### Include the header
```cpp
#include "Matrix1D.h"
```

### Create a matrix
```cpp
Matrix1D myMatrix(3, 4); // 3 rows, 4 columns — all values start at 0
```

### Set a value
```cpp
myMatrix.set_value(1, 2, 99); // row 1, column 2 = 99
```

### Get a value
```cpp
int val = myMatrix.get_value(1, 2); // returns 99
```

### Print the whole matrix
```cpp
myMatrix.print_array();
```
Example output for a 3x4 matrix:
```
0 0 0 0
0 0 99 0
0 0 0 0
```

### Get the raw array (read-only)
```cpp
const int* raw = myMatrix.get_array();
```

### Get total number of elements
```cpp
int size = myMatrix.get_length(); // 3 * 4 = 12
```

### Full example
```cpp
#include "Matrix1D.h"

int main()
{
    Matrix1D grid(2, 3);
    grid.set_value(0, 0, 5);
    grid.set_value(1, 2, 8);
    grid.print_array();
    return 0;
}
```

---

## 4. Features & Design Choices (Why We Built It This Way)

| Feature | What It Does | Why We Chose It |
|---|---|---|
| **Single 1D array (`int* m_array`)** | Stores all matrix elements in one contiguous block instead of an array-of-arrays. | Contiguous memory means better **cache locality** (faster access) and only **one allocation/deallocation**, avoiding the overhead and fragmentation of allocating a separate array per row. |
| **`get_single_index(row, column)`** | Converts 2D coordinates into a 1D index: `row * num_columns + column`. | This is the standard **row-major order** formula (same layout C/C++ uses for native 2D arrays), so behavior stays intuitive and predictable. |
| **Constructor with `assert()` checks** | Rejects `num_of_row <= 0` or `num_of_column <= 0` immediately. | Prevents creating a broken/zero-sized matrix and catches programmer errors **early**, during development, rather than causing silent bugs or crashes later. |
| **Auto-zero initialization (`assign_values()`)** | Every element is set to `0` right after allocation. | Raw `new int[]` does **not** initialize memory — leaving it would give garbage values. Zero-initializing avoids undefined behavior and gives predictable starting state. |
| **Destructor (`~Matrix1D()`) with `delete[]`** | Frees the dynamically allocated array when the object is destroyed. | Prevents **memory leaks** — since we manually used `new[]`, we must manually clean up with `delete[]`. |
| **`const` on getter methods** | `get_value`, `get_array`, `get_length`, `print_array` don't modify the object. | Marking them `const` documents intent, allows use on `const Matrix1D` objects, and lets the compiler catch accidental modifications. |
| **`static_cast<std::size_t>(...)` in allocation** | Explicitly converts the `int` size calculation to an unsigned `size_t`. | `new[]` expects an unsigned size type; the explicit cast avoids compiler warnings and signed/unsigned mismatch bugs. |
| **Header-only design (`#ifndef` include guard)** | Entire class (declaration + implementation) lives in one `.h` file. | Keeps the class **simple and portable** — no need to compile/link a separate `.cpp` file, ideal for small projects, single-file demos, or classroom use. |
| **`get_array()` returns `const int*`** | Read-only access to internal data. | Lets external code inspect data (e.g., pass to another function) **without risking direct mutation** or needing to copy the whole array. |

---

## 5. Known Limitations

- Only supports `int` type (not a template class).
- Fixed size after construction — no resizing.
- No copy constructor / copy assignment operator defined — copying a `Matrix1D` will do a **shallow copy** of the pointer, which can cause double-free bugs or crashes. (Consider adding the "Rule of Three/Five" if you plan to copy these objects.)
- No bounds checking on `row`/`column` in `get_value`/`set_value` — passing an out-of-range index causes undefined behavior.

---

## 6. Possible Next Steps

- Add a **template parameter** to support other types (`float`, `double`).
- Add a **copy constructor, copy assignment, move constructor/assignment** for safety.
- Add **bounds checking** with exceptions instead of relying on caller correctness.
- Add basic matrix operations (add, multiply, transpose).
