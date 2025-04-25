all: parser

testLexer: lexerStandalone.l
	flex lexerStandalone.l
	gcc -o testLexer lex.yy.c
	./testLexer testProg.cmm

parser.tab.c parser.tab.h:	parser.y
	bison -t -v -d --graph parser.y 
	dot -Tpdf parser.gv -o parse.pdf

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

parser: lex.yy.c parser.tab.c parser.tab.h AST.c symbolTable.c semantic.c codeGenerator.c optimizer.c
	gcc -o parser parser.tab.c lex.yy.c AST.c symbolTable.c semantic.c codeGenerator.c optimizer.c 
	./parser testProg.cmm

clean:
	rm -f parser parser.tab.c lex.yy.c parser.tab.h parser.output lex.yy.o parser.tab.o AST.o semantic.o symbolTable.o codeGenerator.o optimizer.o TAC.ir TACoptimized.ir output.s optimizedOutput.s parser.gv parse.pdf parse.pdf testLexer
	ls -l
