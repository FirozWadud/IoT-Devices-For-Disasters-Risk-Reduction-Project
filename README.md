# IoT Devices for Disaster Risk Reduction

**A comprehensive emergency response system with three intelligent devices that detect fires, send instant SMS alerts, and coordinate emergency responses to save lives.**

<div align="center">
<img src="all-devices.PNG" alt="Complete IoT Emergency System" width="700"/>
<p><i>Complete system overview - Three devices working together for disaster risk reduction</i></p>
</div>

---

## How This System Protects Lives

When an emergency happens, every second counts. This system ensures instant communication and coordinated response through three specialized devices that work together seamlessly.

**The Flow:** Emergency Detected → SMS Alert Sent → Alarms Activated → Lives Saved

---

## The Three Smart Devices

### 🔴 Device 1: Manual Emergency Call Point

<table>
<tr>
<td width="60%">

**What it does:**
If someone presses any of the emergency switches, an SMS alert is immediately sent to the central server.

**Perfect for:**
- Building exits and entrances
- Hallways and common areas  
- Areas where people need quick access to emergency alerts

**Phone Number:** `01907808281`

</td>
<td width="40%">
<img src="Device_1/device1-manual-callpoint.PNG" alt="Manual Call Point Device" width="300"/>
</td>
</tr>
</table>

**Technical Design:**
<img src="Device_1/device1-schematic.png" alt="Device 1 Circuit Diagram" width="600"/>

---

### 🔵 Device 2: SMS-Controlled Warning System

<table>
<tr>
<td width="40%">
<img src="Device_2/device2-sms-warning.png" alt="SMS Warning System" width="300"/>
</td>
<td width="60%">

**What it does:**
This device receives SMS commands from the central server and activates strobe horns and warning lights using specific command syntax.

**Perfect for:**
- Large buildings requiring coordinated alarms
- Areas needing remote activation capability
- Central alarm control systems

**Phone Number:** `01907808282`

</td>
</tr>
</table>

**Technical Design:**
<img src="Device_2/device2-schematic.PNG" alt="Device 2 Circuit Diagram" width="600"/>

---

### 🟠 Device 3: Intelligent Fire Detection Unit

<table>
<tr>
<td width="60%">

**What it does:**
This advanced IoT device automatically detects heat and smoke. When triggered (automatically or manually), it sends GPS coordinates to the server via GPRS connection.

**Smart Features:**
- Automatic smoke and heat detection
- Manual emergency button
- GPS location reporting
- Internet connectivity with SMS backup

**Phone Number:** `01907808283`

</td>
<td width="40%">
<img src="Device_3/device3-iot-detector.png" alt="IoT Fire Detection Device" width="300"/>
</td>
</tr>
</table>

**Technical Design:**
<img src="Device_3/device3-schematic.png" alt="Device 3 Circuit Diagram" width="600"/>

---

## System Command Center

### Central Communication Hub

<img src="Device_3/gsm-module.png" alt="GSM GPRS Communication Module" width="400"/>

**Server Module** - Phone: `01907808284`
- Receives all emergency alerts
- Coordinates device communications
- Manages system responses

**Mobile Monitor** - Phone: `01907808285`  
- Real-time system monitoring
- Emergency notifications
- System status updates

---

## System Intelligence

### How the Devices Communicate

```
Manual Press (Device 1) ──┐
                         ├──► Central Server ──┐
Automatic Detection      │   (01907808284)    ├──► Emergency Response
(Device 3) ──────────────┘                    │
                                              ├──► Activate Alarms
SMS Command ◄─────────────────────────────────┘    (Device 2)
```

### Communication Flow

1. **Detection Phase**: Device 1 or Device 3 detects emergency
2. **Alert Phase**: SMS sent to central server with location data  
3. **Response Phase**: Server activates Device 2 alarms across building
4. **Coordination Phase**: All devices work together for complete coverage

---

## Quick Installation Guide

### Step 1: Device Placement Strategy
- **Device 1**: Install near exits, in hallways, and high-traffic areas
- **Device 2**: Mount where alarm sounds can reach maximum people
- **Device 3**: Place in fire-risk areas (kitchens, electrical rooms, storage)

### Step 2: Power and Backup
- Connect main power supply to each device
- Install backup batteries for power outage protection
- Test backup systems monthly

### Step 3: Network Setup  
- Configure SMS settings for all devices
- Set up GPRS connection for Device 3
- Test communication between all components

### Step 4: System Testing
- Test emergency switches on Device 1
- Send SMS commands to Device 2
- Verify automatic detection on Device 3

---

## Device Operation Guide

| Device | How to Use | What Happens |
|--------|------------|--------------|
| **Device 1** | Press any red emergency button | Instant SMS sent to server |
| **Device 2** | Receives automatic SMS commands | Strobe lights and horns activate |
| **Device 3** | Automatic detection or manual button | GPS location sent via internet |

### Emergency Contact Numbers

| Component | Purpose | Phone Number |
|-----------|---------|--------------|
| Manual Call Point | Emergency button alerts | **01907808281** |
| Warning System | Remote alarm control | **01907808282** |
| Fire Detector | Automatic detection | **01907808283** |
| Server Hub | Central coordination | **01907808284** |
| Mobile Monitor | System oversight | **01907808285** |

---

## Real-World Applications

**Residential Buildings**
- Early fire detection in apartments
- Manual emergency alerts in common areas
- Coordinated evacuation alarms

**Commercial Facilities**  
- Employee safety in offices
- Automatic detection in server rooms
- Building-wide emergency coordination

**Educational Institutions**
- Student safety in schools and universities
- Quick emergency response in dormitories
- Campus-wide alert systems

**Industrial Sites**
- Worker protection in factories
- Hazardous area monitoring
- Emergency coordination for large facilities

---

## Code Repository Structure

The Arduino code for each device is organized as follows:

```
📁 Project Root
├── 📁 call_point/              ← Device 1 Code
├── 📁 Relay_gsm/               ← Device 2 Code  
├── 📁 GPRS_beta/               ← Device 3 Code
└── 📁 multiswitch_registration/ ← Additional Features
```

### Getting Started with the Code

1. Choose the device you want to build
2. Navigate to the appropriate folder
3. Open the `.ino` file in Arduino IDE
4. Upload to your Arduino board
5. Configure phone numbers and settings

---

## System Benefits

**Instant Response**  
No delays - SMS alerts sent within seconds of detection

**Multiple Detection Methods**  
Manual switches, automatic sensors, and remote activation

**Reliable Communication**  
SMS backup ensures alerts get through even if internet fails

**Precise Location**  
GPS coordinates help emergency responders find exact location

**Coordinated Response**  
All devices work together for comprehensive emergency management

**Battery Backup**  
System continues operating during power outages

---

## Technical Support

For questions about installation, configuration, or troubleshooting:

- Check the code documentation in each device folder
- Review circuit diagrams for proper connections
- Test SMS functionality with known working SIM cards
- Verify power supply specifications for each device

---

**This system represents a complete approach to emergency detection and response, combining manual activation, automatic detection, and coordinated alarm systems to protect lives and property.**
