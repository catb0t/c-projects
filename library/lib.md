Personal Library
In this project, you will create a simple Library tool to help analyze completed books in a small, personal library. The tool will print out the books that a user has fully read. We will store the books and their completion status in a HashMap.

Next, create a class called Library.
Now create a Library constructor.

Let's create a method that will print all of a user's completed books. Create a method called getFinishedBooks. It should not return any value.

The getFinishedBooks method should accept a HashMap parameter that holds strings and Boolean values. Name the parameter library.
Hint: the parameter is written as:HashMap<String, Boolean> library.

The first thing the method should do is check to see that the HashMap it's analyzing is not empty. Create an if statement that checks if the size of library is less than 1.

Inside of the if block, print out a friendly error message to the user indicating that the HashMap is empty.

Otherwise, in an else block, print out all finished books. First, create a for each loop that iterates through each book in the key set of library.

Inside of the for each block, first check the completion status of each book. Create an if statement that checks to see if the value associated with each book in library is equal to true.

Inside of the if statement, print out the book. This completes the getFinishedBooks method.

Let's test out the functionality we just built. First, create a main method.

Next, create a HashMap object that stores strings and Boolean values. Call the HashMap object myBooks.

Add the following books and their completion status:
Road Down The Funnel, true
Rat: A Biology, false
TimeIn, true
3D Food Printing, false

Now create a Library object called myLibrary.

On the next line, call the getFinishedBooks method on myLibrary and specify myBooks as the argument (parameter).

If you completed this project correctly, the output should only print out the books that have a completion status of true.
Optional: Write an additional method that prints out the incomplete books.

Add comments near the top of the program that describe what the Library program does


After completing the simple Library Class, let’s take a look at expanding its functionality so it acts as a more robust and featured program.

Here are some things that are more useable library program should do:

Continuously run
Have a menu system
Be able to add items to our library
Be able to change items from ‘not read’ to ‘read’ from the program
Be able to view a nice print out of our read items
Be able to view a list of our unread items
Be able to view a list of our entire library
Be able to concisely show total number of read items versus total items
Be able to select an option to exit the program

These are some options for a library of books.  A library is a general enough term (and hopefully general enough class) that we could use it with small modifications to also act as a base for a library of things that interest you.  Try modifying your code to apply to some sort of collection that you have personally.  For example, re-create your Steam library of games (I know mine would have many ‘unplayed’ games versus ‘played’ games.

*NOTE: While we can use multiple if/else if statements for our menu, a more concise way of navigating a menu system would be with a “switch” statement, see if you can research how to implement it!
