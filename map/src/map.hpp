/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:45:19 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/25 06:24:00 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_HPP__
# define __MAP_HPP__

# include <memory>
# include <utility>
# include <functional>
# include "bidirectional_iterator.hpp"
# include "reverse_bidirectional_iterator.hpp"

namespace ft
{
	template < typename Key,                                     		// map::key_type
           typename T,                                       			// map::mapped_type
           typename Compare = std::less<Key>,                     		// map::key_compare
           typename Alloc = std::allocator<std::pair<const Key,T> >    // map::allocator_type
           >
	class map {
		public:
			typedef std::pair<const Key, T> 					value_type;
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef Compare										key_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
            typedef typename allocator_type::const_reference	const_reference;
            typedef typename allocator_type::pointer			pointer;
            typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename  /* a bidirectional iterator to const value_type */ iterator;
			typedef typename /* a bidirectional iterator to const value_type */ const_iterator;
			typedef typename /* a reverse bidirectional iterator to iterator */ reverse_iterator;
			typedef typename /* a reverse bidirectional iterator to const_iterator */ const_reverse_iterator;
			typedef typename /*iterator::difference_type		*/	difference_type;
			typedef size_t										size_type;

		private:
			allocator_type		_alloc;

		public:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
				// TODO: 
			}
	
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
				// TODO: 
			}
				
			map (const map& x) {
				// TODO: 
			}

			map& operator = (const map& x) {
				// TODO: 
			}

			~map() {
				// TODO: 
			}
			
			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;
			bool empty() const;
			size_type size() const;
			size_type max_size() const;
			mapped_type& operator[] (const key_type& k);
			allocator_type get_allocator() const;

			pair<iterator,bool> insert (const value_type& val);
			iterator insert (iterator position, const value_type& val);
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last);

			void erase (iterator position);
			size_type erase (const key_type& k);
     		void erase (iterator first, iterator last);

			void swap (map& x);
			void clear();
			key_compare key_comp() const;
			value_compare value_comp() const;
			iterator find (const key_type& k);
			const_iterator find (const key_type& k) const;
			size_type count (const key_type& k) const;
			iterator lower_bound (const key_type& k);
			const_iterator lower_bound (const key_type& k) const;
			iterator upper_bound (const key_type& k);
			const_iterator upper_bound (const key_type& k) const;
			std::pair<const_iterator, const_iterator> equal_range (const key_type& k) const;
			std::pair<iterator, iterator>             equal_range (const key_type& k);

	};

	template <class Key, class T, class Compare, class Alloc>
  	bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

	template <class Key, class T, class Compare, class Alloc>
	bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );
		
	template <class Key, class T, class Compare, class Alloc>
	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );
		
	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

	template <class Key, class T, class Compare, class Alloc>
  	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y);

} // namespace ft

#endif // __MAP_HPP__
