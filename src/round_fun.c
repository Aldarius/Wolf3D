/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 20:15:20 by lminta            #+#    #+#             */
/*   Updated: 2019/05/28 20:46:24 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ipart(double x)
{
	return ((int)x);
}

int		ft_round(double x)
{
	return (ipart(x + 0.5));
}

double	fpart(double x)
{
	return (x - (double)ipart(x));
}

double	rfpart(double x)
{
	return (1 - fpart(x));
}

void	ft_swap(double *a, double *b)
{
	double buff;

	buff = *a;
	*a = *b;
	*b = buff;
}
