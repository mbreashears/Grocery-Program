import re
import string

def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100

def SquareValue(v):
    return v * v

# function for counting occurences of all items
def CountItems():
    myData = open ('GroceryList.txt') # opens file
    itemDict = {} # creates empty dictionary to store contents in
    items = myData.read().split() # splits the string to allow for items to be counted

    for item in items:
        if item in itemDict:
            itemDict[item] += 1
        else:
            itemDict[item] = 1
        
    for item, frequency in itemDict.items():
        print('{}: {}'.format(item, frequency))
    return itemDict

# function for counting occurences of one item
# v is the user input from C++ passed through to this function
def CountOneItem(v):
    myData = open ('GroceryList.txt')
    itemDict = {}
    items = myData.read().split()
    itemCount = items.count(v) # counts occurences of item from user input

    return itemCount # returns item count for C++ to display

def CreateDatFile():
    myData = open ('GroceryList.txt') # opens file
    itemDict = {} # creates empty dictionary to store contents in
    items = myData.read().split() # splits the string to allow for items to be counted

    for item in items:
        if item in itemDict:
            itemDict[item] += 1
        else:
            itemDict[item] = 1

    newFile = open ('frequency.dat', 'w')
    for item, frequency in itemDict.items():
        newFile.write('{}: {}\n'.format(item, frequency))