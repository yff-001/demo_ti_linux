// test_add.c
#include "../lib/unity/unity.h"
#include "../src/event_queue.h"

void setUp(void) {
    // Set up code if needed
}

void tearDown(void) {
    // Clean up code if needed
}

void test_addition(void) {
    TEST_ASSERT_EQUAL(0, event_queue_available());
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_addition);
    return UNITY_END();
}
