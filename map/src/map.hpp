/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:45:19 by ehakam            #+#    #+#             */
/*   Updated: 2022/07/06 22:52:50 by ehakam           ###   ########.fr       */
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
# include "pair.hpp"
#include "algorithms.hpp"

namespace ft
{
	template < typename Key,                                     		// map::key_type
           typename T,                                       			// map::mapped_type
           typename Compare = std::less<Key>,                     		// map::key_compare
           typename Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
           >
	class map {
		public:
			typedef ft::pair<const Key, T> 							value_type;
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			typedef ft::avl_tree<Key, T, Compare, Alloc>			tree;
			typedef typename tree::node_type								node_type;
			typedef typename allocator_type::reference				reference;
            typedef typename allocator_type::const_reference		const_reference;
            typedef typename allocator_type::pointer				pointer;
            typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename tree::node_pointer						node_pointer;
			typedef typename tree::const_node_pointer				const_node_pointer;
			typedef ft::bidir_iterator<tree, node_pointer>   		iterator;
			typedef ft::bidir_iterator<tree, node_pointer>			const_iterator;
			typedef ft::rbidir_iterator<iterator>					reverse_iterator;
			typedef ft::rbidir_iterator<const_iterator>				const_reverse_iterator;
			typedef size_t											size_type;

			class value_compare;

		private:
			allocator_type		_alloc;
			tree				_tree;
			key_compare			_comp;
			value_compare		_v_comp;

		public:
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _comp(comp), _v_comp(comp) {}

			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				:  _alloc(alloc), _comp(comp), _v_comp(comp) {
				insert<InputIterator>(first, last);
			}

			// TEST
			map(const map& x) : _v_comp(_comp) {
				*this = x;
			}

			// TEST
			map& operator= (const map& x) {
				_comp = x._comp;
				_alloc = x._alloc;
				_tree = x._tree;
				_v_comp = x._v_comp;
				return *this;
			}

			~map() {
				// clear();
			 }

			iterator begin() {
				return _tree.begin();
			}

			const_iterator begin() const {
				return _tree.begin();
			}

			iterator end() {
				return _tree.end();
			}

			const_iterator end() const {
				return _tree.end();
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
					_p = _tree.insert(ft::make_pair(k, mapped_type()));
				}
				return _p->content->second;
			}

			allocator_type get_allocator() const {
				return _alloc;
			}

			ft::pair<iterator, bool> insert(const value_type& val) {
				size_type old_size = _tree.size();
				node_pointer _p = _tree.insert(val);
				return ft::make_pair(_tree.make_iterator(_p), _tree.size() > old_size);
			}

			iterator insert(iterator position, const value_type& val) {
				node_pointer p = NULL;
				if (empty()
					|| position.base() == position.past_end()
					|| position.base()->parent == NULL) {
					p = _tree.insert(val);
				} else {
					p = _tree.insert(position.base(), val);
				}
				return iterator(p, _tree.root());
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last) {
				while (first != last) {
					insert(*(first++));
				}
			}

			void erase(iterator position) {
				if (position.base() == position.past_end()) {
					_tree.delete_node(NULL);
				} else {
					_tree.delete_node(position.base());
				}
			}

			size_type erase(const key_type& k) {
				return _tree.delete_node(k, true);
			}

			void erase(iterator first, iterator last) {
				while (first != last) {
					erase(first++);
				}
			}

			void swap(map& x) {
				tree temp_tree = x._tree;
				allocator_type temp_alloc = x._alloc;
				key_compare temp_comp = x._comp;
				value_compare temp_v_comp = x._v_comp;

				x._tree = this->_tree;
				x._alloc = this->_alloc;
				x._comp = this->_comp;
				x._v_comp = this->_v_comp;

				this->_tree = temp_tree;
				this->_alloc = temp_alloc;
				this->_comp = temp_comp;
				this->_v_comp = temp_v_comp;
			}

			void clear() {
				_tree.delete_all();
			}

			key_compare key_comp() const {
				return _comp;
			}

			value_compare value_comp() const {
				return _v_comp;
			}

			iterator find(const key_type& k) {
				node_pointer found = _tree.find(k);
				return iterator(found, _tree.root());
			}

			const_iterator find(const key_type& k) const {
				node_pointer found = _tree.const_find(k);
				return const_iterator(found, _tree.root());
			}

			size_type count(const key_type& k) const {
				const_iterator it = find(k);
				return (it == end() ? 0 : 1);
			}

			iterator lower_bound(const key_type& k) {
				node_pointer lbp = _tree.lower_bound(k);
				return iterator(lbp, _tree.root());
			}

			const_iterator lower_bound (const key_type& k) const {
				node_pointer lbp = _tree.lower_bound(k);
				return const_iterator(lbp, _tree.root());
			}

			iterator upper_bound(const key_type& k) {
				node_pointer ubp = _tree.upper_bound(k);
				return iterator(ubp, _tree.root());
			}

			const_iterator upper_bound(const key_type& k) const {
				node_pointer ubp = _tree.upper_bound(k);
				return const_iterator(ubp, _tree.root());
			}

			ft::pair<iterator, iterator> equal_range(const key_type& k) {
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}

			ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}

			////// TODO: TEMPORARY
			void print() {
				_tree.printTree();
			}
	
	};

	template <typename Key, typename T, typename Compare, typename Alloc>
	class map<Key, T, Compare, Alloc>::value_compare : std::binary_function<value_type, value_type, bool>
	{
		friend class map;
		protected:
			Compare _comp;
			value_compare (Compare c) : _comp(c) {}
		public:
			bool operator() (const value_type& x, const value_type& y) const
			{
				return _comp(x.first, y.first);
			}
	};

	template <class Key, class T, class Compare, class Alloc>
  	bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs > rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return rhs < lhs;
	}
		
	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
  	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) {
		x.swap(y);
	}

} // namespace ft

#endif // __MAP_HPP__
