/**
 *  @file   ventilator_modes.h
 *  @brief  Supported and Unsupported Modes of Mechanical Ventilation
 * 
 *  This file defines the modes of mechancial ventilation that 
 *  may be supported by one or more implementations of the Open Ventilator.
 *  A mode defines the behavior of the ventilator based on a number
 *  of characteristics -- the trigger, the limit, and cycle.
 * 
 *  \author Joe Turner <joe@rxjet.net>
 * 
 *  \copyright Copyright (C) 2020 RxJet Incorporated.
 */
#pragma once

/*! \defgroup modes Ventilator Operational Modes
    \brief Basic Modes of Mechanical Ventilation

## ACV Assist-Control Ventilation (ACV)
 
The patient receives either controlled or assisted breaths. When the
patient triggers an assisted breath, they receive a breath based on 
either the volume (V A/C) or pressure target (P A/C).

When set to an Assist/Control mode, machine-initiated breaths are delivered at a clinician-set
volume or pressure, inspiratory time, and rate. If the patient triggers a spontaneous breath
between machine breaths, the ventilator will deliver a breath based on the volume or pressure
settings and inspiratory time.

Whether initiated by the patient or the ventilator, all breaths are delivered at the same preset
volume or pressure and inspiratory time.

Also known as continuous mandatory ventilation (CMV). Each breath is 
either an assist or control breath, but they are all of the same volume (or pressure). 
The larger the volume, the more expiratory time required. If the I:E 
ratio is less than 1:2, progressive hyperinflation may result. ACV is 
particularly undesirable for patients who breathe rapidly – they may 
induce both hyperinflation and respiratory alkalosis. Note that mechanical 
ventilation does not eliminate the work of breathing, because the diaphragm 
may still be very active.

## SIMV (Synchronized Intermittent Mandatory Ventilation)

The patient receives controlled breaths based on the set breathing rate. 
Spontaneous breaths are either unsupported demand flow or supported using 
Pressure Support.

This mode guarantees a certain number of breaths, but unlike ACV, patient
breaths are partially their own, reducing the risk of hyperinflation or 
alkalosis. Mandatory breaths are synchronized to coincide with spontaneous 
respirations. Disadvantages of SIMV are increased work of breathing and 
a tendency to reduce cardiac output, which may prolong ventilator dependency.
The addition of pressure support on top of spontaneous breaths can reduce 
some of the work of breathing. SIMV has been shown to decrease cardiac 
output in patients with left-ventricular dysfunction [Crit Care Med 10: 423, 1982]

When set to a SIMV (Synchronized Intermittent Mandatory Ventilation) Mode, machine-initiated
breaths are delivered at a clinician-set volume or pressure, inspiratory time, and rate. 
These mandatory breaths are synchronized with patient effort. If the patient triggers a spontaneous breath
between machine breaths, the ventilator will deliver a spontaneous breath, which is pressuresupported. 

Computational logic: Mandatory breaths are volume-controlled. Spontaneous breaths 
may occur within the window determined by the set rate and are not assisted 
(ie, inspiratory pressure stays at baseline).

## CPAP (Continuous Positive Airway Pressure) 

The patient receives constant positive airway pressure while breathing 
spontaneously. Spontaneous breaths are either demand flow
or supported using Pressure Support.

Positive pressure given throughout the cycle. It can be delivered through 
a mask and is can be used in obstructive sleep apnea (esp. with a nasal mask), 
to postpone intubation, or to treat acute exacerbations of COPD.

is a non-invasive positive pressure mode of respiratory support. 
CPAP is a pressure applied at the end of exhalation to keep the alveoli open 
and not fully deflate. This mechanism for maintaining inflated alveoli helps 
increase partial pressure of oxygen in arterial blood, an appropriate increase
in CPAP increases the PaO2. CPAP is not technically a mode of "ventilation" 
as it does not directly affect the minute volume.

## Pressure Support Ventilation (PSV)

PSV mode maintains a constant level of pressure in the patient’s airway during exhalation. 
This allows the patient to determine inflation volume and respiratory frequency 
(but not pressure, as this is pressure-controlled), thus can only be used to 
augment spontaneous breathing. Pressure support can be used to overcome the 
resistance of ventilator tubing in another cycle (5 – 10 cm H20 are generally
used, especially during weaning), or to augment spontaneous breathing. 
PSV can be delivered through specialized face masks.

Simply stated, the ventilator applies a clinician-set pressure (Pressure Support) to each of the patient’s
breaths. This has the same benefits as CPAP, with the additional benefit of assisting the patient in
moving gas into his or her lungs.

 */


