#!/usr/bin/python
# -*- coding:utf-8 -*-

import scrapy

pages = 4
num   = 25

class Top100(scrapy.Spider):
    name = "top100"
    allowed_domains = ["douban.com"]
    

    #page = 0
    #num  = 25

    start_urls = []

    def __init__(self):
        for page in range(pages):
            url  = u"https://movie.douban.com/top250?start=" + str(page * num) + "&filter="
            print(url)
            self.start_urls.append(url)

    def parse(self, response):
        pass
        for a in response.xpath('//div[@class="hd"]'):
            title = a.xpath('a/span[@class="title"]/text()')[0].extract()
            print(title)
            print("-"*40)
