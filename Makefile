bin/Dino : src/Dino_chrome.cpp $(wildcard Include/*.hpp)
	mkdir -p bin
	g++ src/Dino_chrome.cpp -o bin/Dino -I Include -I/usr/local/include -L/usr/local/lib -lftxui-screen -lftxui-dom -lftxui-component -lncurses -std=c++2a
run : bin/Dino
	./bin/Dino