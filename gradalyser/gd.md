Classroom Grades Analyzer

Note: Java provides built-in classes, but that does not mean they are readily available in all Java programs. Some classes are stored in Java packages. The correct Java package must first be imported into a Java program before a certain class can be used.
The ArrayList class is part of a Java package. On line 1, import the correct package by typing:
import java.util.ArrayList;

Next, create a class called GradeAnalyzer.

Now create a GradeAnalyzer constructor. You can leave the contents of the constructor empty.

Let's create a method that will return the average of all grades. Create a method called getAverage. It should return an int.

The getAverage method should accept anArrayList parameter that holds integers. Call the parameter grades.
Hint: the parameter is written as:ArrayList<Integer> grades.

The first thing the method should do is check to see that the ArrayList it's analyzing is not empty. Create an if statement that checks if the size of grades is less than 1.

Inside of the if block, print out a friendly error message to the user indicating that the ArrayList is empty. On the next line, return 0.

Otherwise, in an else block, find the average of all grades. To find the average, first we will need the sum of all grades. Create an int called sum and set it equal to 0. We will update this variable as we sum the grades.

Create a for each block that iterates through eachgrade in the grades ArrayList.

Inside of the for each block, update sum. Set it equal to sum plus grade. This for each loop will add up all the grades.

Outside of the for each loop, calculate the average of the grades. Create an int called average and set it equal to the sum divided by the size of grades.

On the next line, print out the average.

Finally, on the next line, return the average.

Next, create the main method for this program.

Inside of main create an ArrayList object that stores integers and call it myClassroom.

Next, add the grades 98, 92, 88, 75, 61, 89 and 95 to myClassroom.

On the next line, create a GradeAnalyzer object called myAnalyzer.

Now call the getAverage method on myAnalyzerand specify myClassroom as the argument (parameter).

If you completed this project correctly, the output should show a class average of 85. Feel free to explore more with the program.

Challenge: Write methods that determine both the lowest or highest class grade.

Add comments near the top of the program that describe what the GradeAnalyzer program does.
