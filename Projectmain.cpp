#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include <cstring>
#include "Project.h"

using namespace std;


int main(int argc, char*argv[])
{
    Graph g; //create a graph
    ifstream file;

    file.open("City.txt");//open a file
    vector<string> cityList;

    if (file.is_open())
    {
        string line;
        string city;
        int linecounter = 0;

        while (getline (file,line))
        {
            stringstream citystream(line);

            if (linecounter == 0)
            {
                getline(citystream, city, ',');
                while(getline(citystream, city, ','))
                {
                    cityList.push_back(city);
                    g.addVertex(city);
                }
            }
            else
            {
                string temp;
                int distValue;
                int numCounter = 0;
                getline(citystream, temp, ',');
                while(getline(citystream, temp, ','))
                {
                    distValue = stoi(temp);
                    if (distValue != 0 && distValue != -1)
                    {
                        g.addEdge(cityList[linecounter-1], cityList[numCounter], distValue);
                    }
                    numCounter++;
                }
            }
            linecounter++;
        }
        ifstream file2;
        file2.open("City2.txt");//open a file
        List l; //create a list

        if (file2.is_open())
        {
            string line;
            string line2;
            string line3;
            string line4;
            string line5;
            string line6;
            string line7;
            string line8;
            string line9;
            string line10;
            string line11;
            string city;
            string hotel;
            int star;
            int price;
            string hotel2;
            int star2;
            int price2;
            string resturant;
            string resturant2;
            string dish;
            string attrazioni;

            while ( getline (file2,line))
            {
                int index = line.find(",");
                city = line.substr(0,index);
                line2 = line.substr(index+1, line.length());

                int index2 = line2.find(",");
                hotel= line2.substr(0,index2);
                line3 = line2.substr(index2+1, line2.length());


                int index3 = line3.find(",");
                star=stoi(line3.substr(0,index3));
                line4 = line3.substr(index3+1, line3.length());

                int index4 = line4.find(",");
                price=stoi(line4.substr(0,index4));
                line5=line4.substr(index4+1, line4.length());

                int index5 = line5.find(",");
                hotel2=line5.substr(0,index5);
                line6=line5.substr(index5+1, line5.length());

                int index6 = line6.find(",");
                star2=stoi(line6.substr(0,index6));
                line7=line6.substr(index6+1, line6.length());

                int index7 = line7.find(",");
                price2=stoi(line7.substr(0,index7));
                line8=line7.substr(index7+1, line7.length());

                int index8 = line8.find(",");
                resturant=line8.substr(0,index8);
                line9=line8.substr(index8+1, line8.length());

                int index9 = line9.find(",");
                resturant2=line9.substr(0,index9);
                line10=line9.substr(index9+1, line9.length());

                int index10 = line10.find(",");
                dish=line10.substr(0,index10);
                line11=line10.substr(index10+1, line.length());

                attrazioni=line11;

                l.createLinklist(city,hotel,star,price,hotel2,star2,price2,resturant,resturant2,dish,attrazioni);
            }

        int input;
        g.assignDistricts();

        while (input != 9)
        {
            cout << "=============Main Menu=============" << endl;
            cout << "1. Print major cities in Italy" << endl;
            cout << "2. Connection between all the cities" << endl;
            cout << "3. What you can do with your budget" << endl;
            cout << "4. I would like to go to..." << endl;
            cout << "5. What to eat" << endl;
            cout << "6. Where to eat" << endl;
            cout << "7. Hotels" << endl;
            cout << "8. Things to visit where you are" << endl;
            cout << "9. Quit" << endl;
            cin >> input;

            if (input == 1)
            {
                int g;
                for (int i=0;i<cityList.size()-1;i++)
                {
                    cout<<cityList[i]<<", ";
                    g=i;
                }
                cout<<cityList[g+1]<<endl;
            }

            if (input == 2)
            {
                g.displayEdges();
            }

            if (input == 3)
            {
                string startingCity;
                cout << "Enter where you are:" << endl;
                cin.ignore(1, '\n');
                getline(cin, startingCity);
                bool found = false;
                for (int i=0; i < cityList.size(); i++)
                {
                    if (cityList[i] == startingCity)
                    {
                        found = true;
                    }
                }
                if (found == false)
                {
                    cout << "The city you entered is not in our database." << endl;
                }
                else
                {
                    string bu;
                    cout << "Enter your budget:" << endl;
                    getline(cin, bu);
                    int b=stoi(bu);
                    l.Budget(startingCity,b);
                }
            }

            if (input == 4)
            {
                string startingCity;
                cout << "Enter where you are:" << endl;
                cin.ignore(1, '\n');
                getline(cin, startingCity);
                string endingCity;
                cout << "Enter the destination:" << endl;
                getline(cin, endingCity);
                bool bothfound = false;
                for (int i=0; i < cityList.size(); i++){
                    if (cityList[i] == startingCity){
                        for (int i=0; i < cityList.size(); i++){
                            if (cityList[i] == endingCity){
                                bothfound = true;
                                g.shortestDistance(startingCity, endingCity);
                            }
                        }
                    }
                }
                if (bothfound == false){
                    cout << "One or more cities doesn't exist, or it is not in our database." << endl;
                }
            }

            if (input == 5)
            {
                string startingCity;
                cout << "Enter where you are:" << endl;
                cin.ignore(1, '\n');
                getline(cin, startingCity);
                bool found = false;
                for (int i=0; i < cityList.size(); i++)
                {
                    if (cityList[i] == startingCity)
                    {
                        found = true;
                    }
                }
                if (found == false)
                {
                    cout << "The city you entered is not in our database." << endl;
                }
                else{
                l.Dish(startingCity);
                }
            }

            if (input == 6)
            {
                string startingCity;
                cout << "Enter where you are:" << endl;
                cin.ignore(1, '\n');
                getline(cin, startingCity);
                bool found = false;
                for (int i=0; i < cityList.size(); i++)
                {
                    if (cityList[i] == startingCity)
                    {
                        found = true;
                    }
                }
                if (found == false)
                {
                    cout << "The city you entered is not in our database." << endl;
                }
                else{
                l.rest(startingCity);
                }
            }

            if (input == 7)
            {
                string startingCity;
                cout << "Enter where you are:" << endl;
                cin.ignore(1, '\n');
                getline(cin, startingCity);
                bool found = false;
                for (int i=0; i < cityList.size(); i++)
                {
                    if (cityList[i] == startingCity)
                    {
                        found = true;
                    }
                }
                if (found == false)
                {
                    cout << "The city you entered is not in our database." << endl;
                }
                else{
                l.hotel(startingCity);
                }
            }

            if (input == 8)
            {
                string startingCity;
                cout << "Enter where you are:" << endl;
                cin.ignore(1, '\n');
                getline(cin, startingCity);
                bool found = false;
                for (int i=0; i < cityList.size(); i++)
                {
                    if (cityList[i] == startingCity)
                    {
                        found = true;
                    }
                }
                if (found == false)
                {
                    cout << "The city you entered is not in our database." << endl;
                }
                else{
                l.ToDo(startingCity);
                }
            }
        }

        file.close();
        cout << "Goodbye!" << endl;

        return 0;
        }
    }
}

