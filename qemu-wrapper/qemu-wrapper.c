#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp) {
	if (argc < 2)
	{
		printf("Usage: %s argv0 program [argv1 argv2 ...]\n", argv[0]);
		return 1;
	}
	char **newargv;

	newargv = (char **)malloc((argc + 4) * sizeof(*newargv));
	
	newargv[0] = argv[0];
	newargv[1] = "-cpu";
	newargv[2] = "cortex-a9";
	newargv[3] = "-0";
	newargv[4] = argv[2];
	newargv[5] = argv[1];
	if (argc > 2)
	{
		memcpy(&newargv[6], &argv[3], sizeof(*argv) * (argc - 3));
	}
	newargv[argc + 3] = NULL;
	for (int i = 0; i < argc + 3; ++i)
	{
		printf("\"%s\", ", newargv[i]);
	}
	printf("\n");
	return execve("/usr/bin/qemu-arm-real", newargv, envp);
}
