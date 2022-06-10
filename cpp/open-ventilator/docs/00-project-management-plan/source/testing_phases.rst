Tests Phases Management
=======================

If you instantiate the “software development plan” document and 
describe phases in that doc, you may add a reference to that doc 
and leave this section and subsections blank.

Integration tests
-----------------
Optional.
Describe how integration is managed Phases, reviews, documentation … Even if this may be described in your quality management system, I recommend you to describe what is forecasted.

Verification tests
------------------
Describe how verification tests are managed. Phases, reviews, documentation … Even if this may be described in your quality management system, I recommend you to describe what is forecasted.
Tests is often the weak link of soft development. Thinking about tests at the beginning of the project is worth the effort.
Example:
Tests are split in four phases:
-	Alpha 1 tests: in this phase, V0.1 of software will be tested. Testers will be the software development team. Each member tests a portion of software developed by another member. Software will be directly tested on the development platform
-	Alpha 2 tests: in this phase, V0.5 of software will be tested. Tester will be the software integrator. Software will be installed on the integration and test platform.
-	Beta 1 tests: in this phase, V0.8 of software will be tested. Tester will be the software integrator and selected end-users. Software will be installed on the integration and test platform.
-	Beta 2 tests: in this phase, V0.9 of software will be tested. Testers will be selected end-users. Software will be installed on the pilot platform in ….

Tests phases are described in the software tests plan OR below:

Phase 1
-------

Describe the verification phase:
-	In: what is verified (version Vx.y.z)
-	Tasks: how it is verified (tests are done according to software test description doc XXX)
-	Out: the test report
-	Acceptation criteria: how the tests are passed or failed.

Example of acceptation criteria, with bugs levels ratios (dummy but very effective):
-	Alpha tests: all blocking bugs are fixed
-	Beta tests:  all major bugs found in alpha tests are fixed and less than 20% of remaining bugs are major
-	Final version: all major bugs are fixed and 90% of minor bugs are fixed.

Example of acceptation criteria, with rationale about requirements:
-	Alpha tests: tests about critical requirements (like those from risk analysis) are passed and requirements about system-software interfaces are passed
-	Beta tests:  tests on previous requirements and tests on requirements about main use cases are passed
-	Final version: all tests are passed

Phase 2
-------

Repeat the pattern for each phase
Describe the verification phase:
-	In: what is verified (version Vx.y.z)
-	Task: how it is verified (tests are done according to software test description doc XXX)
-	Out: the test report
-	Acceptation criteria: how the tests are passed or failed.
