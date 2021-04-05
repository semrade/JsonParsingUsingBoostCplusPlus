#if 0
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <cassert>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>

typedef boost::property_tree::ptree tree;
void print(tree const& pt)
{
    using boost::property_tree::ptree;
    ptree::const_iterator end = pt.end();
    for (ptree::const_iterator it = pt.begin(); it != end; ++it) {
        std::cout << it->first << ": " << it->second.get_value<std::string>() << std::endl;
        print(it->second);
    }
}
int main()
{
    try
    {
        //std::stringstream ss;
        // send your JSON above to the parser below, but populate ss first
        //ss << "{ \"particles\": [ { \"electron\": { \"pos\": [ 0, 0, 0 ], \"vel\": [ 0, 0, 0 ] }, \"proton\": { \"pos\": [ -1, 0, 0 ], \"vel\": [ 0, -0.1, -0.1 ] } } ]}";
        std::ifstream jsonFile("text.json");
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(jsonFile, pt);

        std::string msg = pt.get<std::string>("particles");
        std::cout<<msg<<std::endl;

        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("Tarik"))
        {
            assert(v.first.empty());        // array elements have no names
            print(v.second);                // etc
        }
/**
        boost::property_tree::basic_ptree<std::string,std::string>::const_iterator iter = pt.begin(),iterEnd = pt.end();
        for(;iter != iterEnd;++iter)
        {
             iter->first; // Your key, at this level it will be "electron", "proton", "proton"
             iter->second; // The object at each step {"pos": [0,0,0], "vel": [0,0,0]}, etc.
        }
        */
        return EXIT_SUCCESS;
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_FAILURE;
}
#endif // 1

#if 0
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <iostream>
using namespace boost::property_tree;
using namespace std;

// Analyze Json
bool ParseJson()
{
	string str = "{\"ID\":0,\"Student\":[{\"Name\":\"April\"},{\"Name\":\"Harris\"}]}";
	stringstream stream(str);
	ptree strTree;
	try
	{
		read_json(stream, strTree);
	}
	catch (ptree_error & e) {
		return false;
	}

	try
	{
        int id = strTree.get<int>("ID");
        ptree names = strTree.get_child("Student");
        BOOST_FOREACH(ptree::value_type &name, names)
        {
            stringstream s;
            write_json(s, name.second);
            string image_item = s.str();
        }
	}
	catch (ptree_error & e)
	{
		return false;
	}
	return true;
}


 // Construct Json
bool InsertJson()
{
	string str = "{\"ID\":0, \"Student\":[{\"Name\":\"April\"},{\"Name\":\"Harris\"}]}";
	stringstream stream(str);
	ptree strTree;
	try {
		read_json(stream, strTree);
	}
	catch (ptree_error & e) {
		return false;
	}
	ptree subject_info;
	ptree array1, array2, array3;
	array1.put("course", "Java");
	array2.put("course", "C++");
	array3.put("course", "MySql");
	subject_info.push_back(make_pair("", array1));
	subject_info.push_back(make_pair("", array2));
	subject_info.push_back(make_pair("", array3));

	strTree.put_child("Subject", subject_info);
	stringstream s;
	write_json(s, strTree);
	string outstr = s.str();

	return true;
}

int main()
{
	ParseJson();
	InsertJson();
	system("pause");
	return 0;
}
#endif // 1


#if 1
#include <iostream>
#include <map>
#include <list>
#include <string>
#include <boost/filesystem.hpp>
using namespace std;

int main()
{
	map<string,string> coincidence;
	list<map<string,string>> coincidences;

	list<map<string,string>>::iterator list_it;
	map<string,string>::iterator map_it;

	coincidence["C++"] = "Hello World";
	coincidence["toto"] = "5";
	coincidence["tata"] = "10";
	coincidence["zabi"] = "SEMRADE";
	coincidence["coco"] = "TARIK";
	coincidence["SEMRADE"] = "SAMIRA";
	coincidences.push_back(coincidence);

	list_it = coincidences.begin();
	map_it = (*list_it).begin();

	for(; map_it != (*list_it).end(); map_it++)
	{
		cout <<map_it->first<< " : " << map_it->second << endl;
	}

	return 0;
}
#endif
