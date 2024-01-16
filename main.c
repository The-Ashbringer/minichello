/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <dcarenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 23:42:32 by dcarenou          #+#    #+#             */
/*   Updated: 2023/12/27 00:51:37 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(/*int argc, char **argv, char **envp*/)
{
	char	input[] = "- >> << < ' \" |";
	char	*current;
	t_tokenlist	tlist;
	t_tokendata	*currenttoken;
	t_tokendata	*nexttoken;

	tlist.head = NULL;
	current = input;
	while (*current != '\0')
	{
		gettoken(current, &tlist);
		current++;
	}
	printtokens(&tlist);
	currenttoken = tlist.head;
	while (currenttoken != NULL)
	{
		nexttoken = currenttoken->next;
		free(currenttoken);
		currenttoken = nexttoken;
	}
	return (0);
}
