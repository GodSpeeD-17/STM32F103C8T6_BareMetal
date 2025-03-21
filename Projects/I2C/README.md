![I2C Basic Interrupts](./Images/I2C%20Basic%20Interrupts.png)
![I2C Error Interrupts](./Images/I2C%20Error%20IRQ.png)
![I2C Interrupt Mapping](./Images/I2C%20Interrupt%20Mapping.png)

Sending data in master mode:
1. Check the busy flag of SR2 to make sure the bus is not busy. 
2. Set the START bit of CR1 to make a start condition.
3. Monitor the SB bit of SR1 until the start condition is generated.
4. Put the slave address in the data register (DR). Bits 1 to 7 should contain the slave address and the bit 0 is R/W. To send data the R/W needs to be 0.
5. Monitor the status registers. If the address is sent successfully the ADDR flag sets and you can continue the progress. If the ARLO (Arbitration Lost) is set, you should wait until the bus becomes free and you should repeat steps 1 to 5.
6. Load the data register with the data to be sent.
7. Monitor the TxE flag. The flag is set when an ACK is received.
8. Repeat steps 6 and 7 if you have more bytes to send. Otherwise, set the STOP bit of CR1 to make a stop condition.

