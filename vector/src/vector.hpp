/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:22:11 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/13 16:23:36 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>
#include <memory>
#include <algorithm>
#include <iostream>
#include "random_access_iterator.hpp"
#include "reverse_random_access_iterator.hpp"
#include "traits.hpp"
#include "algorithms.hpp"

namespace ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class vector {
        public:
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
			allocator_type	_alloc;
            size_type   _capacity;
            pointer     _begin;
            pointer     _end;

			void _init (size_type initial_capacity) {
                try {
                    this->_begin = _alloc.allocate(initial_capacity);
                } catch (std::bad_alloc& e) {
                    std::cerr << "bad_alloc: " << e.what() << std::endl;
                    exit(1);
                }
			}
            void _reallocate(size_type new_capacity) {
                pointer _new_begin = this->_alloc.allocate(new_capacity);

                // Copy data and delete
                size_type i = 0;
                for (; i < size(); ++i) {
                    this->_alloc.construct(&_new_begin[i], this-> _begin[i]);
                    this->_alloc.destroy(&this->_begin[i]);
                }

                // Clean old data
                this->_alloc.deallocate(this->_begin, this->_capacity);

                // reassign _begin & _end & _capacity
                this->_begin = _new_begin;
                this->_end = this->_begin + i;
                this->_capacity = new_capacity;
            }

		public:
			// constructors
            // GOOD //
			explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _capacity(0) {
                std::cerr << "DEF CONST " << std::endl;
                this->_end = this->_begin = NULL;
			}

            // GOOD //
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _capacity(n) {
                std::cerr << "N VAL CONST " << std::endl;
                // allocate memory (n)
                _init(this->_capacity);

                // construct copies of (val) in the allocated space in (_begin)
                size_type i = 0;
                for (; i < n; ++i) {
                    this->_alloc.construct(&this->_begin[i], val);
                }

                // // reassign _end
                this->_end = this->_begin + i;
			}

            // GOOD //
			template <class InputIterator>
			vector (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
                InputIterator last, const allocator_type& alloc = allocator_type()) : _alloc(alloc) {

                std::cerr << "ITER CONST " << std::endl;
                // convert the difference between (first) & (last) iterators into size_type
                difference_type _diff = last - first;
                if (_diff < 0) throw std::length_error("length between first and last is a negative value");
                this->_capacity = static_cast<size_type>(_diff);
 
                // allocate_memory (_capacity)
                _init(this->_capacity);
 
                // copy elements from first -> last
                size_type i = 0;
                for (; first < last; ++i, ++first) {
                    this->_alloc.construct(&this->_begin[i], *first);
                }

                // reassign _end
                this->_end = this->_begin + i;
			}

            // GOOD //
			vector (const vector& other) {
                std::cerr << "CPY CONST " << std::endl;
                *this = other;
            }

            // GOOD //
            vector& operator = (const vector& other) {
                std::cerr << "= CONST " << std::endl;
                this->_capacity = other.size();
                this->_alloc = other.get_allocator();
                this->_end = this->_begin = NULL;

                if (this->_capacity <= 0) return (*this);

                // allocate memory
                _init(this->_capacity);
                
                // // copy elements from other->_begin
                size_type i = 0;
                for (; i < other.size(); ++i) {
                    this->_alloc.construct(&(this->_begin[i]), other._begin[i]);
                }

                // // _end
                this->_end = this->_begin + i;
                return (*this);
			}

			// GOOD //
			~vector() {
                std::cerr << "DEST CONST " << std::endl;
				// clear & deallocate memory using alloc
                clear();
                this->_alloc.deallocate(this->_begin, this->_capacity);
			}

			// member functions
            // GOOD //
            iterator begin() {
                return iterator(this->_begin);
            }

            // GOOD //
            const_iterator begin() const {
                return iterator(this->_begin);
            }

            // GOOD //
            iterator end() {
                return iterator(this->_end);
            }

            // GOOD //
            const_iterator end() const {
                return const_iterator(this->_end);
            }

            // GOOD //
            reverse_iterator rbegin() {
                return reverse_iterator(end());
            }

            // GOOD //
            const_reverse_iterator rbegin() const {
                return const_reverse_iterator(end());
            }

            // GOOD //
            reverse_iterator rend() {
                return reverse_iterator(begin());
            }

            // GOOD //
            const_reverse_iterator rend() const {
                return const_reverse_iterator(begin());
            }

            // GOOD //
            size_type size() const {
                return static_cast<size_type>(end() - begin());
            }

