redir: redir.c
	gcc -o redir redir.c

Input:
	@echo "generating an input file with 100 lines"
	@seq 1 100 > input.txt

output: redir Input
	./redir input.txt "wc -l" output.txt
	@echo "redirect in output.txt:"
	@cat output.txt

clean:
	rm -f redir input.txt output.txt

