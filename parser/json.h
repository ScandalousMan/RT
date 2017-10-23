/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 10:13:19 by jbouille          #+#    #+#             */
/*   Updated: 2017/10/23 14:53:22 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_H
# define JSON_H

typedef enum		e_jtype
{
	JSTRING,
	JOBJECT,
	JARRAY,
	JBOOL,
	JNULL,
	JINT,
	JDOUBLE,
	JUNKNOWN
}					t_jtype;

typedef struct		s_jarray
{
	t_jtype			type;
	void			*value;
	struct s_array	*next;
}					t_jarray;

typedef enum		e_jbool
{
	FALSE = 0,
	TRUE = 1
}					t_jbool;

typedef char*		t_jstring;

//typedef NULL		t_jnull;

typedef struct		s_jobject
{
	t_jstring		key;
	t_jtype			type;
	void			*value;
	struct s_jobject	*next;
}					t_jobject;

/* FUNCTIONS */

char	*parse_jstring(char *json, void **value);

typedef struct		s_func_type
{
	t_jtype			type;
	char			*(*f)(char*,void**);
}					t_func_type;

const t_func_type	g_func_parse[1] = {
	{JSTRING, &parse_jstring}
};

#endif
