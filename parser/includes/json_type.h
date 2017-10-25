/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_type.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 00:43:09 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/26 00:46:30 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_TYPE_H
# define JSON_TYPE_H

# include <json.h>

int		ft_isjint(char *json);
int		ft_isjdouble(char *json);
t_jtype	get_type(char *json);

#endif
