/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:45:55 by yenyilma          #+#    #+#             */
/*   Updated: 2024/12/13 07:41:45 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_file(char *garbage, int fd)
{
	int		i;
	char	*temp;	

	i = 1;
	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	while (!ft_strchr_gnl(garbage, '\n') && i > 0)
	{
		i = read(fd, temp, BUFFER_SIZE);
		if (i == -1 || (i == 0 && !ft_strlen_gnl(garbage)))
		{
			if (garbage)
				free(garbage);
			free(temp);
			return (NULL);
		}
		temp[i] = '\0';
		garbage = ft_strjoin_gnl(garbage, temp);
	}
	free(temp);
	return (garbage);
}

static char	*remove_line(char *garbage)
{
	int		i;
	int		j;
	char	*n_garbage;

	i = 0;
	j = 0;
	while (garbage[i] != '\n' && garbage[i] != '\0')
		i++;
	if (!*garbage)
	{
		free(garbage);
		return (0);
	}
	if (garbage[i] == '\n')
		i++;
	n_garbage = (char *)malloc(sizeof(char) * (ft_strlen_gnl(garbage) - i + 1));
	if (!n_garbage)
		return (NULL);
	while (garbage[i] != '\0')
		n_garbage[j++] = garbage[i++];
	n_garbage[j] = '\0';
	free(garbage);
	return (n_garbage);
}

static char	*ft_get_line(char *garbage)
{
	char	*line;
	int		i;
	int		stop;

	i = 0;
	while (garbage[i] != '\n' && garbage[i] != '\0')
		i++;
	if (garbage[i] == '\n')
		i++;
	stop = i;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < stop)
	{
		line[i] = garbage[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*garbage;	
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	garbage = ft_read_file(garbage, fd);
	if (!garbage || !*garbage)
		return (NULL);
	line = ft_get_line(garbage);
	garbage = remove_line(garbage);
	return (line);
}
