/*
* ping1d.h
* A device API for the Blue Robotics Ping1D echosounder
*
*~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!
* THIS IS AN AUTOGENERATED FILE
* DO NOT EDIT
*~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!~!
*
*/

#pragma once

#include "Arduino.h"
#include "Stream.h"
#include "pingmessage.h"
#include "pingmessage_all.h"
#include "ping_parser.h"

class Ping1D
{

public:

    /** Constructor
     *  @param ser: The device I/O
     *  @param baudrate: The device I/O baudrate
     */
    Ping1D(Stream& ser, uint32_t baudrate);

    /** Destructor
     *
     */
    ~Ping1D();
  
    /** Read in data from device, return a PingMessage if available
     *  Data will be read in from device until there is no data left in the RX buffer,
     *  or a valid PingMessage is successfully decoded.
     *  Note that there may still be data available in the RX buffer for decoding when
     *  this function returns a PingMessage
     *  @return: The next PingMessage from the device
     *  @return: null if the RX buffer is empty and no PingMessage has been decoded
     */
    PingMessage* read();

    /** Write data to device
     *  @param data: pointer to buffer to write
     *  @param length: buffer length to write
     *  @return: size of data buffer written to the device
     */
    size_t write(uint8_t* data, uint16_t length);

    /** Establish communications with the device, and initialize the update interval
     *  @param ping_interval_ms: The interval (in milliseconds) between acoustic measurements
     *  @return true if the device was initialized successfully
     */
    bool initialize(uint16_t ping_interval_ms = 50);


    /** Wait for reciept of a message with a particular message id from device
     *  @param id: The message id to wait for
     *  @param timeout_ms: The timeout period to wait for a matching PingMessage to be received
     *  @return The PingMessage received with matching id
     *  @return null if the timeout expires and no PingMessage was received with a matching id
     */
    PingMessage* waitMessage(enum Ping1DNamespace::msg_ping1D_id id, uint16_t timeout_ms);

    /** Wait for reciept of a message with a particular message id from device
     *  @param id: The message ID to wait for
     *  @param timeout_ms: The timeout period to wait for a matching PingMessage to be received
     *  @return The PingMessage received with matching id
     *  @return null if the timeout expires and no PingMessage was received with a matching id
     */
    void handleMessage(PingMessage* pmsg);

    /** Request a PingMessage from the device
     *  @param id: The message ID to request
     *  @param timeout_ms: The timeout period to wait for the requested PingMessage to be received
     *  @return The PingMessage that was requested
     *  @return null if the device did not reply with the requested message before the timeout period expired
     *
     *  @par ex.
     *  @code
     *  ping_msg_ping1D_voltage_5 msg(*pd.request(Ping1DNamespace::Voltage_5));
     *  @endcode 
     */
    PingMessage* request(enum Ping1DNamespace::msg_ping1D_id id, uint16_t timeout_ms = 400);
  

    /** Request a PingMessage of type T from the device
     *  @param timeout_ms: The timeout period to wait for the requested PingMessage to be received
     *  @return The PingMessage that was requested
     *  @return null if the device did not reply with the requested message before the timeout period expired
     *
     *  @par ex.
     *  @code
     *  auto msg = pd.request<ping_msg_ping1D_voltage_5>();
     *  @endcode
     */
    template <typename T>
    T* request();

    /** Helper to request distance and confidence
     *  @return true if the distance and confidence have been updated successfully
     */
    bool update() {
        return request(Ping1DNamespace::Distance_simple);
    }

    /** Device information
    *   @return device_type: Device type. 0: 1D Echosounder
    *   @return device_model: Device model. 0: Ping1D
    *   @return firmware_version_major: Firmware version major number.
    *   @return firmware_version_minor: Firmware version minor number.
    */
    bool get_firmware_version(
                     uint8_t* device_type = nullptr,
                     uint8_t* device_model = nullptr,
                     uint16_t* firmware_version_major = nullptr,
                     uint16_t* firmware_version_minor = nullptr
         );

