#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

//Representation of the coalitions, contains a helper function for
// checking if inputed node contains any agent in agents.
struct node
{
    vector<int> agents;
    int value;
    int level;
    int bound;

    bool is_in_coalition(node const &other)
    {
        for (auto element : other.agents)
        {
            if (std::find(agents.begin(), agents.end(), element) != agents.end())
            {
                return true;
            }
        }
        return false;
    }
};
// Used by the priority_queue to make it prioritise with regards to "bound".
struct myComp
{
    constexpr bool operator()(
        node const &a,
        node const &b)
        const noexcept
    {
        return a.bound < b.bound;
    }
};

//Struct which contains the standard input.
// agents : Number of agents
// ncomp  : Number of possible coalitions
// coalitions : Vector with all possible coalitions, represented as nodes.
struct problem
{
    int agents;
    int ncomp;
    vector<node> coalitions;
};

//Assumes that the node coalitions are sorted with regards to cost.
//Calculates the upper boundery for a node, by adding the highest values
// with the input node value.
int bound(node const &u, problem const &p)
{
    int result = u.value;
    for (int i = 0; i < p.agents - u.level; i++)
    {
        result += p.coalitions[i].value; //insert funktion här
    };
    return result;
}

//Function to check if a node is valid.
bool check_best_items(vector<node> const &a, node const &b)
{
    for (auto i : a)
    {
        if (i.is_in_coalition(b))
        {
            return false;
        }
    }
    return true;
}

//Implementation of best search first with branch and bound.
void solve(problem const &problem)
{
    priority_queue<node, vector<node>, myComp> prio_queue;
    vector<node> best_items(problem.agents - 1);
    node u{}, v{};
    v.level = 0;
    v.value = 0;
    v.bound = bound(v, problem);

    int maxvalue = 0;
    bool level = false; 
    prio_queue.push(v);
    vector<node> nodes_to_check = problem.coalitions; 
    vector<node> temp; 


    while (!prio_queue.empty())
    {   
       if(level){
           nodes_to_check = temp; 
           temp.clear(); 
       }
        v = prio_queue.top();
        prio_queue.pop();
        
        if (v.bound > maxvalue)
        {
            u.level = v.level + 1;
            for (auto i : nodes_to_check) //kolla alla chilldren
            {
                if (check_best_items(best_items, i))
                {
                    u.value = v.value + i.value;
                    u.agents = i.agents;
                    u.bound = bound(u, problem);
                    if (u.value > maxvalue)
                    {
                        maxvalue = u.value;
                        best_items.insert(best_items.begin() + u.level, u);
                    }
                    if (u.bound > maxvalue)
                    {
                        prio_queue.push(u);
                        temp.push_back(u);

                    }
                }
            }
        }
        level = true; 
    }

    //Printing final output
    //Subtracting 1 from size, since first element is always 0 and redundant.
    bool first = true;
    //cout << best_items.size() - 1 << endl;
    vector<node> best{};
    int numb = 0; 
    for(auto i : best_items )
    {
        if (i.agents.size() != 0)
        {
            numb++; 
        }
    }
    cout<<numb<<endl; 
    for (auto i : best_items)
    {
        if (i.agents.size() != 0)
        {
            cout << i.agents.size() << " ";
            for (auto agent : i.agents)
            {
                if (agent == 0)
                    break;
                else
                {
                    cout << agent << " ";
                }
            }
            cout << endl;
        }
    }
};

bool struct_sorter(node const &lhs, node const &rhs)
{
    return lhs.value > rhs.value;
}

int main()
{
    problem problem;
    cin >> problem.agents;
    problem.ncomp = pow(2, problem.agents) - 1;

    for (int i = 0; i < pow(2, problem.agents) - 1; ++i)
    {
        int v, k;
        cin >> v >> k;
        node coal{};
        coal.value = v;
        for (int j{}; j < k; ++j)
        {
            int e;
            cin >> e;
            coal.agents.push_back(e);
        }
        problem.coalitions.push_back(coal);
    }
    sort(problem.coalitions.begin(), problem.coalitions.end(), &struct_sorter);
    solve(problem);
    return 0;
}
