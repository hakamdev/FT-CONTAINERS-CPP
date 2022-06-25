/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:41:32 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/25 02:00:26 by ehakam           ###   ########.fr       */
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

	tr.insert(std::make_pair<std::string, int>("0", 100));
	tr.insert(std::make_pair<std::string, int>("1", 10));
	tr.insert(std::make_pair<std::string, int>("2", 20));
	tr.insert(std::make_pair<std::string, int>("3", 20));
	tr.insert(std::make_pair<std::string, int>("4", 20));
	tr.insert(std::make_pair<std::string, int>("5", 20));
	tr.insert(std::make_pair<std::string, int>("6", 20));
	tr.insert(std::make_pair<std::string, int>("7", 20));
	tr.insert(std::make_pair<std::string, int>("8", 20));
	tr.insert(std::make_pair<std::string, int>("9", 20));

	tr.printTree();

	return (0);
}