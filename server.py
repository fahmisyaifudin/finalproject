'''
Created on 08-09-2012

@author: Maciej Wasilak
'''

import sys
import datetime

from twisted.internet import defer
from twisted.internet.protocol import DatagramProtocol
from twisted.internet import reactor
from twisted.python import log

import txthings.resource as resource
import txthings.coap as coap


class SensorResource (resource.CoAPResource):
    """
    Example Resource which supports GET, and PUT methods. It sends large
    responses, which trigger blockwise transfer (>64 bytes for normal
    settings).

    As before name render_<METHOD> is required by convention.
    """
    #isLeaf = True
	

    def __init__(self):
        resource.CoAPResource.__init__(self)
        self.visible = True

    def render_GET(self, request):
        payload=" Now I lay me down to sleep, I pray the Lord my soul to keep, If I shall die before I wake, I pray the Lord my soul to take."
        response = coap.Message(code=coap.CONTENT, payload=payload)
        return defer.succeed(response)

    def render_PUT(self, request):
        payload = "Data " + request.payload
        response = coap.Message(code=coap.CHANGED, payload=payload)
        f = open("datakelembapan.txt", "a+")
        f.write('"Kelembapan":"' + request.payload + '"\n')
        f.close()
        return defer.succeed(response)
	

# Resource tree creation
log.startLogging(sys.stdout)
root = resource.CoAPResource()

well_known = resource.CoAPResource()
root.putChild('.well-known', well_known)

sensor = SensorResource()
root.putChild('sensor', sensor)

endpoint = resource.Endpoint(root)
reactor.listenUDP(coap.COAP_PORT, coap.Coap(endpoint)) #, interface="::")
reactor.run()
