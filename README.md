# bscript
`bscript` is a play-thing scripting language. It cannot be compiled to an executable, but could be executed by typing 
`bscript $(FILE_NAME)`. Every commands are seperated by newline.

There are only 999 `double` variables named `v001`, `v002`, `v003`, ..., `v999`. Note that whatever the number is, one must turn it into three digits by adding `0` in the front. e.g. expressions like `v7` should be changed to `v007`, `v12` to `v012` etc.

For comments, begin the line with an `#`. Note that comments cannot be in the first line of the file.

It currently supports the following syntaxes (here, `$(INTEGER)` should be some number between 1 and 999; `$(STRING_LITERAL)` is some string literal; `$(EXPRESSION)` is an expression consists of `||, &&, ==, !=, >=, <=, >, <, -, +, %, /, *, !`, `v001` to `v009`, and floating-point numbers, and *no* parentheses. These operators are stated according to their priorities):
* `s $(STRING_LITERAL)` prints the string to the output stream. Note that there is no need to add quotation marks to the string literal.
* `n` prints `'\n'` to the output stream
* `t $(INTEGER)` sets a target for `g` (stated below)
* `g$(INTEGER) $(EXPRESSION)` is a goto-like command. It let the program jump to the line where `t $(INTEGER)` is at if the value of `$(EXPRESSION)` is nonzero. It could be used to implement if clause, switch, and various loops.
* `i $(INTEGER)` reads a `double` from the input stream, and load it to the variable `v$(INTEGER)`
* `o $(INTEGER)` outputs the value of the variable `v$(INTEGER)`
* `a$(INTEGER) $(EXPRESSION)` loads the value of `$(EXPRESSION)` to the variable `v$(INTEGER)`
* `e` Terminate the program.

You may see `sample.txt` for an example of a `bscript` program
