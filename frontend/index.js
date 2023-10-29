window.addEventListener("load", () => {
  // Get the form element
  const button = document.getElementById("sendButton");
  var enc = new TextEncoder();
  let port;
  let writer;

  console.log(button);

  async function sendData() {
    console.log("ran");

    if (!port) {
      // Prompt user to select any serial port.
      port = await navigator.serial.requestPort();
      // Wait for the serial port to open.
      await port.open({ baudRate: 9600 });
    }

    writer = port.writable.getWriter();

    const textBox = document.getElementsByClassName("input_text").item(0);

    console.log(textBox.value);

    const data = enc.encode(textBox.value + "\n"); // hello
    console.log(data);
    await writer.write(data);

    textBox.value = "";

    // Allow the serial port to be closed later.
    writer.releaseLock();
  }

  // Add 'submit' event handler
  button.addEventListener("click", (event) => {
    event.preventDefault();
    sendData();
  });
});
