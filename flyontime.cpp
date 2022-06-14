/*******************************************************************************/
//// Project 1 Report: Savvy Traveler //
/// CPSC 535 -section 1 //
/// Prof: Doina Bein //
/// Group: Fly with algo//
/// Group members //
//  NIDHI SHAH :  nidhishah989@csu.fullerton.edu
//  MERIN JOSEPH: merin.joseph@csu.fullerton.edu
//  APEKSHA SHAH: apeksha@csu.fullerton.edu
////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iterator>
#include<map>
#include<set>
#include<iterator>
using namespace std;

/***********************************************************************************/
//                          flyontime function(main algorith)                      //
/**********************************************************************************/

void flyontime(map<char, map<char, double>> graph, char source, char destination)
{
	//output variables declaration
	double highprobpathprob = 0.0; //ontime arrival probability value for given source and destination
	string highprobpath = ""; //ontime arrival path for given source and destination
	
	//set to store all cities reliability from other cities 
	set < pair < double, char >, greater <pair < double, char >> > cityreliability;
	//iterator declaration for cityreliability set
	set < pair < double, char > > ::iterator maxcity;

	//iteration declaration for graph(V,E)
	map<char, map<char, double>>::iterator it;
	map<char, map<char, double>>::iterator createinitialgraph;
	//iteration declaration for inside map of graph-> pair of edge and its probability
	map<char, double>::iterator inside;

	//traverse through map for each city to find reliability of each city and to find the higher probability from each city to other cities
	for (it = graph.begin(); it != graph.end(); it++)
	{
		//set to store next max probability city to find high probability path
		set < pair < double, char >, greater <pair < double, char >> > nextmaxprobcity;
		set < pair < double, char > > ::iterator next;

		//declare the map which will store the probability of each city while finding the high probability path
		//also it will store the source city (the reasone of changing the probability for key city) for key city 
		map<char, pair<double, char>> citytocitiesprobability;
		for (createinitialgraph = graph.begin(); createinitialgraph != graph.end(); createinitialgraph++) {
			citytocitiesprobability.insert({ createinitialgraph->first,{-1,'#'} });
		}

		//iterator declaration for citytocitiesprobability
		map<char, pair<double, char>> ::iterator final;
		//currentvisited node declaration
		char currentvisitcity;
		//production variable declaration
		double product;
		//final sum output variable declaration
		double totalprobforcity = 0.0;
		//set to store the visited city node
		set <char> visited;
		//iterator for visited set
		set<char>::iterator ps;

		//first making the city node at 'it' pointer a source
		//So, changing the probability in citytocitiesprobability for the source city as 0
		citytocitiesprobability.at(it->first).first = 0;
		//make this source city as visited one
		visited.insert(it->first);
		currentvisitcity = it->first;

		//check all cities are visited or not
		while (visited.size() < graph.size())
		{
			//traverse all connected cities (vertices) to calculate the high probability from the source city to connected cities.
			for (inside = graph.at(currentvisitcity).begin(); inside != graph.at(currentvisitcity).end(); inside++)
			{

				//node is not selected-> ps will be point to end of visited set
				ps = visited.find(inside->first);
				//checking the pointer of visited set pointing to end of set or not, if the city is visited -> no need to calculate probability for that city
				if (ps == visited.end())
				{
					//production technique to find the highest ontime travel prbability for connected city from the visited city
					if (citytocitiesprobability.at(currentvisitcity).first == 0) //if it is the souce node -with probability 0
					{
						product = inside->second;
					}
					//for calculating the high probability for connected city from current visited city
					else
					{
						product = citytocitiesprobability.at(currentvisitcity).first * graph.at(currentvisitcity).at(inside->first);
					}
					//check if the production is greater than current probability
					//if so update the current probability for the node (connected city)
					if (product > citytocitiesprobability.at(inside->first).first)
					{
						//change the probability
						citytocitiesprobability.at(inside->first).first = product;
						//change the source node that change the city node value
						citytocitiesprobability.at(inside->first).second = currentvisitcity;

						//insert the new pair of node to nextmaxprobcity
						nextmaxprobcity.insert({ inside->second, inside->first });
					}
				}

			}

			//find new city to visit with maximum probability
			next = nextmaxprobcity.begin();
			//add new city to visited list
			visited.insert(next->second);
			currentvisitcity = next->second;
			//erase the visited city from the nextmaxprobcity set.
			nextmaxprobcity.erase(next);

		} //end of while loop

		
		//calculate the sum of all probability for source city( at it iterator) to find the reliability for that city
		for (final = citytocitiesprobability.begin(); final != citytocitiesprobability.end(); final++)
		{
			totalprobforcity = totalprobforcity + citytocitiesprobability.at(final->first).first;
		}
		//insert the total reliabiity for source city
		cityreliability.insert({ totalprobforcity,it->first });

		//find the ontime high probability path for given source and destination if the user source node is current iteration source node
		if (it->first == source)
		{
			char check = destination;
			highprobpathprob = citytocitiesprobability.at(destination).first;
			highprobpath = destination;
			//it will run the while loop from destination to source until the source node reach.
			while (check != source)
			{
				highprobpath = citytocitiesprobability.at(check).second + highprobpath;
				check = citytocitiesprobability.at(check).second;
			}

		}

	}

	//Show the outputs 
	cout << "\n Highest probability of on-time arrival from source to destination : " << highprobpathprob;
	cout << "\n High probability path from source to destination : " << highprobpath;
	//maximum probability city
	maxcity = cityreliability.begin();
	cout << "\n The most reliable travel destination city : " << maxcity->second << "\n\n";

}

