# STOUT-main
Software repository for the STOUT senior project.

# File Descriptions
All files located in /Documents/STOUT/Stout/src unless otherwise noted

execute.cc
  start_loop

    Description:
    This function initiates all of the interrupts and the main loop through the
    glib library. One interrupt is on GPIO 349, which is triggered by a change in
    the input on this pin. The second interrupt is timer based, and it occurs
    every 100 ms. Additionally, the save location and header for the EMCS data
    is setup.

    What Works:
    Interrupt triggering, interrupt priorities (the timed interrupt has a
    higher priority than the GPIO interrupt), main loop running when no interrupts
    are triggered, setting up save location for temperature, pressure, and
    humidity data.

    What Doesn't:
    Setting up save location for ADS/Controls data and spectrometer data.

  ext_main

    Description:
    This function is the main loop which occurs whenever interrupts are not
    triggered. It gets current temperatures from the spectrometer, ADS, and
    receives the temperature, pressure, and humidity sensor data from the
    Arduino. Additionally, the temperatures are evaluated to determine to turn
    on or off the heating pads. The temperature data is then saved to a text
    file.

    What Works:
    Collecting and saving temperature, pressure, and humidity from all sensors
    attached to the Arduino, the UV spectrometer, and the ADS.

    What Doesn't:
    Collecting and saving temperature data from the UV-Visible spectrometer and
    setting up timing so temperature measurements are only received every 1 s.

  GPIO_event

    Description:
    This function is the GPIO interrupt service routine (ISR) which is used to
    trigger UV spectrometer measurements. Upon a change in the state of the GPIO
    (GPIO 349), the spectrometer beings its integration period. Additionally, the
    polarizer is rotated 22.3 degrees if all 8 polarization angles have not been
    scanning yet, otherwise it is rotated back to 0 degrees.

    What Works:
    Reading UV spectrum data when actuations are done and rotating the polarizer
    to the correct angle.

    What Doesn't:
    Reading UV-Visbile spectrum data and saving the data from both spectrometers.
    Selecting a new scan location when measurements have been taken at all 8
    polarization angles for the current scan location.

  timeout_event

    Description:
    This function is the timed ISR which is used to take new ADS sensor data every
    100 ms. This data is used to compute the required actuations of the horizontal
    and vertical motors which are then sent to the Arduino. Additionally, the ADS
    data is save to a file.

    What Works:
    Collecting ADS angles, computing required actuations, saving ADS data, and
    sending the actuations to the Arduino.

    What Doesn't
    Saving actuation lengths to the same file as the ADS data.

handler.cc
  receive_arduino_data

    Description:
    Used to receive environmental data from the Arduino (20 bytes), read UDOO
    processor temperature, and place this data into a char buffer.

    What Works:
    Receiving environmental data from the Arduino and reading UDOO temperature.

    What Doesn't:
    Receiving GPS data from the Arduino.

  UART_transmit

    Description:
    Used to send environmental data to an external microcontroller through a
    serial connection.

    What Works:
    Transmitting environmental data to an external device.

    What Doesn't:
    N/A

  save_EMCS_data

    Description:
    Saves environmental data to a text file.

    What Works:
    Saving environmental data to a file.

    What Doesn't:
    Saving the data to the USB drives.

  save_ADS_data

    Description:
    Saves ADS angles and additional info to a text file.

    What Works:
    Saving ADS data to a file.

    What Doesn't:
    Saving the data to the USB drives.

serial_comm.cc

  set_arduino_comm, set_ADS_comm, set_UART_comm

    Description:
    Used to setup serial communication for the embedded Arduino, the ADS, and
    an external microcontroller, respectively.

    What Works:
    Setting up all serial communications.

    What Doesn't:
    N/A

  instructions.txt

    Description:
    Contains compilation instructions for compiling necessary files.

    What Works:
    Commands for compiling relevant files into an executable called full_test.

    What Doesn't:
    Putting this functionality into a makefile.

