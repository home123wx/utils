#!/usr/bin/python
# -*- coding:utf-8 -*-

import random
from user_agents import agents

class UserAgentMiddleware(object):
    """ 换 User-Agent  """
    def process_request(self, request, spider):
        agent = random.choice(agents)
        request.headers["User-Agent"] = agent
