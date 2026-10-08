const express = require("express");
const http = require("http");
const WebSocket = require("ws");

const app = express();

app.use(express.static("front"));

const server = http.createServer(app);

const wss = new WebSocket.Server({ server });

let currentIntensity = 128;


wss.on("connection", function (socket) {

    console.log("Client Connected");

    // Send the current value to the new client
    socket.send(currentIntensity.toString());


    socket.on("message", function (message) {

        let intensity = parseInt(message.toString());

        if (isNaN(intensity)) {
            return;
        }

        intensity = Math.max(0, Math.min(255, intensity));


        currentIntensity = intensity;

        console.log("Current Intensity:", currentIntensity);


        wss.clients.forEach(function (client) {

            if (client.readyState === WebSocket.OPEN) {

                client.send(currentIntensity.toString());

            }

        });

    });


    socket.on("close", function () {

        console.log("Client Disconnected");

    });


    socket.on("error", function (error) {

        console.log("WebSocket Error:", error);

    });

});


server.listen(9000, "0.0.0.0", function () {

    console.log("Server Working On:");
    console.log("http://localhost:9000");
    console.log("WebSocket: ws://192.168.1.2:9000");

});