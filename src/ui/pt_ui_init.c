/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_ui_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:59:58 by lluque            #+#    #+#             */
/*   Updated: 2025/06/13 17:55:57 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

int pt_isatty_test(int fd)
{
	struct termios termios_p;

	if (tcgetattr(fd, &termios_p) != 0)
		return (0);
	printf("\ttermios_p.c_iflag & IGNBRK = '%d'\n", termios_p.c_iflag & IGNBRK);
	printf("\ttermios_p.c_iflag & BRKINT = '%d'\n", termios_p.c_iflag & BRKINT);
	printf("\ttermios_p.c_iflag & = INLCR '%d'\n", termios_p.c_iflag & INLCR);
	printf("\ttermios_p.c_iflag & = IGNCR '%d'\n", termios_p.c_iflag & IGNCR);
	printf("\ttermios_p.c_iflag & = ICRNL '%d'\n", termios_p.c_iflag & ICRNL);
	printf("\ttermios_p.c_iflag & = IUCLC '%d'\n", termios_p.c_iflag & IUCLC);
	printf("\ttermios_p.c_iflag & = IUTF8 '%d'\n", termios_p.c_iflag & IUTF8);

	printf("\ttermios_p.c_oflag & = OCRNL '%d'\n", termios_p.c_oflag & OCRNL);
	printf("\ttermios_p.c_oflag & = ONOCR '%d'\n", termios_p.c_oflag & ONOCR);
	printf("\ttermios_p.c_oflag & = ONLRET '%d'\n", termios_p.c_oflag & ONLRET);

	printf("\ttermios_p.c_lflag & ISIG = '%d'\n", termios_p.c_lflag & ISIG);
	printf("\ttermios_p.c_lflag & = ECHO '%d'\n", termios_p.c_lflag & ECHO);

	// Setting: oring
	//termios_p.c_lflag = termios_p.c_lflag | ECHO;
	// Resetting: anding the inverted 
	//termios_p.c_lflag = termios_p.c_lflag & ~ECHO;

	// Setting: oring
//	termios_p.c_lflag = termios_p.c_lflag | ISIG;
	// Resetting: anding the inverted 
//	termios_p.c_lflag = termios_p.c_lflag & ~ISIG;
	//if (tcsetattr(fd, TCSANOW, &termios_p) != 0)
	//	return (0);

//	printf("\tThe echo has been disabled\n");
//	printf("\tThe signals from terminal inputs have been disabled\n");


	struct winsize ws;

    // STDOUT_FILENO is typically the terminal
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
        perror("ioctl for terminal size");
        return 1;
    }

    printf("Rows: %d\n", ws.ws_row);
    printf("Columns: %d\n", ws.ws_col);


	printf("\tTerminal slot (?): '%d'\n", ttyslot());

	printf("\tTerminal name (before isatty): '%s'\n", ttyname(fd));
	if (isatty(fd))
		printf("It is a terminal!!!\n");
	else
	{
		if (errno == ENOTTY)
			printf("NOT a terminal\n");
		else if (errno == EBADF)
			printf("Bad fd\n");
		else
			printf("VERY UNEXPECTED\n");
		return (0);
	}
	printf("\tTerminal name (AFTER isatty): '%s'\n", ttyname(fd));
	return (1);
}

int	pt_ui_check_if_tty(void)
{
	if (!isatty(STDERR_FILENO) || !isatty(STDOUT_FILENO)
			|| !isatty(STDIN_FILENO))
		return (0);
	return (1);
}

int	pt_ui_init(t_pt *pt)
{
	struct termios	new_termios;
	int				status;
	char			*tmp;

	if (!pt_ui_check_if_tty())
		return (dprintf(STDERR_FILENO, "No redirections/piping allowed. "),
				dprintf(STDERR_FILENO, "This is an interactive program.\n"), 0);
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

	printf("Ah? '%s'\n", pt->env_termtype);
	
	status = tgetent (NULL, pt->env_termtype);	// won't free shit
	if (!pt->env_termtype || !*pt->env_termtype)

	if (status < 0)
		return (pt_ui_terminate(pt),
				perror("Couldn't tgetent(), no access"), 0);
	if (status == 0)
		return (pt_ui_terminate(pt),
				perror("Couldn't tgetent(), TERM not defined"), 0);

	// Instead of NULL one could malloc a char* and pass its address (char**)
	// and free it before leaving. Probably won't work with ncurses...
	printf("%s", tgetstr("cl", NULL));
	printf("cm_string '%s'\n", tgetstr("cm", NULL));
	
	printf("Columns according to termcap '%d'\n", tgetnum("co"));
	printf("Lines according to termcap '%d'\n", tgetnum("li"));

	printf("Autowrap? '%d'\n", tgetflag("am"));


	
	return (1);
}
/*
	int	some_file_fd;

	if (pt == NULL)
		return (0);
	printf("dev file case (%d):\n", pt->dev_fd);
	pt_isatty_test(pt->dev_fd);
	printf("stdin case:\n");
	pt_isatty_test(STDIN_FILENO);
	some_file_fd = open("README.md", O_RDONLY);
	printf("some file case (fd = %d):\n", some_file_fd);
	pt_isatty_test(some_file_fd);
	printf("bad fd case:\n");
	pt_isatty_test(43);
	return (1);
*/

int	pt_ui_terminate(t_pt *pt)
{
	if (tcsetattr(STDOUT_FILENO, TCSANOW, &pt->termios_orig) != 0)
		return (0);
	// This call makes termcap to free 
	//status = tgetent (NULL, pt->env_termtype);	// won't free shit
	printf("%s", tgetstr("cl", NULL));
	return (1);
}
