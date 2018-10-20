TARGET = prog

$(TARGET): main.o lib.a
	gcc $^ -o $@

main.o: main.c
	gcc -c $< -o $@

lib.a: lib1.o lib2.o
	ar rcs $@ $^

lib1.o: lib1.c lib1.h
	gcc -c -o $@ $<

lib2.o: lib2.c lib2.h
	gcc -c -o $@ $<

clean:
	rm -f *.o *.a $(TARGET)