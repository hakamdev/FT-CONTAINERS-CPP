/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:48:32 by ehakam            #+#    #+#             */
/*   Updated: 2022/07/24 03:25:31 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RANDOM_ACCESS_ITERATOR_HPP__
# define __RANDOM_ACCESS_ITERATOR_HPP__

# include "iterator.hpp"
# include "traits.hpp"
# include <iterator>

namespace ft
{
	// random access iterator implementation.
	template <typename Iter>
	struct racc_iterator : public ft::iterator<std::random_access_iterator_tag, Iter> {

			typedef Iter															iterator_type;
			typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
			typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
			typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
			typedef typename ft::iterator_traits<iterator_type>::reference			reference;

		private:
			iterator_type _base;

		public:
			// constructors / destructor
			racc_iterator( void ) : _base() {}
			racc_iterator( iterator_type base ) : _base(base) {}
			racc_iterator( racc_iterator<iterator_type> const & copy ) { *this = copy; }
			template <typename T2>
			racc_iterator( racc_iterator<T2> const & copy ) {
				this->_base = copy.base();
			}
			racc_iterator& operator = ( racc_iterator<Iter> const & copy ) {
				this->_base = copy.base();
				return (*this);
			}
			~racc_iterator() {}
			iterator_type base() const { return _base; }

			// overloaded operators
			bool operator == ( racc_iterator const & other ) {
				return (this->_base == other._base);
			}
			bool operator != ( racc_iterator const & other ) {
				return (this->_base != other._base);
			}
			bool operator < ( racc_iterator const & other ) {
				return (this->_base < other._base);
			}
			bool operator > ( racc_iterator const & other ) {
				return (this->_base > other._base);
			}
			bool operator <= ( racc_iterator const & other ) {
				return (this->_base <= other._base);
			}
			bool operator >= ( racc_iterator const & other ) {
				return (this->_base >= other._base);
			}
			reference operator * () {
				return (*this->_base);
			}
			pointer operator-> () {
				return (this->_base);
			}
			racc_iterator& operator ++ () {
				++this->_base;
				return (*this);
			}
			racc_iterator operator ++ ( int ) {
				racc_iterator<Iter> old(*this);
				++this->_base;
				return (old);
			}
			racc_iterator& operator -- () {
				--this->_base;
				return (*this);
			}
			racc_iterator operator -- ( int ) {
				racc_iterator<Iter> old(*this);
				--this->_base;
				return (old);
			}
			racc_iterator operator + ( int n ) {
				return (racc_iterator<Iter>(this->_base + n));
			}
			racc_iterator operator - ( int n ) {
				return (racc_iterator<Iter>(this->_base - n));
			}	
			racc_iterator& operator += ( int n ) {
				this->_base += n;
				return (*this);
			}
			racc_iterator& operator -= ( int n ) {
				this->_base -= n;
				return (*this);
			}
			reference operator [] ( int n ) {
				return (this->_base[n]);
			}
			difference_type operator - ( racc_iterator const & other ) {
				return (this->_base - other._base);
			}
	};

	template <typename Iter>
	racc_iterator<Iter> operator + ( int n, racc_iterator<Iter>& other ) {
		return (other + n);
	}

	template <typename Iter>
	racc_iterator<Iter> operator - ( racc_iterator<Iter> const & lhs, racc_iterator<Iter> const & rhs ) {
		return (lhs.base() - rhs.base());
	}

} // namespace ft

#endif // __RANDOM_ACCESS_ITERATOR_HPP__
