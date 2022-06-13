/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:21:45 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/13 18:24:23 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
	template<typename T>
	struct node {
		typedef T	value_type;
		value_type content;
		node<value_type> left;
		node<value_type> right;
	};
} // namespace ft
