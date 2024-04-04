# bulkhead-shockload
Code translated from FORTRAN66 to C to calculate parachute shock loads. For use with UNLV SEDS' Spaceport America Cup 10K COTS rocket.

Validated through simulation that the bulkhead was sufficiently designed to withstand the shock forces experienced during main parachute deployment.

Results were used to validate FEA analysis performed by a team member.

Used Google Gemini and OpenAI ChatGPT-3 to translate program. Using input values from a Naval Surface Warfare Center (NSWC) whitepaper, the output was validated by checking if results from the translated program matched the document.

Some preprocessing:
![sheets shock calculator](https://github.com/2d1ff1cult/bulkhead-shockload/assets/48054365/90b5df29-5744-4998-bcf1-bcebc12b09a3)


Using the following input parameters:
![input](https://github.com/2d1ff1cult/bulkhead-shockload/assets/48054365/9609f61f-a00c-47f4-b05e-d20e73caf4d1)


I was able to calculate the maximum shock load imparted onto the rocket's bulkhead:
![output](https://github.com/2d1ff1cult/bulkhead-shockload/assets/48054365/77390de3-cd4c-4212-8e83-03569a4f8a85)


Below shows FEA analysis at 1500 lbs, showing little to no yielding:
![Sim_Bulkhead_1460lb](https://github.com/2d1ff1cult/bulkhead-shockload/assets/48054365/36725705-ed70-4ad8-a74d-23855c0d4364)
