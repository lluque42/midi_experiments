/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_ui_experiments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:59:58 by lluque            #+#    #+#             */
/*   Updated: 2025/06/14 12:10:11 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "piano_trainer.h"

int	pt_ui_experiments(t_pt *pt)
{
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
}
/*
	printf("cm_string '%s'\n", tgetstr("cm", NULL));
	
	printf("Columns according to termcap '%d'\n", tgetnum("co"));
	printf("Lines according to termcap '%d'\n", tgetnum("li"));

	printf("Autowrap? '%d'\n", tgetflag("am"));
*/

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



    // STDOUT_FILENO is typically the terminal
	pthread_mutex_lock(&pt->ws_mx);
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &pt->ws) == -1)
		return (pthread_mutex_unlock(&pt->ws_mx),
				perror("ioctl for terminal size"), 0);
    printf("Rows: %d\n", pt->ws.ws_row);
    printf("Columns: %d\n", pt->ws.ws_col);
	pthread_mutex_unlock(&pt->ws_mx);



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
