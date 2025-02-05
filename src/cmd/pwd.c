/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:58:33 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/05 18:27:41 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pwd_cmd(void)
{
	char path[PATH_MAX];

	if (getcwd(path, sizeof(path)) == NULL)
	{
		perror("pwd: error retrieving current directory: getcwd");
		kill_cmd(errno);
	}
	printf("%s\n", path);
	kill_cmd(0);
}
