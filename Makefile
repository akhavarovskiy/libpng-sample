all: src/*.cpp
	mkdir bin >> /dev/null 2>&1 || true
	clang++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -O3 -o bin/out src/*.cpp -lpng -lz

debug: src/*.cpp
	mkdir bin >> /dev/null 2>&1 || true
	clang++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -O3 -o bin/out src/*.cpp -lpng -lz -D DEBUG