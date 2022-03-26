/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetchda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 13:18:59 by ppetchda          #+#    #+#             */
/*   Updated: 2022/02/28 13:22:55 by ppetchda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*check_left_str(char *left_str)
{
	char	*ret;
	size_t	len;
	if (left_str == NULL)
	{
		len = 0;
		ret = NULL;
	}
	else
	{
		len = ft_strlen(left_str);
		ret = ft_strnstr(left_str, "\n", len);
	}
	return (ret);
}

char	*ft_read_to_left_str(int fd, char *left_str)
{
	char	*buff;
	int		rd_bytes;
	char	*ret;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	// while (!ft_strchr(left_str, '\n') && rd_bytes != 0)
	ret = check_left_str(left_str);
	while (!ret && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		// ft_strlcat(left_str, buff, ft_strlen(left_str) + ft_strlen(buff) + 1);
		left_str = ft_strjoin(left_str, buff);
		ret = check_left_str(left_str);
	}
	free(buff);
	return (left_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*left_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	left_str = ft_read_to_left_str(fd, left_str);
	if (!left_str)
		return (NULL);
	line = ft_get_line(left_str);
	left_str = ft_new_left_str(left_str);
	return (line);
}
