# ESP32 MQTT Telemetry – ThingsBoard Integration

An embedded IoT telemetry system built on ESP32 that publishes real-time PIR motion and ultrasonic distance sensor data to ThingsBoard Cloud using the MQTT protocol.

This project demonstrates WiFi connectivity, MQTT communication, JSON telemetry formatting, and automatic reconnection handling for reliable cloud-based monitoring.

---

## Features

- WiFi connectivity (ESP32)
- MQTT communication (TCP, port 1883)
- PIR motion detection
- Ultrasonic distance measurement 
- JSON-formatted telemetry
- Automatic MQTT reconnection
- 1-second telemetry publishing interval
- Cloud dashboard visualization

---

## System Architecture

PIR Sensor  ─┐  
├── ESP32 ── WiFi ── MQTT ── ThingsBoard Cloud ── Dashboard  
Ultrasonic  ─┘  

The ESP32 reads sensor values, formats them into JSON, and publishes telemetry to ThingsBoard.
