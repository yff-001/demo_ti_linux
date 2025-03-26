#include "../lib/unity/unity.h"

#include "../src/handler/communication.h"

void setUp(void) {
    // Set up code if needed
}

void tearDown(void) {
    // Clean up code if needed
}

void test_communication_init(void) {
    communication_init();
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_communication_init);
    return UNITY_END();
}
