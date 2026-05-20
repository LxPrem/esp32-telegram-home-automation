# ESP32 Telegram Home Automation

## Features

- 4 Relay Control
- Telegram Bot
- MC38 Door Sensor
- Door Open Alerts

## Wiring

Relay:
- IN1 -> GPIO 4
- IN2 -> GPIO 5
- IN3 -> GPIO 18
- IN4 -> GPIO 19

MC38:
- One wire -> GND
- Other wire -> GPIO 27

## Required Libraries

Install:
- UniversalTelegramBot
- ArduinoJson 6.21.3

## Setup

Replace:
- YOUR_WIFI_NAME
- YOUR_WIFI_PASSWORD
- YOUR_BOT_TOKEN
- YOUR_CHAT_ID

## Telegram Setup

Use:
- @BotFather
- @userinfobot
