
#ifndef __HUMAN_HPP__
# define __HUMAN_HPP__

#include <string>

class Human {
	private:
		int age;
		std::string name;

	public:
		Human( void ) : age(0), name("Human") {}
		Human(const int age, const std::string& name ) : age(age), name(name) {}
		Human(const Human& rhs ) {
			*this = rhs;
		}
		Human& operator= (const Human& rhs ) {
			this->age = rhs.age;
			this->name = rhs.name;
			return *this;
		}

		int getAge() const {
			return age;
		}

		std::string getName() const {
			return name;
		}

		void setAge(int age) {
			this->age = age;
		}

		void setName(std::string name) {
			this->name = name;
		}
};

#endif