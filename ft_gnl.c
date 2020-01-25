/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 16:08:01 by mashar            #+#    #+#             */
/*   Updated: 2019/12/02 16:26:26 by mashar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include<unistd.h>
#include<stdlib.h>

int ft_strlen(char *s)
{
	int i = 0;
	while(s[i] != '\0')
		i++;
	return i;
}

int ft_free(char **str)
{
	if(!str || !*str)
		return 1;
	free(*str);
	*str = 0;
	return 1;
}

char *ft_stradd(char *str, char ch)
{
	int i = 0;
	int len;
	char *res;

	len = str? ft_strlen(str) : 0;
	len = len +2;
	res = malloc(sizeof(char) * len);
	while(str && str[i] != '\0')
	{
		res[i] = str[i];
		i++;
	}
	res[len -2] = ch;
	res[len -1] = '\0';
	ft_free(&str);
	return res;
}


char *ft_strjoin(char *s1, char *s2)
{
	int i =-1;
	int j = -1;
	char *res;

	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)+1));
	while(s1[++i] != '\0')
		res[i] = s1[i];
	while(s2[++j] != '\0')
		res[i++] = s2[j];
	res[i] = '\0';
	return res;
}

char *init(char *buf, char **p, int fd)
{
	int value =0;
	char *tmp;
	if(!(buf = malloc(sizeof(char) * 11)))
		return NULL;
	if((value = read(fd, buf, 10)) < 0)
		return NULL;
	buf[value] = '\0';
	if ((*p != NULL))
	{
		tmp = ft_strjoin(*p, buf);
		ft_free(&buf);
		ft_free(p);
		buf = tmp;
	}
	return buf;
}

char *process_line(char *p, char *buf, int i , int value)
{
	int j = 0;
	if(!(p = malloc(sizeof(char) * (value - i))))
		return NULL;
	i++;
	while(buf[i] != '\0')
		p[j++] = buf[i++];
	p[j] = '\0';
	return p;
}

int ft_some(char *buf, char ** line, int value, char **p)
{
	int i = 0;

	while(i < value)
	{
		if(buf[i] == '\n')
		{
			*p = process_line(*p, buf, i, value);
			if (*line ==NULL)
			{
				*line = malloc(sizeof(char));
				*line[0] = '\0';
			}
			ft_free(&buf);
			return 1;
			
		}
		else if (ft_free(p))
			*line = ft_stradd(*line, buf[i++]);
	}
	ft_free(&buf);
	return 2;
}


int ft_gnl(int fd, char **line)
{
	int value = 1;
	char *buf;
	static char *p;
	int ret;

	if(!line)
		return -1;
	while( value > 0)
	{
		if(!(buf = init(buf, &p, fd)))
			return  -1;
		if ((!(value = ft_strlen(buf))))
		{
			ft_free(&buf);
			ft_free(&p);
			if (!*line)
			{
				*line = malloc(sizeof(char));
				*line[0] = '\0';
			}
			return 0;
		}
		if ((ret = ft_some(buf, line, value, &p)==1 || ret == -1 ))
			return ret;
	}
	return 1;
}
