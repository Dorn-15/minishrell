/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:14:12 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/11 10:26:44 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	str_isdigit(char *arg)
{
	int i;
	
	i = 0;
	while(arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return(1);
		i++;
	}
	return(0);
}

void	exit_cmd(char **arg)
{
	if (arg && arg[0])
	{
	  	if (!arg[1])
			mem_exit(0);
		if (str_isdigit(arg[1]))
		{
			if (arg[2])
				//message d'erreur trop d'arguments et juste return 
			else
				mem_exit(ft_atoi(arg));
		}
		else
		{
			//message d'erreur argument numérique nécessaire
			mem_exit(2);
		}
	}
}
