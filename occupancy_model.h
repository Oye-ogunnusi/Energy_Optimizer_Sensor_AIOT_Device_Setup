
#ifndef OCCUPANCY_MODEL_H
#define OCCUPANCY_MODEL_H

// Auto-generated decision tree model
// ESP32 / Arduino compatible
// Returns: 0 = Unoccupied, 1 = Occupied

static inline int predict_occupancy(
    float Temperature,
    float Humidity,
    float Light,
    float CO2,
    float HumidityRatio
) {
  if (Light <= 0.514264f) {
    if (CO2 <= 0.259893f) {
      if (Light <= 0.181229f) {
        return 0;
      } else {
        if (Humidity <= -1.590445f) {
          return 0;
        } else {
          return 0;
        }
      }
    } else {
      return 0;
    }
  } else {
    if (CO2 <= -0.815496f) {
      return 1;
    } else {
      if (Light <= 1.368072f) {
        if (Temperature <= 1.036992f) {
          if (Humidity <= -0.830307f) {
            return 1;
          } else {
            return 1;
          }
        } else {
          if (CO2 <= 0.753497f) {
            return 1;
          } else {
            return 1;
          }
        }
      } else {
        if (CO2 <= 1.509382f) {
          return 1;
        } else {
          return 1;
        }
      }
    }
  }

}

#endif // OCCUPANCY_MODEL_H
