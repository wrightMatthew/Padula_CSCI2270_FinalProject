#include "Project.h"
#include <vector>
#include <iostream>
#include <queue>
#include <limits.h>
#include <algorithm>
using namespace std;

Graph::Graph()
{
//constractor
}

Graph::~Graph()
{
    //dtor
}

void Graph::addEdge(string v1, string v2, int weight)//creates edges
{
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                }
            }
        }
    }
}

void Graph::addVertex(string n)//inseet vertecies
{
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        v.district = -1;
        v.visited = false;
        v.ID = vertices.size();
        vertices.push_back(v);
    }
}

void Graph::displayEdges()//print connection between cities
{
    for(int i = 0; i < vertices.size(); i++){
        cout<< vertices[i].district <<":" <<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            cout<<vertices[i].adj[j].v->name;
            if (j != vertices[i].adj.size()-1)
                cout<<"***";
        }
        cout<<endl;
    }
}

void Graph::assignDistricts()// create district
{
    // Starting district num
    int distID = 1;
    // For each of the vertices
    for(int i = 0; i < vertices.size(); i++)
    {
        // Only consider a vertex that has not been assigned a district.
        if (vertices[i].district == -1)
        {
            // Run breadth first traversal and assign each node in the network to this district.
            BFTraversalLabel(vertices[i].name,distID);
            distID++;
        }
    }
}

void Graph::BFTraversalLabel(std::string startingCity, int distID)//function to travers between the verticies
{
    queue<vertex*> q;
    // Label all as unvisited.
    for(int i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
    }
    // Find the starting node and enqueue it.
    for(int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].name == startingCity)
        {
            // set current vertex to be visited.
            vertices[i].visited = true;
            q.push(&vertices[i]);
            vertices[i].district = distID;
            break;
        }
    }
    // Now do the rest of the search.
    while (q.empty() != true)
    {
        vertex * u = q.front();
        q.pop();
        for(int i = 0; i < u->adj.size(); i++)
        {
            if (u->adj[i].v->visited == false)
            {
                u->adj[i].v->visited = true;
                u->adj[i].v->district = distID;
                q.push(u->adj[i].v);
            }
        }
    }
}

void Graph::shortestPath(std::string startingCity,std::string endingCity)//find shortest path
{

    vertex * start = findVertex(startingCity);
    vertex * end = findVertex(endingCity);

    if (start == NULL || end == NULL)
    {
        cout << "One or more cities doesn't exist,or it is not in our Database"<< endl;
        return;
    }
    if (end->district != start->district)
    {
        cout << "You can't get there by car" << endl;
        return;
    }
    if (end->district == -1 || start->district == -1)
    {
        cout << "Please identify the districts before checking distances" << endl;
        return;
    }

    // Initialization
    for(int i = 0; i < vertices.size(); i++)
        vertices[i].visited = false;
    start->visited = true;
    queueVertex qv;
    qv.distance = 0;
    qv.path.push_back(start);
    queue<queueVertex> q;
    q.push(qv);

    while (q.empty() != true)
    {
        qv = q.front();
        q.pop();

        for(int i = 0; i < qv.path.back()->adj.size(); i++)
        {
            if (qv.path.back()->adj[i].v->visited == false)
            {
                // Create a new queueVertex with updated path and distance.
                vector<vertex *> path = qv.path;
                qv.path.back()->adj[i].v->visited = true;
                int distance = qv.distance + 1;

                path.push_back(qv.path.back()->adj[i].v);
                queueVertex temp;
                temp.path = path;
                temp.distance = distance;

                // If we have found the correct path
                if (qv.path.back()->adj[i].v == end)
                {
                    cout << temp.distance;
                    for (int j = 0; j < temp.path.size(); j++)
                        cout << "," << temp.path[j]->name;
                    cout << endl;
                    return;
                }
                else
                    q.push(temp);
            }
        }
    }
    return;
}

