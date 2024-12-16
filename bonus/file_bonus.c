/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:09:53 by aheitz            #+#    #+#             */
/*   Updated: 2024/12/12 16:01:46 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	write_file(const void *ptr, size_t size, size_t n, FILE *s)
{
	const bool	status = fwrite(ptr, size, n, s) == n;

	if (!status)
		perror("The Celestial Proxy refused to write data file");
	return (status);
}

bool	read_file(void *ptr, size_t size, size_t n, FILE *stream)
{
	const bool	status = fread(ptr, size, n, stream) == n;

	if (!status)
		perror("The Celestial Antivirus refused to read data file");
	return (status);
}

FILE	*open_file(const char *filename, const char *modes)
{
	FILE	*file;

	file = fopen(filename, modes);
	if (!file)
		perror("The Celestial Firewall refused to open data file");
	return (file);
}

bool	close_file(FILE *stream, const t_path file)
{
	const bool	status = fclose(stream) == SUCCESS;

	if (!status)
	{
		perror("The Celestial Security refused to close data file");
		if (remove(file) == FAILURE)
			terminate("Sending a file to Hell has failed!");
	}
	return (status);
}
