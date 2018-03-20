/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_key_value.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 00:34:32 by jbouille          #+#    #+#             */
/*   Updated: 2018/03/20 18:53:13 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_KEY_VALUE_H
# define PARSE_KEY_VALUE_H

# include <json.h>

char	*get_key(char *json, t_jstring *key);
char	*get_value(char *json, t_jtype *type, void **value);
char	*parse_key_value(char *json, t_jobject **obj);
char	*extract_string(char *s);

#endif
