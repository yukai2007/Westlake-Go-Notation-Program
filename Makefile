CXXFLAGS	= -mthreads -DHAVE_W32API_H -D__WXMSW__ -D_UNICODE \
			-I/c/msys64/mingw64/lib/wx/include/msw-unicode-3.0 \
           		-I/c/msys64/mingw64/include/wx-3.0 \
			-Wno-ctor-dtor-privacy -pipe -fmessage-length=0 -std=c++17 -fexec-charset=GBK \
			-Wno-deprecated-declarations -O2
LINKFLAGS = -static -static-libstdc++ -static-libgcc -mthreads \
    			-L/c/msys64/mingw64/lib \
    			-lwx_mswu_core-3.0 -lwx_baseu-3.0 -lwxjpeg-3.0 -lwxpng-3.0 -lwxzlib-3.0 -lwxregexu-3.0 -lwxexpat-3.0 \
    			-lwx_mswu_adv-3.0 \
    			-lkernel32 -luser32 -lgdi32 -lcomdlg32 -lwinspool -lwinmm -lshell32 -lcomctl32 -lole32 -loleaut32 \
    			-luuid -loleacc -lrpcrt4 -ladvapi32 -lwsock32 -lversion -lshlwapi -mwindows

CXX			= g++ $(CXXFLAGS) -c
LINK		= g++

BIN			= ./binary
OBJ			= ./object
SRC			= ./source
ART			= ./art

FRAME		= frame
CANVAS		= canvas
GAME		= game
APP			= main
BIN_NAME	= GoPlusPlus

.PHONY: build run clean refresh refresh-art relink clean-bin
build: $(BIN)/$(BIN_NAME).exe
run: $(BIN)/$(BIN_NAME).exe
	$(BIN)/$(BIN_NAME).exe
refresh: clean build
clean-bin:
	rm ./binary/*.exe
relink: clean-bin build
refresh-art: clean-art build
clean:
	rm ./object/*.o
	rm ./binary/*.exe
clean-art:
	rm ./object/$(BIN_NAME)_res.o

$(OBJ)/$(BIN_NAME)_res.o: $(ART)/$(BIN_NAME).rc $(ART)/xp_style.manifest
	windres -F pe-x86-64 -I/c/msys64/mingw64/include/wx-3.0 -O COFF $< -o $@

$(OBJ)/$(FRAME).o: $(SRC)/$(FRAME).cpp $(SRC)/$(FRAME).h $(SRC)/$(CANVAS).h $(SRC)/$(GAME).h
	$(CXX) $< -o $@

$(OBJ)/$(CANVAS).o: $(SRC)/$(CANVAS).cpp $(SRC)/$(CANVAS).h $(SRC)/$(GAME).h
	$(CXX) $< -o $@

$(OBJ)/$(GAME).o: $(SRC)/$(GAME).cpp $(SRC)/$(GAME).h
	$(CXX) $< -o $@

# $(OBJ)/$(DIALOG).o: $(SRC)/$(DIALOG).cpp $(SRC)/$(DIALOG).h $(SRC)/$(FRAME_BASE).h $(SRC)/$(APP).h $(SRC)/ai2/board.hpp
# 	$(CXX) $< -o $@

# $(OBJ)/$(FRAME_BASE).o: $(SRC)/$(FRAME_BASE).cpp $(SRC)/$(FRAME_BASE).h $(SRC)/$(APP).h
# 	$(CXX) $< -o $@

$(OBJ)/$(APP).o: $(SRC)/$(APP).cpp $(SRC)/$(FRAME).h $(SRC)/$(CANVAS).h $(SRC)/$(GAME).h
	$(CXX) $< -o $@

# $(OBJ)/ai.o: $(SRC)/ai2/board.cpp $(SRC)/ai2/board.hpp
# 	$(CXX) $< -o $@

$(BIN)/$(BIN_NAME).exe: $(OBJ)/$(APP).o $(OBJ)/$(FRAME).o $(OBJ)/$(CANVAS).o $(OBJ)/$(GAME).o $(OBJ)/$(BIN_NAME)_res.o
	$(LINK)	$^ -o $@ $(LINKFLAGS)
