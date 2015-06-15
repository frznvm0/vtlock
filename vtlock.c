#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/vt.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stropts.h>
#include <sys/wait.h>
#include <unistd.h>

static void usage(char *);
static void dontkillme(void);

static void
usage(char *progname)
{
	  fprintf(stderr, "usage: %s <command...>\n", progname);
	  exit(1);
}

static void
dontkillme(void)
{
	int fd;

	fd = open("/proc/self/oom_score_adj", O_WRONLY);
	if (fd < 0 && errno == ENOENT)
		return;
	if (fd < 0 || write(fd, "-1000\n", 6) != 6 || close(fd) != 0)
		err(errno, "cannot disable the out-of-memory killer for this process");
}

int
main(int argc, char **argv)
{
	int term, pid, ret = 0;

	if (argc < 2)
		usage(argv[0]);

	dontkillme();

	if ((term = open("/dev/console", O_RDWR)) < 0)
		err(errno, "cannot open console");

	if ((ioctl(term, VT_LOCKSWITCH)) < 0)
		err(errno, "cannot lock console");

	pid = fork();
	if (pid < 0) {
		err(errno, "fork failed");
	} else if (pid == 0) {
		argv++;
		execvp(*argv, argv);
		err(127, "exec failed: %s", *argv);
	}

	wait(&ret);

	if ((ioctl(term, VT_UNLOCKSWITCH)) < 0)
		err(errno, "cannot unlock console");

	close(term);
	return WEXITSTATUS(ret);
}
