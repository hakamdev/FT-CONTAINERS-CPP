/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traits.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:47:05 by ehakam            #+#    #+#             */
/*   Updated: 2022/07/06 18:24:01 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TRAITS_HPP__
# define __TRAITS_HPP__

# include <iterator>

namespace ft
{
	// for class iterators
	template <typename Iter>
	struct iterator_traits
	{
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
	};

	// pointers specialization
	template <typename Ptr>
	struct iterator_traits<Ptr*>
	{
		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef Ptr								value_type;
		typedef Ptr*							pointer;
		typedef Ptr&							reference;
	};

	// const pointers specialization
	template <typename Ptr>
	struct iterator_traits<const Ptr*>
	{
		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef Ptr								value_type;
		typedef const Ptr*						pointer;
		typedef const Ptr&						reference;
	};

} // namespace ft

#endif // __TRAITS_HPP__