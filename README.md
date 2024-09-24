# Automatic Pet Food Dispenser

Led a team of four and developed an Arduino-based pet food dispenser that allows pet owners to schedule when the food should automatically dispense.

-   Pet owners with busy schedules who cannot be home to feed their pets.
-   Owners with multiple pets having different feeding schedules.
-   Pet owners going on vacation who need to manage their pet's feeding.
-   Pet shelters and boarding facilities, ensuring that all animals are fed on time and in the right amounts.
-   Veterinary clinics and animal hospitals, providing feeding for animals undergoing treatment.

## Applied Subsystems

### Input/Output

The input/output subsystem provides a user interface for setting the feeding schedule and controlling the dispenser. The LCD 1602 with IIC displays the feeding schedule and the amount of food to be dispensed, while a keypad or buttons allow the user to input feeding times.

### Memory System

The memory system stores the feeding schedule and the amount of food to be dispensed. The schedule can be easily modified and stored on the Arduino UNO R3, which serves as the memory unit.

### Processing Unit

The processing unit, the Arduino UNO R3, manages the feeding schedule and dispenses food at designated times. It controls the motor and motor driver module to dispense the food. The RTC module helps the processing unit keep track of time and trigger feeding at the correct moments.

## Material Requirements

| Software           | Hardware            | Miscellaneous     |
| ------------------ | ------------------- | ----------------- |
| Arduino IDE        | 16x2 LCD            | Pet Food Bowl     |
| Software Libraries | 4x4 Membrane Keypad | Plywood Enclosure |
|                    | Arduino UNO         |                   |
|                    | Breadboard          |                   |
|                    | Connecting Wires    |                   |
|                    | Piezo Buzzer        |                   |
|                    | Resistors           |                   |
|                    | Servo Motor         |                   |
