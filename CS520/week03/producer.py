 consumer.py  producer.py                                                                                                                        X
#!/usr/bin/env python

import sys
import json
import random
from time import sleep
from random import choice
from argparse import ArgumentParser, FileType
from configparser import ConfigParser
from confluent_kafka import Producer

if __name__ == '__main__':
    # Random Produer ID
    prod_ID = random.randint(0, 99)

    # Parse the command line.
    parser = ArgumentParser()
    parser.add_argument('config_file', type=FileType('r'))
    args = parser.parse_args()

    # Parse the configuration.
    # See https://github.com/edenhill/librdkafka/blob/master/CONFIGURATION.md
    
    config_parser = ConfigParser()
    config_parser.read_file(args.config_file)
    config = dict(config_parser['default'])

    # Create Producer instance
    producer = Producer(config)

    # Optional per-message delivery callback (triggered by poll() or flush())
    # when a message has been successfully delivered or permanently
    # failed delivery (after retries).
    def delivery_callback(err, msg):
        if err:
            print('ERROR: Message failed delivery: {}'.format(err))
        else:
            print("{ID} Produced event to topic {topic}: key = {key:12} value = {value:12}".format(
                ID=prod_ID, topic=msg.topic(), key=msg.key().decode('utf-8'), value=msg.value().decode('utf-8')))

    topic = "purchases"

    # Upload the json
    #with open('/home/wmm2/kafkaconfluence/bcsample.json', 'a') as f:
        #data = json.load(f)

    f = open('/home/wmm2/kafkaconfluence/bcsample.json')
    data = json.load(f)

    for d in data:
        producer.poll(10)
        producer.flush()
        sleep(0.25)
        i_d = d["EVENT_NO_TRIP"]
        # appending the producer id
        p = {"producer_id":prod_ID}
        d.update(p)
        # convert json to str
                                                                                                                            52,19         59%
