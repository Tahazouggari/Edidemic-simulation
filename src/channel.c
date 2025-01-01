#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "channel.h"
#include "logger.h"

Channel *create_channel(const char *name) {
    struct mq_attr attr;

    /* Sets the attributes for the message queue */
    attr.mq_flags   = 0;
    attr.mq_maxmsg  = 10;         /* Maximum number of messages in the queue */
    attr.mq_msgsize = MSG_LENGTH; /* Maximum length of each message */
    attr.mq_curmsgs = 0;

    /* Create the message queue with the specified name and attributes */
    mqd_t mq = mq_open(name, O_CREAT | O_RDWR, 0666, &attr);
    if (mq == (mqd_t) -1) {
        log_error("Failed to create the channel: %s\n", strerror(errno));
        return NULL;
    }

    /* Allocate memory for the Channel structure */
    Channel *channel = (Channel *) malloc(sizeof(Channel));
    if (channel == NULL) {
        log_error("Failed to allocate memory for the channel.\n");
        mq_close(mq);
        return NULL;
    }

    /* Set the message queue descriptor */
    channel->mq = mq;
    channel->send_news = channel_send_news;
    channel->receive_news = channel_receive_news;

    return channel;
}

Channel *open_channel(const char *name) {
    /* Open the existing message queue */
    mqd_t mq = mq_open(name, O_RDWR);
    if (mq == (mqd_t) -1) {
        perror("mq_open");
        return NULL;
    }

    // Allocate memory for the Channel structure
    Channel *channel = malloc(sizeof(Channel));
    if (channel == NULL) {
        perror("malloc");
        mq_close(mq);
        return NULL;
    }

    /* Initialize the Channel structure */
    channel->mq = mq;
    channel->send_news = channel_send_news;
    channel->receive_news = channel_receive_news;

    return channel;
}

void destroy_channel(const char *name) {
    /* Destroy the message queue */
    if (mq_unlink(name) == -1) {
        if (errno == ENOENT) {
            log_error("Channel '%s' does not exist.\n", name);
        } else {
            log_error("Failed to destroy channel '%s': %s\n", name, strerror(errno));
        }
    } else {
        log_info("Channel '%s' destroyed successfully.\n", name);
    }
}

int channel_send_news(Channel *channel, int day, const char *news,
                      int priority) {
    if (channel == NULL) {
        log_error("Invalid channel.\n");
        return -1;
    }

    /* Construct the news message */
    char message[MSG_LENGTH];
    snprintf(message, sizeof(message), "%d;%s", day, news);

    /* Send the news message to the message queue with the given priority */
    if (mq_send(channel->mq, message, strlen(message) + 1, priority) == -1) {
        log_error("Failed to send news to the channel: %s\n", strerror(errno));
        return -1;
    }

    return 0;
}

int channel_receive_news(Channel *channel, int *day, char *news, int size, int *priority) {
    if (channel == NULL) {
        log_error("Invalid channel.\n");
        return -1;
    }

    /* Receive the news message from the message queue */
    char message[MSG_LENGTH];
    unsigned int msg_priority;
    ssize_t bytesReceived = mq_receive(channel->mq, message, size,
                                       &msg_priority);
    if (bytesReceived == -1) {
        log_error("Failed to receive news from the channel: %s\n", strerror(errno));
        return -1;
    }

    /* Parse the day and news content from the message */
    int scanned = sscanf(message, "%d;%[^\n]", day, news);

    if (scanned != 2) {
        log_error("Failed to parse news message.\n");
        return -1;
    }

    /* Copy the news content to the provided buffer */
    if (strlen(news) >= MSG_LENGTH) {
        log_error("News content exceeds the provided buffer size.\n");
        return -1;
    }
    int offset = (int)(strlen(message) - strlen(news));
    strncpy(news, message + offset, strlen(news));

    /* Set the received priority */
    *priority = msg_priority;

    return 0;
}
