<h1 align="center">JSONcxx</h2>
<p align="center">A simple, short, single-header JSON library for C++</p>
<p align="center">
	<a href="./LICENSE">
		<img alt="License" src="https://img.shields.io/badge/license-GPL-blue?color=7aca00"/>
	</a>
	<a href="https://github.com/LordOfTrident/jsoncxx/issues">
		<img alt="Issues" src="https://img.shields.io/github/issues/LordOfTrident/jsoncxx?color=0088ff"/>
	</a>
	<a href="https://github.com/LordOfTrident/jsoncxx/pulls">
		<img alt="GitHub pull requests" src="https://img.shields.io/github/issues-pr/LordOfTrident/jsoncxx?color=0088ff"/>
	</a>
	<br><br><br>
	<img width="500px" src="pic/logo.png"/>
</p>

JSON (JavaScript Object Notation) is a lightweight data-interchange format, read more here https://www.json.org/json-en.html

## Compiling and running the example
#### Linux
Run `compile` as bash in the terminal:
```sh
bash compile
```
If you dont want it to check for g++, you can use the `-nc` parameter.
This will generate an executable in bin folder, run it:
```sh
./bin/app
```
#### Windows
First make sure you have g++ installed (Command Prompt will not recognize the `g++` command if you dont) and run the following commands:
```bat
mkdir bin
g++ -g example/main.cc -o bin/app -O3 -s -Wall -std=c++17;
```
then run it:
```bat
cd bin
app
```

## Library usage
*Im gonna update this soon :)*
