/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 00:58:21 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/26 00:59:37 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_STRING_H
# define PARSE_STRING_H

char	*parse_jstring(char *json, void **value);
char	*parse_jbool(char *json, void **value);
char	*parse_jnull(char *json, void **value);

#endif