            // GOOD //
            size_type max_size() const {
                return std::min<size_type>(this->_alloc.max_size(), std::numeric_limits<difference_type>::max());
            }

            // GOOD //
            size_type capacity() const {
                return this->_capacity;
            }

            // GOOD //
            bool empty() const {
                return size() == 0;
            }

            // GOOD //
			reference operator[] (size_type n) {
                return this->_begin[n];
            }

            // GOOD //
			const_reference operator[] (size_type n) const {
                return this->_begin[n];
            }

            // GOOD //
			reference at (size_type n) {
                if (n >= size()) throw std::out_of_range("index_out_of_range: n is larger or equal to vector size.");
                return this->_begin[n];
            }

			// GOOD //
			const_reference at (size_type n) const {
                if (n >= size()) throw std::out_of_range("index_out_of_range: n is larger or equal to vector size.");
                return this->_begin[n];
            }

            // GOOD //
			reference front() {
                return this->_begin[0];
            }

            // GOOD //
			const_reference front() const {
                return this->_begin[0];
            }

            // GOOD //
			reference back() {
                return *(this->_end - 1);
            }

            // GOOD //
			const_reference back() const {
                return *(this->_end - 1);
            }

            // GOOD //
            void reserve(size_type n) {
                if (n <= this->_capacity) return ;
                if (n > max_size()) throw std::length_error("length_error: the requested size is larger than the max_size allowed.");
                _reallocate(n);
            }

			// GOOD //
            void resize(size_type n, value_type val = value_type()) {
                if (n > this->_capacity) {
                    reserve(n);
                }

                // would add new items with val, if n > size() || capacity)
                for(size_type i = size(); i < n; ++i) {
                    this->_alloc.construct(this->_begin + i, val);
                }

                // would destroy elements beyond n if n < size()
                for(size_type i = n; i < size(); ++i) {
                    this->_alloc.destroy(&this->_begin[i]);
                }

                this->_end = this->_begin + n;
            }

			// GOOD //
			template <class InputIterator>
  			void assign(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
                InputIterator last) {
                difference_type _diff = last - first;
                if (_diff < 0) throw std::length_error("length between first and last is a negative value");

                size_type   _dist = static_cast<size_type>(_diff);
                // Clear previous content
                clear();

                // Reallocate if necessary
                if (_dist > this->_capacity) {
                    reserve(_dist);
                }

                // Copy new content from first -> last
                size_type i = 0;
                for (; first != last; ++i, ++first) {
					this->_begin[i] = *first;
                }

                this->_end = this->_begin + i;
            }

			// GOOD //
			void assign(size_type n, const value_type& val) {
                // Clear previous content
                clear();

                // Reallocate if necessary
                if (n > this->_capacity) {
                    reserve(n);
                }

                // Copy new content from first -> last
                size_type i = 0;
                for (; i < n; ++i) {
					this->_begin[i] = val;
				}

                this->_end = this->_begin + i;
            }

			// GOOD //
			void push_back(const value_type& val) {
                if (this->_capacity == 0 || size() >= this->_capacity) {
                    size_type _new_capacity = this->_capacity > 0 ? (this->_capacity * 2) : 1;
                    reserve(_new_capacity);
                }
                this->_alloc.construct(this->_end, val);
                ++this->_end;
            }

			// GOOD //
			void pop_back() {
                if (empty()) return;
                this->_alloc.destroy(this->_end - 1);
                --this->_end;
            }

			// GOOD //
			template <class InputIterator>
    		void insert (iterator position,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
                InputIterator last) {
                difference_type _diff = last - first;
                if (_diff < 0) return;
				//throw std::length_error("length between first and last is a negative value");

                size_type   _index = static_cast<size_type>(position - begin());
                size_type   _dist = static_cast<size_type>(_diff);

				// Reallocate
                if (_index <= size() && size() + _dist > this->_capacity) {
                    size_type _new_capacity = this->_capacity * 2;
                    if (_new_capacity < size() + _dist) _new_capacity = size() + _dist;
                    reserve(_new_capacity);
                }
				
				// Move items to make space for new items
                for(size_type i = size() - 1; i >= _index; --i) {
                    this->_alloc.construct(this->_begin + (i + _dist), this->_begin[i]);
                    this->_alloc.destroy(&this->_begin[i]);
					if (i == 0) break;
                }

				// Consturct new items in place
				for (size_type i = _index; first != last; ++first, ++i) {
					this->_alloc.construct(this->_begin + i, *first);
				}
                this->_end += _dist;
            }

