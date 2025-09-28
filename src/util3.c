/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 11:13:28 by daflynn           #+#    #+#             */
/*   Updated: 2025/09/28 11:13:35 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_skip_quote(char *str, int i)
{
	char	quote;

	quote = str[i++];
	while (str[i] && str[i] != quote)
		i++;
	if (str[i])
		i++;
	return (i);
}

int	is_special_char(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == ';' || c == '&');
}

char	**ft_sub_tokenize_line(t_dat *d, char *str, int **quote_types_out)
{
	char	**tokens;

	(void)quote_types_out;
	if (!str)
		return (NULL);
	ft_reset_iterators(d);
	d->k = ft_count_tokens(str);
	tokens = malloc(sizeof(char *) * (d->k + 1));
	if (!tokens)
		return (NULL);
	d->qtypes = malloc(sizeof(int) * (d->k + 1));
	if (!d->qtypes)
		return (free(tokens), NULL);
	return (tokens);
}
