/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bidirectional_iterator.hpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 01:42:02 by ehakam            #+#    #+#             */
/*   Updated: 2022/07/24 03:23:37 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RBIDIR_ITER_HPP__
# define __RBIDIR_ITER_HPP__

# include <iterator>
# include "iterator.hpp"
# include "bidirectional_iterator.hpp"

namespace ft
{
	template <typename Iter>
	struct rbidir_iterator : public ft::iterator<std::bidirectional_iterator_tag, Iter> {
		
		typedef Iter									iterator_type;
		typedef typename iterator_type::value_type		value_type;
		typedef typename iterator_type::pointer			pointer;
		typedef typename iterator_type::reference		reference;

		private:
			iterator_type _base;

		public:
			// constructors / destructor
			rbidir_iterator( void ) : _base() {}

			rbidir_iterator( const iterator_type& base ) : _base(base) {}

			rbidir_iterator( const rbidir_iterator<iterator_type>& copy ) {
				*this = copy;
			}

			template<typename Iter2>
			rbidir_iterator( const rbidir_iterator<Iter2>& copy ) {
				this->_base = copy.base();
			}

			rbidir_iterator& operator = ( const rbidir_iterator<iterator_type>& copy ) {
				this->_base = copy.base();
				return (*this);
			}

			~rbidir_iterator() {}

			iterator_type base() const {
				return _base;
			}

			// overloaded operators
			bool operator == ( rbidir_iterator const & other ) {
				return (this->_base == other._base);
			}

			bool operator != ( rbidir_iterator const & other ) {
				return (this->_base != other._base);
			}

			reference operator * () {
				iterator_type _correct = this->_base;
				--_correct;
				return (*_correct);
			}

			pointer operator-> () {
				return &(operator*());
			}

			rbidir_iterator& operator ++ () {
				--this->_base;
				return (*this);
			}

			rbidir_iterator operator ++ ( int ) {
				rbidir_iterator<iterator_type> old(*this);
				--this->_base;
				return (old);
			}

			rbidir_iterator& operator -- () {
				++this->_base;
				return (*this);
			}

			rbidir_iterator operator -- ( int ) {
				rbidir_iterator<iterator_type> old(*this);
				++this->_base;
				return (old);
			}

	};
} // namespace ft

#endif // __BIDIR_ITER_HPP__
