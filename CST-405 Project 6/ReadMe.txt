ReadMe:
To run this compiler you will need Bison version 3.8.2 and flex 2.6.4.

To download these you must follow these instructions:
  If you have Windows:
    Download from https://sourceforge.net/projects/ezwinports/files/ and follow the instructions.
  If you have Mac:
    Install homebrew if you do not have it by using /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)" in the terminal.
    Then in the terminal use command brew install flex
    Then use command brew install bison
  If you have Linux:
    First open the terminal and type commands:
      wget https://github.com/westes/flex/releases/download/v2.6.4/flex-2.6.4.tar.gz
      tar -xvzf flex-2.6.4.tar.gz
      cd flex-2.6.4
      ./configure
      make
      sudo make install
    Then type commands:
      wget https://ftp.gnu.org/gnu/bison/bison-3.8.2.tar.gz
      tar -xvzf bison-3.8.2.tar.gz
      cd bison-3.8.2
      ./configure
      make
      sudo make install

Now you should have Bison version 3.8.2 and flex 2.6.4.

After these have been downloaded you can run the program using the command "make clean; make" in the terminal of the project.

This should go through any code in the "testProg.cmm" and output the final program in "optimizedOutput.s".

If you want to write any code, you can write it in "testProg.cmm".
All code must be within the context of a function.
All non-comment written lines within functions must end with a semicolon.
    ex. write x;
    
You may write comments either using // or /**/.
    ex. // write x;
    ex. /* write x;
        write y notes etc
        */

To declare a function, you must use the format of func "returnType" functionName("parameter") {"desired body of function"}.
    ex. func int addOne(int x) {
            x = x + 1;
            return x;
        }

You can return variables in functions by typing return variableName;
    ex. return x;

To use the main function, you must type the format void func main() {"desired body for main"}.
    ex. void func main() {
            int x = 0;
            write x;
        }

To declare variables you can use type variableName or type variableName = value. The available types are int, bool, string, and float.
    ex. int x;
    ex. string y = "red";

You can adjust variable values by using the format of variableName = variable operator variable.
    ex. x = y + 5;

Valid operators are:
    +    for addition
    -    for subtraction
    *    for multiplication
    /    for division

You can print out variables using the command, write variableName/value or write(variableName/value).
    ex. write x;
    ex. write("hello");

You can use declared functions by using the format of functionName("parameter").
    ex. x = addOne(x);

You can use if statements by typing in the format of if(expr){body}else if(expr){body}else{body}. (The else if and else are not required but if is required to have either of them)
    ex. if (x > y) {
            write(x);
        } else if (x == y) {
            write("same");
        } else {
            write y;
        }

Finally you can write while loops by following the format of while(expr){body}
    ex. while(x < 10) {
            write(x);
        }
  
Valid expressions for if and while statements are:
    ==    for checking if they are equal
    !=    for checking if they are not equal
    >     for checking if parameter 1 is bigger than parameter 2
    <     for checking if parameter 1 is smaller than parameter 2
    >=    for checking if parameter 1 is bigger than or equal to parameter 2
    <=    for checking if parameter 1 is smaller than or equal to parameter 2