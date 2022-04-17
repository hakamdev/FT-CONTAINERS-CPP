/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:48:32 by ehakam            #+#    #+#             */
/*   Updated: 2022/04/17 01:34:24 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RANDOM_ACCESS_ITERATOR_HPP__
# define __RANDOM_ACCESS_ITERATOR_HPP__

# include "iterator.hpp"
# include <iterator>

namespace ft
{
	// random access iterator implementation.
	template	<typename T>
	struct racc_iterator : public ft::iterator<std::random_access_iterator_tag, T> {
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type  difference_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference		reference;

		private:
			pointer _ptr;
			// Make default constructor private
			// to ensure it won't be used outside
			// It's only here for the sh*tty canonical form.
			racc_iterator( void ) {}

		public:
			// Constructors / Destructor
			racc_iterator( pointer ptr ) : _ptr(ptr) {}
			racc_iterator( racc_iterator const & copy ) { *this = copy; }
			racc_iterator& operator = ( racc_iterator const & copy ) {
				this->_ptr = copy._ptr;
				return (*this);
			}
			~racc_iterator() {
				// the _ptr shouldn't be deleted here, because:
				// 1- it needs to be deleted by the allocator, there isn't one accessible from here.
				// 2- the original _ptr comes from the outside container, the container isn't necesserily deleted
				//		when the iterator is deleted.
			}

			// Overloaded operators
			bool operator == ( racc_iterator const & other ) {
				return (this->_ptr == other._ptr);
			}
			bool operator != ( racc_iterator const & other ) {
				return (this->_ptr != other._ptr);
			}
			bool operator < ( racc_iterator const & other ) {
				return (this->_ptr < other._ptr);
			}
			bool operator > ( racc_iterator const & other ) {
				return (this->_ptr > other._ptr);
			}
			bool operator <= ( racc_iterator const & other ) {
				return (this->_ptr <= other._ptr);
			}
			bool operator >= ( racc_iterator const & other ) {
				return (this->_ptr >= other._ptr);
			}
			reference operator * () {
				return (*this->_ptr);
			}
			racc_iterator& operator ++ () {
				++this->_ptr;
				return (*this);
			}
			racc_iterator operator ++ ( int ) {
				racc_iterator<T> old(*this);
				++this->_ptr;
				return (old);
			}
			racc_iterator& operator -- () {
				--this->_ptr;
				return (*this);
			}
			racc_iterator operator -- ( int ) {
				racc_iterator<T> old(*this);
				--this->_ptr;
				return (old);
			}
			racc_iterator operator + ( int n ) {
				return (racc_iterator<T>(this->_ptr + n));
			}
			racc_iterator operator - ( int n ) {
				return (racc_iterator<T>(this->_ptr - n));
			}
			difference_type operator - ( 
			racc_iterator const & other ) {
				return (this->_ptr - other._ptr);
			}
			racc_iterator& operator += ( int n ) {
				this->_ptr += n;
				return (*this);
			}
			racc_iterator& operator -= ( int n ) {
				this->_ptr -= n;
				return (*this);
			}
			reference operator [] ( int n ) {
				return (this->_ptr[n]);
			}
	};

	template <typename T>
	racc_iterator<T> operator + ( int n, 
		racc_iterator<T> const & other ) {
		return (other + n);
	}

} // namespace ft

#endif // __RANDOM_ACCESS_ITERATOR_HPP__