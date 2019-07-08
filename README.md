# not_empty
A C++ template for containers that should not under any circumstance be empty.

Use it just like any old standard library container:
```cpp
not_empty<std::vector<int>> foo{ 1, 2, 3, 4 };
for (auto i : foo) std::cout << i; // a normal range-based for
foo.erase(foo.begin()) // erase an element like normal
//foo.erase(foo.begin(), foo.end()) // NOPE. Fail fast behavior. std::terminate will be called if you try this
std::cout << foo[0] << foo.front(); // so do this with full confidence that the element exists :)
```

## Installing
Header only library. Place it in your project and `#include "not_empty.h++"`. Or add it as a git submodule, then `#include "not_empty/not_empty.h++"`.

## Tests
Many more tests are needed: the current test suite is pathetic. Anyway, building and running what tests there are is a fairly straightforward CMake invocation.
