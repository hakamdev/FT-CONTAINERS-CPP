/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 00:22:11 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/11 20:06:46 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include <algorithm>
#include <iostream>
#include "random_access_iterator.hpp"
#include "reverse_random_access_iterator.hpp"
#include "traits.hpp"
#include "algorithms.hpp"

//////////////////////
//////////////////////
//////////////////////
//////////////////////
// template<typename V>
// void printv(V v) {
// 	std::cout << "===============================" << std::endl;
// 	std::cout << "CAP   : " << v.capacity() << std::endl;
// 	std::cout << "SZE   : " << v.size() << std::endl;
// 	std::cout << "MX SZE: " << v.max_size() << std::endl;
	
// 	std::cout << "[ ";
// 	for(size_t i = 0; i < v.size(); ++i) {
// 		std::cout <<  v[i]; std::cout << (i < v.size() - 1 ? ", " : "");
// 	}
// 	std::cout << " ]" << std::endl;
// 	std::cout << "===============================" << std::endl;
// }
//////////////////////
//////////////////////
//////////////////////
//////////////////////


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
			allocator_type	_alloc;
            //
            size_type		_capacity;
            pointer         _begin;
            pointer         _end;

			void _init (size_type initial_capacity) {
				// TODO: allocate memory for *_data using alloc
                try {
                    this->_begin = _alloc.allocate(initial_capacity);
                } catch (std::bad_alloc& e) {
                    std::cerr << "bad_alloc: " << e.what() << std::endl;
                    exit(1);
                }
			}

            // TODO: Move to private methods
            void _reallocate(size_type new_capacity, bool copy = true) {
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
                this->_end = this->_begin[i];
                this->_capacity = new_capacity;
            }

		public:
			// constructors
			explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _capacity(0) {
                std::cerr << "DEF CONST " << std::endl;
                this->_end = this->_begin = NULL;
			}

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

			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type __t = InputIterator()) : _alloc(alloc) {
                std::cerr << "ITER CONST " << std::endl;
                // convert the difference between (first) & (last) iterators into size_type
                this->_capacity = static_cast<size_type>(last - first);
 
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

			vector (const vector& other) {
                std::cerr << "CPY CONST " << std::endl;
                *this = other;
            }

			vector& operator = (const vector& other) {
                std::cerr << "= CONST " << std::endl;
                this->_capacity = other._capacity;
                this->_alloc = other._alloc;
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

			~vector() {
                std::cerr << "DEST CONST " << std::endl;
				// clear & deallocate memory using alloc
                // clear();
                // this->_alloc.deallocate(this->_begin, this->_capacity);
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
                return std::min<size_type>(this->_alloc.max_size(), std::numeric_limits<difference_type>::max());
            }

            void resize(size_type n, value_type val = value_type()) {
                if (n > this->_capacity) {
                    _reallocate(n);
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

            size_type capacity() const {
                return this->_capacity;
            }

            bool empty() const {
                return size() == 0;
            }

            void reserve(size_type n) {
                if (n <= this->_capacity) return ;
                _reallocate(n);
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

			template <class InputIterator,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type>
  			void assign(InputIterator first, InputIterator last) {
                size_type   _diff = static_cast<size_type>(last - first);
                // Clear previous content
                clear();

                // Reallocate if necessary
                if (_diff > this->_capacity) {
                    _reallocate(_diff);
                }

                // Copy new content from first -> last
                size_type i = 0;
                for (; first != last; ++i, ++first) {
                    this->_alloc.construct(&this->_begin[i], *first);
                }

                this->_end = this->_begin + i;
            }

			void assign(size_type n, const value_type& val) {
                // Clear previous content
                clear();

                // Reallocate if necessary
                if (n > this->_capacity) {
                    _reallocate(n);
                }

                // Copy new content from first -> last
                size_type i = 0;
                for (; i < n; ++i) {
					this->_alloc.construct(this->_begin + i, val);
				}

                this->_end = this->_begin + i;
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

			template <class InputIterator, 
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type>
    		void insert (iterator position, InputIterator first, InputIterator last) {
                size_type   _index = static_cast<size_type>(position - begin());
                size_type   _diff = static_cast<size_type>(last - first);

				// Reallocate
                if (size() + _diff > this->_capacity) {
                    size_type _new_capacity = std::min<size_type>(this->_alloc.max_size(), this->_capacity * 2);
                    if (_new_capacity < size() + _diff) _new_capacity += _diff;
                    _reallocate(_new_capacity);
                    // this->_capacity = _new_capacity;
                }
				// Move items to make space for new items
                for(size_type i = size() - 1; i >= _index; --i) {
                    this->_alloc.construct(this->_begin + (i + _diff), this->_begin[i]);
                    this->_alloc.destroy(&this->_begin[i]);
                }
				// Consturct new items in place
				for (size_type i = _index; first != last; ++first, ++i) {
					this->_alloc.construct(this->_begin + i, *first);
				}
                this->_end += _diff;
            }

			iterator insert (iterator position, const value_type& val) {
                size_type   _index = static_cast<size_type>(position - begin());
				if (size() >= this->_capacity) {
                    size_type _new_capacity = std::min<size_type>(this->_alloc.max_size(), this->_capacity * 2);
                    _reallocate(_new_capacity);
                    // this->_capacity = _new_capacity;
                }
				for(size_type i = size() - 1; i >= _index; --i) {
                    this->_alloc.construct(this->_begin + (i + 1), this->_begin[i]);
                    this->_alloc.destroy(&this->_begin[i]);
                }
				this->_alloc.construct(this->_begin + _index, val);
                this->_end += 1;

                return (iterator(this->_begin + _index));
            }

    		void insert (iterator position, size_type n, const value_type& val) {
                size_type   _index = static_cast<size_type>(position - begin());

				// Reallocate
                if (size() + n > this->_capacity) {
                    size_type _new_capacity = std::min<size_type>(this->_alloc.max_size(), this->_capacity * 2);
                    if (_new_capacity < size() + n) _new_capacity += n;
                    _reallocate(_new_capacity);
                    // this->_capacity = _new_capacity;
                }

				// Move items to make space for new items
                for(size_type i = size() - 1; i >= _index; --i) {
                    this->_alloc.construct(this->_begin + (i + n), this->_begin[i]);
                    this->_alloc.destroy(&this->_begin[i]);
                }

				// Consturct new items in place
				for (size_type i = _index, counter = 0; counter < n; ++counter, ++i) {
					this->_alloc.construct(this->_begin + i, val);
				}

                this->_end += n;
            }

			iterator erase (iterator position) {
                size_type   _index = static_cast<size_type>(position - begin());

                this->_alloc.destroy(&this->_begin[_index]);
                for(size_type i = _index, j = _index + 1; j < size(); ++i, ++j) {
                    this->_alloc.construct(this->_begin + i, this->_begin[j]);
                    this->_alloc.destroy(&this->_begin[j]);
                }
                this->_end -= 1;
                
                return (iterator(this->_end + _index));
            }

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

                return (iterator(this->_end + _index));
            }

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

            void clear() {
                for(size_type i = 0; i < size(); ++i) {
                    this->_alloc.destroy(&this->_begin[i]);
                }
                this->_end = this->_begin;
            }

			allocator_type get_allocator() const {
                return _alloc;
            }
	};

	template <class T, class Alloc>
	bool operator == (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    
	template <class T, class Alloc>
	bool operator != (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return !(lhs == rhs);
    }

	template <class T, class Alloc>
	bool operator < (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

	template <class T, class Alloc>
	bool operator <= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        !(lhs > rhs);
    }

	template <class T, class Alloc>
	bool operator > (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return rhs < lhs;
    }

	template <class T, class Alloc>
	bool operator >= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        !(lhs < rhs);
    }

	template <class T, class Alloc>
  	void swap (vector< T, Alloc>& x, vector< T, Alloc>& y) {
        x.swap(y);
    }

} // namespace ft
