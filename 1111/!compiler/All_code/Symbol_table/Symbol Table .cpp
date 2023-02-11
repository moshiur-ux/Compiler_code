// C++ program to implement Symbol Table 
#include <iostream> 
using namespace std; 

const int MAXIMUM = 100; 

class Node { 

	string identifier, scope, type; 
	int Line_Number; 
	Node* next_Node; 

public: 
	Node() 
	{ 
		next_Node = NULL; 
	} 

	Node(string key, string value, string type, int Line_Number) 
	{ 
		this->identifier = key; 
		this->scope = value; 
		this->type = type; 
		this->Line_Number = Line_Number; 
		next_Node = NULL; 
	} 

	void print() 
	{ 
		cout << "Identifier's Name:" << identifier 
			<< "\nType:" << type 
			<< "\nScope: " << scope 
			<< "\nLine Number: " << Line_Number << endl; 
	} 
	friend class SymbolTable; 
}; 

class SymbolTable { 
	Node* header[MAXIMUM]; 

public: 
	SymbolTable() 
	{ 
		for (int i = 0; i < MAXIMUM; i++) 
			header[i] = NULL; 
	} 

	int hashf(string id); // hash function 
	bool T4Tutorials_insertion(string id, string scope, 
				string Type, int Line_Number); 

	string T4Tutorials_search(string id); 

	bool deleteRecord(string id); 

	bool modify(string id, string scope, 
				string Type, int Line_Number); 
}; 

// Function to modify an identifier 
bool SymbolTable::modify(string id, string s, 
						string t, int l) 
{ 
	int index = hashf(id); 
	Node* start = header[index]; 

	if (start == NULL) 
		return "-1"; 

	while (start != NULL) { 
		if (start->identifier == id) { 
			start->scope = s; 
			start->type = t; 
			start->Line_Number = l; 
			return true; 
		} 
		start = start->next_Node; 
	} 

	return false; // id not found 
} 

// Function to delete an identifier 
bool SymbolTable::deleteRecord(string id) 
{ 
	int index = hashf(id); 
	Node* T4Tutorials_Temporary_Variable = header[index]; 
	Node* par = header[index]; 

	// no identifier is present at that index 
	if (T4Tutorials_Temporary_Variable == NULL) { 
		return false; 
	} 
	// only one identifier is present 
	if (T4Tutorials_Temporary_Variable->identifier == id && T4Tutorials_Temporary_Variable->next_Node == NULL) { 
		T4Tutorials_Temporary_Variable->next_Node = NULL; 
		delete T4Tutorials_Temporary_Variable; 
		return true; 
	} 

	while (T4Tutorials_Temporary_Variable->identifier != id && T4Tutorials_Temporary_Variable->next_Node != NULL) { 
		par = T4Tutorials_Temporary_Variable; 
		T4Tutorials_Temporary_Variable = T4Tutorials_Temporary_Variable->next_Node; 
	} 
	if (T4Tutorials_Temporary_Variable->identifier == id && T4Tutorials_Temporary_Variable->next_Node != NULL) { 
		par->next_Node = T4Tutorials_Temporary_Variable->next_Node; 
		T4Tutorials_Temporary_Variable->next_Node = NULL; 
		delete T4Tutorials_Temporary_Variable; 
		return true; 
	} 

	// delete at the end 
	else { 
		par->next_Node = NULL; 
		T4Tutorials_Temporary_Variable->next_Node = NULL; 
		delete T4Tutorials_Temporary_Variable; 
		return true; 
	} 
	return false; 
} 

// Function to T4Tutorials_search an identifier 
string SymbolTable::T4Tutorials_search(string id) 
{ 
	int index = hashf(id); 
	Node* start = header[index]; 

	if (start == NULL) 
		return "-1"; 

	while (start != NULL) { 

		if (start->identifier == id) { 
			start->print(); 
			return start->scope; 
		} 

		start = start->next_Node; 
	} 

	return "-1"; // not found 
} 

// Function to T4Tutorials_insertion an identifier 
bool SymbolTable::T4Tutorials_insertion(string id, string scope, 
						string Type, int Line_Number) 
{ 
	int index = hashf(id); 
	Node* p = new Node(id, scope, Type, Line_Number); 

	if (header[index] == NULL) { 
		header[index] = p; 
		cout << "\n"
			<< id << " insertion"; 

		return true; 
	} 

	else { 
		Node* start = header[index]; 
		while (start->next_Node != NULL) 
			start = start->next_Node; 

		start->next_Node = p; 
		cout << "\n"
			<< id << " insertion"; 

		return true; 
	} 
	return false; 
} 
int SymbolTable::hashf(string id) 
{ 
	int asciiSum = 0; 

	for (int i = 0; i < id.length(); i++) { 
		asciiSum = asciiSum + id[i]; 
	} 
	return (asciiSum % 100); 
} 
int main() 
{ 
	SymbolTable st; 
	string check; 
	cout << "**** SYMBOL_TABLE ****\n"; 
	// T4Tutorials_insertion 'if' 
	if (st.T4Tutorials_insertion("if", "local", "keyword", 4)) 
		cout << " -successfully"; 
	else
		cout << "\nFailed to T4Tutorials_insertion.\n"; 
	// T4Tutorials_insertion 'number' 
	if (st.T4Tutorials_insertion("number", "global", "variable", 2)) 
		cout << " -successfully\n\n"; 
	else
		cout << "\nFailed to T4Tutorials_insertion\n"; 
	// T4Tutorials_search 'if' 
	check = st.T4Tutorials_search("if"); 
	if (check != "-1") 
		cout << "Identifier Is present\n"; 
	else
		cout << "\nIdentifier Not Present\n"; 
	// delete 'if' 
	if (st.deleteRecord("if")) 
		cout << "if Identifier is deleted\n"; 
	else
		cout << "\nFailed to delete\n"; 
	// modify 'number' 
	if (st.modify("number", "global", "variable", 3)) 
		cout << "\nNumber Identifier updated\n"; 
	// T4Tutorials_search and print 'number' 
	check = st.T4Tutorials_search("number"); 
	if (check != "-1") 
		cout << "Identifier Is present\n"; 
	else
		cout << "\nIdentifier Not Present"; 
	return 0; 
}