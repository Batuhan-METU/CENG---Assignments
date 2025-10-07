Make sure you have a file named the4.py in the this directory and have defined a function OX_to_tree that takes a list as a parameter

There are 8808 small cases, 5901 medium cases, 5059 large cases and 2642 HUGE cases

Small cases contain between 8 and 51 ox strings
Medium cases contain between 50 and 200 ox strings
Large cases contain between 200 and 1.000 ox strings
HUGE cases contain between 1.000 and 10.000 ox strings

Run the4_tester.py as a python script to test your code.

CASE: Tells you the number of the case. You can check it in the corresponding file in the "Cases" folder
RESULT: Whether the code has passed or failed
TIME: The time it took for the function to output the tree
PROBLEM: Specifies the reason the code failed. Namely:
    "Not Psi": At least one of the elements of the tree is not a psi function of the parent node (i.e. the child can not be derived by replacing an 'o' of the parent string with an 'x').
    "Twins": At least one of the nodes has two of the same children.
    "Added element": An element that is not in the original test case is included in the tree or an element is included more than once.
    "Discarded element": An element that is in the original test case is not included in the tree.
    "Changed element": The number of element in the original test case and the tree is the same but at least one of the elements has been changed.
    "Bad tree structure": A node with no children has been represented as a list (it should be represented as just the datum).