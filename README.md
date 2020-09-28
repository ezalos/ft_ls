# ft_ls

This project reimplement in C the ls function
It's MAC and Linux compatible !

## Description

```DESCRIPTION
       List information about the FILEs (the current directory by default).  Sort entries alphabetically if none of -t and -r is specified.

```

This project is from the 42 school.
You can find the subject in the directory of the same name

## Getting Started

* ```make```
  * It will compile the project
* ```./ft_ls```
  * This allows you to execute the program
* ```./ft_ls --help```
  * And this command will instruct you on the usage of the program

## Options

* ```-l```  Will list files in columns
  * ```total BLOCKS```
	* For each directory that is listed, preface the files with a line `total BLOCKS`, where BLOCKS is the total disk allocation for all files in that directory.
	* Each block is 512B and ls give the total size in K
	* Total block_size = Sum(files.block_size * 512) / 1024
  * ```file type and rights```
	* resource : https://en.wikipedia.org/wiki/File-system_permissions#Notation_of_traditional_Unix_permissions
  * ```number of links```
    * Generate all the Makefile sources needed to compile what's inside your srcs/ folder

## Tests

The test folder possess a vast variety of files to validate the similarity of my version.

A Testor thought at this effect can be launch with ```python3 tests/testor.py```

## Acknowledgments

Thank you for using my project !
