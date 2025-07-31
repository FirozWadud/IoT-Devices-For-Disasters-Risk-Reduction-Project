# IoT Devices for Disaster Risk Reduction

A complete fire safety and emergency alert system consisting of three Arduino-based devices that work together to detect emergencies and send SMS notifications. This project was developed for disaster risk reduction in buildings and facilities.

![All 3 Devices](images/all-devices.jpg)

## Overview

This system provides comprehensive emergency detection and response through three interconnected devices:

1. **Manual Call Point** - Emergency switches for manual activation
2. **SMS-Based Warning System** - Remote alarm control via SMS commands  
3. **IoT Fire Detector** - Automatic smoke and heat detection with GPS reporting

All devices communicate via SMS and can operate independently or as part of a coordinated emergency response system.

## Device Specifications

### Device 1: Manual Call Point with Multiple Switches

![Manual Call Point](images/device1-manual-callpoint.jpg)

**Phone Number:** 01907808281

**Features:**
- Five emergency push buttons for manual activation
- Sends SMS alerts to predefined emergency contacts when any button is pressed
- Battery backup for continuous operation during power outages
- Suitable for installation in hallways, exits, and common areas

**Use Case:** Manual emergency reporting where users can quickly alert emergency services by pressing any available button.

### Device 2: SMS-Based Warning System

![SMS Warning System](images/device2-sms-warning.jpg)

**Phone Number:** 01907808282

**Features:**
- Receives SMS commands from authorized numbers
- Controls strobe horn and warning lights
- Remote activation capability from control center
- High-voltage relay control for industrial alarm systems

**SMS Commands:**
```
Drr: stob_horn_on   - Activates alarm system
Drr: stob_horn_off  - Deactivates alarm system
```

**Use Case:** Central control of building-wide alarm systems that can be activated remotely by emergency coordinators.

### Device 3: IoT Fire Detector

![IoT Fire Detector](images/device3-iot-detector.jpg)

**Phone Number:** 01907808283

**Features:**
- Automatic smoke and heat detection
- Manual emergency button for immediate activation
- GPS location reporting via GPRS to central server
- Backup SMS communication when internet connection fails
- Real-time monitoring and data transmission

**Communication Methods:**
- Primary: GPRS data transmission with GPS coordinates
- Backup: SMS alerts to emergency contacts
- Server endpoint: Reports to central monitoring system

**Use Case:** Automated fire detection in areas requiring continuous monitoring with precise location reporting.

## System Architecture

```
Emergency Detection → Local Alarm → SMS/GPRS Notification → Emergency Response
     ↓                    ↓              ↓                      ↓
[Sensors/Buttons] → [Local Buzzer] → [GSM Module] → [Emergency Contacts]
                                           ↓
                                    [Central Server]
```

### Network Configuration

- **Devices 1-3:** Field devices (01907808281, 01907808282, 01907808283)
- **Server Module:** Central monitoring (01907808284)  
- **Mobile Control:** Remote monitoring (01907808285)

## Installation Guide

### Hardware Requirements

**For each device:**
- Arduino microcontroller
- SIM800L GSM module
- Appropriate sensors (smoke, temperature, gas)
- Emergency switches and buttons
- Buzzer/alarm components
- 12V battery backup system
- Weatherproof enclosure

### Circuit Diagrams

![Circuit Diagram](images/circuit-diagram.jpg)

### Setup Instructions

1. **Device Placement**
   - Install Device 1 near building exits and high-traffic areas
   - Mount Device 2 in locations where audible alarms are most effective
   - Place Device 3 in areas with highest fire risk (kitchens, electrical rooms, etc.)

2. **Power Configuration**
   - Connect main power supply to each device
   - Install backup batteries with minimum 4-hour capacity
   - Test backup power systems regularly

3. **Network Registration**
   
   Send registration SMS to each device:
   ```
   1 [Building-Address] [Contact1] [Contact2] [Contact3] [Contact4] [Contact5]
   ```
   
   Set custom emergency message:
   ```
   0 [Your emergency message here]
   ```

