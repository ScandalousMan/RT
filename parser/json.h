/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 10:13:19 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/23 13:28:45 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_H
# define JSON_H

typedef enum	e_jtype
{
	JSTRING,
	JOBJECT,
	JARRAY,
	JBOOL,
	JNULL,
	JINT,
	JDOUBLE
}				t_jtype;

typedef struct	s_jarray
{

}				t_jarray;

typedef enum	e_jbool
{
	FALSE,
	TRUE
}				t_jbool;

typedef char*	t_jstring;

typedef NULL	t_jnull;

typedef struct	s_jobject
{
	t_jstring		key;
	t_jtype			type;
	void			*value;
	struct s_object	next;
}				t_jobject;

#endif
