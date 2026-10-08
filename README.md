# IoT Intensity Control

Real-time LED intensity control using **Node.js, WebSocket, and ESP8266 NodeMCU**.

## Features

* Real-time LED brightness control
* Multiple connected clients
* Shared intensity value
* WebSocket communication
* PWM control from `0` to `255`

## Technologies

* Node.js
* Express
* WebSocket
* JavaScript
* ESP8266
* Arduino

## How It Works

```text
Browser
   ↓
WebSocket
   ↓
Node.js Server
   ↓
ESP8266 NodeMCU
   ↓
LED
```

All connected clients receive the latest intensity value in real time.


