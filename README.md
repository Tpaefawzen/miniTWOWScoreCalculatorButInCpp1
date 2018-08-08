# miniTWOWScoreCalculatorButInCpp1
Since I am used in C++ the most, I try making a prototype using the language.

# Request Definition
1. To use this tool, all the following conditions must be satisfied:
	1. You're using **only a voting screen so no keywords are necessary for votes.**
	2. It has **from 2 to 26 responses.**
	3. From above, **each response has alphabet from letter A in alphabetical order.**
	4. **Each vote has no square brackets.**
	5. **Any votes having same characters twice or more times will be invalid.** e.g. *A*BCDEF*A*
	6. You are using **spreadsheet** or something to make results.
2. You are asked to input how many responses there are and you input the value.
	1. You input the value from 2 to 26, the program goes to the next step.
	6. Otherwise, it shows the error and the program ends.
3. You are asked to input how many votes you received.
4. You are asked to input each vote.
	1. Every time you input, the average and standard deviation will be calculated **unless the vote is invalid.**
5. The program shows the text in the following format to paste your spreadsheet.
	1. alphabet (space) average (space) standard deviation (newline)
