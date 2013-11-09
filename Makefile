##
# This file is part of 3T
# Copyright (C) 2011-2013 Gabriel Margiani
#
# 3T is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# 3T is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with 3T.  If not, see <http://www.gnu.org/licenses/>.
##

CXX=g++

CXXFLAGS=-O2

all: 3T
%.o: src/%.cpp
	$(CXX) -c $(CFLAGS) $<
3T: KI.o main.o
	$(CXX) -o $@ $^ $(LDFLAGS)
clean:
	rm -f *.o

