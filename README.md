# bulkhead-shockload
Code translated from FORTRAN66 to C to calculate parachute shock loads. For use with UNLV SEDS' Spaceport America Cup 10K COTS rocket.

Results were used to validate FEA analysis performed by a team member.

Used Google Gemini and OpenAI ChatGPT-3 to translate program. Using input values from a Naval Surface Warfare Center (NSWC) whitepaper, the output was validated by checking if results from the translated program matched the document.

Some preprocessing:
![sheets shock calculator](https://github.com/2d1ff1cult/bulkhead-shockload/assets/48054365/90b5df29-5744-4998-bcf1-bcebc12b09a3)


Using the following input parameters:
![input](https://github.com/2d1ff1cult/bulkhead-shockload/assets/48054365/ab66ec11-8835-4064-bc06-f3e5ebcaf92a)

I was able to calculate the maximum shock load imparted onto the rocket's bulkhead:
![output](https://github.com/2d1ff1cult/bulkhead-shockload/assets/48054365/d5a17977-79ac-418e-82fc-8bf70479250f)

Below shows FEA analysis at 1500 lbs, showing little to no yielding:
![Sim_Bulkhead_1460lb](https://github.com/2d1ff1cult/bulkhead-shockload/assets/48054365/36725705-ed70-4ad8-a74d-23855c0d4364)

This collaboration validated through simulation that the bulkhead was sufficiently designed to withstand the shock forces experienced during main parachute deployment.
