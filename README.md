# 🛰️ Embedded GPS Tracker — Team 25

An embedded system built using the **TM4C123G LaunchPad** to track real-time GPS coordinates, identify proximity to known landmarks, and display location data using UART and LCD interfaces. This project was developed for the **Introduction to Embedded Systems (CSE 211s - Spring 2025)** course at Ain Shams University.

## 📌 Project Objective

Design and implement a GPS-based embedded system that:
- Interfaces with a GPS module via UART.
- Parses and stores GPS coordinates during motion.
- Identifies and displays the name of the nearest faculty landmark.
- Sends recorded trajectory to a PC upon command.
- Uses LEDs and a buzzer to indicate proximity to a target.
- Operates autonomously on battery with real-time LCD feedback.

---

## 🧠 Theoretical Concepts

### ✅ Embedded Systems
Used the **TM4C123G (Tiva C Series)** microcontroller for its efficiency in real-time applications. All logic was implemented in embedded C.

### ✅ GPS & UART Communication
GPS data is received over UART in NMEA format and parsed to extract latitude and longitude. UART also transmits data to the PC.

### ✅ Systick Timer
Used to synchronize sampling rate with the GPS update frequency (~1 Hz).

---

## 🖥️ System Architecture

1. **GPS Receiver (Neo-6M)** — streams position data to the microcontroller.
2. **TM4C123G LaunchPad** — parses and processes GPS data, manages logic.
3. **LCD (16x2)** — displays the nearest location from memory.
4. **PC Terminal** — receives full trajectory log via UART.
5. **TTL Converter** — bridges microcontroller UART to PC USB.
6. **LEDs & Buzzer** — indicate proximity to preset landmarks.
7. **Battery Pack** — allows portable operation.

---

## 🎯 Functional Features

- UART initialization for GPS and PC communication.
- Real-time GPS data parsing and buffer storage.
- Proximity detection logic using Haversine distance.
- Display of nearest hall name on LCD.
- Visual/audio indication when reaching key proximity thresholds.
- User-triggered transfer of logged path to PC.

---

## 📸 Project Media

### ▶️ Demo Video
👉 [Watch here](#) *(https://www.youtube.com/watch?v=i2bgvukuLss)*

### 🧑‍🏫 Explanation Video
👉 [Watch here](#) *(insert actual link)*

### 📷 Images
| Hardware Prototype | LCD Output |
|--------------------|------------|
| *(insert image)*   | *(insert image)* |

---

## 🧩 Hardware Components

| Component         | Quantity | Part No.         | Price  | Function                      |
|------------------|----------|------------------|--------|-------------------------------|
| TM4C123GH6PM      | 1        | LaunchPad        | 2500EGP| Central microcontroller       |
| GPS Module        | 1        | Neo6m            | 450EGP | Live location tracking        |
| LCD Display       | 1        | 16x2             | 85EGP  | Location name output          |
| TTL Converter     | 1        | USB-to-Serial    | 240EGP | PC communication              |
| Buzzer            | 1        | -                | 10EGP  | Audible proximity alert       |
| LEDs              | 2        | -                | 2EGP   | Visual proximity alert        |
| Battery Pack      | 1        | -                | 60EGP  | Power for portability         |
| Potentiometer     | 1        | 10k              | 10EGP  | LCD contrast control          |
| Jumpers, Resistors| Various  | -                | 65EGP  | Electrical connections        |
| **Total Cost**    | -        |                  | **3472EGP** |                               |

---

## 👥 Team Members & Contributions

| Name                       | Contribution Area              |
|----------------------------|-------------------------------|
| **Youssef Mohamed Eissa** | UART, LEDs, Video, Hardware   |
| **Ibrahim M. M. Hanafy**  | LCD, Hardware                 |
| **Mohamed Alaa El-Din**   | Main Logic, Packaging, Hardware |
| **Mohamed Essam Mohamed** | GPS Parsing, Hardware         |
| **Eyad Wael Ghanem**      | GPIO, Packaging, Hardware     |

---

## 🔄 How to Run

1. Clone the repo:
```bash
git clone https://github.com/Not-Chungus/Embedded-GPS_Tracker_Team25-.git
