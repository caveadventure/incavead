#!/bin/sh
cd /opt/games/incavead
./highscore > /srv/http/dungeon.name/hs.json
./victory > /srv/http/dungeon.name/rs.json
