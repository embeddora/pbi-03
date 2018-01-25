#
# Copyright (C) 2018 ARNERI arneri@ukr.net All rights reserved
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
#  Abstract: a makefile for 'Post-Browser Interface #3' project


# Project Name, i.e. 'Post-Browser Interface #3' abbreviated 
PROJ	=PBI3


CPPFLAGS=-I./include   -std=gnu++11  -g
#
# -g -- debug symbols (to explore dumped core, for instance)
#

LDFLAGS=    -lSDL2main -lSDL2


OBJS=   source/core/Camera.cpp.o source/core/Engine.cpp.o \
	source/core/Mesh.cpp.o source/core/MeshManager.cpp.o \
	source/main.cpp.o source/render/AppWindow.cpp.o \
	source/render/SDL2/AppWindowSDL2.cpp.o \
	source/render/SDL2/DrawSDLUtils.cpp.o

# Not cross-compiling till instance for <Linux/i585> platform is ready
PREFIX=

DOCSCFG=./resources/documents.cfg

DOCSDIR=./resources/documents

CPP=$(PREFIX)g++

LD=$(PREFIX)ld

TARGET=_main

all:	$(OBJS) $(TARGET)

%.cpp.o: %.cpp
	$(CPP) $(CPPFLAGS)  -c -o $@ $<

$(TARGET): $(OBJS)
	$(CPP)  $(OBJS)       -o $@  $(LDFLAGS)

GRBG=	source/render/SDL2/*.o source/render/*.o source/*.o source/core/*.o       \
	source/render/SDL2/*~  source/render/*~  source/*~  source/core/*~        \
	include/render/SDL2/*~ include/render/*~ include/math/*~  include/core/*~ \
	./*.o ./*~

GRBGxt= $(TARGET) $(DOCSDIR) core  *.tar.gz resources/*~


.PHONY: clean docs tar 

docs: $(DOCSCFG)
	doxygen $<

tar:
	$(MAKE) clean ; $(MAKE) docs; tar cfvz $(PROJ).source.tar.gz ./source   ./include   ./resources/meshes ; tar cfvz $(PROJ).docs.tar.gz $(DOCSDIR)

clean:
	rm $(GRBG) $(GRBGxt) ; rm -r -v $(DOCSDIR)