namespace ovp
{




//! \brief Ventilator Operational Mode Enumeration
//! 
//! The Ventilator allows you to select different ventilation modes that 
//! can be selected to optimally manage the patient.   
//!
//! This enumeration defines the modes of mechancial ventilation that 
//! may be supported by one or more implementations of the Open Ventilator.
//! A mode defines the behavior of the ventilator based on a number
//! of characteristics -- the trigger, the limit, and cycle.
//!
enum VENT_OPERATING_MODES
{
    //! \brief Assist-Control Ventilation (ACV)
    //!
    //! The patient receives either controlled or assisted breaths. When the
    //! patient triggers an assisted breath, they receive a breath based on 
    //! either the volume or pressure target.
    //! 
    //! Also known as continuous mandatory ventilation (CMV). Each breath is 
    //! either an assist or control breath, but they are all of the same volume. 
    //! The larger the volume, the more expiratory time required. If the I:E 
    //! ratio is less than 1:2, progressive hyperinflation may result. ACV is 
    //! particularly undesirable for patients who breathe rapidly – they may 
    //! induce both hyperinflation and respiratory alkalosis. Note that mechanical 
    //! ventilation does not eliminate the work of breathing, because the diaphragm 
    //! may still be very active.
    MODE_ACV,

    //! \brief Assist-Control Volume Ventilation
    //!
    //! The patient receives a set Vt and Ve with each assisted and controlled
    //! breath.  Does not limit peak inspiratory pressure.
    MODE_ACVV,

    //! \brief Assist Control Pressure Ventilation
    //! Ventilator delivers breath until set pressure is reached.
    //! Limits peak inspiratory pressure.
    MODE_ACPV,

    //! \brief SIMV (Synchronized Intermittent Mandatory Ventilation) 
    //! 
    //! The patient receives controlled breaths based on the set breathing rate. 
    //! Spontaneous breaths are either unsupported demand flow or supported using 
    //! Pressure Support.
    //!
    //! This mode guarantees a certain number of breaths, but unlike ACV, patient
    //! breaths are partially their own, reducing the risk of hyperinflation or 
    //! alkalosis. Mandatory breaths are synchronized to coincide with spontaneous 
    //! respirations. Disadvantages of SIMV are increased work of breathing and 
    //! a tendency to reduce cardiac output, which may prolong ventilator dependency.
    //! The addition of pressure support on top of spontaneous breaths can reduce 
    //! some of the work of breathing. SIMV has been shown to decrease cardiac 
    //! output in patients with left-ventricular dysfunction [Crit Care Med 10: 423, 1982]
    //!
    //! Computational logic: Mandatory breaths are volume-controlled. Spontaneous breaths 
    //! may occur within the window determined by the set rate and are not assisted 
    //! (ie, inspiratory pressure stays at baseline).
    MODE_SIMV,

    //! \brief Pressure Support Ventilation (PSV)
    //!
    //! Allows the patient to determine inflation volume and respiratory frequency 
    //! (but not pressure, as this is pressure-controlled), thus can only be used to 
    //! augment spontaneous breathing. Pressure support can be used to overcome the 
    //! resistance of ventilator tubing in another cycle (5 – 10 cm H20 are generally
    //! used, especially during weaning), or to augment spontaneous breathing. 
    //! PSV can be delivered through specialized face masks.
    MODE_PSV,

