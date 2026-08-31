#include "InputHandler.h"
#include <gtest/gtest.h>

// Whitespace Tests

TEST(GivenRemovesWhitespaceTest, WhenNoWhitespace_ThenStringUnchanged) {
    std::string input = "Hello";
    InputHandler::removeLeadingAndTrailingWhitespaces(input);
    EXPECT_EQ(input, "Hello");
}

TEST(GivenRemovesWhitespaceTest, WhenLeadingWhitespace_ThenSpacesRemoved) {
    std::string input = "  Hello";
    InputHandler::removeLeadingAndTrailingWhitespaces(input);
    EXPECT_EQ(input, "Hello");
}

TEST(GivenRemovesWhitespaceTest, WhenTrailingWhitespace_ThenSpacesRemoved) {
    std::string input = "Hello  ";
    InputHandler::removeLeadingAndTrailingWhitespaces(input);
    EXPECT_EQ(input, "Hello");
}

TEST(GivenRemovesWhitespaceTest, WhenBothSidesWhitespace_ThenSpacesRemoved) {
    std::string input = "  Hello   ";
    InputHandler::removeLeadingAndTrailingWhitespaces(input);
    EXPECT_EQ(input, "Hello");
}

TEST(GivenRemovesWhitespaceTest, WhenInnerSpaces_ThenSpacesUnchanged) {
    std::string input = "  Hello World  ";
    InputHandler::removeLeadingAndTrailingWhitespaces(input);
    EXPECT_EQ(input, "Hello World");
}

TEST(GivenRemovesWhitespaceTest, WhenOnlyWhitespace_ThenStringEmpty) {
    std::string input = "   ";
    InputHandler::removeLeadingAndTrailingWhitespaces(input);
    EXPECT_EQ(input, "");
}

TEST(GivenRemovesWhitespaceTest, WhenLeadingTab_ThenTabRemoved) {
    std::string input = "\tHello";
    InputHandler::removeLeadingAndTrailingWhitespaces(input);
    EXPECT_EQ(input, "Hello");
}

TEST(GivenRemovesWhitespaceTest, WhenTrailingTab_ThenTabRemoved) {
    std::string input = "Hello\t";
    InputHandler::removeLeadingAndTrailingWhitespaces(input);
    EXPECT_EQ(input, "Hello");
}

TEST(GivenRemovesWhitespaceTest, WhenOnlyTabs_ThenStringEmpty) {
    std::string input = "\t\t\t";
    InputHandler::removeLeadingAndTrailingWhitespaces(input);
    EXPECT_EQ(input, "");
}

TEST(GivenRemovesWhitespaceTest, WhenMixedLeadingWhitespace_ThenAllRemoved) {
    std::string input = " \t Hello";
    InputHandler::removeLeadingAndTrailingWhitespaces(input);
    EXPECT_EQ(input, "Hello");
}

TEST(GivenRemovesWhitespaceTest, WhenNewlineLeading_ThenNewlineRemoved) {
    std::string input = "\nHello";
    InputHandler::removeLeadingAndTrailingWhitespaces(input);
    EXPECT_EQ(input, "Hello");
}
