// Copyright [2025] Mohammed Ayan/ Ansh Patel
#include <fstream>
#include <sstream>
#include "EDistance.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EDistanceTests
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(invalid_cost_check) {
    EDistance ed("A", "T");
    BOOST_TEST(ed.optDistance() == 1);
    BOOST_TEST(ed.alignment().find("A T 1") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(swapped_columns_check) {
    EDistance ed("ACGT", "TGCA");
    BOOST_TEST(ed.optDistance() == 4);
    std::string align = ed.alignment();
    BOOST_TEST(align.find("A T 1") != std::string::npos);
    BOOST_TEST(align.find("C G 1") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(wrong_direction) {
    EDistance ed("AACAGTTACC", "TAAGGTCA");
    BOOST_TEST(ed.optDistance() == 7);
    std::string align = ed.alignment();
    BOOST_TEST(align.find("A T 1") != std::string::npos);
    BOOST_TEST(align.find("G G 0") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(reversed_check) {
    EDistance ed("ACGT", "AGCT");
    BOOST_TEST(ed.optDistance() == 2);
    std::string align = ed.alignment();
    std::vector<std::string> expected = {
        "A A 0",
        "C G 1",
        "G C 1",
        "T T 0"
    };

    size_t last_pos = 0;
    for (const std::string& line : expected) {
        size_t pos = align.find(line, last_pos);
        BOOST_TEST(pos != std::string::npos);
        last_pos = pos;
    }
}

BOOST_AUTO_TEST_CASE(min3) {
    for (int a = 0; a <= 3; ++a) {
        for (int b = 0; b <= 3; ++b) {
            for (int c = 0; c <= 3; ++c) {
                int expected = std::min({a, b, c});
                int actual = EDistance::min3(a, b, c);
                BOOST_CHECK_EQUAL(expected, actual);
            }
        }
    }
}

BOOST_AUTO_TEST_CASE(TestAlignmentHeadAndTail) {
    EDistance ed0("TGCA", "GCA");
    ed0.optDistance();
    std::string a = ed0.alignment();
    BOOST_CHECK_NE(a.find("T - 2"), std::string::npos);

    EDistance ed1("GCA", "TGCA");
    ed1.optDistance();
    std::string b = ed1.alignment();
    BOOST_CHECK_NE(b.find("- T 2"), std::string::npos);

    EDistance ed2("ACTG", "AC");
    ed2.optDistance();
    std::string c = ed2.alignment();
    BOOST_CHECK_NE(c.find("T - 2"), std::string::npos);
    BOOST_CHECK_NE(c.find("G - 2"), std::string::npos);

    EDistance ed3("AC", "ACTG");
    ed3.optDistance();
    std::string d = ed3.alignment();
    BOOST_CHECK_NE(d.find("- T 2"), std::string::npos);
    BOOST_CHECK_NE(d.find("- G 2"), std::string::npos);
}
