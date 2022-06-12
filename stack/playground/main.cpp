/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:41:32 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/12 23:31:52 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
#include "../src/stack.hpp"

template<typename V>
void printv(V& v) {
	std::cout << "===============================" << std::endl;
	std::cout << "CAP   : " << v.capacity() << std::endl;
	std::cout << "SZE   : " << v.size() << std::endl;
	std::cout << "MX SZE: " << v.max_size() << std::endl;
	
	std::cout << "[ ";
	for(size_t i = 0; i < v.size(); ++i) {
		std::cout <<  v[i]; std::cout << (i < v.size() - 1 ? ", " : "");
	}
	std::cout << " ]" << std::endl;
	std::cout << "-------------------------------" << std::endl;
}

int main() {

	const int arr[] = {0, 1, 2, 3, 4};
	const int arr2[] = {0, 1, 32, 3, 4};

	ft::stack<int> s;

	s.push(0);
	s.push(100);
	s.push(200);

	std::cerr << s.top() << std::endl;

	s.pop();

	std::cerr << s.top() << std::endl;

	s.pop();

	std::cerr << s.top() << std::endl;

	std::cerr << "SZE: " << s.size() << std::endl;

	std::cerr << std::boolalpha;

	std::cerr << "EMPT: " << s.empty() << std::endl;
	
	s.pop();

	std::cerr << "EMPT: " << s.empty() << std::endl;
	
	return (0);
}