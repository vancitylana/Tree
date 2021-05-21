#include <iostream>
#include "TTreeMap.h"
using namespace std;
int main()
{
  TTreeMap<string, int> a;
  a.Add("hello", 444);
  a.Add("world", 555);
  a.Add("rainy", 34);
  a;
  TTreeMap<string, int>::iterator it = a.Begin();
  while (!it.IsEnd()) {
    std::cout << it.Get()->GetVal() << std::endl;
    it.GoNext();
  }
  return 0;
}