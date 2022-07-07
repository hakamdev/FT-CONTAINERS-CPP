#include "../src/stack.hpp"
#include <stack>

int main() {

	ft::stack<int> s;

	s.push(1);
	s.push(2);
	s.push(3);

	ft::stack<int> s2;

	s2.push(1);
	s2.push(2);

	std::cout << std::boolalpha;

	std::cout << (s != s2) << std::endl;
	std::cout << (s == s2) << std::endl;
	std::cout << (s < s2) << std::endl;
	std::cout << (s > s2) << std::endl;
	std::cout << (s <= s2) << std::endl;
	std::cout << (s >= s2) << std::endl;

	return 0;
}