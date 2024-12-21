const express = require("express");
const app = express();
app.use(express.json());
app.use(express.urlencoded({ extended: true }));
let latestGpsData = {}; // Initialize the global variable to store GPS data

app.post("/Login", (req, res) => {
  const user = req.body;
  if (user.email === "s@gmail.com" && user.password === "12345") {
    res.json("Login success");
  } else {
    res.json("Login failed");
  }
});

app.post("/Signup", (req, res) => {
  const user = req.body;
  if (user.email.includes("@") && user.password.length >= 8) {
    res.json("Signup success");
  } else {
    res.json("Signup failed");
  }
});

app.get("/Map", (req, res) => {
  res.json("Map endpoint reached");
});

app.post("/gpsdata", (req, res) => {
  const latitude = req.body.latitude;
  const longitude = req.body.longitude;

  console.log(
    `Received GPS data - Latitude: ${latitude}, Longitude: ${longitude}`
  );
  res.json({ status: "success", received: { latitude, longitude } });
});
app.get("/gpsdata", (req, res) => {
  if (latestGpsData.latitude && latestGpsData.longitude) {
    res.json(latestGpsData);
  } else {
    res.status(404).send("No GPS data available");
  }
});

app.listen(8081, "192.168.187.27", () => {
  console.log("Server is running on http://192.168.187.27:8081");
});
