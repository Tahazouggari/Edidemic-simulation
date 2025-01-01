#ifndef CHANNEL_H
#define CHANNEL_H

/**
 * @file channel.h
 *
 * @brief This file contains the functions and structures for the communication
 * channel mechanism.
 *
 * @author Alain Lebret
 * @version 1.0
 * @date 2023
 */

#if __linux__
#include <mqueue.h>
#elif __APPLE__
#include "macosx/mqueue.h"
#endif

#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define CHANNEL_NAME "/channel_with_city"
#define MSG_LENGTH     128

enum priority_e {
    MIN_PRIORITY = 1,
    VERY_LOW_PRIORITY = 2,
    LOW_PRIORITY = 3,
    MEDIUM_PRIORITY = 5,
    HIGH_PRIORITY = 6,
    VERY_HIGH_PRIORITY = 8,
    MAX_PRIORITY = 10
};

typedef enum priority_e Priority;

/**
 * @brief Structure representing a communication channel.
 *
 * The Channel structure encapsulates a communication channel used for sending
 * and receiving news.
 */
 typedef struct channel_s Channel;

struct channel_s {
    mqd_t mq; /**<! Message queue descriptor for the channel. */
    int (*send_news)(Channel *channel, int day, const char *news, int priority);
    int (*receive_news)(Channel *channel, int *day, char *news, int size, int *priority);
};

/**
 * @brief Creates a new communication channel with the specified name.
 *
 * This function creates a new communication channel represented by a Channel
 * structure. The channel is created as a message queue with the given name and
 * specified attributes.
 *
 * @param name The name of the message queue for the channel.
 * @return A pointer to the created Channel structure on success, or NULL on
 *         failure.
 */
 Channel *create_channel(const char *name);

/**
 * @brief Opens an existing communication channel with the specified name.
 *
 * This function opens an existing communication channel represented by a
 * Channel structure. The channel is identified by the given name and must have
 * been previously created using the `create_channel` function or an equivalent
 * method.
 *
 * @param name The name of the existing message queue for the channel.
 * @return A pointer to the opened Channel structure on success, or NULL on
 *         failure.
 */
 Channel *open_channel(const char *name);

/**
 * @brief Destroys an existing communication channel with the specified name.
 *
 * This function destroys an existing communication channel identified by the
 * given name. The channel is removed from the system, freeing associated
 * resources such as the message queue.
 *
 * @param name The name of the message queue for the channel to destroy.
 */
void destroy_channel(const char *name);

/**
 * @brief Sends a news message through the specified communication channel.
 *
 * This function sends a news message through the given communication channel.
 * The message is composed of the provided day, represented as an integer, and
 * the news content as a string. The message is formatted as "day;news" before
 * being sent to the message queue associated with the channel.
 *
 * @param channel  Pointer to the Channel structure representing the
 *                 communication channel.
 * @param day      The day value associated with the news message.
 * @param news     The news content to be sent.
 * @param priority The priority of the news message in the message queue.
 * @return 0 on success, or -1 if an error occurs.
 */
int channel_send_news(Channel *channel, int day, const char *news, int priority);

/**
 * @brief Receives a news item from the specified communication channel.
 *
 * This function receives a news item from the given communication channel. The
 * message is extracted from the channel's message queue and parsed to retrieve
 * the day value and news content.
 * The day value is stored in the provided integer pointer, and the news content
 * is copied into the provided buffer, ensuring it does not exceed MSG_LENGTH.
 * The message is expected to be in the format "day;news".
 *
 * @param channel  Pointer to the Channel structure representing the
 *                 communication channel.
 * @param day      Pointer to an integer variable to store the day value of the
 *                 news item.
 * @param news     Pointer to a buffer to store the news content.
 * @param size     The size of the news buffer.
 * @param priority The priority of the message.
 *
 * @return 0 on success, or -1 if an error occurs.
 */
int channel_receive_news(Channel *channel, int *day, char *news, int size, int *priority);

#endif
