LMIC ChisteraPi
=============

LMIC ChisteraPi is the source code for LoraWAN transmissions with ChisteraPi.

Products
-------
ChisteraPi light LoRa : https://snootlab.com/shields-snootlab/1151-.html
ChisteraPi + accessories LorA : https://snootlab.com/shields-snootlab/1152-.html

Forums
-------
Visit our specific forum at :
http://forum.snootlab.com/viewforum.php?f=59

Links
-------
The LMIC library is a library of IBM with Eclipse Public License.
http://www.research.ibm.com/labs/zurich/ics/lrsc/lmic.html

The Raspberry Hardware Abstraction Library comes from ernstdevreede.
https://github.com/ernstdevreede/lmic_pi

Modification and example comes from Snootlab with GPLv2 license.
https://snootlab.com/72-03-iot-et-sans-fil

Documentation
---------------------
You have documentation on LMIC library and LoraWAN into the doc directory.

Howto start
------------------
Plug the ChisteraPi on your RaspberryPi.
Power on and connect into your RaspberryPi with SSH.
Clone the repository :
<code>
	git clone https://github.com/Snootlab/lmic_chisterapi
</code>

Get into the repository and compile the example :
<code>
	cd lmic_chisterapi
</code>

Modify APPEUI, DEVEUI and DEVKEY with yours :
<code>
    nano src/OTAA_JoinAndTransmit.c
    make all	
</code>

Execute the example :
<code>
	sudo ./OTAA_JoinAndTransmit
</code>

