/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saksoy <saksoy@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:32:24 by saksoy            #+#    #+#             */
/*   Updated: 2022/06/20 12:23:54 by saksoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minlbx.h"

void	putchr(t_win *pnc, int keycode)
{
	if (keycode == 2)
		pnc->chr->chr_cur = pnc->chr->chr_right;
	if (keycode == 0)
		pnc->chr->chr_cur = pnc->chr->chr_left;
	if (keycode == 13)
		pnc->chr->chr_cur = pnc->chr->chr_back;
	if (keycode == 1)
		pnc->chr->chr_cur = pnc->chr->chr_front;
}

void	print_score(t_win *pnc)
{
	ft_printf("%d\n", pnc->chr->point);
}

void	move_p(t_win *pnc, int side, int x, int y)
{
	if (pnc->map->cb == 0 && pnc->map->mappin[y / 64][x / 64] == 'E')
	{
		pnc->chr->point += 1;
		print_score(pnc);
		ft_printf("Win!");
		close_frame(pnc);
	}
	if (pnc->map->mappin[y / 64][x / 64] != '1'
		&& pnc->map->mappin[y / 64][x / 64] != 'E')
	{
		putchr(pnc, side);
		pnc->chr->point += 1;
		if (pnc->map->mappin[y / 64][x / 64] == 'C')
			pnc->map->cb -= 1;
		pnc->map->mappin[pnc->chr->l_y / 64][pnc->chr->l_x / 64] = '0';
		pnc->map->mappin[pnc->map->gate_y / 64][pnc->map->gate_x / 64] = 'E';
		pnc->map->mappin[y / 64][x / 64] = 'P';
		print_score(pnc);
	}
}

int	walk(int keycode, void *param)
{
	t_win	*pnc;

	pnc = param;
	mlx_clear_window(pnc->mlx, pnc->win);
	if (keycode == 2)
		move_p(pnc, keycode, pnc->chr->l_x + 64, pnc->chr->l_y);
	if (keycode == 0)
		move_p(pnc, keycode, pnc->chr->l_x - 64, pnc->chr->l_y);
	if (keycode == 13)
		move_p(pnc, keycode, pnc->chr->l_x, pnc->chr->l_y - 64);
	if (keycode == 1)
		move_p(pnc, keycode, pnc->chr->l_x, pnc->chr->l_y + 64);
	if (keycode == 53)
		close_frame(pnc);
	render_map(pnc);
	return (keycode);
}
