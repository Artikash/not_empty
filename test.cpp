#include "not_empty.h++"
#include <iostream>
#include <vector>
#include <stack>
#include <map>

int main()
{
	not_empty<std::vector<int>> foo{ 1, 2, 3, 4 };
	foo->size();
	for (auto i : foo) std::cout << i;
	std::cout << foo[0];
	//foo.erase(foo.begin(), foo.end());
}
