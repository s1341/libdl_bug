all:
	gcc -shared -fPIC -o test_unload.so test_unload_so.c -ldl -pthread
	gcc -o test_unload test_unload.c -pthread
