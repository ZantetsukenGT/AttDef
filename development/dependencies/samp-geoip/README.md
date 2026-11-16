# samp-geoip

[![sampctl](https://shields.southcla.ws/badge/sampctl-samp--geoip-2f2f2f.svg?style=for-the-badge)](https://github.com/Southclaws/samp-geoip)

A simple library that provides information from [IP-API](https://ip-api.com/) for
connected players.

Currently the results are not cached so you may encounter rate limits if your
server has many players connecting per minute. This may be addressed in future
by using Redis as a cache.

## Installation

Simply install to your project:

```bash
sampctl package install ZantetsukenGT/samp-geoip
```

Include in your code and begin using the library:

```pawn
#include <geoip>
```

## Usage

When a player connects, their details are automatically requested. Once the
response has arrived, the API can be used.

`bool:IsGeoDataReady(playerid)` Checks if the data is ready, requests should
only take milliseconds but this ensures your code doesn't attempt to request
data that isn't ready yet.

The rest of the API corresponds directly to the
[IP-API documentation](https://ip-api.com/docs/api:json):

*   `GetPlayerIPSuccess(playerid, &success)`
*   `GetPlayerIPMessage(playerid, output[], len = sizeof output)`
*   `GetPlayerCountryCode(playerid, output[], len = sizeof output)`
*   `GetPlayerCountryName(playerid, output[], len = sizeof output)`
*   `GetPlayerIPBlock(playerid, &block)`

There is also an event that is called when the data is available:

*   `OnGeoDataReady(playerid)`

## Testing

Just run as normal and connect to `localhost:7777`:

```bash
sampctl package run
```

If you connect locally, you'll see no useful data because you'll be sending the
loopback interface address, but a response will still appear:

```bash
text="requesting ip data" addr="8.8.8.8" playerid=0
text="received ip data" playerid=0 response_code=200
text="determined target player for ip data" playerid=0
text="extracted ip data for player" status="success" message="" country="United States" code="US" proxy=0 hosting=1
```

You can also type `/ip` in-game to see a message containing the data.
