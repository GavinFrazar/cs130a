# Findings
| Method                                       	| BST (time to perform 100 times) 	| O(f(n)) 	| Hash Table (time to perform 100 times) 	| O(g(n))    	|
|----------------------------------------------	|---------------------------------	|---------	|----------------------------------------	|------------	|
| Search                                       	| 1.06 * 10<sup>-4</sup> seconds  	| O(n)    	| 7.52 * 10<sup>-5</sup> seconds         	| O(n)       	|
| Insert                                       	| 1.0 * 10<sup>-4</sup> seconds  	| O(n)    	| 6.47 * 10<sup>-5</sup> seconds         	| O(n)       	|
| Delete                                       	| 1.02 * 10<sup>-4</sup> seconds  	| O(n)    	| 6.85 * 10<sup>-5</sup> seconds         	| O(n)       	|
| Sort                                         	| 5.78 * 10<sup>-3</sup> seconds  	| O(n)    	| 1.56 * 10<sup>-2</sup> seconds         	| O(nlog(n)) 	|
| Range query (n=10) ["a-","ab"]               	| 5.67 * 10<sup>-5</sup> seconds  	| O(n)    	| 2.35 * 10<sup>-3</sup>                 	| O(n)       	|
| Range query (n=100) ["a-","accommodations-"] 	| 4.35 * 10<sup>-4</sup> seconds  	| O(n)    	| 3.75 * 10<sup>-3</sup>                 	| O(n)       	|
| Range query (n=1000) ["a-","assure"]         	| 2.61 * 10<sup>-3</sup> seconds  	| O(n)    	| 6.15 * 10<sup>-3</sup>                 	| O(n)       	|

# Conclusions
The binary search tree and hash table have roughly equal Search, Insert, and Delete times for performing one-hundred of each operation, differing by neglible margins in Insert and Delete, with some constant factor difference in Search time. The sort function is where there is a clear difference. The BST sort is much faster than the Hash Table, because the BST sort is O(n) (if the tree is already constructed, since this corresponds to an in-order-traversal of the tree), while the Hash Table sort is the same as sorting an array O(nlog(n)).  The Binary Search Tree range function is faster than hashtable for small n, because I implemented the range function to find the root of the "in-range" subtree, rather than traversing the entire tree. As the the number of words in the range grows, the BST approaches the same time as the hash table, which corresponds to the range subtree height increasing. Hashtable range is roughly equal for any choice of n, since the entire array must be traversed no matter what.

As for my reasoning for the worst case complexity of each operation:
Since BST is not a balanced tree, it's possible that the search, insert and delete become the same as a search of an ordered linked list (O(n)). The Hash Table could possibly have all words hash to the same location, so the Search, Insert, and Delete become O(n).  Sort and Range were explained previously.
