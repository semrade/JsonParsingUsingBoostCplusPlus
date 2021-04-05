#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <list>
#include <map>
#include <fstream>
#define LIST
using namespace std;


#ifndef LIST
/**short alias for this namespace*/
namespace pt =  boost::property_tree;

/**create a tree*/
boost::property_tree::ptree root;


void
PrintListOfMap(list<map<string,string>>& lst)
{
    list<map<string,string>>::iterator list_it;
	map<string,string>::iterator map_it;


	list_it = lst.begin();
	map_it = (*list_it).begin();

	for(; map_it != (*list_it).end(); map_it++)
	{
		cout << "First  = " << map_it->first << endl;
		cout << "Second = " << map_it->second << endl;
	}
}

list<map<string,string>>
CopyList(list<map<string,string>>& lst)
{
    list<map<string,string>> resList;
    map<string,string> resMap;

    list<map<string,string>>::iterator list_it;
	map<string,string>::iterator map_it;


	list_it = lst.begin();
	map_it = (*list_it).begin();

	for(; map_it != (*list_it).end(); map_it++)
	{
	    resMap.insert(make_pair(map_it->first,map_it->second));
		resList.push_back(resMap);
	}
	return resList;
}

void
printList(std::list<std::string> const &list)
{
    for (auto const& i: list) {
        std::cout << i << "\n";
    }
}

int main()
{

    ///this an output file to write the result in the end of debugging.

    ofstream myJsonFile;
    myJsonFile.open("MyJSONFile.json");

    ///Reading json file using boost library
    cout << "Begin" << endl;
    /** Load the json file in this ptrr IMPORTANT call inside main */
    pt::read_json("file.json", root);

    /** Read values */
    int height = root.get<int>("height",1);
    cout<<height<<endl;

    /** Read a sting*/
    string msg = root.get<string>("some.complex.path");
    cout<<msg<<endl;

    /** A vector to allow storing our animals */
    list< map<string,string>> animals;
    map<string,string> element;

    /** Iterator over all animals */
    for(boost::property_tree::ptree::value_type &animal : root.get_child("animals"))
    {
        /** insert element to the make pair */
        element.insert(make_pair(animal.first,animal.second.data()));

    }
    /** push element to the list */
    animals.push_back(element);

    cout<<animals.size()<<endl;
    PrintListOfMap(animals);


    list<string> fruits;
    for(boost::property_tree::ptree::value_type &fruit : root.get_child("fruits"))
    {
        fruits.push_back(fruit.second.data());
    }

    printList(fruits);

    int matrix[3][3];
    int x = 0;
    for (boost::property_tree::ptree::value_type& row: root.get_child("matrix"))
    {
        int y = 0;
        for (boost::property_tree::ptree::value_type& cell : row.second)
        {
            matrix[x][y] = cell.second.get_value<int>();
            y++;
        }
        x++;
    }
    /// Writing json file using boost library.
    /** building a ptree */


    cout<<"*********************** root is ******************"<<endl;
    boost::property_tree::write_json(cout, root);
    cout<<"*********************** root is ******************"<<endl;

    root.put("height", height);
    cout<<"*********************** root is ******************"<<endl;
    boost::property_tree::write_json(cout, root);
    cout<<"*********************** root is ******************"<<endl;

    root.put("Some.complex.path","Bonjour");
    cout<<"*********************** root is ******************"<<endl;
    boost::property_tree::write_json(cout, root);
    cout<<"*********************** root is ******************"<<endl;

    boost::property_tree::ptree animals_node;
    for(auto  animal : animals)
    {
       animals_node.put("tarik","semrade");
       //animals_node.push_back(make_pair(animal->first, animal->second));
    }
    root.add_child("animals", animals_node);

    cout<<"*********************** root is ******************"<<endl;
    boost::property_tree::write_json(cout, root);
    cout<<"*********************** root is ******************"<<endl;

    pt::ptree fruits_node;
    for (auto &fruit : fruits)
    {
        // Create an unnamed node containing the value
        pt::ptree fruit_node;
        fruit_node.put("", fruit);

        // Add this node to the list.
        fruits_node.push_back(std::make_pair("", fruit_node));
    }
    root.add_child("fruits", fruits_node);

    cout<<"*********************** root is ******************"<<endl;
    boost::property_tree::write_json(cout, root);
    cout<<"*********************** root is ******************"<<endl;

    pt::ptree matrix_node;
    for (int i = 0; i < 3; i++)
    {
        pt::ptree row;
        for (int j = 0; j < 3; j++)
        {
            // Create an unnamed value
            pt::ptree cell;
            cell.put_value(matrix[i][j]);
            // Add the value to our row
            row.push_back(std::make_pair("", cell));
        }
        // Add the row to our matrix
        matrix_node.push_back(std::make_pair("", row));
    }
    // Add the node to the root
    root.add_child("matrix", matrix_node);

    cout<<"*********************** root is ******************"<<endl;
    boost::property_tree::write_json(cout, root);
    cout<<"*********************** root is ******************"<<endl;
    boost::property_tree::write_json(myJsonFile, root);
    myJsonFile.close();
    cout << "Fin" << endl;
    return 0;
}
#endif
#ifdef LIST


