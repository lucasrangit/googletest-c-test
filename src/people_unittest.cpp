#include "people.h"
#include "gtest/gtest.h"

TEST(ListCount, Empty) {
  EXPECT_EQ(0, people_count());
}

TEST(ListCount, AddOneByName) {
    person_add("John Smith");
    EXPECT_EQ(1, people_count());
}

TEST(ListCount, RemoveOneByName) {
    person_remove("John Smith");
    EXPECT_EQ(0, people_count());
}

TEST(PersonExists, Exists) {
    person_add("John Smith");
    EXPECT_TRUE(person_exists("John Smith"));
}

TEST(PersonExists, DoesNotExists) {
    person_remove("John Smith");
    EXPECT_FALSE(person_exists("John Smith"));
}

TEST(Person, AddTwoRemoveByPointer) {
    struct person *person1 = person_add("John Smith");
    struct person *person2 = person_add("Jane Doe");
    person_destroy(person1);
    EXPECT_FALSE(person_exists("John Smith"));
    EXPECT_TRUE(person_exists("Jane Doe"));
    person_destroy(person2);
    EXPECT_FALSE(person_exists("John Smith"));
    EXPECT_FALSE(person_exists("Jane Doe"));
}

TEST(Person, AddTwiceRemoveNonExisting) {
    struct person *person = person_add("John Smith");
    person_destroy(person);
    EXPECT_FALSE(person_exists("John Smith"));
    person_destroy(person);
    EXPECT_FALSE(person_exists("John Smith"));
}