You are tasked with the following:

Create a class named Droid, it has a Constructor that accepts no parameters but it does set a class level property (variable) batteryLevel to 100.

It has a function called activate that accepts and returns no values, but it does print out a message saying the droid has been activated.  This function drains 5 battery, it also prints out the remaining battery level.

It also has a function chargeBattery that returns no values but it does accept an integer number of hours.  It prints a status saying it is charging, and increases the battery level equal to the amount of hours it has charged.  If batteryLevel is greater than 100, batteryLevel is set to 100.  No matter batteryLevel, it prints out the current batteryLevel at the end.

It has a function called checkBatteryLevel that returns an integer (batteryLevel) and accepts no values, It also prints the remaining batteryLevel.

It has a function hover that returns no values but accepts an integer in feet.  If the value in feet is greater than 2 the droid prints out an error message saying it can’t hover more than that.  Otherwise the droid outputs it is hovering and it drains 20 batteryLevel.  It then prints out remaining batteryLevel.

In the main method, create a droid and test each of its functions.