    /** The device ID.
    *   @return device_id: The device ID (0-254). 255 is reserved for broadcast messages.
    */
    bool get_device_id(
                     uint8_t* device_id = nullptr
         );

    /** The 5V rail voltage.
    *   @return voltage_5: Units: mV; The 5V rail voltage.
    */
    bool get_voltage_5(
                     uint16_t* voltage_5 = nullptr
         );

    /** The speed of sound used for distance calculations.
    *   @return speed_of_sound: Units: mm/s; The speed of sound in the measurement medium. ~1,500,000 mm/s for water.
    */
    bool get_speed_of_sound(
                     uint32_t* speed_of_sound = nullptr
         );

    /** The scan range for acoustic measurements. Measurements returned by the device will lie in the range (scan_start, scan_start + scan_length).
    *   @return scan_start: Units: mm; The beginning of the scan range in mm from the transducer.
    *   @return scan_length: Units: mm; The length of the scan range.
    */
    bool get_range(
                     uint32_t* scan_start = nullptr,
                     uint32_t* scan_length = nullptr
         );

    /** The current operating mode of the device. Manual mode allows for manual selection of the gain and scan range.
    *   @return mode_auto: 0: manual mode, 1: auto mode
    */
    bool get_mode_auto(
                     uint8_t* mode_auto = nullptr
         );

    /** The interval between acoustic measurements.
    *   @return ping_interval: Units: ms; The interval between acoustic measurements.
    */
    bool get_ping_interval(
                     uint16_t* ping_interval = nullptr
         );

    /** The current gain setting.
    *   @return gain_index: 0: 0.6dB, 1: 1.8dB, 2: 5.5dB, 3: 12.9dB, 4: 30.2dB, 5: 66.1dB, 6: 144dB
    */
    bool get_gain_index(
                     uint32_t* gain_index = nullptr
         );

    /** The duration of the acoustic activation/transmission.
    *   @return pulse_duration: Units: microseconds; Acoustic pulse duration.
    */
    bool get_pulse_duration(
                     uint16_t* pulse_duration = nullptr
         );

    /** General information.
    *   @return firmware_version_major: Firmware major version.
    *   @return firmware_version_minor: Firmware minor version.
    *   @return voltage_5: Units: mV; Device supply voltage.
    *   @return ping_interval: Units: ms; The interval between acoustic measurements.
    *   @return gain_index: The current gain setting. 0: 0.6dB, 1: 1.8dB, 2: 5.5dB, 3: 12.9dB, 4: 30.2dB, 5: 66.1dB, 6: 144dB
    *   @return mode_auto: The current operating mode of the device. 0: manual mode, 1: auto mode
    */
    bool get_general_info(
                     uint16_t* firmware_version_major = nullptr,
                     uint16_t* firmware_version_minor = nullptr,
                     uint16_t* voltage_5 = nullptr,
                     uint16_t* ping_interval = nullptr,
                     uint8_t* gain_index = nullptr,
                     uint8_t* mode_auto = nullptr
         );

    /** The distance to target with confidence estimate.
    *   @return distance: Units: mm; Distance to the target.
    *   @return confidence: Units: %; Confidence in the distance measurement.
    */
    bool get_distance_simple(
                     uint32_t* distance = nullptr,
                     uint8_t* confidence = nullptr
         );

    /** 
    *   @return distance: Units: mm; The current return distance determined for the most recent acoustic measurement.
    *   @return confidence: Units: %; Confidence in the most recent range measurement.
    *   @return pulse_duration: Units: us; The acoustic pulse length during acoustic transmission/activation.
    *   @return ping_number: The pulse/measurement count since boot.
    *   @return scan_start: Units: mm; The beginning of the scan region in mm from the transducer.
    *   @return scan_length: Units: mm; The length of the scan region.
    *   @return gain_index: The current gain setting. 0: 0.6dB, 1: 1.8dB, 2: 5.5dB, 3: 12.9dB, 4: 30.2dB, 5: 66.1dB, 6: 144dB
    */
    bool get_distance(
                     uint32_t* distance = nullptr,
                     uint16_t* confidence = nullptr,
                     uint16_t* pulse_duration = nullptr,
                     uint32_t* ping_number = nullptr,
                     uint32_t* scan_start = nullptr,
                     uint32_t* scan_length = nullptr,
                     uint32_t* gain_index = nullptr
         );

