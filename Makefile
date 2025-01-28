all:
	@g++ -Wall -Iinclude/SDL2 -Iinclude/header -Linclude/lib -o bin/main src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	@echo You make it!
	@echo Let's run it!
	.\bin\main.exe

#-O3 for optimize, and -s will strip all debugging symbols
.PHONY: release
release:
	@g++ -O3 -Wall -Iinclude/SDL2 -Iinclude/header -Linclude/lib -o bin/main_release src/*.cpp -s -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	@echo You make a release version!
	@echo Let's run it!
	.\bin\main_release.exe

.PHONY: clean
clean: 
	-del .\bin\main.exe .\bin\main_release.exe