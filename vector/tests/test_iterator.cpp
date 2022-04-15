/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_iterator.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 04:47:13 by ehakam            #+#    #+#             */
/*   Updated: 2022/04/15 08:07:35 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/random_access_iterator.hpp"
#include <iostream>

using namespace ft;
using namespace std;

namespace hakam {
	template<typename T> class A {
		
	};

	template<> class A<bool> {
		
	};
}

hakam::A<int> a;

template<typename T> void func() {
	
}

int main() {
	int *ptr = new int[10];
	for (int i = 0; i < 10; i++)
		ptr[i] = i;
	racc_iterator<int> rai(ptr);
	racc_iterator<int> rai1(rai);
	racc_iterator<int> rai2 = rai1;

	func<int>();

	cout << boolalpha;

	cout << *(rai1 + 3) << endl;
	cout << *rai1 << endl;

	cout << *(rai1--) << endl;
	cout << *rai1 << endl;

	cout << (rai1 == rai) << endl;
	cout << (rai == rai1) << endl;
	cout << (rai1 == rai2) << endl;
	cout << (rai == rai2) << endl;

	return (0);
}