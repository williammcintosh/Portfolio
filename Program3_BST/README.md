This is the first beta version of Program 3.
It uses a BST and has a pretty print feature that I created myself.
The pretty print is accomplished by creating a third pointer which is the "parent" pointer.
As opposed to just have a "left" and "right" pointer for each node,
the "parent" pointer points back up to it's parent.
The relationship between the parent and it's child determines the path that gets created.
This path is stored in each node and is called the "ancestor path".
For instance the smallest node in the BST will have an "ancestor path" of LLL0
for a BST with a height of four. Meaning, it's relationship to it's parent
is that it is the Left child, and that node's relationship is a left child.
The zero represents the root, which is not a left or a right child and has no parent.
Then, when printing, the print manager looks for each node specifically based on
it's ancestor path and adds tabs which logarithmically get smaller from top to bottom,
to allow for even spacing.

Supports "holes". Only works for BST's of hieght 4.
Using the txt file (for instance I used the vim command ./a.out < test.txt)
to build a full tree quickly and in an order that is supported for a BST.

Will McIntosh
5-15-20
