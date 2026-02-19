/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:54:18 by cpoulain          #+#    #+#             */
/*   Updated: 2026/02/19 10:54:19 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  H_UTILS_MATH_H
# define H_UTILS_MATH_H

#define __align_mask(_value, _power) ((__typeof__(_value))((_power)-1))

/** @brief Align @c _value to the next multiple of @c _power
 *  @warning This macro assumes _power is a power of 2. When using an arbitrary
 *           value, you must use @ref round_up instead.
 */
#define align_up(_value, _power) \
	((((_value)-1) | __align_mask(_value, _power)) + 1)

#endif