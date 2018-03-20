/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouille <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 10:13:19 by jbouille          #+#    #+#             */
/*   Updated: 2018/03/20 17:54:28 by jbouille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_H
# define JSON_H

typedef enum			e_jtype
{
	JSTRING,
	JOBJECT,
	JARRAY,
	JBOOL,
	JNULL,
	JINT,
	JDOUBLE,
	JUNKNOWN
}						t_jtype;

typedef struct			s_jarray
{
	t_jtype				type;
	void				*value;
	struct s_jarray		*next;
}						t_jarray;

typedef enum			e_jbool
{
	FALSE = 0,
	TRUE = 1
}						t_jbool;

typedef char*			t_jstring;
typedef int				t_jint;
typedef double			t_jdouble;

typedef struct			s_jobject
{
	t_jstring			key;
	t_jtype				type;
	void				*value;
	struct s_jobject	*next;
}						t_jobject;

/*
**		FUNCTIONS
*/
char					*parse_jstring	(char *json, void **value);
char					*parse_jobject	(char *json, void **value);
char					*parse_jarray	(char *json, void **value);
char					*parse_jint		(char *json, void **value);
char					*parse_jdouble	(char *json, void **value);
char					*parse_jbool	(char *json, void **value);
char					*parse_jnull	(char *json, void **value);

typedef struct			s_func_type
{
	t_jtype				type;
	char				*(*f)(char*, void**);
}						t_func_type;

#endif
