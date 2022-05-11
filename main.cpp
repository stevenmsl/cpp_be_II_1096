#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <unordered_map>
#include "solution.h"
#include "util.h"

using namespace std;
using namespace sol1096;

/*
Input: "{a,b}{c,{d,e}}"
Output: ["ac","ad","ae","bc","bd","be"]
*/

tuple<string, vector<string>>
testFixture1()
{
  auto input = string("{a,b}{c,{d,e}}");
  auto output = vector<string>{
      "ac", "ad", "ae", "bc", "bd", "be"};

  return make_tuple(input, output);
}

/*
Input: "{{a,z},a{b,c},{ab,z}}"
Output: ["a","ab","ac","z"]
Explanation: Each distinct word is written only once in the final answer.
*/

tuple<string, vector<string>>
testFixture2()
{
  auto input = string("{{a,z},a{b,c},{ab,z}}");
  auto output = vector<string>{
      "a", "ab", "ac", "z"};

  return make_tuple(input, output);
}

void test1()
{
  auto f = testFixture1();
  cout << "Expect to see: " << Util::toString(get<1>(f)) << endl;
  Solution sol;
  cout << Util::toString(sol.evalExpr(get<0>(f))) << endl;
}

void test2()
{
  auto f = testFixture2();
  cout << "Expect to see: " << Util::toString(get<1>(f)) << endl;
  Solution sol;
  cout << Util::toString(sol.evalExpr(get<0>(f))) << endl;
}

main()
{
  test1();
  test2();
  return 0;
}