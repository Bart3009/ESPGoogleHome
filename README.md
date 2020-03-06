# ESPGoogleHome
<h1>Introduction</h1>
<p> During this mini project a system will be set up to control radio-frequency (RF) switches with the use of an ESP32 microcontroller. The ESP32 microcontroller will be sending RF signals through a RF transmitter breakout board. Which can be bought online. During the project the online services IFTTT.com (If this then that) and Adafruit.io will be combined to switch a klik aan klik uit schakelaar (Kaku switch). At the end of the project the IFTTT service should be able to use your coffee machine to provide you with a fresh cup of coffee in the morning. </p>

<h1>Project requirements</h1>
<h2>Hardware:</h2>
<ul>
  <li>ESP32</li>
  <li>Klik aan klik uit schakelaar (RF Switch)</li>
  <li>Breadboard</li>
  <li>Jumper wires</li>
  <li>RF transmitter breakout</li>
  <li>Mobile phone</li>
  <li>PC</li>
</ul>

<h2>Software:</h2>
<ul>
  <li>Arduino IDE</li>
  <li>Adafruit.io (webpage)</li>
  <li>IFTTT.com (webpage)</li>
  <li>Google assistant application (phone)</li>
</ul>

<h1>Step 1: Setting up an IFTTT.com account</h1>
<p>Head to http://ifttt.com and create an account. After creating an account leave the page till the next step.</p>

<h1>Step 2: Setting up an Adafruit.io account</h2>
<p>Head to http://adafruit.io and create an account. Then follow these steps:</p>
<ol>
  <li>Press the 'actions' button</li>
  <li>Press the 'create new dashboard' button</li>
  <li>Give the dashboard a name and hit create</li>
  <li>Open the dashboard by clicking on it</li>
 </ol>
 <p>Congratualations you've just created your own online Adafruit IoT dashboard.</p>
 
 <h1>Step 3: Create the link between the ESP32 and the Adafruit IO dashboard</h1>
 <ol>
  <li>Within the Adafruit IO dashboard hit the blue button in the top-right corner to create a new block</li>
  <li>Choose to create a toggle block</li>
  <li>In the box that says: 'Enter feed name'. Enter a name (which you need to write down (saves time later on)</li>
  <li>Hit the checkbox before the new feed and hit next</li>
  <li>Name the block title whatever you want</li>
  <li>Change "Button On Text" to: 0</li>
  <li>Change "Button Off Text" to: 1</li>
  <li>Hit "create block"</li>
 </ol>
 
 <p>Now that the Adafruit IO know about the existance of your internet switch, we can start programming the ESP32 MCU. For programming the ESP32 the software can be found within this github repository. Flashing GoogleIoTTest3.ino to the ESP32 (after filling in your personal WiFi-SSID and WiFi-Password you're not done yet. You alsno need to fill in two values for the connection with the Adafruit IO webpage.</p>
 <p>These values are the AIO_USERNAME and the AIO_KEY. The username is the username you've chosen while creating your account. The AIO_KEY can be obtained by hitting the yellow button in the top-right corner while looking at your Adafruit IO dashboard.</p>
 <p>After changing the four values you're ready to go. You can flash the ESP32 by connecting it to the Arduino IDE. And you're able to check if it properly connects to the WiFi by opening the serial monitor at 115200 baudrate.</p>
 
 <p>If everything till now did work out, you're almost done. The only thing that has to be done is creating a link between the google assistant (which is linked to your google account) and the Adafruit IO dashboard.</p>
 
 <h1>Step 4: Setting up the voice commands in IFTTT.com</h1>
 <p>Open the IFTTT.com website on which you've created an account earlier on during this tutorial. Right-mouse-click on the avatar in the top-right corner and hit 'create'.Now it's time to get creative:</p>
 <ol>
  <li>Hit the "This" button</li>
  <li>Search for Google Assistant</li>
  <li>Link your account</li>
  <li>Hit "say a simple phrase"</li>
  <li>Enter three commands and a command for the Google Assistant</li>
  <li>Hit the "That" button</li>
  <li>Search for the Adafruit service</li>
  <li>Link your account</li>
  <li>Hit "Send data to Adafruit IO</li>
  <li>Select the feed name you've just created</li>
  <li>Change data to save in 0 (off) or 1 (on)</li>
 </ol>
 <p>Repeat all of these steps for the off command. You now should have configured the IoT ESP32 IFTTT.com Adafruit IO kit. Happy programming</p>
