CC= gcc
LIBS= external_libs
EXEC = app

all: clearapp app clean

app: jsmn.o file_helper.o pokemon.o type.o app.o
	${CC} -o ${EXEC} jsmn.o file_helper.o pokemon.o type.o app.o

app.o : src/app.c
	${CC} -c -Wall src/app.c

file_helper.o : src/datafinders/file_helper/file_helper.c
	${CC} -c -Wall src/datafinders/file_helper/file_helper.c

type.o : src/datafinders/type/type.c
	${CC} -c -Wall src/datafinders/type/type.c

pokemon.o : src/datafinders/pokemon/pokemon.c
	${CC} -c -Wall src/datafinders/pokemon/pokemon.c

jsmn.o : ${LIBS}/jsmn.c
	${CC} -c -Wall ${LIBS}/jsmn.c

clean:
	rm -rf *.o

clearapp:
	rm -rf $(EXEC)