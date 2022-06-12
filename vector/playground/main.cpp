/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:41:32 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/12 14:04:34 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <algorithm>
#include "../src/algorithms.hpp"
#include "../src/vector.hpp"

template<typename V>
void printv(V v) {
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
	
	std::string arr[] = {"00", "11", "22", "33", "44"};

	ft::vector<std::string> v1;

	std::vector<std::string> v2;

	// printv(v1);
	// printv(v2);

	v1.reserve(300);
	v2.reserve(300);

	v1.push_back("123");
	v1.push_back("123");
	v1.push_back("123");
	v1.push_back("123");
	v1.push_back("123");
	
	v2.push_back("123");
	v2.push_back("123");
	v2.push_back("123");
	v2.push_back("123");
	v2.push_back("123");

	printv(v1);
	printv(v2);
	
	std::cerr << "ENDDDDDD" << std::endl;
	return (0);
}