/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_array_object.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 01:10:09 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/26 01:11:17 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_ARRAY_OBJECT_H
# define PARSE_ARRAY_OBJECT_H

char	*parse_jobject(char *json, void **value);
char	*parse_jarray(char *json, void **value);

#endif
