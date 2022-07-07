#include "../src/map.hpp"

void test1(void) {
	ft::map<std::string, int> m;
	ft::map<std::string, int> m2 = m;

	m.insert(ft::make_pair("key1", 1));
	m.insert(ft::make_pair("key2", 2));
	m.insert(ft::make_pair("key3", 3));
	m.insert(ft::make_pair("key1", 11));

	ft::map<std::string, int> m3(m);

	ft::map<std::string, int> m4(m.begin(), m.end());

	ft::map<std::string, int>::iterator it1 = m.begin();
	ft::map<std::string, int>::iterator it2 = m.end();
	ft::map<std::string, int>::reverse_iterator rit1 = m.rbegin();
	ft::map<std::string, int>::reverse_iterator rit2 = m.rend();

	m2.insert(ft::make_pair("key1", 11));

	ft::map<std::string, int>::iterator ii2 = m2.begin();

	m2.insert(ii2, ft::make_pair("key2", 22));
	m2.insert(ii2, ft::make_pair("key3", 33));
	m2.insert(ii2, ft::make_pair("key4", 44));
	m2.insert(ii2, ft::make_pair("key5", 55));
	m2.insert(ii2, ft::make_pair("key6", 66));
	m2.insert(ii2, ft::make_pair("key7", 77));

	ft::map<std::string, int>::iterator xx = m2.begin();
	ft::map<std::string, int>::iterator yy = m2.end();

	while(xx != yy)
		xx++;

	while(xx != m2.begin())
		xx--;

	// ft::map<std::string, int> m5;

	// m5.insert(it1, it2);
	// m5.insert(m2.begin(), m2.end());

	// m5.print();

	// m5.erase(++(++m5.begin()), --m5.end());

	// m5.print();

	// m5["key5"] = 6666;

	// m5.print();

	// m5.swap(m2);

	// m2.find("key444");
	// m2.lower_bound("key1");
	// m2.lower_bound("key1333");
	// m2.upper_bound("key1");
	// m2.upper_bound("key3331");

	// m2.equal_range("key1");

	// m2.print();

}

int main( void ) {

	test1();

	while (1)
		;

	return 0;
}