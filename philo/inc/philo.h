/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:24:15 by abourdar          #+#    #+#             */
/*   Updated: 2022/03/29 09:24:16 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h> //a sup
# define ERR_MALLOC -1
# define ERR_ARG -2

//STRUCTURES

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_ptr
{
	int				death;
	int				death_id;
	int				nbr;
	int				m_eat;
	long int		start_th;
	int				count;
	pthread_mutex_t	general;
}				t_ptr;

typedef struct s_data
{
	t_ptr			*c;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	long int		start_eat;
	int				id;
	int				h_eat;
	int				tte;
	int				ttd;
	int				tts;
	pthread_t		th;
	pthread_t		death;
}				t_data;

typedef struct s_arg
{
	t_list	*mlc;
	t_data	*philo;
	t_ptr	com;

	int		n_philo;
	int		ms_d;
	int		ms_e;
	int		ms_s;
	int		m_eat;
	int		ac;
	int		*args;
}				t_arg;

//LIB PHILO

void		*ft_memset(void *b, int c, size_t len);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);
void		ft_putstr_fd(char *s, int fd);

void		exit_prog(int error, t_arg *arg);
int			parse_arg(char **av, int ac, t_arg *arg);
int			start_th(t_arg *arg);
void		init_philo(t_arg *arg, t_data *philo);

void		print_message(t_data *tp, int id, char *s);
void		destroy_mutex(t_arg *arg, t_data *philo);
int			check_alive(t_data *tp);
int			check_times_eat(t_data *tp);

void		*is_dead(void *tmp);
void		a_table(t_data *tp);

void		ft_usleep(t_data *philo, long int time_in_ms);

long int	actual_time(void);

#endif
