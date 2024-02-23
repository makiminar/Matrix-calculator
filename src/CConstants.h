/**
* @author Marketa Minarova <minarma5@fit.cvut.cz>
* @date 22.05.20
*/

#pragma once

/** command names */

const char * const COMMAND_HELP = "HELP";
const char * const COMMAND_OP = "OP";
const char * const COMMAND_MERGE = "MERGE";
const char * const COMMAND_SPLIT = "SPLIT";
const char * const COMMAND_SCAN = "SCAN";
const char * const COMMAND_TRANS = "TRANS";
const char * const COMMAND_INV = "INV";
const char * const COMMAND_DET = "DET";
const char * const COMMAND_RANK = "RANK";
const char * const COMMAND_GEM = "GEM";
const char * const COMMAND_QUIT = "QUIT";
const char * const COMMAND_PRINT = "PRINT";

/** messages and quotes in program */

const char * const ENTER_QUOTE = "Type your command:";
const char * const DET_QUOTE = "Determinant is: ";
const char * const RANK_QUOTE = "Rank is: ";
const char * const DELIMITER = " ..... ";
const char * const MSG_INVALID_INPUT = "Invalid input.";
const char * const MSG_INVALID_MATRIX_SIZE = "Invalid matrix size.";
const char * const MSG_INVALID_INDEX = "Matrix index out of range.";
const char * const MSG_NOT_SQUARE_MATRIX = "Matrix is not square.";
const char * const MSG_SINGULAR_MATRIX = "Matrix is singular, inverse matrix does not exist.";
const char * const MSG_WRONG_COMMAND = "Command not found, type 'HELP' to see the command menu.";
const char * const MSG_EXISTING_MATRIX = "Matrix with such name already exists, enter other name: ";
const char * const MSG_MATRIX_NOT_FOUND = "Named matrix not found.";

/** command descriptions */

const char * const DESCRIPTION_HELP = "shows description and usage of every command.";
const char * const DESCRIPTION_OP = "is a complex command, it indicates that there is new matrix to be created. Here are all the usages:\n"
                                    "Usage1: OP X = 1 (3,3)\n"
                                    " --> this creates new identity matrix of size 3x3, named X\n"
                                    "Usage2: OP X = A + B\n"
                                    " --> this creates new X matrix, which is a result of addition of matrices A, B\n"
                                    "Usage3: OP X = A - B\n"
                                    " --> this creates new X matrix, which is a result of subtraction of matrices A, B\n"
                                    "Usage4: OP X = A * B\n"
                                    " --> this creates new X matrix, which is a result of multiplication of matrices A, B\n"
                                    "Usage5: OP X = MERGE A B\n"
                                    " --> this creates new X matrix, which is merged from A, B";
const char * const DESCRIPTION_MERGE = "merges 2 matrices together if they share same row-size.\n"
                                       "Usage:  MERGE A B\n"
                                       " --> this rewrites matrix A to a new one that is merge from A, B\n"
                                       "For other usage see command OP.";
const char * const DESCRIPTION_SPLIT = "splits given matrix to a new one, given by new size and position, from which to cut.\n"
                                       "Usage: SPLIT A [3][3] (3,1)\n"
                                       " --> this cuts matrix A to a new ( with same name ) with size 3x3 from 3rd row, 1st column";
const char * const DESCRIPTION_SCAN = "takes user's input and creates new matrix, which is stored in application"
                                      "\nUsage: SCAN X [3][2]\n1 2\n3 4\n5 6";
const char * const DESCRIPTION_TRANS = "evaluates transposition of a given matrix.";
const char * const DESCRIPTION_INV = "finds inverse of a given matrix, if possible.";
const char * const DESCRIPTION_RANK = "calculates the rank of given matrix.";
const char * const DESCRIPTION_DET = "evaluates determinant of a given matrix ( only for square matrices ).";
const char * const DESCRIPTION_GEM = "evaluates Gauss Elimination for given matrix.";
const char * const DESCRIPTION_QUIT = "exits the program.";
const char * const DESCRIPTION_PRINT = "displays given matrix.";


