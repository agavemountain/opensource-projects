Risk management during software development
===========================================

This chapter covers the risk management process and organization during the software development.

Organization and Responsibilities
---------------------------------
Describe the organization of the team responsible for risk management during design. 
You may add an organization chart or add a reference to your project management plan, 
where the organization of the project should be already described.


+-------------------+--------------------------------------------------------+
| Title             |  Responsibilities                                      |
+===================+========================================================+
| Project Manager   |  - Overall management process responsibility           |
|                   |  - Creation and update of Risk Analysis Table          |
|                   |  - Creation and update of Risk traceability matrix     |
|                   |  - Creation and update Risk Analysis Report            |
+-------------------+--------------------------------------------------------+
| Quality Manager   |  - TDB                                                 |
+-------------------+--------------------------------------------------------+

Qualification of Personnel
--------------------------

Describe the qualification of personnel responsible for the risk management and risk analysis activities. Example:
The personnel who participates to the risk analysis is composed of:
-	Experienced staff who was involved in the design process of similar products
-	The expert praticians who participate to the design process

Objective of risk management activities
---------------------------------------
The objective of risk management activities is to deliver a risk analysis report, which contains:
-	The device characteristics that could impact on safety (ISO 14971),
-	The software safety classification (IEC 62304),
-	The risk analysis table,
-	The risk traceability matrix with design requirements,
-	The overall assessment of residual risk.

The risk analysis table and risk traceability matrix will be created and updated 
as necessary during software development, according to tasks described in §2.4.
Data on the risk analysis table includes:
-	List the columns, according to your risk analysis table in your risk analysis report,
-	…
Data on the risk analysis table includes:
-	List the columns, according to your risk traceability matrix in your risk analysis report,
-	…
See the risk analysis report template for columns samples.
Note: The Risk analysis may be performed with the help of the table B.1 in IEC/TR 80002-1.

The risk analysis report will summarize whether identified and mitigated 
risks meet the acceptable values defined in this plan. It will also include a 
statement indicating whether all known hazards have been identified.

The Risk Management File gathers this document and all documents quoted above.

Tasks, Planning
---------------

Describe how the risk management activities are planned during the project.
The planning of risk activities shall be coherent with the planning of the project found in §2.2 of the project management plan.
Insert a table or list or diagram describing the planning.
Important, list the deliverables and reviews of each phase of the project

Task n
^^^^^^
Optional, add a sub-section for each task with:
-	Inputs of the task
-	Content of the task
-	Outputs of the task
-	Task reviews (in, if necessary, and out)
-	Relationship with development planning.
Note: The tasks may group sets of activities found in §4 to §7 of ISO14971.
Examples of tasks below:

Risk analysis initialization
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
During this phase, the following activities are performed: identification of intended use, identification of characteristics affecting the safety, assignation of safety class (see §2.5.1) identification of hazards, evaluation of hazards, and identification of foreseeable mitigation actions.
-	Inputs: publications, clinical data, any information prior to design phase
-	Two meetings with clinicians involved in the design process
-	Outputs: intended use, safety characteristics and hazards, creation of risk analysis
-	Relationship with development planning: Output data of this task is input data for specification
-	End of Task review: review of risk analysis in draft version.

Risk analysis update
^^^^^^^^^^^^^^^^^^^^
During this phase, the following activities are performed: identification of mitigation actions, evaluation of hazards after mitigation and analysis of risk/patient outcome ratio.
-	Inputs: publications, clinical data, any information prior to design phase
-	Two meetings with clinicians involved in the design process and system architect
-	Outputs: Update of risk analysis
-	Relationship with development planning: this task is performed during specifications
-	End of Task review: review of risk analysis in first revision.

Criteria for Acceptability of Risk
----------------------------------
Warning: I recommend you to read carefully §3.4 of IEC 80002-1 to understand how probability of 
occurrence is determined for software failure.

Risks will be evaluated in accordance with Risk Management Procedures for:
-	Probability of occurrence
-	Consequence of hazard
-	Any other criteria of your choice, like probability of detection …
Based on the risk priority number, for each hazard analyzed for XXXX , the Residual Risk will be considered Acceptable if the risk priority number value is less than <fix your number>.

Based on the risk priority numbers, the Overall Residual Risk for a device will be considered acceptable if the following conditions are satisfied:
1.	None of the identified hazards leads to an unacceptable risk (i.e., no risk priority number above <your number minus 1> is identified); and
2.	Another quantitative criterion of your choice
3.	Another one …

Any risk priority numbers above these values need to have actions taken to reduce the risk.

Verification and Risk traceability matrix
-----------------------------------------
Verification testing activities will be cross-referenced in the risk traceability matrix, as applicable.

Approvals
---------
The Risk Management Plan must be reviewed and approved by XXXX prior to 
the start of the risk assessment process.
The Risk Analysis Report will be reviewed and approved by XXXX to ensure 
completeness and conformance to this Risk Management Plan.

Location of Risk Management File
--------------------------------
The Risk Management File is located in XXX (for example a document management tool defined 
in the software development plan or project management plan). This file contains all the 
documents related to the management of risk for the device and is kept for the life of the product.
