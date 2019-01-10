/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 21:42:53 by malexand          #+#    #+#             */
/*   Updated: 2019/01/12 14:22:57 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	show_eye(t_param *param)
{
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 6);
	{
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_double(param->graph->ctx, "eye x:", MIN_DOUBLE_POS_EYE,
			&param->eye[0], MAX_DOUBLE_POS_EYE, 2.0f, 0.2f);
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_double(param->graph->ctx, "eye y:", MIN_DOUBLE_POS_EYE,
			&param->eye[1], MAX_DOUBLE_POS_EYE, 2.0f, 0.2f);
		nk_layout_row_push(param->graph->ctx, 0.33f);
		nk_property_double(param->graph->ctx, "eye z:", MIN_DOUBLE_POS_EYE,
			&param->eye[2], MAX_DOUBLE_POS_EYE, 2.0f, 0.2f);
		nk_layout_row_end(param->graph->ctx);
	}
}

void	show_dir(t_param *param)
{
	char *str;

	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 6);
	{
		nk_layout_row_push(param->graph->ctx, 0.33f);
		str = ft_strjoin_free(ft_strdup("dir x: "), ft_dtoa(param->look[0], 2));
		nk_label(param->graph->ctx, str, NK_TEXT_ALIGN_CENTERED);
		ft_strdel(&str);
		nk_layout_row_push(param->graph->ctx, 0.33f);
		str = ft_strjoin_free(ft_strdup("dir y: "), ft_dtoa(param->look[1], 2));
		nk_label(param->graph->ctx, str, NK_TEXT_ALIGN_CENTERED);
		ft_strdel(&str);
		nk_layout_row_push(param->graph->ctx, 0.33f);
		str = ft_strjoin_free(ft_strdup("dir z: "), ft_dtoa(param->look[2], 2));
		nk_label(param->graph->ctx, str, NK_TEXT_ALIGN_CENTERED);
		ft_strdel(&str);
		nk_layout_row_end(param->graph->ctx);
	}
}

void	show_align(t_param *param)
{
	char *str;

	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 6);
	{
		nk_layout_row_push(param->graph->ctx, 0.33f);
		str = ft_strjoin_free(ft_strdup("align x: "),
			ft_dtoa(param->look[0], 2));
		nk_label(param->graph->ctx, str, NK_TEXT_ALIGN_CENTERED);
		ft_strdel(&str);
		nk_layout_row_push(param->graph->ctx, 0.33f);
		str = ft_strjoin_free(ft_strdup("align y: "),
			ft_dtoa(param->look[0], 2));
		nk_label(param->graph->ctx, str, NK_TEXT_ALIGN_CENTERED);
		ft_strdel(&str);
		nk_layout_row_push(param->graph->ctx, 0.33f);
		str = ft_strjoin_free(ft_strdup("align z: "),
			ft_dtoa(param->look[0], 2));
		nk_label(param->graph->ctx, str, NK_TEXT_ALIGN_CENTERED);
		ft_strdel(&str);
		nk_layout_row_end(param->graph->ctx);
	}
}

void	nukl_camera(t_param *param)
{
	if (nk_tree_push(param->graph->ctx, NK_TREE_NODE, "Eye", NK_MAXIMIZED))
	{
		show_eye(param);
		show_dir(param);
		show_align(param);
		nk_tree_pop(param->graph->ctx);
	}
}
