cmake_minimum_required(VERSION 3.23)
project(project_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(project_1
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.cpp
        Token.h
        PeriodAutomaton.cpp PeriodAutomaton.h CommaAutomaton.cpp CommaAutomaton.h QMarkAutomaton.h QMarkAutomaton.cpp LeftParenAutomaton.cpp LeftParenAutomaton.h RightParenAutomaton.cpp RightParenAutomaton.h AddAutomaton.cpp AddAutomaton.h MultiplyAutomaton.cpp MultiplyAutomaton.h FactsAutomaton.cpp FactsAutomaton.h RulesAutomaton.cpp RulesAutomaton.h SchemesAutomaton.cpp SchemesAutomaton.h QueriesAutomaton.cpp QueriesAutomaton.h StringAutomaton.cpp StringAutomaton.h IDAutomaton.cpp IDAutomaton.h CommentAutomaton.cpp CommentAutomaton.h EOFAutomaton.cpp EOFAutomaton.h DatalogProgram.h Parser.cpp Parser.h Predicate.cpp Predicate.h Rule.cpp Rule.h Parameter.cpp Parameter.h Tuple.cpp Tuple.h Header.cpp Header.h Relation.cpp Relation.h Database.cpp Database.h Interpreter.cpp Interpreter.h)
