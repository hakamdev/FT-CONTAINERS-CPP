/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:45:19 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/30 21:29:17 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_HPP__
# define __MAP_HPP__

# include <memory>
# include <utility>
# include <functional>
# include "bidirectional_iterator.hpp"
# include "reverse_bidirectional_iterator.hpp"
# include "avl_tree.hpp"

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
			typedef ft::avl_tree<Key, T, Compare, Alloc>		tree;
			typedef typename allocator_type::reference			reference;
            typedef typename allocator_type::const_reference	const_reference;
            typedef typename allocator_type::pointer			pointer;
            typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename tree::node_pointer					node_pointer;
			typedef ft::bidir_iterator<tree>   					iterator;
			typedef ft::bidir_iterator<const tree> 				const_iterator;
			typedef ft::rbidir_iterator<iterator>				reverse_iterator;
			typedef ft::rbidir_iterator<const_iterator>			const_reverse_iterator;
			typedef size_t										size_type;

		private:
			allocator_type		_alloc;
			tree				_tree;
			key_compare			_comp;

		public:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc) {
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

			iterator begin() {
				return iterator(_tree.min_node(), _tree.root());
			}

			const_iterator begin() const {
				return const_iterator(_tree.min_node(), _tree.root());
			}

			iterator end() {
				return iterator(NULL, _tree.root());
			}

			const_iterator end() const {
				return const_iterator(NULL, _tree.root());
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

			bool empty() const {
				return _tree.empty();
			}
			
			size_type size() const {
				return _tree.size();
			}
			
			size_type max_size() const {
				return this->_alloc.max_size();
			}
			
			mapped_type& operator[] (const key_type& k) {
				node_pointer _p = _tree.find(k);
				if (_p == NULL) {
					_p = _tree.insert(std::make_pair(k, mapped_type()));
				}
				return _p->content->second;
			}

			// TMEPORARY
			iterator findNode (const key_type& k) {
				node_pointer _p = _tree.find(k);
				return iterator(_p, _tree.root());
			}

			allocator_type get_allocator() const {
				return _alloc;
			}

			std::pair<iterator, bool> insert (const value_type& val) {
				size_type old_size = _tree.size();
				node_pointer _p = _tree.insert(val);
				return std::make_pair(iterator(_p, _tree.root()), _tree.size() > old_size);
			}

			iterator insert (iterator position, const value_type& val) {
				node_pointer p = NULL;
				if (position.base() == position.past_end()
					|| position.base()->parent == NULL) {
					p = _tree.insert(val);
				} else {
					p = _tree.insert(position.base(), val);
				}
				return iterator(p, _tree.root());
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last);

			void erase (iterator position);

			size_type erase (const key_type& k) {
				return _tree.delete_node(k);
			}

     		void erase (iterator first, iterator last);

			void swap (map& x);

			void clear();

			key_compare key_comp() const;

			// value_compare value_comp() const;
			iterator find (const key_type& k);
			const_iterator find (const key_type& k) const;
			size_type count (const key_type& k) const;
			iterator lower_bound (const key_type& k);
			const_iterator lower_bound (const key_type& k) const;
			iterator upper_bound (const key_type& k);
			const_iterator upper_bound (const key_type& k) const;
			std::pair<const_iterator, const_iterator> equal_range (const key_type& k) const;
			std::pair<iterator, iterator>             equal_range (const key_type& k);

			//////
			void print() {
				_tree.printTree();
			}
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
