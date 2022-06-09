/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:22:11 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/09 23:33:02 by ehakam           ###   ########.fr       */
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
            // pointer         _begin;
            //
			size_type		_capacity;
            //
			allocator_type	_alloc;
            pointer         _begin;
            pointer         _end;

			void _init (size_type initial_capacity) {
				// TODO: allocate memory for *_Data using alloc
                try {
                    _begin = _alloc.allocate(initial_capacity);
                } catch (std::bad_alloc& e) {
                    std::cerr << "bad_alloc: " << e.what() << std::endl;
                    exit(1);
                }
			}

            // TODO: Move to private methods
            void _reallocate(size_type new_capacity) {
                size_type _current_size = size();
                // size_type _new_capacity =
                //     std::min<size_type>(this->_alloc.max_size(), this->_capacity * 2);
                pointer _new_begin = this->_alloc.allocate(new_capacity);

                // Copy data and delete
                size_type i = 0;
                for (; i < size(); ++i) {
                    this->_alloc.construct(&_new_begin[i],this-> _begin[i]);
                    this->_alloc.destroy(&this->_begin[i]);
                }

                // Clean old data
                this->_alloc.deallocate(this->_begin, this->_capacity);

                // reassign _begin & _begin & _end
                this->_begin = _new_begin;
                this->_capacity = new_capacity;
                //this->_begin = this->_begin;
                this->_end = this->_begin[i];
            }

		public:
			// constructors
			explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _capacity(0) {
                // allocate memory (0)
                _init(_capacity);

                // reassign _begin & _end
                this->_begin = NULL;
                this->_end = NULL;
			}

			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _capacity(n) {
                // allocate memory (n)
                _init(this->_capacity);

                // construct copies of (val) in the allocated space in (_begin)
                size_type i = 0;
                for (; i < n; ++i) {
                    this->_alloc.construct(&this->_begin[i], val);
                }

                // reassign _begin & _end
                // _begin = _begin;
                this->_end = this->_begin[i];
			}

			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type __t = InputIterator()) : _alloc(alloc) {
                // convert the difference between (first) & (last) iterators into size_type
                this->_capacity = static_cast<size_type>(last - first);
 
                // allocate_memory (_capacity)
                _init(this->_capacity);
 
                // copy elements from first -> last
                size_type i = 0;
                for (; first < last; ++i, ++first) {
                    this->_alloc.construct(&this->_begin[i], *first);
                }

                // reassign _begin & _end
                // _begin = _begin;
                this->_end = this->_begin[i];
			}
        
			vector (const vector& other) {
                *this = other;
            }

			vector& operator = (const vector& other) {
                this->_capacity = other._capacity;
                this->_alloc = other._alloc;
                
                // allocate memory
                _init(this->_capacity);
                
                // copy elements from other->_begin
                size_type i = 0;
                for (; i < size(); ++i) {
                    this->_alloc.construct(&this->_begin[i], other._begin[i]);
                }

                // reassign _begin & _end
                // _begin = _begin;
                this->_end = this->_begin[i];
			}

			~vector() {
				// TODO: deallocate memory using alloc
			}
	
			// member functions
            iterator begin() {
                return iterator(this->_begin);
            }

            const_iterator begin() const {
                return iterator(this->_begin);
            }
            
            iterator end() {
                return iterator(this->_end);
            }
            
            const_iterator end() const {
                return const_iterator(this->_end);
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
                return std::min<size_type>(this->_alloc.max_size(),
                            numeric_limits<difference_type>::max());
            }

            void resize(size_type n, value_type val = value_type()) {
                // TODO: Implement
            }
            
            size_type capacity() const {
                return this->_capacity;
            }

            bool empty() const {
                return size() == 0;
            }

            void reserve(size_type n) {
                // TODO: Implement
            }  

			reference operator[] (size_type n) {
                return this->_begin[n];
            }

			const_reference operator[] (size_type n) const {
                return this->_begin[n];
            }

			reference at (size_type n) {
                return this->_begin[n];
            }

			const_reference at (size_type n) const {
                return this->_begin[n];
            }

			reference front() {
                return this->_begin[0];
            }

			const_reference front() const {
                return this->_begin[0];
            }

			reference back() {
                return *(this->_end - 1);
            }

			const_reference back() const {
                return *(this->_end - 1);
            }

			template <class InputIterator>
  			void assign(InputIterator first, InputIterator last) {
                // TODO: implement
            }

			void assign(size_type n, const value_type& val) {
                // TODO: implement
            }

			void push_back(const value_type& val) {
                if (size() >= this->_capacity) {
                    size_type _new_capacity =
                        std::min<size_type>(this->_alloc.max_size(), this->_capacity * 2);
                    _reallocate(_new_capacity);
                }
                this->_alloc.construct(this->_end, val);
                ++this->_end;
            }

			void pop_back() {
                if (empty()) return;
                this->_alloc.destroy(this->_end - 1);
                --this->_end;
            }

			template <class InputIterator>
    		void insert (iterator position, InputIterator first, InputIterator last) {
                // TODO: implement
                size_type   _index = static_cast<size_type>(position - begin());
                // pointer     _p = this->_begin + _index;
                size_type   _diff = static_cast<size_type>(last - first);
                if (size() + _diff > this->_capacity) {
                    _reallocate();
                }

                for(size_type i = size() - 1; i >= _index; --i) {
                    this->_alloc.construct(this->_begin + (i + _diff), this->_begin[i]);
                     this->_alloc.destr
                }
            }

			iterator insert (iterator position, const value_type& val) {
                // TODO: implement
                pointer _p = this->_begin + (position - begin());
                
                
                
            }

    		void insert (iterator position, size_type n, const value_type& val) {
                // TODO: implement
                pointer _p = this->_begin + (position - begin());
            }

			iterator erase (iterator position) {
                // TODO: implement
            }

			iterator erase (iterator first, iterator last) {
                // TODO: implement
            }

			void swap (vector& x) {
                // TODO: implement
            }
			
            void clear() {
                // TODO: implement
            }

			allocator_type get_allocator() const {
                return _alloc;
            }
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
