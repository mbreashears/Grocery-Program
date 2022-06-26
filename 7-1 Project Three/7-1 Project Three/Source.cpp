#include <Python.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

ifstream inFS; // opens file system to allow for creation of histogram from frequency.dat


void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

// function to display menu options
void DisplayMenu() {
	cout << "Select an option" << endl;
	cout << "1. Display all items purchased in one day." << endl;
	cout << "2. Display the number of times one item was purchased" << endl;
	cout << "3. Create text file." << endl;
	cout << "4. Exit program." << endl << endl;
}


void main()
{
	int i = 0; // variable to keep loop going
	

	while (i == 0) {
		DisplayMenu(); // calls function to display menu
		int userInput; // variable for user input for menu options

		cin >> userInput; // gets user input

		// executes if user inputs 1
		if (userInput == 1) {
			CallProcedure("CountItems"); // calls Python function to count all frequency of all items
			cout << endl << endl;
		}

		// executes if user inputs 2
		else if (userInput == 2) {
			cout << "Enter the item you want to check the frequency of." << endl;
			string itemInput; // string to get user input for item
			cin >> itemInput; // fills item input with input from user
			// prints frequency of one item
			cout << endl << itemInput << " " << callIntFunc("CountOneItem", itemInput) << endl << endl;
		}

		// executes if user inputs 3
		else if (userInput == 3) {
			CallProcedure("CreateDatFile");
			inFS.open("frequency.dat");

			string item;
			int frequency;

			while (!inFS.eof()) {
				inFS >> item >> frequency; // gets data to create histogram

				cout << item << string(frequency, '*') << endl << endl; // prints histogram with chars to show frequency
			}
		}

		// exits program if user inputs 4
		else if (userInput == 4) {
			cout << "You have chosen to exit this program. Goodbye for now." << endl;
			i = 4;
		}

		// makes sure that user inputs a valid option
		else {
			cout << "Please input a valid option." << endl << endl;
		}
	}

	inFS.close(); // closes file system
}