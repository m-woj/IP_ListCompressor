import ipaddress, random

MAX = 255 * 255 * 255 * 255

with open("rfeed10M", "w") as fd:
    for i in range(0, 10_000_000):
        fd.write(str(ipaddress.IPv4Address(random.randint(0, MAX))) + "\n")
