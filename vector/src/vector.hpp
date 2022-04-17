/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:22:11 by ehakam            #+#    #+#             */
/*   Updated: 2022/04/17 02:35:11 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include <iostream>
#include "random_access_iterator.hpp"
#include "traits.hpp"

namespace ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class vector {
		// member types
		typedef T								value_type;
		typedef Alloc							allocator_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef typename ft::racc_iterator<value_type>			iterator;
		// typedef typename ft::racc_iterator<value_type>				const_iterator;
		// typedef typename ft::racc_iterator<value_type>			reverse_iterator;
		// typedef typename ft::racc_iterator<value_type>		const_reverse_iterator;
		typedef typename iterator::difference_type				difference_type;
		typedef size_t											size_type;

		private:
			value_type		*_data;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;

		public:
			// constructors
			explicit vector (const allocator_type& alloc = allocator_type()) _alloc(alloc) {
				// TODO: allocate memory for *_Data using alloc
				
				
			}
			explicit vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()) {
				// TODO: allocate memory for *_Data using alloc
				std::cout << "N CONS" << std::endl;
			}
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type t = InputIterator()) {
				// typename ft::iterator_traits<InputIterator>::reference p;
				// TODO: allocate memory for *_Data using alloc
				std::cout << "InputIterator CONS" << std::endl;
			}
			vector (const vector& other) {
				// TODO: copy the other vector
				std::cout << "COPY CONS" << std::endl;
			}
			vector& operator = (const vector& other) {
				// copy the other vector
			}
			~vector() {
				// TODO: deallocate memory using alloc
			}
	
			// member functions
			// iterator begin();
			// const_iterator begin() const;
			// iterator end();
			// const_iterator end() const;
			// reverse_iterator rbegin();
			// const_reverse_iterator rbegin() const;
			// reverse_iterator rend();
			// const_reverse_iterator rend() const;

			// size_type size() const;
			// size_type max_size() const;
			// void resize (size_type n, value_type val = value_type());
			// size_type capacity() const;
			// bool empty() const;
			// void reserve (size_type n);

			// reference operator[] (size_type n);
			// const_reference operator[] (size_type n) const;
			// reference at (size_type n);
			// const_reference at (size_type n) const;
			// reference front();
			// const_reference front() const;
			// reference back();
			// const_reference back() const;

			// template <class InputIterator>
  			// void assign (InputIterator first, InputIterator last);	
			// void assign (size_type n, const value_type& val);
			// void push_back (const value_type& val);
			// void pop_back();

			// template <class InputIterator>
    		// void insert (iterator position, InputIterator first, InputIterator last);
			// iterator insert (iterator position, const value_type& val);
    		// void insert (iterator position, size_type n, const value_type& val);	
			
			// iterator erase (iterator position);
			// iterator erase (iterator first, iterator last);
			// void swap (vector& x);
			// void clear();
			// allocator_type get_allocator() const;
	};

	template <class T, class Alloc>
	bool operator == (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool operator != (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool operator < (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool operator <= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool operator > (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool operator >= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
  	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);

} // namespace ft