#include <fstream>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

int main()
{
    // Short alias for this namespace
    namespace pt = boost::property_tree;

    // Create a root
    pt::ptree iroot;

    // Load the json file in this ptree
    pt::read_json("file.json", iroot);


    ////////////////////
    /// READING      ///
    ////////////////////

    std::cout << "Reading file.json :" << std::endl;

    //Read values
    int height = iroot.get<int>("height");
    std::string msg = iroot.get<std::string>("some.complex.path");
    std::cout << "height : "            << height   << std::endl
              << "some.complex.path : " << msg      << std::endl;

    std::vector< std::pair<std::string, std::string> > animals;
    for (pt::ptree::value_type &animal : iroot.get_child("animals"))
    {
        std::string name = animal.first;
        std::string color = animal.second.data();
        animals.push_back(std::make_pair(name, color));
    }

    std::cout << "Animals :" << std::endl;
    for (auto animal : animals)
        std::cout << "\t"   << animal.first
                  << " is " << animal.second
                  << std::endl;

    std::vector<std::string> fruits;
    for (pt::ptree::value_type &fruit : iroot.get_child("fruits"))
    {
        // fruit.first contain the string ""
        fruits.push_back(fruit.second.data());
    }

    std::cout << "Fruits :";
    for (auto fruit : fruits)
        std::cout << " " << fruit;
    std::cout << std::endl;

    int matrix[3][3];
    int x = 0;
    for (pt::ptree::value_type &row : iroot.get_child("matrix"))
    {
        int y = 0;
        for (pt::ptree::value_type &cell : row.second)
        {
            matrix[x][y] = cell.second.get_value<int>();
            y++;
        }
        x++;
    }

    std::cout << "Matrix :" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            std::cout << " " << matrix[i][j];
        std::cout << std::endl;
    }


    ////////////////////
    /// WRITING      ///
    ////////////////////

    pt::ptree oroot;

    // Some values
    oroot.put("height", height);
    oroot.put("some.complex.path", "bonjour");

    // Add a list of animals

    // Create a node
    pt::ptree animals_node;
    // Add animals as childs
    for (auto &animal : animals)
        animals_node.put(animal.first, animal.second);
    // Add the new node to the root
    oroot.add_child("animals", animals_node);

    // Add two objects with the same name
    pt::ptree fish1;
    fish1.put_value("blue");
    pt::ptree fish2;
    fish2.put_value("yellow");
    oroot.push_back(std::make_pair("fish", fish1));
    oroot.push_back(std::make_pair("fish", fish2));

    // Add a list
    pt::ptree fruits_node;
    for (auto &fruit : fruits)
    {
        // Create an unnamed node containing the value
        pt::ptree fruit_node;
        fruit_node.put("", fruit);

        // Add this node to the list.
        fruits_node.push_back(std::make_pair("", fruit_node));
    }
    oroot.add_child("fruits", fruits_node);

    // Add a matrix
    pt::ptree matrix_node;
    for (int i = 0; i < 3; i++)
    {
        pt::ptree row;
        for (int j = 0; j < 3; j++)
        {
            // Create an unnamed value
            pt::ptree cell;
            cell.put_value(matrix[i][j]);
            // Add the value to our row
            row.push_back(std::make_pair("", cell));
        }
        // Add the row to our matrix
        matrix_node.push_back(std::make_pair("", row));
    }
    // Add the node to the root
    oroot.add_child("matrix", matrix_node);

    pt::write_json(std::cout, oroot);

    return 0;
}
#endif // VECTOR
