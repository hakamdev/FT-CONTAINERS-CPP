/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_iterator.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 04:47:13 by ehakam            #+#    #+#             */
/*   Updated: 2022/04/17 02:21:32 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/random_access_iterator.hpp"
#include "../src/vector.hpp"
#include <iostream>
#include <set>
#include <string>
#include <vector>

//using namespace ft;

int main() {
	// std::set<int> s;
	// s.insert(5);
	// s.insert(6);
	// s.insert(7);
	// std::set<int>::iterator it = s.begin();
	// std::set<int>::iterator itend = s.end();
	// int xx[] = {1, 2, 3, 4};
	// std::vector<int> v(it, itend);
	// for (int x : v) {
	// 	std::cout << x << std::endl;
	// }

	int xx[] = {1, 2, 3};

	std::vector<int> vv(xx, xx + 3);

	std::vector<int>::iterator start = vv.begin();
	std::vector<int>::iterator end = vv.end();

	ft::vector<int> v(start, end);

	return (0);
}

// int main() {
// 	int *ptr = new int[10];
// 	for (int i = 0; i < 10; i++)
// 		ptr[i] = i;
// 	racc_iterator<int> rai(ptr);
// 	racc_iterator<int> rai1(rai);
// 	racc_iterator<int> rai2 = rai1;

// 	cout << boolalpha;

// 	cout << *(rai1 + 3) << endl;
// 	cout << *rai1 << endl;

// 	cout << *(rai1--) << endl;
// 	cout << *rai1 << endl;

// 	cout << (rai1 == rai) << endl;
// 	cout << (rai == rai1) << endl;
// 	cout << (rai1 == rai2) << endl;
// 	cout << (rai == rai2) << endl;

// 	return (0);
// }