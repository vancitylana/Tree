#include "TTreeMap.h"
#include <gtest.h>

using namespace std;

TEST(TTreeMap, can_build_and_run_sample_test)
{
  TTreeMap<string, int> a;
  EXPECT_EQ(0, a.GetCount());
}

TEST(TTreeMap, can_add_item)
{
  TTreeMap<string, int> a;
  a.Add("hello", 444);
  EXPECT_EQ(444, a["hello"]);
}

TEST(TTreeMap, can_find_item)
{
  TTreeMap<string, int> a;
  a.Add("hello", 444);
  a.Add("world", 555);
  a.Add("rainy", 3);
  EXPECT_EQ(3, a.Find("rainy"));
}


TEST(TTreeMap, unexpected_indexation_wont_cause_error)
{
  TTreeMap<string, int> a;
  a.Add("hello", 444);
  a.Add("world", 555);
  a.Add("rainy", 34);
  ASSERT_NO_THROW(a["some key"]);
}

TEST(TTreeMap, can_iterate_object)
{
  TTreeMap<string, int> a;
  a.Add("hello", 444);
  a.Add("world", 555);
  a.Add("rainy", 34);
  int sorted[3] = { 444, 555, 34 };
  int i = 0;
  TTreeMap<string, int>::iterator it = a.Begin();
  while (it.IsEnd()) {
    EXPECT_EQ(sorted[i], it.Get()->GetVal());
    it.GoNext();
    i++;
  }
}