#include <u.h>
#include <libc.h>

void check(int, char*);
void checkDir(int, char *);
void rmdir(char *);
void clean();

char* dir;


void
main(int argc, char **argv){
	if (argc < 2){
		print("Please specify  a directory\n");
		print("FAIL\n");
		exits("FAIL");
	}
	dir = argv[1];
	check(chdir(dir), dir);
	checkDir(create("A", OREAD, DMDIR | 0777), "A");
	check(chdir("A"), "A");
	checkDir(create("B", OREAD, DMDIR | 0777), "B");
	checkDir(create("C", OREAD, DMDIR | 0777), "C");
	check(chdir("B"), "B");
	check(chdir(".."), "..");
	remove("B");
	check(chdir("C"), "C");
	check(chdir(".."), "..");
	remove("C");
	check(chdir(".."), "..");
	remove("A");
	print("PASS\n");
	exits("PASS");
}

void
check(int r, char *d){
	if(r<0){
		print("chdir(\"%s\") Err: '%r'\n", d);
		clean();
		print("FAIL\n");
		exits("FAIL");
	}
}

void
checkDir(int r, char *d){
	if(r<0){
		print("Error creating dir '%s'\n", d);
		clean();
		print("FAIL\n");
		exits("FAIL");
	}
}

void
clean() {
	chdir(dir);
	remove("A/B");
	remove("A/C");
	remove("A");
}
