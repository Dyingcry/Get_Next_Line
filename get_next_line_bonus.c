/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsion <thsion@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:02:19 by thsion            #+#    #+#             */
/*   Updated: 2024/01/29 14:07:21 by thsion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_extract(char **stash)
{
	char	*res;
	char	*temp;
	int		i;

	i = 0;
	temp = *stash;
	if (!*stash)
		return (NULL);
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		i++;
	res = ft_strndup(temp, i);
	*stash = ft_strndup((temp + i), (ft_strlen(temp + i)));
	free(temp);
	return (res);
}

char	*ft_free(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*str;
	int			ncl;

	ncl = 1;
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd < 0)
		return (ft_free(&stash[fd]));
	if (ft_strchr(stash[fd], '\n'))
		return (ft_extract(&stash[fd]));
	str = malloc ((sizeof(char)) * (BUFFER_SIZE + 1));
	if (!str)
		return (NULL);
	while (ncl > 0 && !ft_strchr(stash[fd], '\n'))
	{
		ncl = read(fd, str, BUFFER_SIZE);
		str[ncl] = '\0';
		stash[fd] = ft_strjoin(stash[fd], str);
	}
	ft_free(&str);
	return (ft_extract(&stash[fd]));
}
/* 
int	main(void)
{
	char	*content;
	int		fd;

	fd = open("text.txt", O_RDONLY);
	while (1)
	{
		content = get_next_line(fd);
		if (!content)
		{
			break ;
		}
		printf("%s", content);
		free(content);
	}
	if (content)
		free(content);
	close(fd);
	return (0);
}
 */