// Dijkstra
void Graph::shortestDistance(std::string startingCity,std::string endingCity)//find shortest distance
{
    // Search from "end" city to "start" city so that the path prints path in correct order.
    vertex * start = findVertex(endingCity);
    vertex * end = findVertex(startingCity);

    if (start == NULL || end == NULL)
    {
        cout << "One or more cities doesn't exist,or it is not in our Database" << endl;
        return;
    }
    if (end->district != start->district)
    {
        cout << "You can't get there by car" << endl;
        return;
    }
    if (end->district == -1 || start->district == -1)
    {
        cout << "Please identify the districts before checking distances" << endl;
        return;
    }

    // Initialization
    int previous[vertices.size()];
    for(int i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
        previous[vertices[i].ID] = -1;
        vertices[i].distance = INT_MAX;
    }
    priority_queue<vertex * ,vector<vertex *>, Comparator> q;
    start->distance = 0;
    q.push(start);
    vertex * cur;

    while (q.empty() != true)
    {
        cur = q.top();
        q.pop();

        // Visit each adjacent node.
        for(int i = 0; i < cur->adj.size(); i++)
        {
            if (cur->adj[i].v->visited == false)
            {
                // Calculate distance to this node.
                int distance = cur->distance + cur->adj[i].weight;

                // If distance is less than the tentative distance at the node, update the node.
                if (distance < cur->adj[i].v->distance)
                {
                   cur->adj[i].v->distance = distance;
                   previous[cur->adj[i].v->ID] = cur->ID;
                }

                // Add adjacent node to queue.
                q.push(cur->adj[i].v);
            }
        }
        // Mark this node as visited.
        cur->visited = true;

        // If we have found the correct path, output and return.
        if (cur == end)
        {
            int i = cur->ID;
            int c=cur->distance;
            cout << cur->distance;
            cout << "," << cur->name;
            while (previous[i] != -1)
            {
                cout << "," << vertices[previous[i]].name;
                i = vertices[previous[i]].ID;
            }
            cout << endl;
            time(c);
            break;
        }
    }
    return;
}

void Graph::time(int i)//Using as a prameter the km from the above function convert it in time of travelling
{
    int minutes2 = i/100;
    int minutes = minutes2*60;
    int convert_to_hours;
    convert_to_hours = minutes / 60;
    int remainder2;
    remainder2 = minutes % 60;
    cout<<endl;
    cout<<"TIME OF TRAVELLING"<<endl;
    cout<<"=================="<<endl;
    cout<<"The time to get to your destination by car is ";
    if (convert_to_hours < 1)
    {
        cout << "less than an hour." << endl;
    }
    else
    {
        if (convert_to_hours > 1)
            cout << "approximately " << convert_to_hours << " hours ";
        else
            cout << "approximately " << convert_to_hours << " hour ";
        if (remainder2 != 0)
        {
            if (remainder2 > 1)
                cout << "and " << remainder2 << "minutes." << endl;
            else
                cout << "and " << remainder2 << "minute." << endl;
        }
    }

    cout<<endl;
}


// Traveling Salesman
void Graph::shortestDistanceRoundTrip(std::string startingCity)
{
    vertex * start = findVertex(startingCity);
    if (start == NULL)
    {
        cout << "One or more cities doesn't exist,or it is not in our database." << endl;
        return;
    }
    if (start->district == -1)
    {
        cout << "Please identify the districts before checking distances." << endl;
        return;
    }

    // Initialization
    queueVertex qv;
    qv.distance = 0;
    qv.path.push_back(start);
    queue<queueVertex> q;
    q.push(qv);

    // Contains all of the possible path solutions we run into.
    std::priority_queue<queueVertex> possibleSolutions;

    while (q.empty() != true)
    {
        qv = q.front();
        q.pop();

        // If we have covered all nodes, we need to add the connection back to the first node if it exists.
        if (qv.path.size() == vertices.size())
        {
            for(int i = 0; i < qv.path.back()->adj.size(); i++)
            {
                // If we find a link to the first node.
                if (qv.path.back()->adj[i].v == start)
                {
                    // Add it to path
                    qv.distance += qv.path.back()->adj[i].weight;
                    qv.path.push_back(qv.path.back()->adj[i].v);
                    // Add this as a possible solution.
                    possibleSolutions.push(qv);
                }
            }
        }

        else
        {
            // For each adjacent city
            for(int i = 0; i < qv.path.back()->adj.size(); i++)
            {

                // Create a new path that contains this node, if node doesn't already exist in path.
                if (std::find(qv.path.begin(), qv.path.end(),qv.path.back()->adj[i].v) == qv.path.end())
                {
                    vector<vertex *> path = qv.path;
                    int distance = qv.distance + qv.path.back()->adj[i].weight;
                    path.push_back(qv.path.back()->adj[i].v);
                    queueVertex temp;
                    temp.path = path;
                    temp.distance = distance;
                    q.push(temp);
                }
            }
        }
    }
    if (!possibleSolutions.empty())
    {
        queueVertex solution = possibleSolutions.top();
        cout << solution.distance << endl;
        cout << solution.distance;
        for (int j = 0; j < solution.path.size(); j++)
            cout << "," << solution.path[j]->name;
        cout << endl;
    }
    else
        cout << "No possible path." << endl;
    return;
}

