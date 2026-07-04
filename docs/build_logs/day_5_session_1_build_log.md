## Session 1
### Date: 29 June
### Duration : 9:30 a.m. - 11:30 a.m. (2 Hours)

### Goal 
Started implementation of the Redis Lite command-line interface by integrating it with the custom HashMap and implementing all required commands.

### Problem Encountered
Although I had already studied the architecture of Redis Lite, integrating the command parser with the HashMap required careful separation of responsibilities. I also had to ensure that invalid commands and missing arguments were handled correctly without crashing the program.

### What I Tried
Reviewed the Redis Lite design planned in the previous session. Tried implementing various commands like 1. run() command loop, 2. Command parsing using getline() and stringstream, 3. printCommands(), 4. handleSet(), 5. handleGet() 6. handleDel() 7. handleExists() 8. handleCount() 9. handlePrint() 10. handleStats() 11. handleClear().
Tested the implemented commands manually using different key-value pairs and invalid inputs.

### Outcomes 
Successfully completed implementation of few commands on Redis lite using command line interface.

#### Next Step: Complete implementation and start testing using GTest