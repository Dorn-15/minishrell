/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:00:28 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/10 17:54:34 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*

oldpwd = pwd

cd = (pwd == home)
cd - = (pwd == OLDPWD)
cd /xxx = (pwd == "/xxx")

cd ./xxx = rester sur le dossier actuel
cd xxx = ./xxx

cd ../xxx = revenir au dossier precedant

cd ~/xxx = valide uniquement en premier start at $home/xxx
ne pas geree si home n'existe pas


accepter les / a la fin mais de pas les ajouter a env
accepte les in et out file mais ne renvoie rien
ne s'execute pas avec des pip | devant et derriere

bash: cd: to many argument
bash: cd: (arg): No such file or directory
bash: cd: (arg): Not a directory
bash: cd: (arg): Permission denied
bash: cd: (arg): Too many levels of symbolic links
bash: cd: (arg): File name too long
bash: cd: OLDPWD not set
bash: cd: HOME not set

exit (0), valid
exit (1), fail
*/

void	cd_cmd(char **arg, char **env)
{
	int i;

	i = 0;
	if (!arg || !env)
		return;
}
