/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:00:28 by adoireau          #+#    #+#             */
/*   Updated: 2025/02/11 12:38:33 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*

oldpwd = pwd

cd = (pwd == home)
cd - = (pwd == OLDPWD) swap pwd et oldpwd
cd /xxx = (pwd == "/xxx") envoie brut dans change dir

cd ./xxx = join du pwd actuel avec le xxx en suprimant tous les autres ./
cd xxx = ./xxx

cd ../xxx = supr le dernier str de pwd jusquau / en partant de la fin

cd ~/xxx = valide uniquement en premier start at $home/xxx
chemin absolut si home n'existe pas

accepter les / a la fin mais de pas les ajouter a env
accepte les in et out file mais ne renvoie rien (geree au parsing)
pas d'impacte avec les pip cat procesusse enfant

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

use change_dir pour changer sur l'env principale puis aply env[pwd] a newenv
*/

void	cd_cmd(char **arg, char **env)
{
	int	i;
	int	pwd;
	int	oldpwd;

	if (!arg || !env)
		return;
	i = 0;
	pwd = -1;
	oldpwd = -1;
	while(env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4))
			pwd = i;
		if (ft_strncmp(env[i], "OLDPWD=", 8))
			oldpwd = i;
		i++;
	}
	if (pwd == -1)
	{
		//dup + 1 de env
	}
}
