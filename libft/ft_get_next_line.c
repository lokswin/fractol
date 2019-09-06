/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drafe <drafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 20:26:45 by drafe             #+#    #+#             */
/*   Updated: 2019/07/26 17:17:17 by drafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_gnl_write(char **line, char **s_file)
{
	char			*out;
	char			*ptr;
	size_t			out_len;
	size_t			s_len;

	out_len = 0;
	s_len = ft_strlen(*s_file);
	ptr = NULL;
	out = NULL;
	while ((s_file[0][out_len] != '\n') && (s_file[0][out_len] != '\0'))
		out_len++;
	out = ft_strsub(*s_file, 0, out_len);
	ptr = ft_strsub(*s_file, out_len + 1, (s_len - out_len));
	if ((s_file[0][0] == '\n') || (out_len >= 1))
		out_len = 1;
	free(*s_file);
	*s_file = NULL;
	*s_file = ptr;
	*line = out;
	return (out_len);
}

int			ft_gnl_read(const int fd, char **s)
{
	char			*tmp;
	char			*ptr;
	int				bytes;
	size_t			i;

	if (!(tmp = (char *)malloc(sizeof(char) * (32 + 1))))
		return (-1);
	while (((bytes = read(fd, tmp, 32)) > 0))
	{
		tmp[bytes] = '\0';
		i = 0;
		ptr = ft_strjoin(*s, tmp);
		free(*s);
		*s = ptr;
		while (s[0][++i] != '\0')
			if (s[0][i] == '\n')
				break ;
		if (i < ft_strlen(*s))
			break ;
	}
	free(tmp);
	if (bytes == -1)
		return (-1);
	return (1);
}

int					ft_get_next_line(const int fd, char **line)
{
	static char		*output_line[10240];
	char			*ptr;

	ptr = NULL;
	if ((fd < 0) || (!line) || (fd > 10240))
		return (-1);
	if (output_line[fd] == NULL)
	{
		if (!(output_line[fd] = (char *)malloc(sizeof(char) * 1)))
			return (0);
		output_line[fd][0] = '\0';
	}
	if ((ft_gnl_read(fd, &output_line[fd])) == -1)
		return (-1);
	return (ft_gnl_write(line, &output_line[fd]));
}
