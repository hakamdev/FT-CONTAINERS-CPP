/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:41:32 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/11 20:02:35 by ehakam           ###   ########.fr       */
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
	//std::vector<int> v1(5, 100);
	ft::vector<int> v2(5, 100);
	std::cerr << "N VAL CONST 0" << std::endl;

	//printv(v1);
	printv(v2);

	return (0);
}