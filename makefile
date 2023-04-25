bisonTradutor: tradutorLex.l tradutorBison.y tradutorC.c
	bison -d tradutorBison.y
	flex -o tradutorBison.lex.c tradutorLex.l
	gcc -o $@ tradutorBison.tab.c tradutorBison.lex.c tradutorC.c -lfl -lm
	@echo Parser do tradutor pronto...