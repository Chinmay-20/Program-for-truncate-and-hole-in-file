build:
	gcc truncateorhole.c -o myexe

run:
	./myexe ${arg1}

clean:
	rm  myexe

help:
	@echo "Usage:make arg1=\"directory_name\" run"
