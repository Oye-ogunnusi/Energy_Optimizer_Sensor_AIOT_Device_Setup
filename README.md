# Energy_Optimizer_Sensor_AIOT_Device_Setup

An **AIoT-based Energy Optimization System** that uses environmental sensor data and machine learning–based occupancy detection to intelligently manage energy consumption in smart buildings.

This project integrates:
- IoT sensors (temperature, humidity, light, CO₂, etc.)
- Edge AI inference on microcontrollers
- Occupancy detection using a trained ML model
- Energy-aware decision-making for smart environments

---

## 🚀 Project Overview

The system predicts **room occupancy** using sensor data and dynamically optimizes energy usage (e.g., HVAC, lighting) based on occupancy status.

### Key Features
- 📡 Environmental sensor data collection
- 🧠 Machine learning–based occupancy detection
- 🔌 Edge deployment using microcontroller-compatible models
- ⚡ Energy optimization logic
- 🏠 Designed for smart home / smart building use cases

---

## 🧠 Dataset Information

The machine learning model was trained using a dataset derived from **publicly available smart home occupancy datasets**, inspired by:

- **UCI Room Occupancy Detection Dataset**
- **Kaggle Mirror Dataset**

### Dataset Source
🔗 https://www.kaggle.com/datasets/robmarkcole/occupancy-detection-data-set-uci

### Dataset Description
The dataset contains:
- Environmental sensor readings:
  - Temperature
  - Humidity
  - Light
  - CO₂
  - Humidity Ratio
- Binary occupancy labels:
  - `0` → Not Occupied
  - `1` → Occupied

---

## 🗂️ Project Structure

```text
Energy_Optimizer_Sensor_AIOT_Device_Setup/
│
├── data/
│   └── datatraining.csv          # Training dataset
│
├── model/
│   └── occupancy_model.h         # Trained ML model for edge deployment
│
├── notebooks/
│   └── Room_Occupancy_Detection.ipynb  # Model training & evaluation
│
├── firmware/
│   ├── wifi-scan.ino              # Microcontroller firmware
│   └── wokwi-project.txt          # Wokwi simulation configuration
│
├── diagrams/
│   └── diagram_1.json              # System architecture diagram
│
├── README.md
└── .gitignore
