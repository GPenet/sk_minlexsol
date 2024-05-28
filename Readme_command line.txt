A quick command line guide for anybody willing to test the code

The code has so far 8 active processes numered "10" "11" "20" "30" "80" "81" "90" "91" "92"

"10" 
testing a chunk of solution grids defined by the rank 
for each rank, the solution grid is searched, then the rank is searched for the found solution grid

parameters
. first rank
. increment
currently limited to 11 solution grids


"11"
Testing one given rank (assumed known solution grid by the user)

find the solution grid corresponding to the given rank
look for the rank using the found solution grid
and do the same using a non minimal morph of the solution grid

parameter : rank to test


"20"
entry is a file of solution grids in any form
output is the file in minlex form 
currently in test mode, Missing the cleaning of the code and the final output in the "results" file


"30"
process used to create the table of rows4 
starting from the file produced by the code builder

"31"
print a partial catalog for a given chunk of rows 4parameters :
. firs row4 ot expand (0-652408)
. last row4 to expand
note : for a given row4, the number of solution grids can be around 50 000
the count per row4 is in the rable located in catr4nsol

"80"
this the enumeration through the catalog builder 
the test uses the known count per band to give the possibility to run the enumaration for part of the catalog

parameters :
first band 1 (0-415)
last band 1 (0-415)

"81"
same as "80", using the rows4 table.
This is a check that the rows4 gives the same results than the direct builder.

"90"
miscellaneous temporary  tasks run building the tables using mladen's file


"91"
current work to recognize the gangster using a morph of the internal table



"92"
finding the solution grids per gangster
results file containd the 1892 possible fills for a gangster shon in min lexical morph
fill;gangster;rank for the gangster; band 1 index (0-415)
157423968249186573368759124;43;6,358


Command line ====================================================

the command line is a variant of my general command line structure
the grneral parameters are

"xxx.exe"  -cnn -i"file" -o"outputroot" >"cout redirection"

"xxx.exe" is here sk_gcat
-cnn ne of the -c10 ... -c92
-i"file" if needed the entry file as -iww.txt

-o"outputroot"
>"cout redirection"

usually names for files to get as output

if -o"outputroot" is -omyoutput
the used output name here will be myoutput-file1.txt
(in other programs could be _file1   _file2...)

"cout redirection" is the standard output redirection, Could be for example myoutput_cout.txt

specific parameters for each process=======================

here they are some among the 10 expected integers of the form -va-nnnnnn where

a is one of the digits 0-9 (usually, added "-vx-" with mathmagics for a specific use.
nnnnnn is the parameter value.


"10" 

sk_gcat -c10 -v0-1000256899  -v1-1384652 -odt10 >dt10_couta.txt

looking for solution grid rank 
a1=1000256899
a2= a1+1384652
...
a11=a1+10*1384652

adding -v2-1 ask for some output in dt10_file1.txt
_________________________________________________

"11" 

sk_gcat -c11 -v0-5011334115  -v2-1  -odt11 >dt11_coutb.txt

looking for solution grid rank 5011334115
-v2-1 ask for some output in dt10_file1.txt
______________________________________

"20"

sk_gcat -c20 -v0-0 -v1-10  -v2-1 -ipass1.txt -odt20 >dt20_cout.txt

reading solution grids 0 to 10 in the file pass1.txt
giving the minlex morph (currently in cout

hereabove the pass1.txt first records

123456789457189326698273514384791652512864937769325841271938465846517293935642178;....5...94...8.3.........1....7.16..5..................71.....5..6..........42..8;1;107
123456789456789123789123456367592814592841367841637295214975638675318942938264571;.2.4.......6...1.......3.5...7.9.8............4..............3.....1..429.8.6....;2;359
123456789456789123789123456214537968835691247967248531348972615571864392692315874;...4...8..5...9...7.......62...3...........4.........1.48.7........6.3.2.9.......;2;361
123456789457893612896127345218735496569284137734961528372518964685349271941672853;....5.78.4....3....9.......2.....4.6....8..............7........85.....1...6.2..3;3;361
and the minlex found
123456789457189236869273145318725694642391578795864312274618953586937421931542867 min final
currently in test
_____________________________________________________
"30".

sk_gcat -c30 -v0-400 -v1-415   -odt30 >dt30_cout.txt

catalog output for bands 1 index 400 to 415
18 records in output giving the count per row4
_____________________________________________________

"31"

sk_gcat -c31 -v0-652390 -v1-652408 -v2-1  -odt31 >dt31_cout.txt

catalog output for rows 4 index 652390 to 652408
28 solution grids in output
_____________________________________________________

"80"
sk_gcat -c80 -v0-21 -v1-50   -odt80_21_50 >dt80_21_50_cout.txt

enumeration for the bands 21 to 50, 
currently modified to get in output the data used to create tables inserted in the code

___________________________________________________________

"81" 

sk_gcat -c81 -v0-165  -v1-165 -od81_165 >d81_165_cout.txt

enumeration using rows4 modified in output _file1 to build internal tables
here for the band1 index 165 

___________________________

"91"
sk_gcat -c91   -oht91 >ht91_cout.txt

current work to regnize the gangster in a non min lexical morph

_____________________________________

"92"

sk_gcat -c92   -oht92 >ht92_cout.txt

finding all fills for the 44 gangsters in min lexical morph