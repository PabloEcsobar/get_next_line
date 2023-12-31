/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:53:17 by polenyc           #+#    #+#             */
/*   Updated: 2023/12/14 15:52:24 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	char	*str;
	char	*str1;
    char    *str2;
	int		file;
	int		file1;
    int     file2;

	file = open("file.txt", O_RDONLY);
	file1 = open("file1.txt", O_RDONLY);
    file2 = open("file3.txt", O_RDONLY);
    printf("BUFFER SIZE: %d\n", BUFFER_SIZE);
	str = get_next_line(file);
	str1 = get_next_line(file1);
    str2 = get_next_line(file2);
	while (str || str1 || str2)
	{
		printf("file:\t%s", str);
		printf("file1:\t%s", str1);
        printf("file2:\t%s", str2);
		free(str);
		free(str1);
		free(str2);
		str = get_next_line(file);
		str1 = get_next_line(file1);
        str2 = get_next_line(file2);
	}
	free(str);
	free(str1);
	free(str2);
	close(file);
	close(file1);
    close(file2);
	return (0);
}
