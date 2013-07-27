BBI
===
This folder contains the source, header and data files for the PeFlow app. The app takes a CSV file that has price and earnings information for some securities.

A sample file called "Initial.txt" has been provided in the data folder for reference. The format of the data in the file is as follows:

<3-leter security mnemonic>,<Price in USD>,<12-mo earnings in USD>

e.g.:

BCA,13.21,.320000

Once started, the application will load this data into memory, and then start manipulating the price and the earnings in a random fashion. It updates the price of a random security once every second such that the new price of it is +/-80% of it's current price. It modifies the earnings every 60s, such that the new earnings are +/-20% of the current earnings. 

All this information is displayed on the terminal for the user to see what's going on. Please note that to have the screen "refresh" you must be using a VT100-type terminal.

e.g. usage:

./peflow -initpefile data/Initial.txt 


TO BUILD SOURCE:
===
Ensure you have g++ and other build-essentials to build ANSI C++ code. One can build the code by running the "make" command.

