/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 21:42:49 by malexand          #+#    #+#             */
/*   Updated: 2019/01/12 16:00:58 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	global_settings_1(t_param *param)
{
	char *number;

	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 3);
	nk_layout_row_push(param->graph->ctx, 0.25f);
	nk_label(param->graph->ctx, "Anti aliasing:", NK_TEXT_RIGHT);
	nk_layout_row_push(param->graph->ctx, 0.6f);
	nk_slider_int(param->graph->ctx, MIN_ANTI_ALIASING,
		&param->macro.anti_aliasing, MAX_ANTI_ALIASING, STEP_ANTI_ALIASING);
	nk_layout_row_push(param->graph->ctx, 0.15f);
	number = ft_itoa(param->macro.anti_aliasing);
	nk_label(param->graph->ctx, number, NK_TEXT_CENTERED);
	ft_strdel(&number);
	nk_layout_row_end(param->graph->ctx);
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 3);
	nk_layout_row_push(param->graph->ctx, 0.25f);
	nk_label(param->graph->ctx, "Recursion:", NK_TEXT_RIGHT);
	nk_layout_row_push(param->graph->ctx, 0.6f);
	nk_slider_int(param->graph->ctx, MIN_RECURSION, &param->macro.recursion,
		MAX_RECURSION, STEP_RECURSION);
	nk_layout_row_push(param->graph->ctx, 0.15f);
	number = ft_itoa(param->macro.recursion);
	nk_label(param->graph->ctx, number, NK_TEXT_CENTERED);
	ft_strdel(&number);
	nk_layout_row_end(param->graph->ctx);
}

void	global_settings_2(t_param *param)
{
	char *number;

	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 3);
	nk_layout_row_push(param->graph->ctx, 0.25f);
	nk_label(param->graph->ctx, "Cartoon factor:", NK_TEXT_RIGHT);
	nk_layout_row_push(param->graph->ctx, 0.6f);
	nk_slider_int(param->graph->ctx, MIN_CARTOON_FACTOR,
		&param->macro.cartoon_factor, MAX_CARTOON_FACTOR, STEP_CARTOON_FACTOR);
	nk_layout_row_push(param->graph->ctx, 0.15f);
	number = ft_itoa(param->macro.cartoon_factor);
	nk_label(param->graph->ctx, number, NK_TEXT_CENTERED);
	ft_strdel(&number);
	nk_layout_row_end(param->graph->ctx);
	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 3);
	nk_layout_row_push(param->graph->ctx, 0.25f);
	nk_label(param->graph->ctx, "Blur radius:", NK_TEXT_RIGHT);
	nk_layout_row_push(param->graph->ctx, 0.6f);
	nk_slider_int(param->graph->ctx, MIN_BLUR_RADIUS,
		&param->macro.blur_radius, MAX_BLUR_RADIUS, STEP_BLUR_RADIUS);
	nk_layout_row_push(param->graph->ctx, 0.15f);
	number = ft_itoa(param->macro.blur_radius);
	nk_label(param->graph->ctx, number, NK_TEXT_CENTERED);
	ft_strdel(&number);
	nk_layout_row_end(param->graph->ctx);
}

void	global_settings_3(t_param *param)
{
	char	*number;

	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 3);
	nk_layout_row_push(param->graph->ctx, 0.25f);
	nk_label(param->graph->ctx, "Rotation:", NK_TEXT_RIGHT);
	nk_layout_row_push(param->graph->ctx, 0.6f);
	nk_slider_int(param->graph->ctx, MIN_ROTATION_ANGLE,
		&param->macro.rotation_angle, MAX_ROTATION_ANGLE, STEP_ROTATION_ANGLE);
	nk_layout_row_push(param->graph->ctx, 0.15f);
	number = ft_itoa(param->macro.rotation_angle);
	nk_label(param->graph->ctx, number, NK_TEXT_CENTERED);
	ft_strdel(&number);
	nk_layout_row_end(param->graph->ctx);
}

void	global_settings_4(t_param *param)
{
	char *number;

	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 3);
	{
		nk_layout_row_push(param->graph->ctx, 0.25f);
		nk_label(param->graph->ctx, "K Ambience:", NK_TEXT_RIGHT);
		nk_layout_row_push(param->graph->ctx, 0.6f);
		nk_slider_float(param->graph->ctx, MIN_K_AMBIENCE,
			&param->macro.k_ambience, MAX_K_AMBIENCE, STEP_K_AMBIENCE);
		nk_layout_row_push(param->graph->ctx, 0.15f);
		number = ft_dtoa(param->macro.k_ambience, 2);
		nk_label(param->graph->ctx, number, NK_TEXT_CENTERED);
		ft_strdel(&number);
	}
	nk_layout_row_end(param->graph->ctx);
}

void	global_settings_filters(t_param *param)
{
	int						tmp_filter;
	const char				*filter[7] = {
								"None",
								"Cartoon",
								"Greyscale",
								"Sepia",
								"Blur",
								"Stéréoscopie",
								"Négatif"};
	const struct nk_vec2	size_button = {470.0, 150.0};

	nk_layout_row_begin(param->graph->ctx, NK_DYNAMIC, 30, 1);
	nk_layout_row_push(param->graph->ctx, 1.0f);
	tmp_filter = nk_combo(param->graph->ctx, filter, 7,
		param->macro.filter, 30, size_button);
	if (param->macro.filter != tmp_filter)
	{
		param->macro.filter = tmp_filter;
		param->up_img.post_process = TRUE;
	}
	nk_layout_row_end(param->graph->ctx);
}
