#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main (int argc, char **argv)
{

		int num = 0;
		char *line = NULL;
		int ret = 2;
		
		//argv[1] = "hhh";
		
		int fd = open(argv[1], O_RDONLY);
		//while (get_next_line(fd, line) == 1)
		//{
		//		printf("- |%s|", *line);
		//}
		while ((ret = ft_gnl(fd, &line)) > 0)
		{
			printf("Final line is (%s)\n", line);
			if (line)
			{
				ft_free(&line);
				line = 0;
			}
		}
		printf("%d %d %s\n", ++num, ret, line);
		ft_free(&line);
		//printf("Return equals to : %d", ret);
}

