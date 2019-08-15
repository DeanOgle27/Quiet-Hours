# Quiet Hours by Team SOLUTI/ON (Feb 2-3, 2019)
[Vish Anand](https://www.vishanand.com), [Dean Ogle](https://github.com/DeanBrogle), [Noah Sediqe](https://github.com/NoahSediqe), & [JT Thrash](https://github.com/JT-Thrash)

[Presentation Given at the OSU MakeOHI/O Hackathon](https://drive.google.com/file/d/1Gth503BGLpS9QvUULUKfwbs327lDW-KX/view?usp=sharing)

Won **1st Place** for the Best Use of Voice Technology ([EdgeThingz sponsor challenge](https://hack.osu.edu/make/2019/#prizes-page))

### Objective
As Sophomores at Ohio State, the four of us were living in the Dorms and would often hear our RA's complain about excessive noise, so we decided to develop a system to automate the warning process---thereby making the RA's job easier. This system can also easily be adapted to other environments that would benefit from noise-level monitoring, such as hospitals and libraries.

### Technical Details
Our project had two major components:
* The Arduino-powered Listening Device
  * We wired a microphone to the Arduino's analog input ports so that it could monitor noise levels, we also wired it to four colored LED's that acted as status lights
  * The Arduino board we used had an ESP8266 Wireless module, so we pinged our server with the max noise levels from each 10-second interval every 10 seconds
  * Each Arduino device was assigned its own Device ID QR code so that we may scale our architecture to account for multiple Listening Devices in the future
  * The code was written using the Arduino IDE in a variant of C++
  * Source code is located at */Arduino/*
* The Node.js Backend
  * Ran off of a rented DigitalOcean server droplet in New York City during the Hackathon
  * The server code was written in Node.js, and it listened to pings from the Arduino at a specified endpoint
  * When the server detects excessive noise levels, it sends a message to a specified GroupMe group using GroupMe's [Bot API](https://dev.groupme.com) subject to appropriate cooldown periods
  * We also made a Bootstrap Configuration Panel that allows users to configure their Device ID, GroupMe Bot ID, custom messages to send for excessive noise, the cooldown period, and the acceptable volume threshold
  * Source code is located at */Server/*

## Pictures

**Front of device**
![Image](Screenshot/front.jpg?raw=true)

**Inside of device**
![Image](Screenshot/inside1.jpg?raw=true)

![Image](Screenshot/inside2.jpg?raw=true)
