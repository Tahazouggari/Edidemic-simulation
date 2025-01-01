#include <unistd.h>
#include <string.h>

#include "minunit.h"
#include "channel.h"

void test_setup(void) {
}

void test_teardown(void) {
    destroy_channel(CHANNEL_NAME);
}


MU_TEST(test_send_receive) {
    int day;
    int priority;
    char news[MSG_LENGTH];
    Channel *channel_in;
    Channel *channel_out;

    printf("Testing send and receive\n");

    channel_in = create_channel(CHANNEL_NAME);
    mu_assert(channel_in != NULL, "Failed to create channel_in");

    channel_out = open_channel(CHANNEL_NAME);
    mu_assert(channel_out != NULL, "Failed to open channel_out");

    int send_result = channel_in->send_news(channel_in, 12, "So lonely!", VERY_HIGH_PRIORITY);
    mu_assert_int_eq(0, send_result);

    int receive_result = channel_out->receive_news(channel_out, &day, news, &priority);
    mu_assert_int_eq(0, receive_result);

    mu_assert_int_eq(12, day);
    mu_assert_string_eq("So lonely!", news);

    printf("\n-- passed\n");
}

MU_TEST(test_send_receive_with_priority) {
        int day;
        int priority;
        char news[MSG_LENGTH];
        Channel *channel_in;
        Channel *channel_out;

        printf("Testing send and receive with priority\n");

        channel_in = create_channel(CHANNEL_NAME);
        mu_assert(channel_in != NULL, "Failed to create channel_in");

        channel_out = open_channel(CHANNEL_NAME);
        mu_assert(channel_out != NULL, "Failed to open channel_out");

        int send_result1 = channel_in->send_news(channel_in, 12, "So lonely!", VERY_LOW_PRIORITY);
        mu_assert_int_eq(0, send_result1);

        int send_result2 = channel_in->send_news(channel_in, 13, "A song by Police...", HIGH_PRIORITY);
        mu_assert_int_eq(0, send_result2);

        int receive_result = channel_out->receive_news(channel_out, &day, news, &priority);
        mu_assert_int_eq(0, receive_result);

        mu_assert_int_eq(13, day);
        mu_assert_string_eq("A song by Police...", news);

        printf("\n-- passed\n");
}

MU_TEST_SUITE(test_suite) {
        MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
        MU_RUN_TEST(test_send_receive);
        MU_RUN_TEST(test_send_receive_with_priority);
}

int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
