# Lab03 Guide
## Getting Started

Please review the [CS253 Style Guide](https://docs.google.com/document/d/1zKIpNfkiPpDHEvbx8XSkZbUEUlpt8rnZjkhCSvM-_3A/edit?usp=sharing) and apply it in all lab warmups, lab activities and projects this semester. Coding Style will assessed as part of your lab and project grades.

## Lab Warmup - Variables, input and casting
### Problem Description

1. Prompt the user to input an integer, a double, a character, and a string, storing each into separate variables. Then, output those four values on a single line separated by a space.  

  *Note: This Lab outputs a newline after each user-input prompt. For convenience in the examples below, the user's input value is shown on the next line, but such values don't actually appear as output when the program runs.*  


```
Enter integer:
99
Enter double:
3.77
Enter character:
z
Enter string:
Howdy
99 3.770000 z Howdy
```

2. Extend to also output in reverse.  

```
Enter integer:
99
Enter double:
3.77
Enter character:
z
Enter string:
Howdy
99 3.770000 z Howdy
Howdy z 3.770000 99
```


3.  Extend to cast the double to an integer, and output that integer.  
```
Enter integer:
99
Enter double:
3.77
Enter character:
z
Enter string:
Howdy
99 3.770000 z Howdy
Howdy z 3.770000 99
3.770000 cast to an integer is 3
```


### Implementation Guide
1. Edit file src/warmup.c
2. Enter the program code to create an application as described in the Problem Description.
3. Test the program using to ensure it functions as expected.
4. Commit the changes to your local repository with a message stating that LabWarmup is completed.
5. Push the changes from your local repository to the github classroom repository.
6. Update the Coding Journal with an entry describing your experience using the steps outlined below.


## Lab Activity
### Problem Description

Output each floating-point value with two digits after the decimal point, which can be achieved as follows:
<br />  

`printf("%0.2lf", yourValue);`

<br />
1. Prompt the user to input a wall's height and width. Calculate and output the wall's area.
<br />

*Note: This Lab outputs a newline after each user-input prompt. For convenience in the examples below, the user's input value is shown on the next line, but such values don't actually appear as output when the program runs.*

```
Enter wall height (feet):
12.0
Enter wall width (feet):
15.0
Wall area: 180.00 square feet
```

<br />
2. Extend to also calculate and output the amount of paint in gallons needed to paint the wall. Assume a gallon of paint covers 350 square feet. Store this value using a const double variable.

```
Enter wall height (feet):
12.0
Enter wall width (feet):
15.0
Wall area: 180.00 square feet
Paint needed: 0.51 gallons
```

<br />
3. Extend to also calculate and output the number of 1 gallon cans needed to paint the wall. This should be represented as an integer value. Hint: Use a math function to round up to the nearest gallon.  

```
Enter wall height (feet):
12.0
Enter wall width (feet):
15.0
Wall area: 180.00 square feet
Paint needed: 0.51 gallons
Cans needed: 1 can(s)
```

### Implementation Guide
1. Edit file src/activity.c
2. Enter the program code to create an application as described in the Problem Description.
3. Test the program using to ensure it functions as expected.
4. Commit the changes to your local repository with a message stating that LabActivity is completed.
5. Push the changes from your local repository to the github classroom repository.
6. Update the Coding Journal with an entry describing your experience using the steps outlined below.

## Coding Journal (Optional)
Keep a journal of your activities as you work on this lab. 

Your journal can track ideas, bugs, cool links, code snippets, shell commands, rants, or simply a reflection on what worked well or not-so-well with this lab activity. I will not be grading the content of your journal, but I will expect at least two timestamped journal entries of at least a 75 to 150 words each added to the provided Journal.md file.  The purpose of this component is to help develop the habit of taking notes and creating documentation while you code. The more detail you provide the better as that will help you if you ever need to refer back to this project in the future.

## Markdown Resources
Markdown is a notation that is used to format text documents.  It is widely used in Software Development shops around the world, which is why we're asking you to use it in your lab documentation.  

Github provides a guide for getting started:  [Mastering Markdown](https://guides.github.com/features/mastering-markdown/)
