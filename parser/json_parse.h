/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parse.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 01:11:47 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/29 18:10:36 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_PARSE_H
# define JSON_PARSE_H

# include <json.h>

int		json_parse(char *json, t_jobject **obj);
char	*stringify(char *s);

#endif
