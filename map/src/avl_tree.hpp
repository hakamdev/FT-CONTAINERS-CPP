/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:21:45 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/20 22:32:26 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __AVL_TREE_HPP__
# define __AVL_TREE_HPP__


# include <memory>
# include <utility>
# include <functional>
# include "node.hpp"

namespace ft
{
	template <
           typename T,
           typename Compare,
           typename Alloc
           >
	class avl_tree {
		public:
			typedef T					value_type;
			typedef Alloc				allocator_type;
			typedef node<T, Alloc>		node_type;
			typedef Compare				key_compare;

		private:
			node_type	_root;

		public:
			avl_tree() {
				// TODO:
			}

			void insert(const value_type& val) {
				
			}
	};
} // namespace ft

#endif // __AVL_TREE_HPP__