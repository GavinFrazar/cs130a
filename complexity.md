| Method                                       	| BST (time to perform 100 times) 	| O(f(n)) 	| Hash Table (time to perform 100 times) 	| O(g(n))    	|
|----------------------------------------------	|---------------------------------	|---------	|----------------------------------------	|------------	|
| Search                                       	| 2.95 * 10<sup>-5</sup> seconds  	| O(n)    	| 1.31 * 10<sup>-5</sup> seconds         	| O(n)       	|
| Insert                                       	| 3.19 * 10<sup>-5</sup> seconds  	| O(n)    	| 2.84 * 10<sup>-5</sup> seconds         	| O(n)       	|
| Delete                                       	| 2.28 * 10<sup>-5</sup> seconds  	| O(n)    	| 2.66 * 10<sup>-5</sup> seconds         	| O(n)       	|
| Sort                                         	| 5.78 * 10<sup>-3</sup> seconds  	| O(n)    	| 1.56 * 10<sup>-1</sup> seconds         	| O(nlog(n)) 	|
| Range query (n=10) ["a-","ab"]               	| 5.67 * 10<sup>-5</sup> seconds  	| 10      	| 6.11 * 10<sup>-3</sup>                 	| 10         	|
| Range query (n=100) ["a-","accommodations-"] 	| 4.35 * 10<sup>-4</sup> seconds  	| 100     	| 6.48 * 10<sup>-3</sup>                 	| 100        	|
| Range query (n=1000) ["a-","assure"]         	| 4.50 * 10<sup>-3</sup> seconds  	| 1000    	| 4.61 * 10<sup>-3</sup>                 	| 1000       	|
