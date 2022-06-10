Introduction
============

Background and Scope
--------------------

Hospitals all over the world are facing dire shortages of mechancial ventilators.  This need
was forseen years ago by health officials in the U.S., who attempted to acquire ventilators
to be stored in strategic reserves for use during a major pandemic.

Thirteen years ago, the U.S. Goverment started a project - code named Aura to make 
ventilators that were to cost less than $3,000 each, to add to the National Stockpile.
Newport Medical Instruments won the contract, and received $6.1 million upfront.  Everything was 
going smoothly and a working protoype was sent to the government. However, in May 2012 Covidien 
purchased Newport Medical. Coviden shut down the project and never shipped a single ventilator.

Five years ago, the U.S. Department of Health and Human Services signed a $13.8
million contract with a subsiderary of Royal Philips N.V. (Respironics). The contract was to
create a low-cost, portable, easy to use ventilator with a price of $3,280 each.
The company took the money, developed the product and then started selling a commercial version 
around the world.  According to news reports, they have not yet shipped a single ventilator.
In light of recent events, the prices the commercial version of this low cost ventilator have
soared ($17,154 retail price at vendor).

Ventilator manufacturers have shown little to no interest in building a low-cost ventilator 
which would undercut their expensive ventilator sales, or work with the government to drastically speed up
ventilator production.  This is while they are making record profits due to demand.

As a result, there is a dramatic and pressing need for a low-cost FDA certified ventilator. 

While a mechanical ventilator is a somewhat complex piece of machinery, the electronics
and mechanical design is relatively simplistic.  The bulk of the work in getting 
a modern mechanical ventilator working and certified is in the software.  Arguably, the 
most difficult, onerous, and time-consuming part of developing a ventilator is in 
the software engineering and testing.

The aim of this project is to produce an modular MCU-agnostic ventilator application
to control the operation of an open-source ventilator, complete with unit tests, 
hardware simulation, and testing procedures.

Approach for Managing the project
---------------------------------

In a medical device company, a project like this would involve a large number of people and
would leverage many different design disiplines.  A large contingent of people would 
be assigned to generating documentation required for FDA approval, and ultimately resolving
issues.

This project will be an open source project from the outset, enlisting resources and 
contract manufacturing as needed.

Project Milestones
------------------

There are a number of key challenges that must be overcome in order to get a medical device
cleared and on the market.  In our case, there will be additional hurdles.  

One of the biggest hurdles is FDA regulatory process itself, which requires an enormous amount of 
documentation.  That documentation must often be controlled in a quality management system, 
for which we are using github as an SCM. 

However, we estimate that once the first device does become cleared and is proven safe and
effective, that it will ease the burden on other manufacturers who rely on this software
and testing framework, possibly standardizing ventilator design throughout the world.

For the short term, we are going to focus producing what we think are the minimum required
documents per relavent standards, and spend most of our effort on testing, simulation, and 
mock test hardware to ensure safety.

Objectives
----------

Our objectives are simple.  We intend to:

- provide a software framework for developing a low-cost, safe, and effective ventilator; and
- design a modular electronic control system to control; and
- build and submit a complete ventilator for FDA approval;

Guiding Principles
------------------

The project management framework for this project will be focused on providing an
environment in which project activities can operate effectively and efficiently. These guiding principles help
ensure that communication is timely, project issues are being resolved in a timely manner and that project
risks are being managed appropriately. The key strategies that will be employed for the Name Project
include:

Absolute transparency.  All designs, code, testing, and plans will be provided and accessible online.
Utilizing the GNU Public License, anyone wishing to use the software or build the hardware may do so.
They must make thier modifications public, per the GNU Public License.

Contributions.  We intend to foster an environment where others can contribute to the project, within reason.  All Contributions
will be reviewed, discussed, and must be approved before inclusion into our repositories.

Focus on delivery.  We intend to work to produce a viable, professional product for delivery to the market.
