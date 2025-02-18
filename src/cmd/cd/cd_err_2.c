/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_err_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:43:14 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/18 14:36:27 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	cd_to_many_arg(void)
{
	ft_putstr_fd("bash: cd: too many arguments\n", 2);
	return (1);
}

int	cd_home_not_set(void)
{
	ft_putstr_fd("bash: cd: HOME not set\n", 2);
	return (1);
}

int	cd_oldpwd_not_set(void)
{
	ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
	return (1);
}