vertex * Graph::findVertex(std::string name) //find verticies
{
    for(int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].name == name)
            return &vertices[i];
    }
    return NULL;
}

List::List()//constractor for link list
{
    head = NULL;
    curr = NULL;
}

void List::createLinklist(string name ,string hotel,int star, int price,string hotel2,int star2,int price2,string rest,string rest2,string dish, string attrazioni)//create a link list
{
    nodePtr n=new city;
    n->name=name;
    n->hotel.name=hotel;
    n->hotel.star=star;
    n->hotel.avgNight=price;
    n->hotel2.name=hotel2;
    n->hotel2.star=star2;
    n->hotel2.avgNight=price2;
    n->rest=rest;
    n->rest2=rest2;
    n->dish=dish;
    n->vist=attrazioni;
    n->next=NULL;
    if (head!=NULL)
    {
        curr=head;
        while(curr->next != NULL)
        {
            curr= curr->next;
        }
        curr->next=n;
    }
    else
        head=n;
}

void List::print()//print the link list
{
    cout<<"===CURRENT PATH==="<<endl;
    curr= head;
    while(curr != NULL)
    {
        cout << curr -> name<<","<<curr->hotel.name<<","<<curr->hotel.star<<","<<curr->hotel.avgNight<<","<<curr->hotel2.name<<curr->hotel2.star<<","<<curr->hotel2.avgNight<<","<<curr->rest<<","<<curr -> rest2<<","<<curr -> dish<<","<< curr->vist<<endl;
        curr=curr ->next;
        cout<<"================="<<endl;
    }
    cout <<" NULL"<<endl;
}


void List::hotel(string city)//funtcion that based on the city outputs the hotel in that city
{
    curr= head;
    while(curr !=NULL)
    {
        if (curr->name== city)
        {
            break;
        }
        curr=curr ->next;
    }

    cout<<"In "<<curr->name<<" we suggest these hotels:"<<endl;
    cout<<"Hotel: "<<curr->hotel.name<<endl;
    cout<<"Star: "<<curr->hotel.star<<endl;
    cout<<"Price/night: "<<curr->hotel.avgNight<<"$"<<endl;
    cout<<"=========="<<endl;
    cout<<"Hotel: "<<curr->hotel2.name<<endl;
    cout<<"Star: "<<curr->hotel2.star<<endl;
    cout<<"Price/night: "<<curr->hotel2.avgNight<<"$"<<endl;
    return;
}


void List::ToDo(string city)//funtcion that based on the city outputs things to do in that city
{
    curr= head;
    while(curr !=NULL)
    {
        if (curr->name== city){
            break;
        }
        curr=curr ->next;
    }
    cout<<"In "<<curr->name<<" we suggest visiting: ";
    cout<< curr->vist<<endl;
}

void List::rest(string city) //funtcion that based on the city outputs the resturant in that city
{
    curr= head;
    while(curr !=NULL)
    {
        if (curr->name== city){
            break;
        }
        curr=curr ->next;
    }
    cout<<"In "<<curr->name<<" we suggest eating at: "<<endl;
    cout<< curr->rest<<endl;
    cout<<curr->rest2<<endl;
}


void List::Dish(string city)//funtcion that based on the city outputs the dish in that city
{
    curr= head;
    while(curr !=NULL)
    {
        if (curr->name== city){
            break;
        }
    curr=curr ->next;
    }
    cout<<"In "<<curr->name<<" the typical dish is: "<<endl;
    cout<< curr->dish<<endl;
}

void List::Budget(string city,int bu) //funtcion that based on the city and your budget outputs what you can afford
{
    curr = head;
    while(curr !=NULL)
    {
        if (curr->name== city)
        {
            break;
        }
        curr=curr ->next;
    }
    if (bu <4)
    cout<<"I am sorry but I am afraid you can't do much with your budget."<<endl;
    if (bu>4)
    cout<<"You can get a pizza." <<endl;
    else if (bu>13)
    cout<<"You can eat in a pizzeria."<<endl;
    if (bu>20)
    cout<<"You can go to a restaurant."<<endl;
    if (bu>50)
    cout<<"You can travel within 500 km where you are by train." << endl;
    if (bu>100)
    cout<<"You can travel all around Italy."<<endl;
    if (bu>curr->hotel2.avgNight)
    cout<<"You can stay one night at the "<<curr->hotel.name<<", one of the best hotel in "<<curr->name<<endl;
    if (bu>curr->hotel.avgNight)
    cout<<"You can stay one night at the "<<curr->hotel2.name<<", one of the best hotel in "<<curr->name<<endl;
}
