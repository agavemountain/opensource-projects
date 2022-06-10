/**
 *  @file   alarm_defs.h
 *  @brief  Ventilator Alarm Definitions
 * 
 *  This file defines the various alarms which will trigger buzzers,
 *  indicators, or other actions which need to be logged or acted upon.
 * 
 *  \author Joe Turner <joe@rxjet.net>
 * 
 *  \copyright Copyright (C) 2020 RxJet Incorporated.
 */
#pragma once

namespace ovp
{


//! \brief Ventilator Alarm Enumeration
enum VENT_ALARM
{
    //! Alarm occurring in case of main supply failure
    ALARM_AC_POWER_FAIL,

    //! Alarm ambient temperature is too high or too low
    ALARM_AMBIENT_TEMPERATURE,

    //! Alarm occurring when the patient does not make any INSPIRATORY TRIGGER during
    //! APNEA TIME.
    ALARM_APNEA,       

    //! Alarm triggering when the internal battery temperature is
    //! too low or too high.
    ALARM_BATTERY_TEMP,

    //! Alarm triggering when too much breath are terminated by a time limit
    //! in SIMV modes. Typically trigger when too much leak is present in the patient interface.
    ALARM_BREATH_TIME_CYCLED,

    //! Alarm triggering when the buzzer battery is not able to
    //! be charged by the ventilator.
    ALARM_BATTERY_BUZZER_FAIL,

    //! Alarm occurring when a battery default is detected.
    ALARM_CHECK_BATTERY,

    //! Alarm occurring when a buzzer default is detected.
    ALARM_CHECK_BUZZER,

    //! Alarm triggering when the FIO2 is below 18% which means the sensor may be faulty.
    ALARM_CHECK_FIO2,

    //! Alarm occurring when an INTERNAL PRESSURE default is detected.
    ALARM_CHECK_PRESSURE,

    //! Alarm occurring when a PROXIMAL PRESSURE default is detected.
    ALARM_CHECK_PROXIMAL,

    //! Alarm occurring when the remote control (?)
    ALARM_CHECK_REMOTE,

    //! Alarm occurring when NEW VERSION, EEPROM OUT OF RANGE or
    //! LOOSING SETTINGS event is detected.
    ALARM_CHECK_SETTINGS,

    //! Alarm occurring when INFO SUPPLY is not consistent with INFO LED AC
    //! and INFO LED DC
    ALARM_CHECK_SUPPLY,

    //! Alarm occurring when a significant rebreathing is detected.
    ALARM_CHECK_VALVE,

    //! Alarm triggering when the valve pressure is faulty.
    ALARM_CHECK_VALVE_PRESSURE,

    //! Alarm occurring when a QI default or a VTI deviation from consign is
    //! detected.
    ALARM_CHECK_VOLUME,

    //! Alarm triggering when the ventilation mode is not compatible with a 
    //! leak configuration.
    ALARM_CONNECT_VALVE,

    //! Alarm triggering when the pressure settings are not compatible with 
    //! a leak configuration.
    ALARM_CONNECT_VALVE_CHG_PRESSURE,
};

} // namespace