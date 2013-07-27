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
-----------------
Ensure you have g++ and other build-essentials to build ANSI C++ code. One can build the code by running the "make" command.


LICENSE:
--------

Use of this work is subject to the Microsoft Public License (MS-PL) agreement.

This license governs use of the accompanying software. If you use the software, you
accept this license. If you do not accept the license, do not use the software.

1. Definitions
The terms "reproduce," "reproduction," "derivative works," and "distribution" have the
same meaning here as under U.S. copyright law.
A "contribution" is the original software, or any additions or changes to the software.
A "contributor" is any person that distributes its contribution under this license.
"Licensed patents" are a contributor's patent claims that read directly on its contribution.

2. Grant of Rights
(A) Copyright Grant- Subject to the terms of this license, including the license conditions and limitations in section 3, each contributor grants you a non-exclusive, worldwide, royalty-free copyright license to reproduce its contribution, prepare derivative works of its contribution, and distribute its contribution or any derivative works that you create.
(B) Patent Grant- Subject to the terms of this license, including the license conditions and limitations in section 3, each contributor grants you a non-exclusive, worldwide, royalty-free license under its licensed patents to make, have made, use, sell, offer for sale, import, and/or otherwise dispose of its contribution in the software or derivative works of the contribution in the software.

3. Conditions and Limitations
(A) No Trademark License- This license does not grant you rights to use any contributors' name, logo, or trademarks.
(B) If you bring a patent claim against any contributor over patents that you claim are infringed by the software, your patent license from such contributor to the software ends automatically.
(C) If you distribute any portion of the software, you must retain all copyright, patent, trademark, and attribution notices that are present in the software.
(D) If you distribute any portion of the software in source code form, you may do so only under this license by including a complete copy of this license with your distribution. If you distribute any portion of the software in compiled or object code form, you may only do so under a license that complies with this license.
(E) The software is licensed "as-is." You bear the risk of using it. The contributors give no express warranties, guarantees or conditions. You may have additional consumer rights under your local laws which this license cannot change. To the extent permitted under your local laws, the contributors exclude the implied warranties of merchantability, fitness for a particular purpose and non-infringement.


