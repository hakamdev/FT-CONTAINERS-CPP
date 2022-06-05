/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:22:11 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/04 19:46:45 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include <algorithm>
#include <iostream>
#include "random_access_iterator.hpp"
#include "reverse_random_access_iterator.hpp"
#include "traits.hpp"

namespace ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class vector {
		// member types
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename ft::racc_iterator<pointer>			iterator;
		typedef typename ft::racc_iterator<const_pointer>	const_iterator;
		typedef typename ft::rracc_iterator<iterator>		reverse_iterator;
		typedef typename ft::rracc_iterator<const_iterator>	const_reverse_iterator;
		typedef typename iterator::difference_type			difference_type;
		typedef size_t										size_type;

		private:
            pointer         _data;
            //
			size_type		_size;
			size_type		_capacity;
            //
			allocator_type	_alloc;
            pointer         _begin;
            pointer         _end;

			// private helper functions
			void _reallocate_and_copy_data( size_type _new_capacity ) {
				
			}

			void _init (size_type _initial_capacity) {
				// TODO: allocate memory for *_Data using alloc
                try {
                    _data = _alloc.allocate(_initial_capacity);
                } catch (std::bad_alloc& e) {
                    std::cerr << "bad_alloc: " << e.what() << std::endl;
                    exit(1);
                }
			}

		public:
			// constructors
			explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0) {
                // allocate memory (0)
                _init(_capacity);
                
                // reassign _begin & _end
                _begin = NULL;
                _end = NULL;
			}

			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _capacity(n), _size(0) {
                // allocate memory (n)
                _init(_capacity);
                
                // construct copies of (val) in the allocated space in (_data)
                for (size_type i = 0; i < n; ++i, ++_size) {
                    _alloc.construct(&_data[i], val);
                }
                
                // reassign _begin & _end
                _begin = _data;
                _end = _data[_size];
			}

            // enable_if only works if the condition inside its <> evaluates to true.
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type __t = InputIterator()) : _alloc(alloc), _size(0) {
                // convert the difference between (first) & (last) iterators into size_type
                _capacity = static_cast<size_type>(last - first);
 
                // allocate_memory (_capacity)
                _init(_capacity);
 
                // copy elements from first -> last
                for (; first < last; ++_size, ++first) {
                    _alloc.construct(&_data[_size], *first);
                }
                
                // reassign _begin & _end
                _begin = _data;
                _end = _data[_size];
			}
        
			vector (const vector& other) {
                *this = other;
            }

			vector& operator = (const vector& other) {
                this->_size = other._size;
                this->_capacity = other._capacity;
                this->_alloc = other._alloc;
                
                // allocate memory
                _init(_capacity);
                
                // copy elements from other->_data
                for (size_type i = 0; i < _size; ++i) {
                    _alloc.construct(&_data[i], other._data[i]);
                }
                
                // reassign _begin & _end
                _begin = _data;
                _end = _data[_size];
			}
			~vector() {
				// TODO: deallocate memory using alloc
			}
	
			// member functions
            iterator begin() {
                return iterator(_begin);
            }
            const_iterator begin() const {
                return iterator(_begin);
            }
            iterator end() {
                return iterator(_end);
            }
            const_iterator end() const {
                return const_iterator(_end);
            }
            reverse_iterator rbegin() {
                return reverse_iterator(end());
            }
            const_reverse_iterator rbegin() const {
                return const_reverse_iterator(end());
            }
            reverse_iterator rend() {
                return reverse_iterator(begin());
            }
            const_reverse_iterator rend() const {
                return const_reverse_iterator(begin());
            }
            size_type size() const {
                return static_cast<size_type>(end() - begin());
            }
            size_type max_size() const {
                return std::min<size_type>(_alloc.max_size(),
                            numeric_limits<difference_type>::max());
            }
            void resize (size_type n, value_type val = value_type()) {
                // TODO: Implement
            }
            size_type capacity() const {
                return _capacity;
            }
            bool empty() const {
                return _size == 0;
            }
            void reserve (size_type n) {
                // TODO: Implement
            }

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
  	void swap (vector< T, Alloc>& x, vector< T, Alloc>& y);

} // namespace ft
