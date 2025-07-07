#include <Arduino.h>
#include "webpage.h"

const char PAGE_MAIN[] PROGMEM = R"=====(

<!DOCTYPE html><html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
    <style>
        html { 
        font-family: "Lucida Console", Helvetica; 
        display: inline-block; 
        margin: 0px auto; 
        text-align: center;
        }
        .button-container { 
        display: flex; 
        flex-wrap: wrap; 
        justify-content: center; 
        gap: 20px; 
        }
        .pin-block { 
        display: flex; 
        flex-direction: column; 
        align-items: center; 
        padding: 10px; 
        border: 1px solid #ccc; 
        border-radius: 10px; 
        }
        .button { 
        background-color:rgb(104, 255, 109); 
        border: none; 
        border-radius: 12px; 
        color: white; 
        padding: 16px 40px;
        text-decoration: none; 
        font-size: 30px; 
        margin: 2px; 
        cursor: pointer;
        }
        .button2 {
        background-color:rgb(255, 0, 0); 
        }
    </style>
</head>
<body>
    <h1>ESP32 WiFi Lighting Control</h1> 
    <div class="button-container">

)=====";