4. **System Testing**
   - Test all manual switches on Device 1
   - Send SMS commands to Device 2 to verify alarm control
   - Test smoke detection on Device 3 using controlled smoke source
   - Verify SMS delivery to all registered contacts

## Configuration

### SMS Commands

**Registration Format:**
```
1 BuildingName +1234567890 +1234567891 +1234567892 +1234567893 +1234567894
```

**Message Setup:**
```
0 FIRE EMERGENCY at [Location]. Call 911 immediately. Evacuate building.
```

**Remote Activation:**
```
activate
```

### Server Communication

Device 3 transmits data to: `http://202.74.244.242:5000/gprs`

Data includes:
- Device identifier
- GPS coordinates  
- Sensor readings
- Timestamp
- Emergency status

## Code Structure

### Key Functions

**SMS Handling:**
- `sendSMS()` - Transmits messages to registered contacts
- `receiveSMS()` - Processes incoming commands
- `registration()` - Manages contact list updates

**Sensor Management:**
- `readSensorValues()` - Monitors all connected sensors
- `checkThresholds()` - Evaluates alarm conditions
- `triggerAlarm()` - Activates local and remote alerts

**Data Storage:**
- `writeStringToEEPROM()` - Saves configuration data
- `readStringFromEEPROM()` - Retrieves stored settings

### Threshold Settings

Default values (adjustable in code):
```cpp
int SmokeThreshold = 500;
int TemperatureThreshold = 80;  // Celsius
String activationText = "activate";
```

## Technical Specifications

| Component | Device 1 | Device 2 | Device 3 |
|-----------|----------|----------|----------|
| Microcontroller | Arduino Uno | Arduino Uno | Arduino Uno |
| Communication | SMS only | SMS only | SMS + GPRS |
| Sensors | 5x Switches | None | Smoke, Heat, Manual |
| Outputs | SMS alerts | Strobe, Horn | SMS, GPS data |
| Power | 12V + Battery | 12V + Battery | 12V + Battery |
| Backup Duration | 4+ hours | 4+ hours | 4+ hours |

## Troubleshooting

### Common Issues

**SMS not delivered:**
- Check SIM card balance and network coverage
- Verify phone number format includes country code
- Confirm GSM module antenna connection

**False alarms:**
- Adjust sensor sensitivity in code
- Check sensor placement away from heat sources
- Use reset button to clear false alarm state

**Power issues:**
- Test backup battery voltage (should be >11V)
- Check main power supply connections
- Verify current capacity for GSM module operation

**GPRS connection problems:**
- Confirm APN settings for carrier
- Check internet connectivity
- Verify server endpoint accessibility

### Debug Mode

Enable serial monitoring for troubleshooting:
```cpp
// Uncomment in main loop for debug output
debugSensors();
```

## Maintenance

### Regular Checks

**Monthly:**
- Test all emergency buttons
- Verify SMS delivery to all contacts
- Check battery backup functionality
- Clean sensor components

**Quarterly:**
- Update emergency contact list if needed
- Test GPRS connectivity and GPS accuracy
- Verify alarm volume and visibility
- Check enclosure integrity

**Annually:**
- Replace backup batteries
- Update firmware if available
- Conduct full system integration test
- Review and update emergency procedures

## Applications

This system is suitable for:

- **Residential buildings** - Early fire detection and occupant notification
- **Commercial facilities** - Employee safety and emergency coordination  
- **Educational institutions** - Student and staff protection
- **Industrial sites** - Worker safety in high-risk environments
- **Healthcare facilities** - Patient safety and staff notification
- **Government buildings** - Public safety and security

## Contributing

To contribute to this project:

1. Fork the repository
2. Create a feature branch for your changes
3. Test thoroughly with actual hardware
4. Submit a pull request with detailed description of changes

## License

This project is open source. Please ensure compliance with local fire safety regulations when implementing these devices.

## Support

For technical assistance:
- Review troubleshooting section above
- Check circuit diagrams for proper connections
- Verify power supply specifications
- Test with known working SIM cards

## Safety Notice

These devices are intended to supplement, not replace, certified fire safety equipment. Always comply with local building codes and fire safety regulations. Regular testing and maintenance are essential for reliable operation.
