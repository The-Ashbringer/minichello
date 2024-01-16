/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <dcarenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:12:20 by dcarenou          #+#    #+#             */
/*   Updated: 2023/12/27 00:54:51 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	addtoken(t_tokenlist *tlist, int type, char c)
{
	t_tokendata	*newtoken;

	newtoken = malloc(sizeof(t_tokendata));
	newtoken->type = type;
	newtoken->content = c;
	newtoken->next = NULL;
	if (tlist->head == NULL)
	{
		tlist->head = newtoken;
		tlist->tail = newtoken;
	}
	else
	{
		tlist->tail->next = newtoken;
		tlist->tail = newtoken;
	}
}

void	gettoken(char *str, t_tokenlist *tlist)
{
		if (*str == '|')
			addtoken(tlist, PIPE_C, *str);
		else if (*str == '	')
			addtoken(tlist, WHITESPACE_C, *str);
		else if (*str == '\'')
			addtoken(tlist, QUOTE_C, *str);
		else if (*str == '\"')
			addtoken(tlist, DQUOTE_C, *str);
		else if (*str == ' ')
			addtoken(tlist, WHITESPACE_C, *str);
		else if (*str == '>')
			addtoken(tlist, GREATER_C, *str);
		else if (*str == '<')
			addtoken(tlist, LESSER_C, *str);
		else if (*str == '$')
			addtoken(tlist, DOLLAR_C, *str);
		else
			addtoken(tlist, GENERAL_C, *str);
		str++;
}

void	printtokens(t_tokenlist *tlist)
{
	t_tokendata	*current;

	current = tlist->head;
	while (current != NULL)
	{
		printf("Type: %d, Value \"%c\"\n", current->type, current->content);
		current = current->next;
	}
}