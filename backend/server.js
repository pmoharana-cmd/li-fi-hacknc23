const express = require("express");
const { SerialPort } = require("serialport");
const bodyParser = require("body-parser");
const cors = require("cors");

const app = express();
app.use(cors());
const port = new SerialPort({ path: "/dev/cu.usbmodem101", baudRate: 9600 }); // Adjust 'COM3' to your Arduino's port

app.use(express.static("public")); // Serve files from the 'public' directory
app.use(bodyParser.urlencoded({ extended: false }));

app.post("/sendToArduino", (req, res) => {
  console.log(req.body);
  //   let text = req.body.text;
  let text = "TESTING!";
  port.write(text + "\n"); // Send the text to the Arduino, followed by a newline
  const stuff = port.read();
  console.log(stuff);
  res.send("Text sent to Arduino!");
});

app.get("/");

app.listen(3000, () => {
  console.log("Server started on http://localhost:3000");
});
