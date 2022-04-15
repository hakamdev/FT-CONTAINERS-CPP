/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:41:32 by ehakam            #+#    #+#             */
/*   Updated: 2022/04/15 08:11:27 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>

using namespace std;

int main() {
	int arr[] = {1, 2, 3, 4, 5, 6};
	
	vector<int> v(arr, arr + 6);

	vector<int>::iterator it = v.begin();

	cout << v.capacity() << endl;
	cout << v.size() << endl;

	try {
		cout << *(it + 10000) << endl;
	} catch (std::exception& e) {
		cerr << "ERROR" << e.what() << endl;
	}

	// for (int vl : v) {
	// 	cout << vl << endl;
	// }
	
	return (0);
}