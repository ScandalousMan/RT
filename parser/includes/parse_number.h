/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_number.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 00:51:55 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/26 00:53:00 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_NUMBER_H
# define PARSE_NUMBER_H

char	*parse_jdouble(char *json, void **value);
char	*parse_jint(char *json, void **value);

#endif