/***********************************************************************************/
//                          Main function                                          //
/**********************************************************************************/
int main() {

	/***************************************************************/
	/////////// Ask user to input the graph, source and destination /////
	/********************************************************************/

	char endnode, startnode, source1, destination1;
	int more, morenodes;
	double weight;

	map<char, map<char, double>> map1;
	map<char, double> map11;
	map<char, map<char, double>>::iterator it;


	printf("...............ENTER YOUR GRAPH................\n");
	do
	{
		printf("Enter the node : ");
		scanf(" %c", &startnode);
		map<char, double> map11;
		// map1.insert(startnode);
		do
		{
			//map1[startnode][].push_back();
			printf("Enter the connected NODE to %c and PROBABILITY : ", startnode);
			// it->second = map<char,double> map11;
			scanf(" %c %lf", &endnode, &weight);
			map11.insert(pair<char, double>(endnode, weight));
			cout << "PRESS 1 to add connected nodes or PRESS 2 to end :";
			scanf(" %d", &more);
		} while (more == 1);
		map1[startnode] = map11;
		printf("PRESS 0  to add a new node or PRESS 2 to end :  ");
		scanf(" %d", &morenodes);
	} while (morenodes == 0);

	printf("Enter the SOURCE node: ");
	scanf(" %c", &source1);
	printf("Enter the DESTINATION node: ");
	scanf(" %c", &destination1);
	flyontime(map1, source1, destination1);



	/***************************************************************************************/
	//////////////// Other way to provide the graph, source and destination ////////////////
	/***************************************************************************************/
	//Example one: Graph input and source and destination input
	//cout << "......EXAMPLE 1......" << "\n";
	//map<char, map<char, double>> map1{
	//									{'A',{{'B',0.8},{'C',0.7},{'D',0.9}}},
	//									{'B',{{'A',0.8},{'C',0.8},{'E',0.6},{'F',0.6}}},
	//									{'C',{{'A',0.7},{'B',0.8},{'F',0.9}}},
	//									{'D',{{'A',0.9},{'F',0.6},{'G',0.8}}},
	//									{'E',{{'B',0.6},{'F',0.8},{'H',0.6}}},
	//									{'F',{{'B',0.6},{'C',0.9},{'D',0.6},{'E',0.8},{'G',0.7},{'H',0.7}}},
	//									{'G',{{'D',0.8},{'F',0.7},{'H',0.9}}},
	//									{'H',{{'E',0.6},{'F',0.7},{'G',0.7}}}
	//		                        };
	//char source1 = 'A';
	//char destination1 = 'F';
	////Call the function to get the shortest path between source and destination
	//// and to get what city is the most reliable travel destination
	//flyontime(map1, source1, destination1);
	////Example two: Graph input and source and destination input
	//cout << "......EXAMPLE 2......" << "\n";
	//map<char, map<char, double>> map2 = {
	//												{'A',{{'B',0.8},{'D',0.9}}},
	//												{'B',{{'A',0.8},{'C',0.6},{'E',0.7}}},
	//												{'C',{{'B',0.6},{'F',0.8}}},
	//												{'D',{{'A',0.9},{'E',0.8},{'G',0.8}}},
	//												{'E',{{'B',0.7},{'D',0.8},{'F',0.9},{'H',0.6}}},
	//												{'F',{{'C',0.8},{'E',0.9}}},
	//												{'G',{{'D',0.8},{'H',0.9}}},
	//												{'H',{{'E',0.6},{'G',0.9}}}
	//									};
	//char source2 = 'C';
	//char destination2 = 'A';
	//flyontime(map2, source2, destination2);
	////Example three: Graph input and source and destination input
	//cout << "......EXAMPLE 3......" << "\n";
	//map<char, map<char, double>> map3 = {
	//												{'A',{{'B',0.8},{'D',0.9},{'E',0.8}}},
	//												{'B',{{'A',0.8},{'C',0.6},{'F',0.7}}},
	//												{'C',{{'B',0.6},{'D',0.9},{'G',0.6}}},
	//												{'D',{{'A',0.9},{'C',0.9},{'H',0.7}}},
	//												{'E',{{'A',0.8},{'F',0.6},{'H',0.8}}},
	//												{'F',{{'B',0.7},{'E',0.6},{'G',0.9}}},
	//												{'G',{{'C',0.6},{'F',0.9},{'H',0.6}}},
	//												{'H',{{'D',0.7},{'E',0.8},{'G',0.6}}}
	//									};
	//char source3 = 'E';
	//char destination3 = 'C';
	//flyontime(map3, source3, destination3);

	/******************** All examples from the documents **************************/
	return 0;
}




