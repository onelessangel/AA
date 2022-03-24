make: run_retele

build: retele reclame registre

run_retele: retele
	java Retele

run_reclame: reclame
	java Reclame

run_registre: registre
	java Registre

retele: Retele.java Task.java
	javac $^

reclame: Reclame.java Task.java
	javac $^

registre: Registre.java Task.java
	javac $^

clean:
	rm -f *.class

.PHONY: build clean
