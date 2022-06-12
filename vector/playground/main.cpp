/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:41:32 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/11 21:28:24 by ehakam           ###   ########.fr       */
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
	std::cout << "===============================" << std::endl;
}

int main() {
	
	int arr[] = {0, 1, 2, 3, 4};

	ft::vector<int> v1(arr, arr + 5);

	std::vector<int> v2(v1.rbegin(), v1.rend() - 2);

	printv(v1);
	printv(v2);
	
	std::cerr << "ENDDDDDD" << std::endl;
	return (0);
}