/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:41:32 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/24 21:10:28 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <stack>
#include <map>
#include <iostream>
#include <algorithm>
#include "../src/avl_tree.hpp"

int main() {

	// const int arr[] = {0, 1, 2, 3, 4};
	// const int arr2[] = {0, 1, 32, 3, 4};

	// std::map<std::string, int> m;

	// std::pair<std::string, int>("", 0);

	// std::make_pair<std::string, int>("", 0);

	ft::avl_tree<std::string, int> tr;

	tr.insert(std::make_pair<std::string, int>("7", 100));
	tr.insert(std::make_pair<std::string, int>("3", 10));
	tr.insert(std::make_pair<std::string, int>("9", 20));
	// tr.insert(std::make_pair<std::string, int>("5", 20));
	// tr.insert(std::make_pair<std::string, int>("8", 20));
	// tr.insert(std::make_pair<std::string, int>("9", 20));
	// tr.insert(std::make_pair<std::string, int>("1", 20));

	tr.printTree();

	// std::allocator<std::pair<std::string, int> > alloc;
	// std::pair<std::string, int> *p1 = alloc.allocate(1);
	// alloc.construct(p1, std::pair<std::string, int>("key", 100));

	return (0);
}