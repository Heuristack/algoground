#ifndef GRAPH_H
#define GRAPH_H

#include <ostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <optional>

using namespace std;

template <typename Vertex, typename Edge> struct OrderedRetrievableAdjanceyList : map<Vertex, set<Edge>> {};
template <typename Vertex, typename Weight = double, typename Edge = pair<Vertex, Weight>, template <typename, typename> typename BasicGraph = OrderedRetrievableAdjanceyList>
struct Graph : BasicGraph<Vertex, Edge>
{
    struct GraphOption
    {
        bool directed = false;
        bool weighted = false;
    };

    Graph(vector<pair<Vertex, Vertex>> const & edges, bool directed = false) : option{directed, false}
    {
        for (auto const & e : edges) {
            this->operator[](e.first).emplace(e.second);
            if (!option.directed) {
                this->operator[](e.second).emplace(e.first);
            }
        }
    }

    Graph(vector<pair<pair<Vertex, Vertex>, Weight>> const & edges, bool directed = false): option {directed, true}
    {
        for (auto const & e : edges) {
            this->operator[](e.first.first).emplace(Edge{e.first.second, e.second});
            if (!option.directed) {
                this->operator[](e.first.second).emplace(Edge{e.first.first, e.second});
            }
        }
    }

    ostream & print(ostream & s)
    {
        for (auto const & v : *this) {
            s << v.first << ": ";
            for (auto const & w : v.second) {
                s << w << " ";
            }
            s << "\n";
        }
        return s;
    }

    ostream & print_weighted(ostream & s)
    {
        for (auto const & v : *this) {
            s << v.first << ": ";
            for (auto const & w : v.second) {
                s << "[" << w.first << ": " << w.second << "] ";
            }
            s << "\n";
        }
        return s;
    }

    GraphOption option;
};

template <typename Vertex, typename Weight = double> explicit Graph(vector<pair<pair<Vertex, Vertex>, Weight>> const & edges) -> Graph<Vertex, Weight>;
template <typename Vertex, typename Weight> ostream & operator<<(ostream & s, Graph<Vertex, Weight> & g)
{
    return g.print_weighted(s);
}

template <typename Vertex> explicit Graph(vector<pair<Vertex, Vertex>> const & edges) -> Graph<Vertex, nullopt_t, Vertex>;
template <typename Vertex> ostream & operator<<(ostream & s, Graph<Vertex, nullopt_t, Vertex> & g)
{
    return g.print(s);
}

#endif

