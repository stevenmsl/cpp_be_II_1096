#include "solution.h"
#include "util.h"
#include <unordered_set>
#include <numeric>
#include <iterator>
#include <unordered_map>
#include <deque>
#include <string>
#include <sstream>
#include <algorithm>
#include <stack>
using namespace sol1096;
using namespace std;

/*takeaways
  - process the inner most pair of braces
    first
  - {a,b}{c,{d,e}}
    - the first pair we will process is {a,b}
    - remove the braces and for each element
      we generate a new expression
      {a,b}{c,{d,e}} -> a{c,{d,e}} and b{c,{d,e}}
    - following the sub-expr b{c,{d,e}}
    - we will remove the inner most braces {d,e}
      b{c,{d,e}} -> b{cd} and b{ce}
    - following the sub-expr b{ce}
    - remove the braces and we get bc and be
      which can be added to the answer


*/

vector<string> Solution::evalExpr(string expr)
{
  auto result = vector<string>();
  auto visited = unordered_set<string>();
  auto stk = stack<string>();

  stk.push(expr);

  while (!stk.empty())
  {
    auto str = stk.top();
    stk.pop();

    /* no more braces in the expression
       - we have composed a word
    */
    if (str.find("{") == string::npos)
    {
      if (!visited.count(str))
        visited.insert(str), result.push_back(str);
      continue;
    }

    auto i = 0, left = 0, right = 0;

    /* find the inner most pair of {} */
    while (str[i] != '}')
    {
      if (str[i++] == '{')
        /* we have to move it back by one
           as i is increased by 1 after
           the comparsion
           - keep updating the location
             until we find the inner most
             '{'
        */
        left = i - 1;
    }
    right = i;
    auto before = str.substr(0, left);
    auto after = str.substr(right + 1);
    /* except the '{' and '}'
       - the size is right-left+1-2
       - {a,b} -> a,b
    */
    auto elemts = str.substr(left + 1, right - left + 1 - 2);

    /* remove one pair of braces
       - remove ',' to apply the rule 2 (union)
       - for each elements create a new expression
         to apply the rule 3 (product and concatenation)
       - {a,b}{c,{d,e}} will be broken down into
         a{c,{d,e}} and b{c,{d,e}}
    */

    auto ss = stringstream(elemts);
    string elemt;
    /* generate a new expression for
       each element inside this pair
       of braces
       - this is the product part
         for the rule 3
    */
    while (getline(ss, elemt, ','))
      /* this is the concatenation part of the rule 3 */
      stk.push(before + elemt + after);
  }

  sort(result.begin(), result.end());
  return result;
}
