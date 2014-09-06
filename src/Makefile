C = gcc
CXX = g++

CFLAGS= -O3
SRC_DIR=./

SRCLIST_CPP = $(wildcard $(addsuffix *.cpp,$(SRC_DIR)))
OBJECTS = $(subst .cpp,.o,$(SRCLIST_CPP))
TARGET=binary2double.out

all:$(TARGET)
$(TARGET):$(OBJECTS)

debug:$(TARGET)
	$(CXX) -o ../$@ -g -Wall -O0 $(INCLIST)  $(SRCLIST_CPP)

# .dファイルを読み込む
-include $(subst .c,.d,$(SOURCES))

PHONY: check-syntax
check-syntax:
	$(CXX) -Wall -Wextra -pedantic -fsyntax-only $(CHK_SOURCES)

# .cppファイルを解析して、.cppが依存しているヘッダファイルを.dファイルに書き出す g++ -M
%.d: %.cpp
	$(CXX) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

clean:
	@rm -rf ../*.out *.o  *.d  *.deps  ../*.dSYM ../debug  \ Doxygen *.bak

#sufix rule
.cpp.o:
	$(CXX) -o $@ $(CFLAGS) $(INCLIST) -c $<
.o.out:
	$(CXX) -o ../$@ $(CFLAGS) $(INCLIST)  $<
doc:docclean
	doxygen -g
	Doxygen Doxyfile
	rm Doxyfile
	rm -rf latex
	mv html ../
docclean:
	rm -rf ../html  \ Doxygen
