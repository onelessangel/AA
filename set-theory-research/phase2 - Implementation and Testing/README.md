							 ____  _____    _    ____  __  __ _____
							|  _ \| ____|  / \  |  _ \|  \/  | ____|
							| |_) |  _|   / _ \ | | | | |\/| |  _|
							|  _ <| |___ / ___ \| |_| | |  | | |___
							|_| \_\_____/_/   \_\____/|_|  |_|_____|

									Stroe Teodora, 321CA

1. File guide
```
	.
	├── avl
	│	├── avl.c		-> AVL implementation
	│	├── avl.h		-> header file for the AVL implementation
	│	└── utils.h		-> DIE macro used for checking the error code returned by a system call
	├── hashmap
	│	├── Hashtable.c		-> hashtable implementation
	│	├── Hashtable.h		-> header file for the hashtable implementation
	│	├── LinkedList.c	-> linked list implementation
	│	├── LinkedList.h	-> header file for the linked list implementation
	│	└── utils.h		-> DIE macro used for checking the error code returned by a system call
	├── in
	│	└── testX.in		-> input files
	├── out
	│	└── testX.out		-> output files
	├── test_avl
	│	├── commands.c		-> insert/delete/modify commands implementation for AVL
	│	├── commands.h		-> header file for the AVL  commands implementation
	│	├── main_avl.c		-> main file for the AVL test
	│	├── messages.c		-> message functions
	│	├── messages.h		-> header file for message functions
	│	└── utils.h		-> DIE macro used for checking the error code returned by a system call
	├── test_ht
	│	├── commands.c		-> insert/delete/modify commands implementation for hashtable
	│	├── commands.h		-> header file for the hashtable  commands implementation
	│	├── main_ht.c		-> main file for the hashtable test
	│	├── messages.c		-> message functions
	│	├── messages.h		-> header file for message functions
	│	└── utils.h		-> DIE macro used for checking the error code returned by a system call
	├── test_treap
	│	├── commands.c		-> insert/delete/modify commands implementation for treap
	│	├── commands.h		-> header file for the treap  commands implementation
	│	├── main_treap.c	-> main file for the treap test
	│	├── messages.c		-> message functions
	│	├── messages.h		-> header file for message functions
	│	└── utils.h		-> DIE macro used for checking the error code returned by a system call
	├── time
	│	├── time_avl.txt	-> average time of AVL execution for each input file
	│	├── time_ht.txt		-> average time of hashtable execution for each input file
	│	└── time_treap.txt	-> average time of treap execution for each input file
	├── treap
	│	├── treap.c		-> treap implementation
	│	└── treap.h		-> header file for the treap implementation
	├── engmix.txt			-> a list of 84,000 English words
	├── Makefile
	├── README
	└── test_generator.sh		-> script used to automatically generate input files
```
2. Test generator

	## Installation

	chmod a+x test_generator.sh

	## Usage

	./test_generator.sh [NO_COMMANDS] [INPUT_TYPE]

	NO_COMMANDS - positive natural number
	INPUT_TYPE  - {int, string}

	- If the `INPUT_TYPE` is not specified, the script will generate commands using strings.
	- If the `NO_COMMANDS` is not specified, is not a positive natural number, or there are no
	arguments given at all, the script will display an error message and no test file will be
	generated.

	## Output

	The script will output a file named `out` in the `in` input folder. If a file with the same
	name already exists, it will be overwritten.

	## Description

	On the first line of the generated file is printed the number of commands contained in it,
	followed by the input type.
	Afterwards, the script generates a number of `NO_COMMANDS` random commands, each on a new line.

	There are 3 available commands:
	1. `insert` <new_element>
	2. `delete` <existing_element>
	3. `modify` <existing_element> <new_element>

	- If the `INPUT_TYPE` is `int`, the <new_element> is a random number with the maximum value of
	32767, which is the upper limit for a signed 16 bit integer. Otherwise, the <new_element> is a
	word in English choosen at random from a list of 84,000 English words contained in the file
	`engmix.txt` [1].
	- The <existing_element> is chosen at random from arguments of the last 10 commands previously
	printed in the file. If the command the element is chosen from has two arguments, the latter is
	selected. This approach minimizes the number of possibilities that the selected item no longer
	exists. If there are no previous elements to choose from, a new element is used.

3. Test structure

	## Input test format

	- On the first line:
		N (int - the number of commands in the file)
		input_type (string - the type of data in the test: {int, string})
	- On the following N lines:
		<command> <element> - the command can be {insert, delete, modify}
							- the element respects the input type

	## Output test format

	- On each line, a message according to the outcome of the task:
		* insert:
			- successful insertion -- "<element> added"
			- unsuccessful insertion -- "<element> already exists"
		* delete:
			- successful deletion -- "<element> deleted"
			- unsuccessful deletion -- "<element> can't be deleted"
		* modify:
			- successful modification -- "<old_element> modified into <new_element>"
			- unsuccessful modification -- "<old_element> cannot be modified"

4. Implementation details

	- The implementation of the data structures are based on the frameworks available on Open
	CourseWare, more precisely, the SD laboratories in which the notions of dictionary [2],
	treap [3] and avl trees [4] are presented.
	- The best algorithm was chosen based on the comparison of the execution times of each algorithm.
	The time results for each test file, sorted by algorithm, are in the `time` folder, each in a
	different file named time_ALGORITHM_NAME.txt.

5. Sources

	[1] http://www.gwicks.net/dictionaries.htm
	[2] https://ocw.cs.pub.ro/courses/sd-ca/laboratoare/lab-04
	[3] https://ocw.cs.pub.ro/courses/sd-ca/laboratoare/lab-10
	[4] https://ocw.cs.pub.ro/courses/sd-ca/laboratoare/lab-11
