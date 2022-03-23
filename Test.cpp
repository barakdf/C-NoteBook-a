

/**
 * Name = <Barak Dafna>, ID = <206795841>
 * */


#include <iostream>
#include <stdexcept>
#include "doctest.h"
#include "Notebook.hpp"
#include "Direction.hpp"

#define TEST_CASE DOCTEST_TEST_CASE


using namespace ariel;

TEST_CASE ("Good Input") {
    Notebook notebook;

            SUBCASE("Plain Notebook") {
                CHECK(notebook.read(0, 0, 0, Direction::Horizontal, 4) == "____");
                CHECK(notebook.read(0, 0, 0, Direction::Vertical, 4) == "____");
    }


            SUBCASE("After Writing") {
                notebook.write(0, 0, 0, Direction::Horizontal, "TEST");
                CHECK(notebook.read(0, 0, 0, Direction::Horizontal, 4) == "TEST");
                CHECK(notebook.read(0, 0, 0, Direction::Horizontal, 2) == "TE");
                CHECK(notebook.read(0, 0, 0, Direction::Vertical, 4) == "T___");
    }


            SUBCASE("After Erasing") {

                /* erase blank row */
                notebook.erase(0, 5, 2, Direction::Horizontal, 4);
                CHECK(notebook.read(0, 5, 2, Direction::Horizontal, 4) == "~~~~");
                /* erase half of written space */
                notebook.erase(0, 0, 2, Direction::Horizontal, 2);
                CHECK(notebook.read(0, 0, 2, Direction::Horizontal, 4) == "TE~~");
                /* erase the rest of the written space of the test above */
                notebook.erase(0, 0, 0, Direction::Horizontal, 2);
                CHECK(notebook.read(0, 0, 0, Direction::Horizontal, 4) == "~~~~");
                /* erase a place that already erased */
                notebook.erase(0, 0, 0, Direction::Horizontal, 4);
                CHECK(notebook.read(0, 0, 0, Direction::Horizontal, 4) == "~~~~");
                /* read vertical direction where the first spot is erased */
                CHECK(notebook.read(0, 0, 0, Direction::Vertical, 4) == "~___");
                /* read vertical direction after erasing the first spot that already erased and second spot that was blank */
                notebook.erase(0, 0, 0, Direction::Vertical, 2);
                CHECK(notebook.read(0, 0, 0, Direction::Vertical, 4) == "~~__");
    }

}

TEST_CASE("Bad Input") {
    Notebook notebook;

    SUBCASE("Negative page") {
        /* write */
        CHECK_THROWS(notebook.write(-1, 0, 0, Direction::Horizontal, "TEST"));
        /* read */
        CHECK_THROWS(notebook.read(-1, 0, 0, Direction::Horizontal, 4));
        /* erase */
        CHECK_THROWS(notebook.erase(-1, 0, 0, Direction::Vertical, 2));
    }

    SUBCASE("Negative row") {
        /* write */
                CHECK_THROWS(notebook.write(0, -1, 0, Direction::Horizontal, "TEST"));
        /* read */
                CHECK_THROWS(notebook.read(0, -1, 0, Direction::Horizontal, 4));
        /* erase */
                CHECK_THROWS(notebook.erase(0, -1, 0, Direction::Vertical, 2));
    }

    SUBCASE("Negative collum") {
        /* write */
                CHECK_THROWS(notebook.write(0,0, -1, Direction::Horizontal, "TEST"));
        /* read */
                CHECK_THROWS(notebook.read(0, 0, -1, Direction::Horizontal, 4));
        /* erase */
                CHECK_THROWS(notebook.erase(0,0, -1, Direction::Vertical, 2));
    }

    SUBCASE("Write on used space") {

        /* try to write on written space */
        notebook.write(0,0, 0, Direction::Horizontal, "ALREADY_TAKEN");
        CHECK_THROWS(notebook.write(0,0, 0, Direction::Horizontal, "I_DONT_CARE"));

        /* try to right on erased space*/
        notebook.erase(0,1, 0, Direction::Vertical, 2);
        CHECK_THROWS(notebook.write(0,1, 0, Direction::Horizontal, "MAYBE_HERE"));
    }



}