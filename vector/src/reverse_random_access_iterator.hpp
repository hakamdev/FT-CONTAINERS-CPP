/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_random_access_iterator.hpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 05:34:16 by ehakam            #+#    #+#             */
/*   Updated: 2022/07/24 03:25:51 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __REVERSE_RANDOM_ACCESS_ITERATOR_HPP__
# define __REVERSE_RANDOM_ACCESS_ITERATOR_HPP__

# include "iterator.hpp"
# include "random_access_iterator.hpp"
# include "traits.hpp"
# include <iostream>

namespace ft
{
	// random access iterator implementation.
	template	<typename Iter>
	struct rracc_iterator : public ft::iterator<std::random_access_iterator_tag, Iter> {
			typedef Iter												iterator_type;
			typedef typename ft::iterator_traits<Iter>::value_type		value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type	difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer			pointer;
			typedef typename ft::iterator_traits<Iter>::reference		reference;

		private:
			iterator_type _base;

		public:
			// constructors / destructor
			rracc_iterator( void ) : _base() {}
			rracc_iterator( iterator_type base ) : _base(base) {}
			template <typename T2>
			rracc_iterator( rracc_iterator<T2> const & copy ) {
				this->_base = copy.base();
			}
			rracc_iterator( rracc_iterator const & copy ) { *this = copy; }
			rracc_iterator& operator = ( rracc_iterator const & copy ) {
				this->_base = copy._base;
				return (*this);
			}
			~rracc_iterator() {}
			iterator_type base() const { return _base; }

			// overloaded operators
			bool operator == ( rracc_iterator const & other ) {
				return (this->_base == other._base);
			}
			bool operator != ( rracc_iterator const & other ) {
				return (this->_base != other._base);
			}
			bool operator < ( rracc_iterator const & other ) {
				return (this->_base > other._base);
			}
			bool operator > ( rracc_iterator const & other ) {
				return (this->_base < other._base);
			}
			bool operator <= ( rracc_iterator const & other ) {
				return (this->_base >= other._base);
			}
			bool operator >= ( rracc_iterator const & other ) {
				return (this->_base <= other._base);
			}
			reference operator * () {
				iterator_type _correct = this->_base - 1;
				return (*_correct);
			}
			pointer operator-> () {
				return &(operator*());
			}
			rracc_iterator& operator ++ () {
				--this->_base;
				return (*this);
			}
			rracc_iterator operator ++ ( int ) {
				rracc_iterator<iterator_type> old(*this);
				--this->_base;
				return (old);
			}
			rracc_iterator& operator -- () {
				++this->_base;
				return (*this);
			}
			rracc_iterator operator -- ( int ) {
				rracc_iterator<iterator_type> old(*this);
				++this->_base;
				return (old);
			}
			rracc_iterator operator + ( int n ) {
				return (rracc_iterator<iterator_type>(this->_base - n));
			}
			rracc_iterator operator - ( int n ) {
				return (rracc_iterator<iterator_type>(this->_base + n));
			}
			difference_type operator - ( rracc_iterator const & other ) {
				return (other.base() - this->base());
			}
			rracc_iterator& operator += ( int n ) {
				this->_base -= n;
				return (*this);
			}
			rracc_iterator& operator -= ( int n ) {
				this->_base += n;
				return (*this);
			}
			reference operator [] ( int n ) {
				return (*(*this + n));
			}
	};

	template <typename Iter>
	rracc_iterator<Iter> operator + ( int n, rracc_iterator<Iter>& other ) {
		return (other + n);
	}

	template <typename Iter>
	rracc_iterator<Iter> operator - ( int n, rracc_iterator<Iter>& other ) {
		return (other - n);
	}

} // namespace ft

#endif // __REVERSE_RANDOM_ACCESS_ITERATOR_HPP__