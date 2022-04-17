/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_iterator.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 04:47:13 by ehakam            #+#    #+#             */
/*   Updated: 2022/04/17 07:55:57 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/random_access_iterator.hpp"
#include "../src/reverse_random_access_iterator.hpp"
#include "../src/vector.hpp"
#include <iostream>
#include <set>
#include <string>
#include <vector>

//using namespace ft;

class Human {
	private:
		int age;
		std::string name;
	public:
		Human( void ) : age(0), name("DEFAULT NAME") {
			std::cout << "DEF CONS" << std::endl;
		}
		Human(int _age, std::string _name) : age(_age), name(_name) { 
			std::cout << "PARAM CONS" << std::endl;
		}
		Human( Human const & h ) { 
			std::cout << "COPY CONS" << std::endl;
			*this = h;
			print();
			std::cout << "---------" << std::endl;
		}
		Human& operator = ( Human const & h ) {
			std::cout << "COPY ASSIGN" << std::endl;
			age = h.age;
			name = h.name;
			return (*this);
		}
		~Human() {
			std::cout << "DESTR" << std::endl;
		}
		void print( void ) {
			std::cout << "AGE: " << age << " - NAME: " << name << std::endl;
		}
};

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

	int xx[] = {1, 2, 3, 4, 55, 66};

	std::vector<int> vv(xx, xx + 6);

	std::vector<int>::iterator it(xx);
	std::vector<int>::reverse_iterator rit(it);

	ft::racc_iterator<int*> myit(xx);
	ft::rracc_iterator< ft::racc_iterator<int*> > myrit(myit);

	std::cout << "IT" << std::endl;
	//std::cout << *it << std::endl;

	int n = -3;
	std::cout << (rit[n]) << std::endl;

	std::cout << "MY IT" << std::endl;	
	//std::cout << *myit << std::endl;
	std::cout << (myrit[n]) << std::endl;
	
	// std::cout << *it << std::endl;
	// std::cout << *rit << std::endl;

	// std::vector<Human> v;

	// Human *h1 = new Human(12, "Hamza");
	// //Human h3;

	// std::cout << "== END DECLARATION ==" << std::endl;

	// std::vector<Human> v2(3, *h1);
	// v2.push_back(*h1);
	// v.push_back(h3);

	// for (int i = 0; i < 30; ++i) {
	// 	std::cout << "CAP:  " << v.capacity() << std::endl;
	// 	std::cout << "SIZE: " << v.size() << std::endl;
	// 	v.push_back(i);
	// 	std::cout << "PUSHED: " << i << std::endl;
	// }
	// std::cout << "CAP:  " << v.capacity() << std::endl;
	// std::cout << "SIZE: " << v.size() << std::endl;
	// v.push_back(3);
	
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