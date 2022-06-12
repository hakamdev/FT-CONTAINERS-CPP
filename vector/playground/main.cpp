/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:41:32 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/12 20:56:58 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <algorithm>
#include "../src/algorithms.hpp"
#include "../src/vector.hpp"

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

	std::vector<int> v1(arr, arr + 5);
	std::vector<int> v2(arr2, arr2 + 5);

	std::cerr << std::boolalpha;
	std::cerr << "(v1 == v2) " << (v1 == v2) << std::endl;
	std::cerr << "(v1 != v2) " << (v1 != v2) << std::endl;
	std::cerr << "(v1 < v2) " << (v1 < v2) << std::endl;
	std::cerr << "(v1 > v2) " << (v1 > v2) << std::endl;
	std::cerr << "(v1 <= v2) " << (v1 <= v2) << std::endl;
	std::cerr << "(v1 >= v2) " << (v1 >= v2) << std::endl;
	return (0);
}