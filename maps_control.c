/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saksoy <saksoy@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:18:49 by saksoy            #+#    #+#             */
/*   Updated: 2022/06/04 12:58:37 by saksoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minlbx.h"

int	str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	player_control(t_win *pnc)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pnc->map->mappin[i])
	{
		while (pnc->map->mappin[i][j])
		{
			if (pnc->map->mappin[i][j] == 'P')
			{
				pnc->map->p_cnt += 1;
			}
			j++;
		}
		i++;
		j = 0;
	}
	if (pnc->map->p_cnt != 1)
	{
		write(1, "Player Count Error", 19);
		close_frame(pnc);
	}
}

void	wall_control(t_win *pnc)
{
	int	i;
	int	last;

	i = -1;
	while (pnc->map->mappin[0][++i])
	{
		if (pnc->map->mappin[0][i] != '1' ||
			pnc->map->mappin[pnc->map->h - 1][i] != '1')
		{
			write(1, "Wall Error", 11);
			close_frame(pnc);
		}
	}
	i = -1;
	last = pnc->map->w - 1;
	while (pnc->map->mappin[++i])
	{
		if (pnc->map->mappin[i][0] != '1' || pnc->map->mappin[i][last] != '1')
		{
			write(1, "Wall Error", 11);
			close_frame(pnc);
		}
	}
}

void	map_size_control(t_win *pnc)
{
	int	i;
	int	len;

	i = 0;
	len = pnc->map->w;
	while (pnc->map->mappin[i])
	{
		if (str_len(pnc->map->mappin[i]) != len)
		{
			write(1, "Line Size Error", 16);
			close_frame(pnc);
		}
		i++;
	}
}

void	end_control(t_win *pnc)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (pnc->map->mappin[++i])
	{
		while (pnc->map->mappin[i][++j])
		{
			if (pnc->map->mappin[i][j] == 'E')
			{
				pnc->map->end_cnt = pnc->map->end_cnt + 1;
			}
		}
		j = 0;
	}
	if (pnc->map->end_cnt < 1)
	{
		write (1, "End Door Count Error", 21);
		close_frame(pnc);
	}
}
