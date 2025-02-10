/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:58:33 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/10 17:54:37 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*modifier pour utiliser le pwd de l'env plutot que getcwd*/
void	pwd_cmd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) == NULL)
	{
		perror("pwd: error retrieving current directory: getcwd");
		return;
	}
	printf("%s\n", path);
}