			// GOOD //
            void insert (iterator position, size_type n, const value_type& val) {
                size_type   _index = static_cast<size_type>(position - begin());

				// Reallocate
                if (_index <= size() && size() + n > this->_capacity) {
                    size_type _new_capacity = this->_capacity * 2;
                    if (_new_capacity < size() + n)
						_new_capacity = size() + n;
                    reserve(_new_capacity);
                }

				// Move items to make space for new items
                for(size_type i = size() - 1; i >= _index; i--) {
                    this->_alloc.construct(this->_begin + (i + n), this->_begin[i]);
                    this->_alloc.destroy(&this->_begin[i]);
					if (i == 0) break;
                }

				// Consturct new items in place
				for (size_type i = _index, counter = 0; counter < n; ++counter, ++i) {
					this->_alloc.construct(this->_begin + i, val);
				}
                this->_end += n;
            }

			// GOOD //
			iterator insert (iterator position, const value_type& val) {
                size_type   _index = static_cast<size_type>(position - begin());
				// Reallocate
				if (_index <= size() && size() >= this->_capacity) {
                    reserve(this->_capacity * 2);
                }
				// Move items after position 
				for(size_type i = size() - 1; i >= _index; --i) {
                    this->_alloc.construct(this->_begin + (i + 1), this->_begin[i]);
                    this->_alloc.destroy(&this->_begin[i]);
					if (i == 0) break;
                }
				// insert item in place
				this->_alloc.construct(this->_begin + _index, val);
                this->_end += 1;
                return (iterator(this->_begin + _index));
            }

			// GOOD //
			iterator erase (iterator position) {
                size_type   _index = static_cast<size_type>(position - begin());

                this->_alloc.destroy(&this->_begin[_index]);
				
                for(size_type i = _index, j = _index + 1; j < size(); ++i, ++j) {
                    this->_alloc.construct(this->_begin + i, this->_begin[j]);
                    this->_alloc.destroy(&this->_begin[j]);
                }

				this->_end -= 1;
                return (iterator(this->_begin + _index));
            }

			// GOOD //
			iterator erase (iterator first, iterator last) {
                size_type   _index = static_cast<size_type>(first - begin());
                size_type   _diff = static_cast<size_type>(last - first);

                // Destroy desired items
                for(size_type i = _index; i < _index + _diff; ++i) {
                    this->_alloc.destroy(&this->_begin[i]);
                }
                // Move items back to fill the destroyed space
                for(size_type i = _index, j = _index + _diff; j < size(); ++i, ++j) {
                    this->_alloc.construct(this->_begin + i, this->_begin[j]);
                    this->_alloc.destroy(&this->_begin[j]);
                }
				
                this->_end -= _diff;
                return (iterator(this->_begin + _index));
            }

			// GOOD //
			void swap (vector<T, Alloc>& x) {
                size_type       _tmp_capacity = x._capacity;
                allocator_type  _tmp_alloc = x._alloc;
                pointer         _tmp_begin = x._begin;
                pointer         _tmp_end = x._end;

                x._capacity = this->_capacity;
                x._alloc = this->_alloc;
                x._begin = this->_begin;
                x._end = this->_end;

                this->_capacity = _tmp_capacity;
                this->_alloc = _tmp_alloc;
                this->_begin = _tmp_begin;
                this->_end = _tmp_end;
            }

			// GOOD //
            void clear() {
                for(size_type i = 0; i < size(); ++i) {
                    this->_alloc.destroy(&this->_begin[i]);
                }
                this->_end = this->_begin;
            }

			// GOOD //
			allocator_type get_allocator() const {
                return _alloc;
            }
	};

	// GOOD //
	template <class T, class Alloc>
	bool operator == (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

	// GOOD //
	template <class T, class Alloc>
	bool operator != (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return !(lhs == rhs);
    }

	// GOOD //
	template <class T, class Alloc>
	bool operator < (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

	// GOOD //
	template <class T, class Alloc>
	bool operator <= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return !(lhs > rhs);
    }

	// GOOD //
	template <class T, class Alloc>
	bool operator > (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return rhs < lhs;
    }

	// GOOD //
	template <class T, class Alloc>
	bool operator >= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return !(lhs < rhs);
    }

	// GOOD //
	template <class T, class Alloc>
  	void swap (vector< T, Alloc>& x, vector< T, Alloc>& y) {
        x.swap(y);
    }

} // namespace ft
