# Energy Optimizer Sensor AIoT Device Setup

<div align="center">

![Project Status](https://img.shields.io/badge/status-active-success.svg)
![Platform](https://img.shields.io/badge/platform-ESP32-blue.svg)
![TinyML](https://img.shields.io/badge/TinyML-Enabled-orange.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

**Intelligent Room Occupancy Detection & Energy Optimization using Edge AI**

[Features](#features) • [Architecture](#system-architecture) • [Installation](#installation) • [Usage](#usage) • [Model Training](#model-training) • [Hardware](#hardware)

</div>

---

## 📋 Overview

This project implements an intelligent energy optimization system that uses machine learning-based occupancy detection to automate climate control. By deploying a lightweight decision tree model directly on ESP32 microcontrollers, the system achieves real-time inference at the edge without cloud dependency, ensuring privacy, low latency, and minimal power consumption.

The system monitors environmental conditions (temperature, humidity, light, CO2 levels) and intelligently controls heating and ventilation systems based on detected room occupancy, significantly reducing energy waste in unoccupied spaces.

### Key Achievements

- ✅ **High Accuracy**: 98.99% classification accuracy on test data
- ✅ **TinyML Ready**: Optimized decision tree runs on microcontrollers with <5KB memory footprint
- ✅ **Sub-millisecond Inference**: Real-time predictions (<1ms latency)
- ✅ **Energy Efficient**: Automated HVAC control based on occupancy reduces unnecessary energy consumption
- ✅ **Privacy-Preserving**: All inference happens at the edge, no video/audio surveillance required
- ✅ **Cloud Integration**: Optional ThingSpeak integration for monitoring and analytics
- ✅ **Simulation Ready**: Full Wokwi simulation support for prototyping without hardware

---

## 🎯 Features

### Machine Learning
- **Optimized Decision Tree Classifier**: Shallow tree architecture (max_depth=5) balancing accuracy and efficiency
- **StandardScaler Preprocessing**: Feature normalization embedded in firmware
- **Time-Series Aware Training**: Proper temporal splitting to prevent data leakage
- **Class Imbalance Handling**: Random oversampling for minority class

### Edge Deployment
- **TinyML Implementation**: Exported sklearn model to native C++ code
- **Real-time Inference**: Continuous prediction loop with 400ms sampling rate
- **Embedded Preprocessing**: Z-score normalization implemented on-device
- **Low Memory Footprint**: Entire model fits in <5KB SRAM

### IoT Integration
- **WiFi Connectivity**: Seamless connection to local networks
- **ThingSpeak Cloud**: Real-time data logging and visualization
- **Simulated Sensors**: Potentiometer-based sensor emulation for testing
- **Actuator Control**: Automated fan and heater control based on predictions

### Energy Optimization Logic
- **Occupancy-Based Control**: 
  - Room occupied → Fan active, heater ON if temperature < 20.5°C
  - Room unoccupied → All systems OFF (energy saving mode)
- **Temperature Regulation**: Smart heating control maintains comfort during occupancy
- **Immediate Response**: Real-time adjustments based on current conditions

---

## 🏗️ System Architecture

```
┌──────────────────────────────────────────────────────────────┐
│                     DATA COLLECTION LAYER                     │
│  ┌────────────┐  ┌────────────┐  ┌────────┐  ┌────────────┐ │
│  │ Temperature│  │  Humidity  │  │  Light │  │    CO2     │ │
│  │   Sensor   │  │   Sensor   │  │ Sensor │  │   Sensor   │ │
│  └──────┬─────┘  └──────┬─────┘  └────┬───┘  └──────┬─────┘ │
└─────────┼────────────────┼─────────────┼─────────────┼───────┘
          │                │             │             │
          └────────────────┴─────────────┴─────────────┘
                              │
          ┌───────────────────▼────────────────────┐
          │        ESP32 MICROCONTROLLER           │
          │  ┌──────────────────────────────────┐  │
          │  │   Feature Preprocessing Layer    │  │
          │  │  (StandardScaler Normalization)  │  │
          │  └─────────────┬────────────────────┘  │
          │                │                        │
          │  ┌─────────────▼────────────────────┐  │
          │  │    TinyML Inference Engine       │  │
          │  │  (Decision Tree Classifier)      │  │
          │  │    - Max Depth: 5                │  │
          │  │    - Memory: <5KB                │  │
          │  │    - Latency: <1ms               │  │
          │  └─────────────┬────────────────────┘  │
          │                │                        │
          │  ┌─────────────▼────────────────────┐  │
          │  │   Control Logic & Optimization   │  │
          │  │  - Occupancy-based switching     │  │
          │  │  - Temperature regulation        │  │
          │  └─────────────┬────────────────────┘  │
          └────────────────┼───────────────────────┘
                           │
          ┌────────────────┴────────────────┐
          │                                 │
    ┌─────▼──────┐                  ┌──────▼──────┐
    │    Fan     │                  │   Heater    │
    │  (Cooling) │                  │  (Heating)  │
    └────────────┘                  └─────────────┘
          │                                 │
          └─────────────┬───────────────────┘
                        │
              ┌─────────▼──────────┐
              │  ThingSpeak Cloud  │
              │  (Data Logging &   │
              │   Visualization)   │
              └────────────────────┘
```

### Data Flow

1. **Sensor Reading**: Environmental sensors continuously measure temperature, humidity, light intensity, and CO2 levels
2. **Preprocessing**: Raw sensor values are mapped to realistic ranges and normalized using embedded StandardScaler parameters
3. **Inference**: The TinyML decision tree model predicts room occupancy in real-time
4. **Control Decision**: Based on prediction and current conditions, the system decides actuator states
5. **Actuation**: Fan and heater are controlled automatically to optimize energy usage
6. **Cloud Sync**: Sensor readings and predictions are periodically uploaded to ThingSpeak for monitoring

---

## 🛠️ Installation

### Prerequisites

**Hardware:**
- ESP32 Development Board (ESP32-WROOM-32 or compatible)
- Environmental sensors (or use Wokwi simulation):
  - DHT22/BME280 (Temperature & Humidity)
  - BH1750/TSL2561 (Light)
  - MH-Z19/SCD30 (CO2)
- LEDs and resistors (220Ω) for actuator indication
- Breadboard and jumper wires

**Software:**
- Arduino IDE 1.8.x or 2.x
- Python 3.8+
- Jupyter Notebook or Google Colab
- Git

**Libraries (Arduino):**
- WiFi (built-in with ESP32)
- HTTPClient (built-in with ESP32)

**Libraries (Python):**
```bash
pandas
numpy
matplotlib
seaborn
scikit-learn
imbalanced-learn
```

### Quick Start

1. **Clone the Repository**
   ```bash
   git clone https://github.com/yourusername/Energy_Optimizer_Sensor_AIOT_Device_Setup.git
   cd Energy_Optimizer_Sensor_AIOT_Device_Setup
   ```

2. **Install Python Dependencies**
   ```bash
   pip install -r requirements.txt
   ```

3. **Train the Model (Optional)**
   
   If you want to retrain the model with your own data:
   ```bash
   jupyter notebook Room_Occupancy_Detection.ipynb
   ```
   
   The notebook will:
   - Load and preprocess the training data
   - Train an optimized decision tree classifier
   - Export the model as `occupancy_model.h`
   - Generate evaluation metrics and visualizations

4. **Configure WiFi and ThingSpeak**
   
   Edit `wifi-scan.ino`:
   ```cpp
   // WiFi credentials
   const char* WIFI_SSID = "Your_WiFi_SSID";
   const char* WIFI_PASS = "Your_WiFi_Password";
   
   // ThingSpeak API key (get from thingspeak.com)
   String THINGSPEAK_KEY = "YOUR_THINGSPEAK_API_KEY";
   ```

5. **Upload to ESP32**
   - Open `wifi-scan.ino` in Arduino IDE
   - Select board: "ESP32 Dev Module"
   - Select the correct COM port
   - Click Upload

6. **Monitor Serial Output**
   - Open Serial Monitor (115200 baud)
   - Observe sensor readings, predictions, and actuator states

---

## 🚀 Usage

### Running on Real Hardware

1. **Connect Sensors** according to pin mappings:
   - Humidity sensor → GPIO 32 (ADC)
   - Light sensor → GPIO 34 (ADC)
   - CO2 sensor → GPIO 35 (ADC)
   - Fan LED → GPIO 2 (via 220Ω resistor)
   - Heater LED → GPIO 4 (via 220Ω resistor)

2. **Power the ESP32** via USB or external 5V supply

3. **Monitor Operation**:
   - Serial console shows real-time sensor values and predictions
   - ThingSpeak dashboard displays historical data and trends
   - LEDs indicate actuator states (blue=fan, red=heater)

### Running Wokwi Simulation

1. Visit: https://wokwi.com/projects/305569599398609473
2. Click "Play" to start simulation
3. Adjust potentiometers to simulate different environmental conditions
4. Observe how the system responds to occupancy predictions

### Testing Different Scenarios

**Scenario 1: Unoccupied Room (Low Light, Low CO2)**
```
Expected Behavior:
- Prediction: Occupancy = 0
- Fan: OFF
- Heater: OFF
- Energy Saving: Maximum
```

**Scenario 2: Occupied Room - Comfortable Temperature**
```
Expected Behavior:
- Prediction: Occupancy = 1
- Fan: ON (ventilation)
- Heater: OFF (T > 20.5°C)
- Energy Use: Moderate
```

**Scenario 3: Occupied Room - Cold Temperature**
```
Expected Behavior:
- Prediction: Occupancy = 1
- Fan: ON (circulation)
- Heater: ON (T < 20.5°C)
- Energy Use: High (comfort prioritized)
```

---

## 🤖 Model Training

### Dataset Information

The model was trained using a dataset derived from publicly available smart home occupancy datasets, inspired by the **UCI Room Occupancy Detection Dataset** and its Kaggle mirrors. The data consists of environmental sensor readings and binary occupancy labels.

**Source**: [Kaggle - Occupancy Detection Dataset](https://www.kaggle.com/datasets/robmarkcole/occupancy-detection-data-set-uci)

**Features:**
- `Temperature` (°C): Room temperature
- `Humidity` (% RH): Relative humidity
- `Light` (Lux): Light intensity
- `CO2` (ppm): CO2 concentration
- `HumidityRatio` (kg water/kg air): Derived humidity metric

**Target:**
- `Occupancy`: Binary classification (0 = Unoccupied, 1 = Occupied)

**Dataset Statistics:**
- Total samples: 8,143 time-series observations
- Training set: 6,514 samples (80%)
- Test set: 1,629 samples (20%)
- Class distribution after balancing: 50-50 split

### Training Pipeline

The complete training pipeline is documented in `Room_Occupancy_Detection.ipynb`:

1. **Data Loading & Exploration**
   - Load dataset and examine structure
   - Visualize distributions and temporal patterns
   - Identify correlations between features

2. **Preprocessing**
   - Handle missing values (if any)
   - Time-based train-test split (prevents data leakage)
   - Feature scaling using StandardScaler
   - Address class imbalance with RandomOverSampler

3. **Model Development**
   - Decision Tree Classifier with optimized hyperparameters
   - Grid search for max_depth, min_samples_split, min_samples_leaf
   - TinyML constraints: max_depth=5 for memory efficiency

4. **Model Evaluation**
   - Accuracy: 98.99%
   - Precision: 99.21%
   - Recall: 98.98%
   - F1-Score: 99.09%
   - Confusion matrix analysis

5. **Model Export**
   - Extract decision tree structure from sklearn
   - Generate optimized C++ header file
   - Embed StandardScaler parameters for on-device preprocessing
   - Verify exported model accuracy

### Hyperparameter Optimization

After extensive grid search, optimal parameters were identified:

```python
{
    'max_depth': 5,           # Shallow tree for TinyML
    'min_samples_split': 10,  # Prevent overfitting
    'min_samples_leaf': 5,    # Larger leaves = more generalization
    'criterion': 'gini'       # Standard splitting criterion
}
```

These parameters balance:
- **Accuracy**: High performance on unseen data
- **Generalization**: Low overfitting
- **Efficiency**: Small model size and fast inference
- **Explainability**: Shallow tree is interpretable

### Model Deployment

The trained sklearn model is automatically converted to ESP32-compatible C++ code:

```cpp
// occupancy_model.h
static inline int predict_occupancy(
    float Temperature,
    float Humidity,
    float Light,
    float CO2,
    float HumidityRatio
) {
    // Decision tree logic exported from sklearn
    // Uses z-score normalized features
    // Returns: 0 = Unoccupied, 1 = Occupied
}
```

This enables:
- Zero-dependency inference (no external libraries)
- Sub-millisecond prediction time
- Minimal memory footprint (<5KB)
- Deterministic behavior

---

## 🔌 Hardware

### Required Components

| Component | Specification | Purpose | Quantity |
|-----------|--------------|---------|----------|
| ESP32 DevKit | ESP32-WROOM-32 | Main microcontroller | 1 |
| Temperature Sensor | DHT22 or BME280 | Temperature & humidity | 1 |
| Light Sensor | BH1750 or TSL2561 | Light intensity (Lux) | 1 |
| CO2 Sensor | MH-Z19 or SCD30 | CO2 concentration (ppm) | 1 |
| LED (Blue) | 5mm | Fan indicator | 1 |
| LED (Red) | 5mm | Heater indicator | 1 |
| Resistors | 220Ω | LED current limiting | 2 |
| Breadboard | Standard | Prototyping | 1 |
| Jumper Wires | M-M, M-F | Connections | Assorted |
| USB Cable | Micro-USB | Power & programming | 1 |

### Pin Configuration

```cpp
// Analog Inputs (ADC pins - 12-bit resolution)
const int PIN_HUM_ADC   = 32;  // Humidity sensor
const int PIN_LIGHT_ADC = 34;  // Light sensor
const int PIN_CO2_ADC   = 35;  // CO2 sensor

// Digital Outputs
const int PIN_FAN    = 2;      // Fan control (Blue LED)
const int PIN_HEATER = 4;      // Heater control (Red LED)
```

### Wiring Diagram

```
                           ESP32
                    ┌──────────────┐
    Humidity ───────┤ GPIO 32      │
    Light ──────────┤ GPIO 34      │
    CO2 ────────────┤ GPIO 35      │
                    │              │
                    │         GPIO 2├────[220Ω]────LED(Blue)────GND
                    │         GPIO 4├────[220Ω]────LED(Red)─────GND
                    │              │
    3.3V ───────────┤ 3V3          │
    GND ────────────┤ GND          │
                    └──────────────┘
```

### Power Requirements

- **ESP32**: 80-260mA (WiFi active), 10mA (deep sleep)
- **Sensors**: ~30mA total
- **LEDs**: ~20mA each (with 220Ω resistors)
- **Recommended Power Supply**: 5V @ 500mA minimum

### Alternative Platforms

The TinyML model can be deployed on various microcontrollers:

| Platform | RAM | Flash | Cost | Suitability |
|----------|-----|-------|------|-------------|
| ESP32 | 520KB | 4MB | $5-10 | ✅ Excellent (WiFi included) |
| Arduino Nano 33 BLE | 256KB | 1MB | $20-25 | ✅ Good (BLE available) |
| STM32F103 | 20KB | 64KB | $2-5 | ✅ Good (ultra-low cost) |
| Raspberry Pi Pico | 264KB | 2MB | $4 | ✅ Good (dual-core) |
| Arduino Uno | 2KB | 32KB | $20 | ⚠️ Limited (tight on RAM) |

---

## 📊 Performance Metrics

### Model Accuracy

| Metric | Score |
|--------|-------|
| **Overall Accuracy** | 98.99% |
| **Precision (Occupied)** | 99.21% |
| **Recall (Occupied)** | 98.98% |
| **F1-Score (Occupied)** | 99.09% |
| **Precision (Unoccupied)** | 98.57% |
| **Recall (Unoccupied)** | 98.99% |
| **F1-Score (Unoccupied)** | 98.78% |

### Computational Performance

| Metric | Value |
|--------|-------|
| **Model Size** | <5KB |
| **Inference Time** | <1ms |
| **Inference Frequency** | 2.5 Hz (400ms loop) |
| **CPU Usage** | <5% (single core) |
| **Power Consumption** | ~150mW (WiFi active) |
| **Power Consumption** | <50mW (WiFi sleep) |

### Energy Savings Estimation

Assuming a typical office space with 8-hour occupancy per day:

- **Uncontrolled System**: HVAC runs 24/7 = 100% energy consumption
- **Occupancy-Based System**: HVAC runs only during occupancy ≈ 33% energy consumption
- **Estimated Savings**: ~67% reduction in HVAC energy usage

For a 1000W HVAC system:
- Daily savings: 16 hours × 1000W = 16 kWh
- Annual savings: ~5,840 kWh
- Cost savings (at $0.12/kWh): ~$700/year per room

---

## 📁 Project Structure

```
Energy_Optimizer_Sensor_AIOT_Device_Setup/
│
├── wifi-scan.ino                    # Main ESP32 firmware
├── occupancy_model.h                # Exported TinyML model (C++ header)
├── diagram_1.json                   # Wokwi circuit diagram
├── wokwi-project.txt                # Wokwi project metadata
│
├── Room_Occupancy_Detection.ipynb   # Model training notebook
├── datatraining.csv                 # Training dataset
│
├── README.md                        # Project documentation (this file)
├── .gitignore                       # Git ignore rules
├── LICENSE                          # MIT License
└── requirements.txt                 # Python dependencies
```

---

## 🔧 Configuration

### WiFi Settings

Edit `wifi-scan.ino` to configure your network:

```cpp
// For Wokwi simulation
const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASS = "";

// For real hardware
const char* WIFI_SSID = "Your_Network_Name";
const char* WIFI_PASS = "Your_Network_Password";
```

### ThingSpeak Integration

1. Create a free account at [thingspeak.com](https://thingspeak.com)
2. Create a new channel with 6 fields:
   - Field 1: Occupancy (0 or 1)
   - Field 2: Temperature (°C)
   - Field 3: Humidity (% RH)
   - Field 4: Light (Lux)
   - Field 5: CO2 (ppm)
   - Field 6: HumidityRatio
3. Copy your Write API Key
4. Update `wifi-scan.ino`:

```cpp
String THINGSPEAK_KEY = "YOUR_API_KEY_HERE";
```

### Sensor Calibration

If using real sensors, adjust mapping ranges in `wifi-scan.ino`:

```cpp
float Temperature = /* your sensor reading */;
float Humidity    = mapAdcToRange(rawHum, 18.0f, 35.0f);    // Adjust range
float Light       = mapAdcToRange(rawLight, 0.0f, 800.0f);  // Adjust range
float CO2         = mapAdcToRange(rawCO2, 350.0f, 1200.0f); // Adjust range
```

Ensure these ranges match your training data distribution for optimal accuracy.

---

## 🐛 Troubleshooting

### WiFi Connection Issues

**Problem**: ESP32 fails to connect to WiFi

**Solutions**:
- Verify SSID and password are correct
- Check if WiFi is 2.4GHz (ESP32 doesn't support 5GHz)
- Ensure WiFi network allows ESP32 connections (some enterprise networks block IoT devices)
- Increase connection timeout in code

### Inaccurate Predictions

**Problem**: Model predictions don't match actual occupancy

**Solutions**:
- Verify sensor readings are within expected ranges
- Check StandardScaler parameters match training data
- Ensure HumidityRatio is calculated correctly
- Recalibrate sensors if drift is suspected
- Consider retraining model with local data

### ThingSpeak Upload Failures

**Problem**: Data not appearing on ThingSpeak dashboard

**Solutions**:
- Verify Write API Key is correct
- Ensure publish interval is ≥15 seconds (ThingSpeak rate limit)
- Check internet connectivity
- Verify channel has correct number of fields
- Review Serial Monitor for HTTP response codes

### High Power Consumption

**Problem**: Battery drains too quickly

**Solutions**:
- Implement deep sleep between readings
- Disable WiFi when not needed
- Reduce sampling frequency
- Use low-power sensors (e.g., BME280 in forced mode)

---

## 🔬 Research & Educational Use

This project demonstrates several important concepts in embedded AI and IoT:

### Machine Learning Concepts
- **TinyML**: Deploying ML models on resource-constrained devices
- **Model Optimization**: Balancing accuracy with efficiency
- **Feature Engineering**: Preprocessing for edge deployment
- **Time-Series Handling**: Proper train-test splitting for temporal data
- **Class Imbalance**: Techniques for handling skewed datasets

### Embedded Systems
- **Real-Time Inference**: Sub-millisecond prediction loops
- **Memory Optimization**: Fitting models in <5KB SRAM
- **Sensor Fusion**: Combining multiple environmental sensors
- **Actuator Control**: Automated decision-making at the edge
- **IoT Protocols**: MQTT, HTTP, WiFi integration

### Sustainability & Energy
- **Smart Buildings**: Occupancy-driven automation
- **Energy Efficiency**: Reducing HVAC waste
- **Carbon Footprint**: Lower energy consumption = fewer emissions
- **Privacy-Preserving**: No cameras or microphones required

### Potential Extensions

This project can be extended for research purposes:

1. **Advanced Models**: Compare with CNNs, LSTMs, or Random Forests
2. **Multi-Room Systems**: Coordinated control across building zones
3. **Predictive Maintenance**: Detect sensor drift or HVAC failures
4. **Occupancy Forecasting**: Predict future occupancy patterns
5. **Privacy Analysis**: Evaluate data sensitivity and anonymization
6. **Energy Modeling**: Detailed analysis of savings vs. comfort trade-offs

---

## 📚 References & Acknowledgments

### Dataset
- Candanedo, Luis M., and Véronique Feldheim. "Accurate occupancy detection of an office room from light, temperature, humidity and CO2 measurements using statistical learning models." *Energy and Buildings* 112 (2016): 28-39.
- UCI Machine Learning Repository: [Occupancy Detection Dataset](https://archive.ics.uci.edu/ml/datasets/Occupancy+Detection+)
- Kaggle Mirror: [Occupancy Detection Data Set](https://www.kaggle.com/datasets/robmarkcole/occupancy-detection-data-set-uci)

### Technologies
- **ESP32**: Espressif Systems
- **Arduino**: Arduino IDE and Libraries
- **scikit-learn**: Machine learning in Python
- **Wokwi**: Online electronics simulator
- **ThingSpeak**: MathWorks IoT platform

### Inspiration
This project was developed as part of MSc Artificial Intelligence coursework, focusing on practical TinyML deployment for sustainable smart building applications.

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

**MIT License Summary**:
- ✅ Commercial use
- ✅ Modification
- ✅ Distribution
- ✅ Private use
- ⚠️ No warranty or liability

---

## 🤝 Contributing

Contributions are welcome! If you'd like to improve this project:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Areas for Contribution
- Additional sensor support (e.g., PIR motion sensors)
- Alternative ML models (Random Forest, Gradient Boosting)
- Mobile app for monitoring
- MQTT support for Home Assistant integration
- PCB design files
- Power optimization techniques

---

## 📧 Contact & Support

**Project Maintainer**: Englitchman  
**Institution**: Northumbria University - MSc Artificial Intelligence  
**Course**: Machine Learning & TinyML Deployment  

For questions, issues, or collaboration opportunities:
- 🐛 **Bug Reports**: Open an issue on GitHub
- 💡 **Feature Requests**: Open an issue with the "enhancement" label
- 📫 **Academic Inquiries**: Contact through university channels

---

## 🎓 Dissertation Context

This project is part of a broader dissertation titled:  
**"Evaluating and Enhancing the Reliability and Interpretability of AI-Based Medical Imaging Systems for Clinical Decision Support"**

While this specific implementation focuses on occupancy detection, the methodologies developed here (model interpretability, edge deployment, real-time inference) are directly applicable to medical AI systems where reliability and explainability are paramount.

---

## 🌟 Acknowledgments

Special thanks to:
- **Northumbria University** for providing resources and guidance
- **UCI Machine Learning Repository** for the occupancy detection dataset
- **Open-source community** for Arduino, ESP32, and scikit-learn libraries
- **Wokwi** for providing excellent simulation capabilities

---

<div align="center">

**⭐ If you found this project useful, please consider giving it a star on GitHub! ⭐**

Made with ❤️ for sustainable smart buildings and edge AI

</div>