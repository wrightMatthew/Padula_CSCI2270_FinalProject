#ifndef PROJECT_H
#define PROJECT_H

#include <vector>
#include <iostream>

struct vertex;

struct adjVertex{
    vertex *v;
    int weight;
};





struct vertex{
    int ID;
    std::string name;
    int district;
    bool visited;
    int distance;
    std::vector<adjVertex> adj;
};

struct queueVertex{
    int distance;
    std::vector<vertex *> path;
    // Must override the less operatator so that we get a min value from priority queue.
    bool operator<(const queueVertex& a) const
    {
        return distance > a.distance;
    }
};

// Must override operator so we get a min value from priority queue.
struct Comparator {
public:
    bool operator()(const vertex* a, const vertex* b)
    {
        return (a->distance > b->distance);
    }
};

class Graph
{
    public:
        Graph();
        ~Graph();
        void addEdge(std::string v1, std::string v2, int weight);
        void addVertex(std::string name);
        void displayEdges();
        void assignDistricts();
        void BFTraversalLabel(std::string startingCity, int distID);
        void shortestPath(std::string startingCity,std::string endingCity);
        void shortestDistance(std::string startingCity,std::string endingCity);
        void shortestDistanceRoundTrip(std::string startingCity);
        void time(int);
        vertex * findVertex(std::string name);

    protected:
    private:
        //vector<edge> edges;
        std::vector<vertex> vertices;

};

struct hotels{
    std::string name;
    int star;
    int avgNight;
};


class List{
private:
typedef struct city
{
city *next;
std::string name;
hotels hotel;
hotels hotel2;
std::string rest;
std::string rest2;
std::string dish;
std::string vist;
}* nodePtr;

nodePtr head;
nodePtr curr;
public:
 List();
 void createLinklist(std::string name ,std::string hotel,int star, int price,std::string hotel2,int star2,int price2,std::string rest,std::string rest2,std::string dish, std::string attrazioni);
void print();
void hotel(std::string);
void ToDo(std::string);
void Dish(std::string);
void rest(std::string);
void Budget(std::string,int);

};




#endif // PROJECT_H