/sensors/ADS/ADS_read.cc

  ADS_read

    Description:
    Transmits bytes to ADS sensor to request data, waits, receives response
    (19 bytes), and saves this data.

    What Works:
    Requesting ADS data, receiving it, and saving it.

    What Doesn't:
    There are some issues with the angles jumping from 0 to 0.26 degrees when a
    sign change from a negative off-angle occurs. This is likely due to a sign
    issue someone in the receiving process.

/sensors/spectrometer/spectrometer.cc

  Spectrometer

    Description:
    Initializing spectrometer and configuring settings.

    What Works:
    Setting up the UV spectrometer.

    What Doesn't:
    The functionality for using two spectrometers is unknown, this needs to be
    tested.

  ReadSpectrum

    Description:
    Begins spectrometer integration and polls the data line until the spectra is
    ready.

    What Works:
    N/A

    What Doesn't:
    This function has not been tested, so it is not known whether or not it works,
    although I am sure that it does. A simple call of the function with the
    spectrometer attached should suffice for testing the functionality.

  ReadSpectrometerTemperature, ConvertVoltageToTemperature

    Description:
    Reads spectrometer thermistor voltage and converts this to temperature.

    What Works:
    Reading spectrometer temperature.

    What Doesn't:
    N/A

/controls/heater_control.cc

  heater_eval

    Description:
    Turns on/off the two heating pads if the evaluated temperatures are less than
    5 degrees C.

    What Works:
    Turning off/on heaters based on input temperatures.

    What Doesn't:
    Sending a PWM signal to the heaters without using a delay (possibly using
    interrupts).

/controls/optics_control.cc

  optics_compute

    Description:
    Calculates the required motor actuations (horizontal and vertical stepper
    motors) based on inputted off-Sun azimuth and elevation angles.

    What Works:
    Calculating motor actuations in terms of relative actuation length from a
    zero location.

    What Doesn't:
    Calculating actuations based on current actuation lengths and saving
    calculated lengths along with ADS data. Refining the algorithm may be
    necessary.

  optics_transmit

    Description:
    Sends calculated actuation lengths to the embedded Arduino via a serial
    connection.

    What Works:
    Sending data from UDOO processor to Arduino processor.

    What Doesn't:
    N/A

  polarizer_rotate

    Description:
    Used to rotate the polarizer based on whether or not a home position is
    desired.

    What Works:
    Rotating 22.5 degrees when the home input is set to 0, rotating back to 0
    degrees when the home input is set to 1.

    What Doesn't:
    There is an FTDI function to return to home which is more accurate than what
    is currently being used. It may be good to explore this option.

  /arduino_main/arduino_main.ino

    Description:
    Arduino function that controls everything the microcontroller needs to do.
    The main loop collects all of the environmental sensor and GPS data and
    transmits it to the UDOO processor. There is a GPIO based interrupt on pin
    14 which is triggered when new actuation lengths are sent from the UDOO. This
    ISR calculates the necessary number of steps to take for both of the motors
    and actuates them at the same time until all actuations are complete. The
    encoders are checked each step and the final values are compared to the
    commanded number of steps. The number of steps is changed if the values
    don't match up. The state of pin 15 is then changed to signal the UDOO that
    motor actuations are complete.

    What Works:
    Taking environmental sensor measurements, receiving actuation lengths from
    the UDOO, stepping the calculated number of steps, signaling end of motor
    actuations.

    What Doesn't:
    Some issues with the encoders were encountered, mainly that the pulse widths
    of the signals were no consistent. The time between steps was changed since
    testing the encoders, so this problem may have resolved itself. Otherwise it
    could be an issue with the encoders themselves. The actuation distance from the zero position for both motors need to be saved in EEPROM to keep track
    of them. Additionally, limits need to be applied for both motors to ensure
    that the motors do not try to actuate too far. The total number of steps that
    could be taken by the vertical motor was 13500 in testing, and it was 4000
    for the horizontal motor.
