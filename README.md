# Arduino Morse Code Transmitter/Receiver


This Arduino sketch allows two boards to communicate with each other using Morse Code.

After uploading this sketch to two Arduino boards, a user may send a string input to one of the boards via the Serial Monitor. This board then transmits in Morse Code each character of the input using an infrared emitter. The other board simultaneously receives this message with an infrared sensor, converting the received Morse Code back into English and printing it to the Serial Monitor. When the transmission is complete, new string inputs may continue to be sent to either board to be transmitted and received as described above. Note that if inputs are sent to both boards at the same time, neither will be received.


*NOTE: This project was completed in April 2017 and was committed to this repository on March 4, 2019. Progressive versions of each file were committed in order to keep an accurate revision history.*
