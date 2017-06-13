/**
 * \file
 * \brief     GAS module main
 * \author    Chris Smeele
 * \author    David Driessen
 * \author    Paul Ettema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "wrap-hwlib.hh"

#include "hwlib-due-spi.hh"
#include "sd-spi.hh"
#include "data-logger.hh"
#include "alarm.hh"

// TODO: Move to separate file (Temporary warning fix)
/**
 * \brief Reads the gas sensor data
 * \param sensor The analog pin the gas sensor is connected to
 * \returns The measured data as float voltage
 */
float readGasSensor(hwlib::target::pin_adc &sensor);
int compareToCalibration(hwlib::target::pin_adc &sensor, float calibrationValue);
float calibration(hwlib::target::pin_adc &sensor, int calibrationCounter);


int compareToCalibration(hwlib::target::pin_adc &sensor, float calibrationValue) {
    return (int)(100 / calibrationValue * readGasSensor(sensor));
}

float readGasSensor(hwlib::target::pin_adc &sensor) {
    // 4096.0f is previous max value
    // 3.3f is new max value
    float analogValue = (((float)sensor.get()) / 4096.0f * 3.3f);
    return analogValue;
}

float calibration(hwlib::target::pin_adc &sensor, int calibrationCounter) {
    float totalValue = 0;
    for(int i = 0; i < calibrationCounter; i++){
        totalValue += readGasSensor(sensor);
        hwlib::wait_ms(250);
    }
    return totalValue/calibrationCounter;
}

int main() {
    namespace target = hwlib::target;

    WDT->WDT_MR = WDT_MR_WDDIS;

    // Setup pins
    target::pin_adc sensor = target::pin_adc(target::ad_pins::a0);
    target::spi_bus_due spiBus;
    auto cs = target::pin_out(target::pins::d7);
    auto alarmled = target::pin_out(target::pins::d8);
    auto a = target::pin_out(target::pins::d13);

    // Initialize classes
    SdSpi sd(cs, spiBus);
    auto logger = DataLogger(sd);

    Alarm alarm = Alarm(2.7f, alarmled);
    float calibrationValue = calibration(sensor, 10);
    int sensorValue = 0;
    // Startup blink
    a.set(0);
    hwlib::wait_ms(200);
    a.set(1);
    hwlib::wait_ms(100);
    a.set(0);
    hwlib::cout << "writing to sd card\r\n";
    using namespace hwlib;
    while (true) {
        uint64_t time = hwlib::now_us();
        // For debugging print a . for each measurement
        sensorValue = compareToCalibration(sensor, calibrationValue);
        cout << sensorValue << "\t";
        logger.writeValue(sensorValue);
        alarm.checkGasValue(sensorValue);

        hwlib::wait_us((int_fast32_t) (2500000 - (hwlib::now_us() - time)));
    }

    return 0;
}
