This program acts as a feed for job postings.
All sources are txt files.
The data structure is an array of linear linked lists.
Each element in the array represents the posting's priority.
It can therefore have direct access to the head pointer of each LLL.
Sort of like a hash table.
Also, the highest priority (the lowest number) comes up first in the array.
Collisions are handled by adding nodes to the LLL.

Will McIntosh
6-2-20