    //! \brief CPAP (Continuous Positive Airway Pressure) 
    //! The patient receives constant positive airway pressure while breathing 
    //! spontaneously. Spontaneous breaths are either demand flow
    //! or supported using Pressure Support.
    //!
    //! Positive pressure given throughout the cycle. It can be delivered through 
    //! a mask and is can be used in obstructive sleep apnea (esp. with a nasal mask), 
    //! to postpone intubation, or to treat acute exacerbations of COPD.
    //!
    //! is a non-invasive positive pressure mode of respiratory support. 
    //! CPAP is a pressure applied at the end of exhalation to keep the alveoli open 
    //! and not fully deflate. This mechanism for maintaining inflated alveoli helps 
    //! increase partial pressure of oxygen in arterial blood, an appropriate increase
    //! in CPAP increases the PaO2. CPAP is not technically a mode of "ventilation" 
    //! as it does not directly affect the minute volume.
    MODE_CPAP,

#if 0 
    //! \brief Pressure-Controlled Ventilation (PCV)
    //!
    //! Less risk of barotrauma as compared to ACV and SIMV. Does not allow for 
    //! patient-initiated breaths. The inspiratory flow pattern decreases exponentially, 
    //! reducing peak pressures and improving gas exchange [Chest 122: 2096, 2002]. 
    //! The major disadvantage is that there are no guarantees for volume, especially
    //! when lung mechanics are changing. Thus, PCV has traditionally been preferred 
    //! for patients with neuromuscular disease but otherwise normal lungs
    MODE_PCV,

    //! \brief Pressure Controlled Inverse Ratio Ventilation (PCIRV)
    //!
    //! Pressure controlled ventilatory mode in which the majority of time is spent 
    //! at the higher (inspiratory) pressure. Early trials were promising, however 
    //! the risks of auto PEEP and hemodynamic deterioration due to the decreased
    //! expiratory time and increased mean airway pressure generally outweight 
    //! the small potential for improved oxygenation.
    MODE_PCIRV,

    //! \brief Airway Pressure Release Ventilation (APRV)
    //!
    //! Airway pressure release ventilation is similar to PCIRV – instead of being 
    //! a variation of PCV in which the I:E ratio is reversed, APRV is a variation 
    //! of CPAP that releases pressure temporarily on exhalation. This unique 
    //! mode of ventilation results in higher average airway pressures. Patients 
    //! are able to spontaneously ventilate at both low and high pressures, although 
    //! typically most (or all) ventilation occurs at the high pressure. In the 
    //! absence of attempted breaths, APRV and PCIRV are identical. As in PCIRV, 
    //! hemodynamic compromise is a concern in APRV. Additionally, APRV typically 
    //! requires increased sedation.
    MODE_APRV,

    //! \brief Pressure Regulated Volume Control (PRVC)
    //!
    //! A volume target backup is added to a pressure assist-control mode
    MODE_PRVC,

    //! \brief Proportional Assist Ventilation (PAV)
    //! 
    //! During PAV, the clinician sets the percentage of work of breathing to be 
    //! provided by the ventilator. PAV uses a positive feedback loop to accomplish 
    //! this, which requires knowledge of resistance and elastance to properly 
    //! attenuate the signal
    //!
    //! Compliance and resistance must therefore be periodically calculated – this 
    //! is accomplished by usingintermittent end-inspiratory and end-expiratory 
    //! pause maneuvers (which also calculate auto PEEP). In addition to percent 
    //! support, the clinician sets the trigger and the cycle (what actually ends 
    //! the breath)
    //! 
    //! The theoretical advantage of PAV is increased synchrony compared to PSV 
    //! (which provides the same amount of support regardless of how much effort 
    //! the patient makes)
    MODE_PAV,

    MODE_APAP,

    //! \brief BL (Bi Level)
    //! The ventilator provides two pressure settings to assist patients breathing
    //! spontaneously: a higher inhalation pressure (IPAP) and a lower exhalation 
    //! pressure (EPAP).
    MODE_BL,

    //! \brief Volume Assured Pressure Support Ventilation
    MODE_VAPS,

    //! \brief Automatic Tube Compensation (ATC)
    MODE_ATC,

    //! \brief Neurally Adjusted Ventilatory Assist (NAVA) 
    MODE_NAVA,
#endif
};

}