    /** Temperature of the device cpu.
    *   @return processor_temperature: Units: cC; The temperature in centi-degrees Centigrade (100 * degrees C).
    */
    bool get_processor_temperature(
                     uint16_t* processor_temperature = nullptr
         );

    /** Temperature of the on-board thermistor.
    *   @return pcb_temperature: Units: cC; The temperature in centi-degrees Centigrade (100 * degrees C).
    */
    bool get_pcb_temperature(
                     uint16_t* pcb_temperature = nullptr
         );

    /** Acoustic output enabled state.
    *   @return ping_enabled: The state of the acoustic output. 0: disabled, 1:enabled
    */
    bool get_ping_enable(
                     uint8_t* ping_enabled = nullptr
         );

    /** A profile produced from a single acoustic measurement. The data returned is an array of response strength at even intervals across the scan region. The scan region is defined as the region between <scan_start> and <scan_start + scan_length> millimeters away from the transducer. A distance measurement to the target is also provided.
    *   @return distance: Units: mm; The current return distance determined for the most recent acoustic measurement.
    *   @return confidence: Units: %; Confidence in the most recent range measurement.
    *   @return pulse_duration: Units: us; The acoustic pulse length during acoustic transmission/activation.
    *   @return ping_number: The pulse/measurement count since boot.
    *   @return scan_start: Units: mm; The beginning of the scan region in mm from the transducer.
    *   @return scan_length: Units: mm; The length of the scan region.
    *   @return gain_index: The current gain setting. 0: 0.6dB, 1: 1.8dB, 2: 5.5dB, 3: 12.9dB, 4: 30.2dB, 5: 66.1dB, 6: 144dB
    *   @return profile_data: The number of data points for the profile. (The length of the proceeding array)
    */
    bool get_profile(
                     uint32_t* distance = nullptr,
                     uint16_t* confidence = nullptr,
                     uint16_t* pulse_duration = nullptr,
                     uint32_t* ping_number = nullptr,
                     uint32_t* scan_start = nullptr,
                     uint32_t* scan_length = nullptr,
                     uint32_t* gain_index = nullptr,
                     uint16_t* profile_data_length = nullptr,
                     uint8_t** profile_data = nullptr
         );

    /** The protocol version
    *   @return protocol_version: The protocol version
    */
    bool get_protocol_version(
                     uint32_t* protocol_version = nullptr
         );


    /** Set the device ID.
    *   @param device_id - Device ID (0-254). 255 is reserved for broadcast messages.
    */
    bool set_device_id(uint8_t device_id, bool verify = true);

    /** Set the scan range for acoustic measurements.
    *   @param scan_start - Units: mm; 
    *   @param scan_length - Units: mm; The length of the scan range.
    */
    bool set_range(uint32_t scan_start, uint32_t scan_length, bool verify = true);

    /** Set the speed of sound used for distance calculations.
    *   @param speed_of_sound - Units: mm/s; The speed of sound in the measurement medium. ~1,500,000 mm/s for water.
    */
    bool set_speed_of_sound(uint32_t speed_of_sound, bool verify = true);

    /** Set automatic or manual mode. Manual mode allows for manual selection of the gain and scan range.
    *   @param mode_auto - 0: manual mode. 1: auto mode.
    */
    bool set_mode_auto(uint8_t mode_auto, bool verify = true);

    /** The interval between acoustic measurements.
    *   @param ping_interval - Units: ms; The interval between acoustic measurements.
    */
    bool set_ping_interval(uint16_t ping_interval, bool verify = true);

    /** Set the current gain selection.
    *   @param gain_index - 0: 0.6dB, 1: 1.8dB, 2: 5.5dB, 3: 12.9dB, 4: 30.2dB, 5: 66.1dB, 6: 144dB
    */
    bool set_gain_index(uint8_t gain_index, bool verify = true);

