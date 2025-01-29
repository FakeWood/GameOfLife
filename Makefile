SHELL := cmd.exe

all:
	@g++ -Wall -fopenmp -Iinclude/SDL2 -Iinclude/headers -Linclude/lib -o bin/main src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
	@echo You make it!
	@echo Let's run it!
	.\bin\main.exe

#-O3 for optimize, and -s will strip all debugging symbols
.PHONY: release
release:
	@g++ -O3 -Wall -fopenmp -Iinclude/SDL2 -Iinclude/headers -Linclude/lib -o bin/main_release src/*.cpp -s -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
	@echo You make a release version!
	@echo Let's run it!
	.\bin\main_release.exe

.PHONY: clean
clean: 
	-del .\bin\main.exe .\bin\main_release.exe