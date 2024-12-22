//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Arka Tu
// Version     : 1.0
// Description : CS 300 Project Two
//============================================================================

#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);


struct Course {
    // Course number ie "CS300"
    string courseNumber = "";
    // Course name ie "DSA: Analysis and Design"
    string courseName = "";
    // Prerequisite courses to take this course
    vector<string> prerequisites;
};

struct Node {
    // holds a course
    // holds left and right node pointers
    Course course;
    Node* left;
    Node* right;

    // Default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Init with course
    Node(Course aCourse) {
        left = nullptr;
        right = nullptr;
        course = aCourse;
    }
};


//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */

class BinarySearchTree {

private:
    Node* root;

    void inOrder(Node* node);
    void preOrder(Node* node);
    void addNode(Node* node, Course course);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void preOrder();
    void inOrder();
    void insert(Course course);
    Course search(string courseNumber);
    void printCourse(Course course);
    bool isEmpty();
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // set current node to root
    Node* curr = root;

    // recurse from root deleting every node
    // while current node isn't null
    while (curr != nullptr) {
        // check if the left child node is null
        if (curr->left != nullptr) {
            // if it isn't null, get the next left child
            curr = curr->left;
        }
        // check if there's a right child
        else if (curr->right != nullptr) {
            // if there is, get the next right child
            curr = curr->right;
        }
        // if no children
        else {
            // delete node and reset current to root node
            delete curr;
            curr = root;
        }
    }
}

/**
* Insert a course
*/
void BinarySearchTree::insert(Course course) {
    // if root is null
    if (root == nullptr) {
        // set node with this course as the root
        root = new Node(course);
    }
    // otherwise
    else {
        // call addNode, passing in the root and the course
        this->addNode(root, course);
    }
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course Course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // if node is larger then add to left
    if (node->course.courseNumber.compare(course.courseNumber) > 0) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
        }
        // else recurse down the left node
        else {
            this->addNode(node->left, course);
        }

    }
    // else add to right
    else {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course);
        }
        // else recurse down the right node
        else {
            this->addNode(node->right, course);
        }
    }
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::inOrder() {
    // call inOrder fuction and pass root 
    this->inOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::preOrder() {
    // preOrder root
    this->preOrder(root);
}

void BinarySearchTree::inOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //InOrder left
        inOrder(node->left);
        //output bidID, title, amount, fund
        this->printCourse(node->course);
        //cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | "
            //<< node->bid.fund << endl;
        //InOder right
        inOrder(node->right);
    }
}

void BinarySearchTree::preOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //output bidID, title, amount, fund
        this->printCourse(node->course);
        //preOrder left
        preOrder(node->left);
        //preOrder right
        preOrder(node->right);
    }
}
/**
* Search for a course
* 
* @param courseNumber string to be searched
*/
Course BinarySearchTree::search(string courseNumber) {
    // start at root node
    Node* current = root;

    // keep looping downwards until bottom reached or matching bidId found
    while (current != nullptr) {
        // if match found, return current bid
        if (current->course.courseNumber.compare(courseNumber) == 0) {
            return current->course;
        }

        // if bid is smaller than current node then traverse left
        if (courseNumber.compare(current->course.courseNumber) < 0) {
            current = current->left;
        }
        // else larger so traverse right
        else {
            current = current->right;
        }
    }

    // Create empty course
    Course course;
    // Return empty course
    return course;
}

/**
* Print course information
* 
* @param course Course to be printed
*/
void BinarySearchTree::printCourse(Course course) {
    // Print course number and course name
    cout << "Course number: " << course.courseNumber << endl;
    cout << "Course name: " << course.courseName;

    // If prereq vector isn't empty
    if (!empty(course.prerequisites)) {
        // Print "Prerquisites: "
        cout << endl << "Prerequisites: ";

        // For each prereq, print the course number
        for (string prereq : course.prerequisites) {
            cout << prereq;
            // Print a comma and a space if not at the end of the vector
            if (prereq != course.prerequisites.back()) {
                cout << ", ";
            }
        }
    }

    cout << endl << endl;
}

/**
* Check if BST is empty
* 
* @return bool true if empty, false if at least one node
*/
bool BinarySearchTree::isEmpty() {
    // if root is null
    if (root == nullptr) {
        // return true
        return true;
    }
    // else
    else {
        // return false
        return false;
    }
}


//============================================================================
// Static methods used for testing
//============================================================================