    /** Enable or disable acoustic measurements.
    *   @param ping_enabled - 0: Disable, 1: Enable.
    */
    bool set_ping_enable(uint8_t ping_enabled, bool verify = true);


    // Return the latest value received
    uint32_t distance() { return _distance; }

    // Return the latest value received
    uint16_t confidence() { return _confidence; }

    // Return the latest value received
    uint16_t profile_data_length() { return _profile_data_length; }
    uint8_t* profile_data() { return _profile_data; }

    // Return the latest value received
    uint16_t ping_interval() { return _ping_interval; }

    // Return the latest value received
    uint8_t ping_enabled() { return _ping_enabled; }

    // Return the latest value received
    uint16_t voltage_5() { return _voltage_5; }

    // Return the latest value received
    uint8_t device_model() { return _device_model; }

    // Return the latest value received
    uint32_t speed_of_sound() { return _speed_of_sound; }

    // Return the latest value received
    uint16_t firmware_version_minor() { return _firmware_version_minor; }

    // Return the latest value received
    uint32_t ping_number() { return _ping_number; }

    // Return the latest value received
    uint16_t firmware_version_major() { return _firmware_version_major; }

    // Return the latest value received
    uint16_t pcb_temperature() { return _pcb_temperature; }

    // Return the latest value received
    uint8_t mode_auto() { return _mode_auto; }

    // Return the latest value received
    uint32_t scan_start() { return _scan_start; }

    // Return the latest value received
    uint8_t device_type() { return _device_type; }

    // Return the latest value received
    uint32_t protocol_version() { return _protocol_version; }

    // Return the latest value received
    uint32_t scan_length() { return _scan_length; }

    // Return the latest value received
    uint32_t gain_index() { return _gain_index; }

    // Return the latest value received
    uint16_t processor_temperature() { return _processor_temperature; }

    // Return the latest value received
    uint16_t pulse_duration() { return _pulse_duration; }

    // Return the latest value received
    uint8_t device_id() { return _device_id; }


private:
    // Device I/O
    Stream& _stream;

    // For decoding PingMessages from the device
    PingParser _parser;

    // The current return distance determined for the most recent acoustic measurement.
    uint32_t _distance;

    // Confidence in the most recent range measurement.
    uint16_t _confidence;

    // The number of data points for the profile. (The length of the proceeding array)
    uint16_t _profile_data_length;
    uint8_t* _profile_data;

    // The interval between acoustic measurements.
    uint16_t _ping_interval;

    // The state of the acoustic output. 0: disabled, 1:enabled
    uint8_t _ping_enabled;

    // Device supply voltage.
    uint16_t _voltage_5;

    // Device model. 0: Ping1D
    uint8_t _device_model;

    // The speed of sound in the measurement medium. ~1,500,000 mm/s for water.
    uint32_t _speed_of_sound;

    // Firmware minor version.
    uint16_t _firmware_version_minor;

    // The pulse/measurement count since boot.
    uint32_t _ping_number;

    // Firmware major version.
    uint16_t _firmware_version_major;

    // The temperature in centi-degrees Centigrade (100 * degrees C).
    uint16_t _pcb_temperature;

    // The current operating mode of the device. 0: manual mode, 1: auto mode
    uint8_t _mode_auto;

    // The beginning of the scan region in mm from the transducer.
    uint32_t _scan_start;

    // Device type. 0: 1D Echosounder
    uint8_t _device_type;

    // The protocol version
    uint32_t _protocol_version;

    // The length of the scan region.
    uint32_t _scan_length;

    // The current gain setting. 0: 0.6dB, 1: 1.8dB, 2: 5.5dB, 3: 12.9dB, 4: 30.2dB, 5: 66.1dB, 6: 144dB
    uint32_t _gain_index;

    // The temperature in centi-degrees Centigrade (100 * degrees C).
    uint16_t _processor_temperature;

    // The acoustic pulse length during acoustic transmission/activation.
    uint16_t _pulse_duration;

    // The device ID (0-254). 255 is reserved for broadcast messages.
    uint8_t _device_id;

};
