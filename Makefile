a.out:shell.c do_execvp.c get_hint.c do_strtok.c my_alias.c
	gcc -o $@ $^ -g
.PYONY:clean
clean:
	rm a.out
