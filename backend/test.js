const { SerialPort } = require("serialport");

const port = new SerialPort({ path: "/dev/cu.usbmodem101", baudRate: 9600 }); // Adjust 'COM3' to your Arduino's port

port.write("on" + "\n"); // Send the text to the Arduino, followed by a newline
