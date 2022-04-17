/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:48:11 by ehakam            #+#    #+#             */
/*   Updated: 2022/04/17 01:27:28 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ITERATOR_HPP__
# define __ITERATOR_HPP__

#include "stddef.h"

namespace ft {
	// iterator base class
	// Used sturct because members are public by default.
	template <typename Category,
			typename T,
			typename Distance = ptrdiff_t,
			typename Pointer = T*,
			typename Reference = T&>
	struct iterator {
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};
}

#endif // __ITERATOR_HPP__