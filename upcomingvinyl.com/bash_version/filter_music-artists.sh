#!/bin/bash
# Reads xml from STDIN and fuzzy-match to your list of artists to watch
#   xml can be sourced from https://upcomingvinyl.com/feed
#
# FUZZYMATCH variable adjusts fuzzy-sensitivity, between 0 and 1
# FAVART file is plaintext (can be utf8) list of artists, one per line
#
# 2025-03 - v1.0 by maniac
#


FAVART=~/filter_music-artists.txt
FUZZYMATCH=0.7

OIFS=$IFS
IFS=$'\n'
NEWLINE=$'\n'

I=0
X=0
FAVS=""
FAVS_FULL=""
FAVS_FULL2=""

rm -f /dev/shm/releases.txt
while read LINE ; do
  if [ "${LINE}" == "Upcoming Vinyl" ] ; 
    then continue
  fi
  echo "$LINE" >> /dev/shm/releases.txt
done

# Extract "artist - album" ("title" in xml)
xml_grep 'title' --text_only /dev/shm/releases.txt > /dev/shm/releases-artist-title.txt

# Extract "artist" ("title" in xml)
xml_grep 'title' --text_only /dev/shm/releases.txt | sed 's/-.*//' > /dev/shm/releases-artist.txt

# Read list of releases (about 100)
while read LINE ; do
    # Read fav artists and check titles against it (about 450)
    while read FILTER ; do
      I=$(fstrcmp "$LINE" "$FILTER")
        if (( $(echo "$I > $FUZZYMATCH" |bc -l) )) ; then
          FAVS="${FAVS}${NEWLINE}${LINE}"
        fi
    done <<< $(cat $FAVART)
done <<< $(cat /dev/shm/releases-artist.txt | grep -v 'Upcoming Vinyl')

FAVS=$(echo "$FAVS" | egrep -v '^$' | sed 's/\s*$//')

while read LINE ; do
    ADD=$(grep "$LINE" /dev/shm/releases-artist-title.txt)
    ADD2=$(grep -A10 "$LINE" /dev/shm/releases.txt | sed '/<\/item>/q' | egrep '<title>|<link>|<description>|<pubDate>' | sed 's/^\s*<[a-z|A-Z]\+>//')
    FAVS_FULL="${FAVS_FULL}${NEWLINE}${ADD}"
    FAVS_FULL2="${FAVS_FULL2}${NEWLINE}${ADD2}"
done <<< $(echo "${FAVS}")

FAVS_FINAL=$(echo "${FAVS_FULL}" | egrep -v '^$')
FAVS_FINAL2=$(echo "${FAVS_FULL2}" | egrep -v '^$')

if [ "x${FAVS_FINAL}" == "x" ] ; then	# no favs matched in releases
  exit 0
fi

echo "New releases found!"
echo "-------------------"
echo "${FAVS_FINAL}"
echo "----- Details: ----"
echo "${FAVS_FINAL2}"

