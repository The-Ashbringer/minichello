/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <dcarenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 17:29:33 by dcarenou          #+#    #+#             */
/*   Updated: 2023/12/27 00:52:35 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./lexer/lexer.h"
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_lst
{
	char			*content;
	int				type;
	int				pos;
	struct s_lst	*next;
}				t_lst;

typedef struct s_tokendata
{
	char				content;
	int					type;
	struct s_tokendata	*next;
}				t_tokendata;

typedef struct s_tokenlist
{
	struct s_tokendata	*head;
	struct s_tokendata	*tail;
}				t_tokenlist;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}				t_env;

enum e_tokentype
{
	GENERAL_C = -1,
	NULL_C = 0,
	PIPE_C = '|',
	MINUS_C = '-',
	AMPERSAND_C = '&',
	QUOTE_C = '\'',
	DQUOTE_C = '\"',
	WHITESPACE_C = ' ',
	ESCAPE_C = '\\',
	TAB_C = '\t',
	NEWLINE_C = '\n',
	GREATER_C = '>',
	LESSER_C = '<',
	WILDCART_C = '*',
	LPAREN_C = '(',
	RPAREN_C = ')',
	EQUAL_C = '=',
	DOLLAR_C = '$',
};
void	addtoken(t_tokenlist *tlist, int type, char c);
void	gettoken(char *str, t_tokenlist *tlist);


// testers
void	printtokens(t_tokenlist *tlist);

#endif