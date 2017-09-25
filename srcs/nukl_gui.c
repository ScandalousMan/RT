/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nukl_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malexand <malexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:04:37 by malexand          #+#    #+#             */
/*   Updated: 2017/09/25 14:11:25 by malexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tool.h"

void    nukl_gui(t_sdl *graph)
{
	if (nk_begin(graph->ctx, "RT UI", nk_rect(0, 0, 200, WINDOW_HEIGHT),
        NK_WINDOW_SCALE_LEFT))
    {
		nk_layout_space_begin(graph->ctx, NK_STATIC, 20, INT_MAX);
		nk_layout_space_push(graph->ctx, nk_rect(15,0,160,20));
        if (nk_button_label(graph->ctx, "REFRESH"))
            mprintf(1, "Refresh engaged\n");
		nk_layout_space_end(graph->ctx);
    }
    nk_end(graph->ctx);
}
