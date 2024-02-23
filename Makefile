TARGET = minarma5

CXX = g++
CXX_FLAGS = -Wall -pedantic -Wextra -std=c++14 -g

MKDIR = mkdir -p
BUILD_DIR = build
SRC_DIR = src

.PHONY: all
all: compile doc

.PHONY: compile
compile: $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET)

$(TARGET): $(BUILD_DIR)/CMatrix.o $(BUILD_DIR)/COperator.o $(BUILD_DIR)/COperatorMinus.o $(BUILD_DIR)/COperatorMulti.o $(BUILD_DIR)/COperatorPlus.o  $(BUILD_DIR)/CInterface.o $(BUILD_DIR)/CCommand.o $(BUILD_DIR)/CApplication.o $(BUILD_DIR)/main.o $(BUILD_DIR)/CDenseMatrix.o $(BUILD_DIR)/CSparseMatrix.o
	$(CXX) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(MKDIR) $(BUILD_DIR) 
	$(CXX) $(CXX_FLAGS) $< -c -o $@


$(SRC_DIR)/%.cpp:
doc: Doxyfile $(SRC_DIR)/CMatrix.h $(SRC_DIR)/COperator.h $(SRC_DIR)/COperatorMinus.h $(SRC_DIR)/CSparseMatrix.h $(SRC_DIR)/CDenseMatrix.h $(SRC_DIR)/COperatorMulti.h $(SRC_DIR)/COperatorPlus.h $(SRC_DIR)/CCommand.h $(SRC_DIR)/CInterface.h $(SRC_DIR)/CApplication.h
	doxygen Doxyfile

.PHONY: clean
clean:
	rm -rf $(TARGET) doc/ $(BUILD_DIR)/ 2>/dev/null


$(BUILD_DIR)/CMatrix.o: $(SRC_DIR)/CMatrix.cpp $(SRC_DIR)/CMatrix.h
$(BUILD_DIR)/COperator.o: $(SRC_DIR)/COperator.cpp $(SRC_DIR)/COperator.h $(SRC_DIR)/CMatrix.h
$(BUILD_DIR)/COperatorMinus.o: $(SRC_DIR)/COperatorMinus.cpp $(SRC_DIR)/COperatorMinus.h $(SRC_DIR)/COperator.h $(SRC_DIR)/CMatrix.h $(SRC_DIR)/CSparseMatrix.h $(SRC_DIR)/CDenseMatrix.h
$(BUILD_DIR)/COperatorMulti.o: $(SRC_DIR)/COperatorMulti.cpp $(SRC_DIR)/COperatorMulti.h $(SRC_DIR)/COperator.h $(SRC_DIR)/CMatrix.h $(SRC_DIR)/CSparseMatrix.h $(SRC_DIR)/CDenseMatrix.h
$(BUILD_DIR)/COperatorPlus.o: $(SRC_DIR)/COperatorPlus.cpp $(SRC_DIR)/COperatorPlus.h $(SRC_DIR)/COperator.h $(SRC_DIR)/CMatrix.h $(SRC_DIR)/CSparseMatrix.h $(SRC_DIR)/CDenseMatrix.h
$(BUILD_DIR)/CInterface.o: $(SRC_DIR)/CInterface.cpp $(SRC_DIR)/CInterface.h $(SRC_DIR)/CMatrix.h $(SRC_DIR)/CConstants.h
$(BUILD_DIR)/CCommand.o: $(SRC_DIR)/CCommand.cpp $(SRC_DIR)/CCommand.h $(SRC_DIR)/CMatrix.h $(SRC_DIR)/COperator.h $(SRC_DIR)/CInterface.h
$(BUILD_DIR)/CApplication.o: $(SRC_DIR)/CApplication.cpp $(SRC_DIR)/CApplication.h  $(SRC_DIR)/CMatrix.h $(SRC_DIR)/COperator.h $(SRC_DIR)/CCommand.h $(SRC_DIR)/CInterface.h $(SRC_DIR)/COperatorPlus.h $(SRC_DIR)/COperatorMinus.h $(SRC_DIR)/COperatorMulti.h $(SRC_DIR)/CSparseMatrix.h $(SRC_DIR)/CDenseMatrix.h
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/CApplication.h  $(SRC_DIR)/CMatrix.h $(SRC_DIR)/COperator.h $(SRC_DIR)/CCommand.h $(SRC_DIR)/CInterface.h $(SRC_DIR)/COperatorPlus.h $(SRC_DIR)/COperatorMinus.h $(SRC_DIR)/COperatorMulti.h $(SRC_DIR)/CSparseMatrix.h $(SRC_DIR)/CDenseMatrix.h
$(BUILD_DIR)/CDenseMatrix.o: $(SRC_DIR)/CDenseMatrix.cpp $(SRC_DIR)/CDenseMatrix.h $(SRC_DIR)/CMatrix.h
$(BUILD_DIR)/CSparseMatrix.o: $(SRC_DIR)/CSparseMatrix.cpp $(SRC_DIR)/CSparseMatrix.h $(SRC_DIR)/CMatrix.h
