/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouar <alaaouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:37:23 by alaaouar          #+#    #+#             */
/*   Updated: 2024/02/18 20:53:32 by alaaouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	shift_left(char *buffer, int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return ;
	while ((i + nb) < BUFFER_SIZE)
	{
		buffer[i] = buffer[i + nb];
		i++;
	}
	while (i < BUFFER_SIZE)
		buffer[i++] = 0;
}

void	change_buffer(char *buffer)
{
	int	count;

	count = 0;
	while (count < BUFFER_SIZE && buffer[count] && buffer[count] != '\n')
		count++;
	if (count == BUFFER_SIZE || buffer[count] == 0)
	{
		while (count--)
			buffer[count] = 0;
	}
	else if (buffer[count] == '\n')
		shift_left(buffer, count);
}

char	*line_join(char *old_line, char *buffer)
{
	int		count;
	int		i;
	char	*new_line;

	count = 0;
	while (count < BUFFER_SIZE && buffer[count] && buffer[count] != '\n')
		count++;
	if (count < BUFFER_SIZE && buffer[count] == '\n')
		count++;
	new_line = malloc((ft_strlen(old_line) + count + 1) * sizeof(char));
	if (!new_line)
		return (ft_free(old_line));
	i = -1;
	while (old_line && old_line[++i])
		new_line[i] = old_line[i];
	if (!old_line)
		i++;
	new_line[i + count] = 0;
	while (count--)
		new_line[i + count] = buffer[count];
	change_buffer(buffer);
	ft_free (old_line);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	buffer[OPEN_MAX][BUFFER_SIZE];
	char		*line;
	int			nb_read;

	line = NULL;
	if (fd >= 0 && buffer[fd][0])
		line = line_join(line, buffer[fd]);
	while (fd >= 0)
	{
		if (buffer[fd][0] == '\n')
		{
			shift_left(buffer[fd], 1);
			break ;
		}
		nb_read = read(fd, buffer[fd], BUFFER_SIZE);
		printf("exit : %s\n", buffer[fd]);
		if (nb_read == -1)
			return (ft_free(line));
		if (nb_read == 0)
			return (line);
		line = line_join(line, buffer[fd]);
		if (!line)
			return (NULL);
	}
	return (line);
}

// int	main()
// {
// 	char *line;
// 	char *line1;
// 	int fd = open("file/file.txt", O_RDONLY);
// 	int fd1 = open("file/file1.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf ("%d\n", fd);
// 	line1 = get_next_line(fd1);
// 	printf ("%d\n", fd1);
// 	while (line || line1)
// 	{
// 		printf("%s \n", line);
// 		printf("%s ", line1);
// 		line = get_next_line(fd);
// 		line1 = get_next_line(fd1);
// 	}
// 	close (fd);
// 	close (fd1);
// 	return (0);
// }
