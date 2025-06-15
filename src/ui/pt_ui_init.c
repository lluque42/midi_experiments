/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_ui_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:59:58 by lluque            #+#    #+#             */
/*   Updated: 2025/06/14 20:14:48 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

int	pt_ui_init(t_pt *pt)
{
	struct termios	new_termios;
	int				status;
	char			*tmp;

	if (!pt_ui_check_if_tty())
		return (dprintf(STDERR_FILENO, "No redirections/piping allowed. "),
				dprintf(STDERR_FILENO, "This is an interactive program.\n"), 0);

	// Initialize winsize
	// (1) ioctl() is the most low-level and less portable way to
	// interact with a terminal. Just for simple low-level stuff:
	// Input modes, echo, signals, baud rate, etc.
	// It uses Kernel-level or OS interface (ioctl() is a system call).
	pthread_mutex_lock(&pt->ws_mx);
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &pt->ws) == -1)
		return (pthread_mutex_unlock(&pt->ws_mx),
				perror("ioctl for terminal size"), 0);
	pthread_mutex_unlock(&pt->ws_mx);
	
	// Retrieve and backup original termios struct for eventual restoring.
	// Disable the terminal echo during the execution
	// (2) tcgetattr()/tcsetattr() using the termios struct is a just a tiny
	// little bit less low-level and more portable way to interact with a
	// terminal. But don't fool yourself, It's still just for simple
	// low-level stuff: Input modes, echo, signals, baud rate, etc.
	// It also uses Kernel-level or OS interface (tcgetattr()/tcsetattr()
	// are system call and termios is a kernel structure).
	if (tcgetattr(STDOUT_FILENO, &pt->termios_orig) != 0)
		return (perror("Couldn't tcgetattr()."), 0);
	new_termios = pt->termios_orig;
	// Evaluating if set
	//if (termios_p.c_lflag & ECHO)
	// Setting: oring
	//new_termios.c_lflag |= ECHO;
	//pt->termios_orig.c_lflag |= ECHO;
	// Clearing: anding the inverted 
	new_termios.c_lflag &= ~ECHO;
	if (tcsetattr(STDOUT_FILENO, TCSANOW, &new_termios) != 0)
		return (perror("Couldn't tcsetattr()."), 0);

	// Obtain the terminal type to use with termcap
	tmp = getenv("TERM");
	if (tmp == NULL)
	{
		//return (perror("Couldn't getenv(\"TERM\")"), 0);
		// try with "vt100" if no TERM is found, or hardcode the typical
		printf("Couldn't getenv(\"TERM\"), defaulting to 'vt100'\n");
		pt->env_termtype = strdup("vt100");
	}
	else
		pt->env_termtype = strdup(tmp);
	
	// Initialize access to the termcap database based on the terminal type
	// (3) Termcap library is the highest level way to interact with the
	// terminal. It uses user-space database access (instead of system calls)
	// like /etc/termcap. It controls different things, called capabiilities,
	// of a higher level nature, such as: Cursor movement, screen clear,
	// key mapping. Its API include: tgetent(), tgetstr(), tgetnum(),
	// tgetflag(), tputs(), tgoto()...
	//
	// IMPORTANT: Apparently termcap is kind of obsolete. For example, in my
	// Ubuntu its role is assumed by 'ncurses' which presents a compatibility
	// layer interface for termcap. So, this program 'thinks' it's talking
	// to termcap but it's actually talking to 'ncurses'. This has important
	// consequences such as the memory management that is NOT implemented by
	// ncurses in the way described by termcap manual. There are no memory
	// leaks but a lot of memory allocated by termcap/ncurses stays reachable
	// by-design to be dealt with by the OS when the program using said library
	// terminates.
	status = tgetent (NULL, pt->env_termtype);	// won't free shit
	if (status < 0)
		return (pt_ui_terminate(pt),
				perror("Couldn't tgetent(), no access"), 0);
	if (status == 0)
		return (pt_ui_terminate(pt),
				perror("Couldn't tgetent(), TERM not defined"), 0);

	// Clear the screen using "cl" terminal capability obtained from termcap
	//printf("%s", tgetstr("cl", NULL));
	return (1);
}
