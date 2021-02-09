#The Coalition Structure Generation Problem
##Input
In the first line there will be an integer 1≤n≤18. Then, there will be 2n−1 lines. Each such line represents exactly one team (together, the lines represent all possible teams), and consists of three parts. First, there will be an integer −100000≤v≤100000 equal to the team’s expected performance. Then, there will be a number k>0 equal to the team’s size. Finally, there will be k integers, each representing an employee e∈{1,…,n} on the team.
##Output
non-negative integer 1≤m≤n that is equal to the number of teams in the coalition structure. Then, m lines should follow, each representing one team.

##Sample 
Input
2
1 1 1
2 1 2
1 2 1 2

Output
2
1 1
1 2