/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
* Reads file and loads into BST
* 
* @param csvPath string to try to load from file directory
* @ bst BinarySearchTree* to load courses into
*/
void readFile(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // Declare ifstream to read file
    std::ifstream fin;

    // Set exceptions for ifstream
    fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // Open file
        fin.open(csvPath);

        // Set empty row and empty line to read
        vector<string> row;
        string line = "";

        // FIXME: when there's a blank line at the end of the file, it throws an error
        // while ifstream is still good
        while (fin.good()) {
            // get the next line
            getline(fin, line);

            // clear the row vector
            row.clear();

            // Set stringstream to break up words
            stringstream s(line);

            // Set word to empty string
            string word = "";

            // Get each word
            while (getline(s, word, ',')) {
                // Checks if string is empty
                // Might happen with ",,"
                if (!empty(word)) {
                    // Add word to row vector
                    row.push_back(word);
                }
            }

            // Set new course
            Course course;

            // if at least params
            if (row.size() >= 2) {
                // Get course number and name and add to course
                course.courseNumber = row.at(0);
                course.courseName = row.at(1);
                // Clear course prerquisites to be safe
                course.prerequisites.clear();

                // For each prereq in row
                for (unsigned int i = 2; i < row.size(); i++) {
                    // Get the course number from row
                    string courseNum = row.at(i);
                    // Search the course
                    Course searchedCourse = bst->search(courseNum);
                    // If course exists, add to prereq vector
                    if (!empty(searchedCourse.courseNumber)) {
                        course.prerequisites.push_back(row.at(i));
                    }
                    // else, print out error that course wasn't found
                    else {
                        cout << "ERROR: " << courseNum << " not found" << endl;
                    }
                }

                // Insert course in bst
                bst->insert(course);
            }
            // else, print that there's invalid input
            else {
                cout << "Invalid input for course" << endl;
            }

        }
    }
    // catch ifstream error
    catch (const ifstream::failure& e) {
        cout << endl << "FIXME: this happens when there's a blank line at the end of the csvfile" << endl;
        cout << "ERROR: " << e.what() << endl;
    }

    // catch other errors
    catch (std::exception& e) {
        cout << "ERROR" << endl;
    }

    // close file
    fin.close();
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, searchedCourseNum;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    case 3:
        csvPath = argv[1];
        break;
    default:
        csvPath = "ABCU_Advising_Program_Input.csv";
    }


    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;

    int choice = 0;
    bool loaded = false;

    // Input excpetions
    cin.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // try/catch to catch if user inputs string
    try {
        while (choice != 9) {
            cout << "Menu:" << endl;
            cout << "  1. Load Bids" << endl;
            cout << "  2. Display All Bids" << endl;
            cout << "  3. Find Bid" << endl;
            cout << "  9. Exit" << endl;
            cout << "Enter choice: ";


            cin >> choice;

            switch (choice) {

                // load courses
                case 1:

                    // Ask user what file to load
                    cout << "What file would you like to load?" << endl;
                    cout << "File name: ";

                    // Get path from input
                    cin >> csvPath;

                    // Complete the method call to load the bids
                    readFile(csvPath, bst);

                    // Check if bst is empty
                    if (bst->isEmpty()) {
                        // If empty, loaded is false
                        loaded = false;
                    }
                    // else
                    else {
                        // loaded is true
                        loaded = true;
                    }

                    break;

                // print courses
                case 2:
                    // if the bst is loaded
                    if (loaded) {
                        // print courses using inorder traversal
                        bst->inOrder();
                    }
                    // else
                    else {
                        // print that courses aren't loaded
                        cout << "Courses not loaded yet" << endl;
                    }
                    break;

                // get course
                case 3:
                    // Ask user what course to search to load
                    cout << "What course would you like to search for?" << endl;
                    cout << "Course number: ";

                    // Get path from input
                    cin >> searchedCourseNum;
                    course = bst->search(searchedCourseNum);

                    if (!course.courseNumber.empty()) {
                        cout << endl;
                        cout << "Course found: " << endl << endl;
                        bst->printCourse(course);
                    }
                    else {
                        cout << "Course " << searchedCourseNum << " not found." << endl;
                    }

                    break;

                default:
                    break;
            }

        }
    }
    catch (std::exception& e) {
        cout << "Error" << endl;
    }

    cout << "Good bye." << endl;

    return 0;
}
