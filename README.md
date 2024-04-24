# sk_minlexsol
This is a small package designed to work on the sudoku solution grids expressed in min lexical morph.

The core of the package is a catalog builder finding directly the solution grids in the min lexical order.
We have NED= 5 472 730 538 such solution grids. So the program is designed to be somehow a virtual storage of these NED solution grids.

The catalog builder can start at various points of the search, using tables giving the count of upstream solution grids. 
The starts can be

. the first band (usually given throudh the 0-415 id of the min lexical "one band"
. The first band plus the minirow r4c1,r4c2,r4c3 with 9992 known possibilities
. the first band plus the row 4, with 652408 known possibilities.

The last step (after row4) is always done by the catalog builder.

The package will also offer a direct link { min lexical sol <==> NED rank }
And the same starting from any solution grid first moved to the min lexical morph.

The first version of the repository contains the catalog builder and the tables to use for future options.

As virtual storage of the catalog, this package takes around 4 MB to compare to GB (tens of) for compressed versions of the NED solution grids.


