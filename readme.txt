Homework 2 : Paint






I have implemented the program using Qt creator(as recommended) on a ubuntu running on a VMware workstation. I have included main.cpp,widget.h andwidget.cpp files in the submission along with the icons.Basically, I took the Sample solution given by the professor as base file and implemented the functionalities asked.


I made sure that program builds and runs successfully without any issues. Please follow the following instructions to build and run the project.


1. Open hw3.pro project in Qt creator.
2. Build(Ctrl+B) the project( I made sure that project builds without any issues)
3. Run the project. You should be able to see the menu with different options displayed on the console.


I have implemented both menu driven and the image driven functionalities as asked in the homework. I took the pictures from the Icon BMP files for the project given by the professor.


In the File Menu we have the following functionalities.
1. New File → To open a new image file
2. Save File → To save the image file in the required location
3. Clear → To clear the image
4. Set Foreground Color → To set the front color
5. Set Background Color → To set the back picture color 


In the Edit Menu we have the following functionalities.
1. Undo → To step back 
2. Redo → To redo the last action performed




The above functionalities are also being implemented by using the icons. There is an extra feature to draw a line in the icon menu to draw lines. 


After selecting tool viz pen or draw line, right clicking provides the below functionalities. 
A slider which helps to select the font size. Sometimes logic for the properties like selection of different styled line is failing. I really tried hard to get rid of that, but couldn’t solve it.


 I tried hard to implement undo and redo functionalities but  couldn’t succeed, so commented that part of the code in order not to get any errors . 




I would like to acknowledge following resources that helped me to gain valuable insights in completing this project


1.C++ GUI Programming with Qt 4, Second Edition  by Jasmin Blanchette; Mark Summerfield 


2. www.stackoverflow.com


3.https://www.qt.io/developers/