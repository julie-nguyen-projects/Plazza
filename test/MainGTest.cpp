/*
** EPITECH PROJECT, 2017
** Piscine CPP
** File description:
** MainGTest.cpp
*/

#include "gtest/gtest.h"
#include "gmock/gmock.h"

int main(int ac, char **av) {
        testing::InitGoogleTest(&ac, av);
        return RUN_ALL_TESTS();
}