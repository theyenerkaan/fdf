/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:31:24 by yenyilma          #+#    #+#             */
/*   Updated: 2024/10/30 16:01:17 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read_file(char *garbage, int fd)
{
	int		i;
	char	*temp;	

	i = 1;
	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	while (!ft_strchr(garbage, '\n') && i > 0)
	{
		i = read(fd, temp, BUFFER_SIZE);
		if (i == -1 || (i == 0 && !ft_strlen(garbage)))
		{
			if (garbage)
				free(garbage);
			free(temp);
			return (NULL);
		}
		temp[i] = '\0';
		garbage = ft_strjoin(garbage, temp);
	}
	free(temp);
	return (garbage);
}

static char	*remove_line(char *garbage)
{
	int		i;
	int		j;
	char	*new_garbage;

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
	new_garbage = (char *)malloc(sizeof(char) * (ft_strlen(garbage) - i + 1));
	if (!new_garbage)
		return (NULL);
	while (garbage[i] != '\0')
		new_garbage[j++] = garbage[i++];
	new_garbage[j] = '\0';
	free(garbage);
	return (new_garbage);
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
	static char	*garbage[10240];	
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 10240)
		return (NULL);
	garbage[fd] = ft_read_file(garbage[fd], fd);
	if (!garbage[fd] || !*garbage[fd])
		return (NULL);
	line = ft_get_line(garbage[fd]);
	garbage[fd] = remove_line(garbage[fd]);
	return (line);
}
