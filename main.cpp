#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include <fstream>
#include <iostream>


int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();
    std::string fileName = argv[1];
    std::ifstream input(fileName);

    std::string fileStr;

    std::istreambuf_iterator<char> inputIt(input), emptyInputIt;
    std::back_insert_iterator<std::string> stringInsert(fileStr);

     copy(inputIt, emptyInputIt, stringInsert);

    lexer->Run(fileStr);

    Parser* parser = new Parser(lexer->getToken());
    parser->parse();

    Interpreter* interpreter = new Interpreter(parser->GetProgram());
    interpreter->PrintRelations();

  //lexer->PrintTokens();

    delete lexer;
    delete parser;

    return 0;
}