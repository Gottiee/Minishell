/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eedy <eliot.edy@icloud.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 19:09:29 by eedy              #+#    #+#             */
/*   Updated: 2022/08/23 19:33:48 by eedy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eliot.h"

int	pwd(void)
{
	char	*pwd;

	pwd = get_current_path();
	if (!pwd)
		return (-1);
	printf("\n%s\n", pwd);
	return (0);
}